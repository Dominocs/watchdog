//*/99 ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//


#include<opencv2\opencv.hpp>
#include"remap.h"
using namespace std;
using namespace cv;




int main()
{
	namedWindow("origin", WINDOW_AUTOSIZE);
	namedWindow("right", WINDOW_AUTOSIZE);
	namedWindow("left", WINDOW_AUTOSIZE);


	//VideoCapture cap(1);
	//cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	//cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	//cap >> origin;



	Mat origin(480, 1280,CV_8UC3);
	Mat left_origin = imread("C:/Users/Administrator/Desktop/left/21_left.jpg");
	Mat right_origin = imread("C:/Users/Administrator/Desktop/right/21_right.jpg");

	cout << left_origin.type();
	imshow("left", left_origin);


	left_origin.copyTo(origin(Rect(0, 0, 640, 480)));

	right_origin.copyTo(origin(Rect(640, 0, 640, 480)));
	img_remap img(origin);
	imshow("cc", origin);


	img.myremap();
	imshow("origin", img.output);
	cvWaitKey(0);


	//	if (!cap.isOpened())
	//		return 0;
	//while (1)
	{
		//cap >> origin;
		//for (int i = 0; i < 480; i += 30)
		//line(origin, Point(0, i), Point(1279, i), Scalar(0, 0, 255));

		//undistort(left_origin, Left, left_index, distCoeffs_left);
		//undistort(right_origin, Right, right_index, distCoeffs_right);
		//sift->detectAndCompute(Left,  noArray(),keypoint_left,temp);
		//drawKeypoints(Left, keypoint_left, Left, Scalar(0, 255, 255));


	}
	return 0;
}

