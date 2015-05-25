#include <opencv/cv.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc,char *argv[])
{

	Mat left = imread("C:/Users/davide/Desktop/homework_embedded2/Tsukuba_L.png",0);
	Mat right = imread("C:/Users/davide/Desktop/homework_embedded2/Tsukuba_R.png",0);

	imshow("left",left);
	waitKey(0);

	Mat output(left.rows,left.cols,CV_8UC1);

	uchar soglia = 12;
	uchar numeroRange = 16;

	for(int i=0;i<left.rows;i++)
	{
		
		for(int j=0;j<left.cols;j++)
		{
			uchar dist= 255;
			int iMin = -1;
			for(int k=0;k<=numeroRange-1;k++)
			{
				
				if(j - k < 0)
					continue;
				uchar lP = left.at<uchar>(i,j);
				uchar rP = right.at<uchar>(i,j-k);
				
				uchar t = abs(lP-rP);
				t = (t > soglia) ?  soglia : t ;

				if(t < dist)
				{
					dist = t;
					iMin = k;
				}

			}

			output.at<uchar>(i,j) = (uchar) ( 255* ( ((float)iMin) /numeroRange) );
			
		}
	}

	//GaussianBlur(output,output,Size(3,3),3);
	imshow("output",output);
	waitKey(0);

}

