#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

//int main (int argc, char** argv) 
//{
//
//	Mat frame;
//	Mat gray ;
//	Mat gray_dilate1 ;
//	Mat gray_dilate2 ;
//	Mat gray_dilate3 ;
//	Mat background ,background_gray ,foreground,foreground_BW;
//	Mat mid_filer;   //image after median filter
//	background = imread("C:/Users/LYN/Desktop/test/2087.tif");
//	frame = imread("C:/Users/LYN/Desktop/test/2088.tif");
//	Mat frame_0,foreground_BW_morphologyEx;
//	//---------------------------------------------------------------------
//	//Get video's width, height, fps and totoal frames
//	int frameH    = background.rows; //get frames height
//	int frameW    =  background.cols;  //get frames width
//
//
//		imshow("frame_resize",frame);
//		cvtColor( frame,gray, CV_RGB2GRAY );
//		//-----------------------------------------------------------------------------------
//		//Choosing the first read frame as background
//		imshow("background",background);
//		cvtColor( background,background_gray, CV_RGB2GRAY );
//		//------------------------------------------------------------------------------------
//		absdiff(gray,background_gray,foreground);//use frame difference to get movement
//		imshow("foreground",foreground);
//		Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
//
//
//		//threshold( foreground, foreground_BW, 20, 255 , 0 );//binarize the image
//		threshold(foreground, foreground_BW, 0, 255 ,CV_THRESH_BINARY | CV_THRESH_OTSU) ;  //Otsu method
//		imshow("foreground_BW",foreground_BW);
//		Mat element1 = getStructuringElement(MORPH_RECT, Size(3, 3)); //rectangular convolution
//		morphologyEx(foreground_BW, foreground_BW_morphologyEx, MORPH_OPEN, element1);
//		imshow("foreground_BW_morphologyEx",foreground_BW_morphologyEx);
//		medianBlur(foreground_BW,mid_filer,3);     //Median filter
//		imshow("mid_filer",mid_filer);
//		dilate(mid_filer,gray_dilate1,element);
//		imshow("gray_dilate1",gray_dilate1);
//		dilate(gray_dilate1,gray_dilate2,element);
//		imshow("gray_dilate2",gray_dilate2);
//		dilate(gray_dilate2,gray_dilate3,element);
//		imshow("gray_dilate3",gray_dilate3);
//
//		frame_0=gray.clone();
//		char c = waitKey(0);
//		return 0;
//
//}


double getDistance (Point2f pointO,Point2f pointA )    
{    
	double distance;    
	distance = powf((pointO.x - pointA.x),2) + powf((pointO.y - pointA.y),2);    
	distance = sqrtf(distance);    

	return distance;    
}  

Mat imageDiff(Mat img1,Mat img2,int count,int &flag_match)
{
	Mat diff;
	absdiff(img1,img2,diff);//ps: watch out difference is zero
	/*
	imshow("img1",img1);
	imshow("img2",img2);
	imshow("diff",diff);
	*/
	Mat gray;
	cvtColor(diff,gray,COLOR_BGR2GRAY);//Converting to gray-scale image
	//adaptiveThreshold(gray,gray,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,3);
	//threshold(gray,gray,5,255,THRESH_BINARY);
	//threshold(gray, gray, 0, 255 ,CV_THRESH_BINARY | CV_THRESH_OTSU) ; 
	threshold( gray, gray, 20, 255 , 0 );
	//imshow("threshold",gray);

	//Morphology
	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
	morphologyEx(gray,gray,MORPH_OPEN,element);//Open operation
	//imshow("contrast1",gray);
	//waitKey(0);
	medianBlur(gray,gray,9);//Median filter
	//imshow("contrast2",gray);
	//waitKey(0);
	erode(gray,gray,element);
	//imshow("contrast3",gray);
	
    //imshow("dst",gray);

	vector<vector<Point>> contours;  
	vector<Vec4i> hierarchy;  
	findContours(gray,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE,Point());  

	Mat imageContours=Mat::zeros(gray.size(),CV_8UC1); //Least rectanglular-empty contour 

	vector<vector<Point>>::iterator it;
	it = contours.begin();
	for(it;it!=contours.end();)  
	{         
		
		//drawContours(imageContours,contours,i,Scalar(255),1,8,hierarchy);  
 
		
		RotatedRect rect=minAreaRect(*it);  
		Point2f P[4];  
		rect.points(P);  
		//for(int j=0;j<=3;j++)  
		//{  
		//	line(imageContours,P[j],P[(j+1)%4],Scalar(255),2);  
		//}  
		int recH = getDistance(P[0],P[1]);
		int recW = getDistance(P[1],P[2]);
		if (recW>recH)
		{
			int temp = recH;
			recH = recW;
			recW = temp;
		}

		int recArea = recH*recW; 
		float ratio = float(recH)/float(recW);
		bool loc = false;
		
		if (P[0].x<gray.cols/2&&P[1].x<gray.cols/2&&P[2].x<gray.cols/2&&P[3].x<gray.cols/2&&
			P[0].y>gray.rows/2&&P[1].y>gray.rows/2&&P[2].y>gray.rows/2&&P[3].y>gray.rows/2&&
			P[0].x>0.1*gray.cols&&P[1].x>0.1*gray.cols&&P[2].x>0.1*gray.cols&&P[3].x>0.1*gray.cols)
		{
			loc = true;
		}
		if (recArea>400&&ratio<5&&loc)
		{
			it++;
		}
		else
		{
			it=contours.erase(it);
		}
		
	}  
	//imshow("MinAreaRect",imageContours);    

	Mat imageContours_=Mat::zeros(gray.size(),CV_8UC1); 

	for(int i = 0;i<contours.size();i++)  
	{         
		
		drawContours(imageContours_, contours, i, Scalar(255), CV_FILLED);
	} 
   	//imshow("imageContours_",imageContours_);    
  

	Mat resImage=Mat::zeros(gray.size(),CV_8UC3);
	img2.copyTo(resImage,imageContours_);  
	//cv::imshow("resImage", resImage); 

	char picname[128];
	sprintf_s(picname,"D:/machine_learning/image_video_processing/worldcup1_match/%d.jpg",count);
	if (contours.size()>0)
	{
		imwrite(picname,resImage);
		flag_match = 1;
	}
	waitKey(1); 
	return resImage;

}
Mat findColor(Mat img)
{
	Mat hsv;
	cvtColor(img,hsv,CV_BGR2HSV);  
	for (int i = 0; i < hsv.rows; i++)
	{
		uchar* hsv_pixel = hsv.ptr(i);
		uchar* rgb_pixel = img.ptr(i);
		for (int j = 0; j < hsv.cols; j++)
		{
			if ((hsv_pixel[j*3]<11||hsv_pixel[j*3]>34)||(rgb_pixel[j*3+1]<43)||(rgb_pixel[j*3+2]<46)) 
			{
				rgb_pixel[j*3] = 0;
				rgb_pixel[j*3+1] = 0;
				rgb_pixel[j*3+2] = 0;

			}
		}
	}
	return img;
}
void imageColor(Mat img1,int count)
{
	
	imshow("img1",img1);

	Mat gray;
	cvtColor(img1,gray,COLOR_BGR2GRAY);
	//adaptiveThreshold(gray,gray,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,3);
	//threshold(gray,gray,5,255,THRESH_BINARY);
	//threshold(gray, gray, 0, 255 ,CV_THRESH_BINARY | CV_THRESH_OTSU) ; 
	threshold( gray, gray, 20, 255 , 0 );
	
	imshow("threshold",gray);


	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));//Structure element
	morphologyEx(gray,gray,MORPH_OPEN,element);//Open operation
	medianBlur(gray,gray,9);//Median filter
	erode(gray,gray,element);
	//imshow("dst",gray);

	vector<vector<Point>> contours;  
	vector<Vec4i> hierarchy;  
	findContours(gray,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE,Point());  

	Mat imageContours=Mat::zeros(gray.size(),CV_8UC1); //Least rectanglular-empty contour 

	vector<vector<Point>>::iterator it;
	it = contours.begin();
	for(it;it!=contours.end();)  
	{         
	
		//drawContours(imageContours,contours,i,Scalar(255),1,8,hierarchy);  

		 
		RotatedRect rect=minAreaRect(*it);  
		Point2f P[4];  
		rect.points(P);  
		//for(int j=0;j<=3;j++)  
		//{  
		//	line(imageContours,P[j],P[(j+1)%4],Scalar(255),2);  
		//}  
		int recH = getDistance(P[0],P[1]);
		int recW = getDistance(P[1],P[2]);
		if (recW>recH)
		{
			int temp = recH;
			recH = recW;
			recW = temp;
		}

		int recArea = recH*recW; 
		float ratio = float(recH)/float(recW);
		bool loc = true;
		if (P[0].x<gray.cols/2&&P[1].x<gray.cols/2&&P[2].x<gray.cols/2&&P[3].x<gray.cols/2&&
			P[0].y>gray.rows/2&&P[1].y>gray.rows/2&&P[2].y>gray.rows/2&&P[3].y>gray.rows/2)
		{
			loc = false;
		}
		if (recArea<400||ratio>5||loc)
		{
			it=contours.erase(it);
		}
		else
		{
			it++;
		}
	}  
	//imshow("MinAreaRect",imageContours);    

	Mat imageContours_=Mat::zeros(gray.size(),CV_8UC1); //最小外接矩形画布  

	for(int i = 0;i<contours.size();i++)  
	{         
	
		drawContours(imageContours_, contours, i, Scalar(255), CV_FILLED);
	} 
	
	imshow("imageContours_",imageContours_);    


	Mat resImage=Mat::zeros(gray.size(),CV_8UC3);
	img1.copyTo(resImage,imageContours_);  
	
	cv::imshow("resImage", resImage); 

	char picname[128];
	sprintf_s(picname,"F:/output2/%d.jpg",count);
	if (contours.size()>0)
	{
		//imwrite(picname,resImage);
	}
	waitKey(1); 
}


Mat templateMatch_(Mat img, Mat templ)
{
	Mat result;

	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	result.create(result_cols, result_rows, CV_32FC1);

	matchTemplate(img, templ, result, CV_TM_SQDIFF_NORMED);//use normal squared difference to match with template
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal = -1;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());


	cout << "匹配度：" << minVal << endl;

	matchLoc = minLoc;
	if (minVal < 0.001)
	{
		rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 0), 2, 8, 0);
	}

	imshow("img", img);
	waitKey(1);

	return img;
}
int templateMatch(Mat& image_source_, Mat image_template)
{  
 
	cv::Mat image_source ;  
	cv::cvtColor(image_source_, image_source, CV_BGR2GRAY);
	//cv::cvtColor(image_template_, image_template, CV_GRAY2BGR);

	cv::Mat image_matched;  

  
	cv::matchTemplate(image_source, image_template, image_matched, cv::TM_CCOEFF_NORMED);  

	double minVal, maxVal;  
	cv::Point minLoc, maxLoc;  
	//Determine designated location
	cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);  
	//cout << "matching rate：" << minVal << endl;

	if(abs(minVal)<0.0001)
	{
		cv::Mat image_color;  
		//cv::cvtColor(image_source, image_color, CV_GRAY2BGR);  
		cv::circle(image_source_,  
			cv::Point(maxLoc.x + image_template.cols/2, maxLoc.y + image_template.rows/2),  
			20,   
			cv::Scalar(0, 0, 255),   
			2,   
			8,   
			0);  

		//cv::imshow("source image", image_source);  
		//cv::imshow("match result", image_matched);  
		cv::imshow("target", image_source_);  
		cv::waitKey(1);
		return 1;
	}
	return 0;

	  
}  
int main (int argc, char** argv)   
{  
	VideoCapture capture("D:/machine_learning/image_video_processing/advertise1.mp4");  
	if (!capture.isOpened())  
	{  
		cout<<"No camera or video input!\n"<<endl;  
		return -1;  
	} 
	Mat frame_back,frame_fore,frame,frame_,diffRes,tempRes;
//	tempRes = imread("D:/Users/Shengjia/Desktop/template/template.jpg",IMREAD_GRAYSCALE);

	int i = 0;
	int flag_diff,flag_match;
	while(1)  
	{ 
		capture>>frame;  
		flag_diff = 0;
		flag_match = 0;
		//cout<<i<<endl;
		resize(frame, frame_, Size(frame.cols/4,frame.rows/4), 0, 0); 
		frame_ = findColor(frame_);
		if (i == 0)
		{
			frame_fore = frame_.clone();
			i++;
			continue;
		}
		i++;
		frame_back = frame_fore.clone();
		frame_fore = frame_.clone();
		diffRes = imageDiff(frame_back,frame_fore,i,flag_diff);
		if (flag_diff == 1)
		{
			//flag_match = templateMatch(diffRes,tempRes);
			if (flag_match == 1)
			{
				cout<<"！！！Matched： "<<i<<endl;
			}
		}
		//imageColor(frame_,i);

	}
}