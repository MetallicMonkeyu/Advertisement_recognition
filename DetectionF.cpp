#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <array>
#include <string>

using namespace std;
using namespace cv;
bool matched_color(Mat bgr_img,String color);
int num_color(String color);
float Rgb2Hsv(float R, float G, float B, float& H, float& S, float&V);
int num_color(String color);
int return_frame(Mat frm);
bool pick_five(bool cond1, bool cond2, bool cond3, bool cond4, bool cond5, bool cond6);
struct frame
{
	int frame_NO;
	int score;
	int which_frame;
	
};
//Set five detection frames
int getFirstROI(Mat image)
	{
		Rect rect_1 = Rect(570,770,10,10);
		Rect rect_2 = Rect(600,800,10,10);
		Rect rect_3 = Rect(660,850,10,10);
		Rect rect_4 = Rect(710,860,10,10);
		Rect rect_5 = Rect(390,840,10,10);
		Rect rect_6 = Rect(450,860,10,10);
		Mat img=image.clone();
		int flag = 0;
		Mat frame1, frame2, frame3, frame4, frame5, frame6;

		frame1 =img(Rect(rect_1.x, rect_1.y, rect_1.width, rect_1.height));
		frame2 =img(Rect(rect_2.x, rect_2.y, rect_2.width, rect_2.height));
		frame3 =img(Rect(rect_3.x, rect_3.y, rect_3.width, rect_3.height));
		frame4 =img(Rect(rect_4.x, rect_4.y, rect_4.width, rect_4.height));
		frame5 =img(Rect(rect_5.x, rect_5.y, rect_5.width, rect_5.height));
		frame6 =img(Rect(rect_6.x, rect_6.y, rect_6.width, rect_6.height));

		if (pick_five((matched_color(frame1,"yellow") == 1),(matched_color(frame2,"yellow") == 1),(matched_color(frame3,"yellow") == 1),(matched_color(frame4,"yellow") == 1),(matched_color(frame5,"yellow") == 1),(matched_color(frame6,"yellow") == 1))){
			flag = 1;
		}

		return flag;
  
	}
	int getFourthROI(Mat image)
	{
		Rect rect_1 = Rect(460,560,10,10); 
		Rect rect_2 = Rect(360,660,10,10);
		Rect rect_3 = Rect(1240,510,10,10);
		Rect rect_4 = Rect(340,810,10,10);
		Rect rect_5 = Rect(1670,310,10,10);
		Rect rect_6 = Rect(1610,350,10,10);
		Mat img=image.clone();
		int flag = 0;
		Mat frame1, frame2, frame3, frame4, frame5, frame6;

		frame1 =img(Rect(rect_1.x, rect_1.y, rect_1.width, rect_1.height));
		frame2 =img(Rect(rect_2.x, rect_2.y, rect_2.width, rect_2.height));
		frame3 =img(Rect(rect_3.x, rect_3.y, rect_3.width, rect_3.height));
		frame4 =img(Rect(rect_4.x, rect_4.y, rect_4.width, rect_4.height));
		frame5 =img(Rect(rect_5.x, rect_5.y, rect_5.width, rect_5.height));
		frame6 =img(Rect(rect_6.x, rect_6.y, rect_6.width, rect_6.height));

		if (pick_five((matched_color(frame1,"yellow")),(matched_color(frame2,"yellow")),(matched_color(frame3,"red")),(matched_color(frame4,"yellow")),(matched_color(frame5,"green")),(matched_color(frame6,"green")))){
			flag = 4;
		}
		return flag;

	}
	int getEighthROI(Mat image)
	{
		Rect rect_1 = Rect(480,480,10,10);
		Rect rect_2 = Rect(1470,580,10,10);
		Rect rect_3 = Rect(1160,680,10,10);
		Rect rect_4 = Rect(1280,430,10,10);
		Rect rect_5 = Rect(1350,150,10,10);
		Rect rect_6 = Rect(420,410,10,10);
		Mat img=image.clone();
		int flag = 0;
		Mat frame1, frame2, frame3, frame4, frame5, frame6;

		frame1 =img(Rect(rect_1.x, rect_1.y, rect_1.width, rect_1.height));
		frame2 =img(Rect(rect_2.x, rect_2.y, rect_2.width, rect_2.height));
		frame3 =img(Rect(rect_3.x, rect_3.y, rect_3.width, rect_3.height));
		frame4 =img(Rect(rect_4.x, rect_4.y, rect_4.width, rect_4.height));
		frame5 =img(Rect(rect_5.x, rect_5.y, rect_5.width, rect_5.height));
		frame6 =img(Rect(rect_6.x, rect_6.y, rect_6.width, rect_6.height));

		if (pick_five((matched_color(frame1,"yellow")),(matched_color(frame2,"yellow")),(matched_color(frame3,"red")),(matched_color(frame4,"red")),(matched_color(frame5,"green")),(matched_color(frame6,"green")))){
			flag = 8;
		}

		return flag;
    
	}
	int getSixteenthROI(Mat image)
	{
		Rect rect_1 = Rect(90,540,10,10);
		Rect rect_2 = Rect(1430,750,10,10);
		Rect rect_3 = Rect(540,570,10,10);
		Rect rect_4 = Rect(930,590,10,10);
		Rect rect_5 = Rect(370,240,10,10);
		Rect rect_6 = Rect(830,260,10,10);
		Mat img=image.clone();
		int flag = 0;
		Mat frame1, frame2, frame3, frame4, frame5, frame6;

		frame1 =img(Rect(rect_1.x, rect_1.y, rect_1.width, rect_1.height));
		frame2 =img(Rect(rect_2.x, rect_2.y, rect_2.width, rect_2.height));
		frame3 =img(Rect(rect_3.x, rect_3.y, rect_3.width, rect_3.height));
		frame4 =img(Rect(rect_4.x, rect_4.y, rect_4.width, rect_4.height));
		frame5 =img(Rect(rect_5.x, rect_5.y, rect_5.width, rect_5.height));
		frame6 =img(Rect(rect_6.x, rect_6.y, rect_6.width, rect_6.height));
	
		if (pick_five((matched_color(frame1,"yellow")),(matched_color(frame2,"yellow")),(matched_color(frame3,"red")),(matched_color(frame4,"red")),(matched_color(frame5,"green")),(matched_color(frame6,"green")))){
			flag = 16;
		}



		return flag;
    
	}
	int getLastROI(Mat image)
	{
		Rect rect_1 = Rect(360,610,10,10);
		Rect rect_2 = Rect(1270,880,10,10);
		Rect rect_3 = Rect(560,400,10,10);
		Rect rect_4 = Rect(1600,620,10,10);
		Rect rect_5 = Rect(1650,140,10,10);
		Rect rect_6 = Rect(1700,430,10,10);
		Mat img=image.clone();
		int flag = 0;
		Mat frame1, frame2, frame3, frame4, frame5, frame6;

		frame1 =img(Rect(rect_1.x, rect_1.y, rect_1.width, rect_1.height));
		frame2 =img(Rect(rect_2.x, rect_2.y, rect_2.width, rect_2.height));
		frame3 =img(Rect(rect_3.x, rect_3.y, rect_3.width, rect_3.height));
		frame4 =img(Rect(rect_4.x, rect_4.y, rect_4.width, rect_4.height));
		frame5 =img(Rect(rect_5.x, rect_5.y, rect_5.width, rect_5.height));
		frame6 =img(Rect(rect_6.x, rect_6.y, rect_6.width, rect_6.height));


		if (pick_five((matched_color(frame1,"red")),(matched_color(frame2,"red")),(matched_color(frame3,"red")),(matched_color(frame4,"red")),(matched_color(frame5,"red")),(matched_color(frame6,"red")))){
			flag = 20;
		}
	
		return flag;
    
	}
	int num_color(String color){
		int x = 0;
		if (color == "yellow"){
			x = 1;
		}
		else if (color == "green"){
			x = 2;
		}
		else if (color == "red"){
			x = 3;
		}
		return x;
	}

	float Rgb2Hsv(float R, float G, float B, float& H, float& S, float&V)  
	{  
			// r,g,b values are from 0 to 1  
		// h = [0,360], s = [0,1], v = [0,1]  
		// if s == 0, then h = -1 (undefined)  
		float min, max, delta,tmp;  
		tmp = R>G?G:R;  
		min = tmp>B?B:tmp;  
		tmp = R>G?R:G;  
		max = tmp>B?tmp:B;  
		V = max; // v  
		delta = max - min;  
		if( max != 0 )  
			S = delta / max; // s  
		else  
		{  
			// r = g = b = 0 // s = 0, v is undefined  
			S = 0;  
			H = 0;  
		}  
		if (delta == 0){  
			H = 0;   
		}  
		else if(R == max){  
			if (G >= B)  
				H = (G - B) / delta; // between yellow & magenta  
			else  
				H = (G - B) / delta + 6.0;  
		}  
		else if( G == max )  
			H = 2.0 + ( B - R ) / delta; // between cyan & yellow  
		else if (B == max)  
			H = 4.0 + ( R - G ) / delta; // between magenta & cyan  
		H *= 60.0; // degrees  
		return H;
	}  

	bool matched_color(Mat bgr_img,String color){

		int flag = false;
		int count = 0;
		int ret = 0;
		float h=0,s=0,v=0;
		ret = num_color(color);
		switch(ret){
			case 1:
				for (size_t i = 0; i < bgr_img.rows; i++) {
					uchar* current_mask_pixel = bgr_img.ptr(i);

					for (size_t j = 0; j < bgr_img.cols; j++){
	
						Rgb2Hsv(float(current_mask_pixel[j * 3+2]), float(current_mask_pixel[j * 3 + 1]), float(current_mask_pixel[j * 3]), h, s, v);
						if (30<h&&h<60){
								count+=1;
						}
					}
	
				}
				if (count>=90){
					flag = true;
				}
				break;
			case 2:
				for (size_t i = 0; i < bgr_img.rows; i++) {
					uchar* current_mask_pixel = bgr_img.ptr(i);

					for (size_t j = 0; j < bgr_img.cols; j++){
					
						h = Rgb2Hsv(float(current_mask_pixel[j * 3+2]), float(current_mask_pixel[j * 3 + 1]), float(current_mask_pixel[j * 3]), h, s, v);
						if (75<h&&h<115){
								count+=1;
						
						}
					}
	
				}
				if (count>=90){
					flag = true;
				}
				break;
			case 3:
				for (size_t i = 0; i < bgr_img.rows; i++) {
					uchar* current_mask_pixel = bgr_img.ptr(i);

					for (size_t j = 0; j < bgr_img.cols; j++){
						h = Rgb2Hsv(float(current_mask_pixel[j * 3+2]), float(current_mask_pixel[j * 3 + 1]), float(current_mask_pixel[j * 3]), h, s, v);
						if ((0<h&&35>h)||(150<h&&180>h)||(h==0)){
								count+=1;
						}
					}
	
				}
				if (count>=90){
					flag = true;
				}
				break;
		}
		return flag;
	}

	bool pick_five(bool cond1, bool cond2, bool cond3, bool cond4, bool cond5, bool cond6){
		int count = 0;
		bool flag = false;
	
		if (cond1){
			count ++;
		}
		if (cond2){
			count ++;
		}
		if (cond3){
			count ++;
		}
		if (cond4){
			count ++;
		}
		if (cond5){
			count ++;
		}
		if (cond6){
			count ++;
		}
		if (count > 5 || count ==5){
			flag = true;
		}
		return flag;
	}
//set score for each frame to determine which frame 
	int set_score(bool cond1, bool cond2, bool cond3, bool cond4, bool cond5){
		int count = 0;
	
		if (cond1){
			count ++;
		}
		if (cond2){
			count ++;
		}
		if (cond3){
			count ++;
		}
		if (cond4){
			count ++;
		}
		if (cond5){
			count ++;
		}
	
		return count;
	}


	int set_whichframe(Mat frame){
		int frame_num = 0;
		if (getFirstROI(frame)==1){
			frame_num = 1;
		}
		if (getFourthROI(frame)==4){
			frame_num = 4;
		}
		if (getEighthROI(frame)==8){
			frame_num = 8;
		}
		if (getSixteenthROI(frame)==16){
			frame_num = 16;
		}
		if (getLastROI(frame)==20){
			frame_num = 20;
		}
		return frame_num;
	}



int main(int argc, char *argv[]){
	
	Mat frame_img,frame_;
	vector <int> v_interest;
	vector <frame> v;
	vector <frame> decide_frame;
	VideoCapture capture("D:/machine_learning/image_video_processing/worldcup1.mp4");  
	if (!capture.isOpened())  
	{  
		cout<<"No camera or video input!\n"<<endl;  
		return -1;  
	} 

	int total_num =  capture.get(CV_CAP_PROP_FRAME_COUNT);

	String defaul = "default";
	ofstream outf; //recording
	int max_index=0;
	//vector<int>::iterator it;
	outf.open("D:/machine_learning/image_video_processing/test.txt");
	for(int frameNum = 0; frameNum < total_num;frameNum++)

	{
		capture >> frame_img;
		frame f;
		int max=0;
		f.frame_NO=(frameNum);
		f.which_frame = set_whichframe(frame_img);
		cout << frameNum << endl;
		v.push_back(f);
		//in a series of 25 frames
		if (v.size()==25){
			max = 3;
			//cout<<"v[0].which_frame: "<<v[0].which_frame<<" "<<"v[3].which_frame: "<<v[3].which_frame<<" "<<"v[7].which_frame: "<<v[7].which_frame<<" "<<"v[15].which_frame: "<<v[15].which_frame<<" "<<"v[18].which_frame: "<<v[18].which_frame<<" "<<" "<< "v[19].which_frame: "<<v[19].which_frame<<" "<<endl;
			for (int j = 0; j<v.size();j++){
				decide_frame.push_back(v[j]);
				if (decide_frame.size()==20){
					v[j].score = set_score((decide_frame[0].which_frame==1||decide_frame[1].which_frame==1),(decide_frame[3].which_frame == 4),(decide_frame[7].which_frame == 8),(decide_frame[15].which_frame == 16),((decide_frame[19].which_frame == 20)||(decide_frame[18].which_frame == 20)));
					if (v[j].score > max){
						max = v[j].score;
						max_index = v[j].frame_NO;
					}
					decide_frame.erase(decide_frame.begin());
				}
				
			}
				if (max_index!=0&&v_interest.size()==0){
						v_interest.push_back(max_index);
						outf<<max_index<<endl;
					}
				else if (max_index!=0&& (max_index>v_interest[v_interest.size()-1]+5)){
						v_interest.push_back(max_index);
						outf<<max_index<<endl;
					}
			
			decide_frame.clear();
			v.erase(v.begin());
		}
  	}

	outf.close();
    return 0;
}

