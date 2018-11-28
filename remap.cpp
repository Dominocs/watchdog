#include<opencv2\opencv.hpp>
#include"remap.h"
#include<iostream>
using namespace std;
using namespace cv;
img_remap::img_remap(Mat origin)
{
	//原始图像roi区
	img_left_origin = origin(Rect(0, 0, 640, 480));
	img_right_origin = origin(Rect(640, 0, 640, 480));
	//左摄像头矩阵
	left_index.at<double>(0, 0) = 4.435730960577183e+02;
	left_index.at<double>(0, 1) = 0;
	left_index.at<double>(0, 2) = 3.117550904495228e+02;
	left_index.at<double>(1, 1) = 4.447657745398987e+02;
	left_index.at<double>(1, 2) = 2.434727286125830e+02;

	//左摄像头畸变系数
	distCoeffs_left.at<double>(0, 0) = 0.016320051270838;
	distCoeffs_left.at<double>(1, 0) = -0.066550199545216;
	distCoeffs_left.at<double>(2, 0) = 0;
	distCoeffs_left.at<double>(3, 0) = 0;

	//右摄像头矩阵
	right_index.at<double>(0, 0) = 4.430141598572413e+02;
	right_index.at<double>(0, 1) = 0;
	right_index.at<double>(0, 2) = 3.005537911009538e+02;
	right_index.at<double>(1, 1) = 4.439392421667503e+02;
	right_index.at<double>(1, 2) = 2.501508704597152e+02;

	//右摄像头畸变系数
	distCoeffs_right.at<double>(0, 0) = 0.011620793789258;
	distCoeffs_right.at<double>(1, 0) = -0.052882989396995;
	distCoeffs_right.at<double>(2, 0) = 0;
	distCoeffs_right.at<double>(3, 0) = 0;
	//T矩阵
	T.at<double>(0, 0) = -78.995876383877050;
	T.at<double>(0, 1) = 0.915102093854816;
	T.at<double>(0, 2) = -0.997874266019444;
	//R矩阵
	R.at<double>(0, 0) = 0.999931638008728;
	R.at<double>(0, 1) = 0.010643142233902;
	R.at<double>(0, 2) = -0.004841779897082;
	R.at<double>(1, 0) = -0.010664029076178;
	R.at<double>(1, 1) = 0.999933854565328;
	R.at<double>(1, 2) = -0.004308709550207;
	R.at<double>(2, 0) = 0.004795601426859;
	R.at<double>(2, 1) = 0.004360047879846;
	R.at<double>(2, 2) = 0.999978995874133;
	//图像分割参数
	sf = 600. / 480;
	w = cvRound(640 * sf);
	h = cvRound(480 * sf);
	//获取立体标定矩阵
	stereoRectify(left_index, distCoeffs_left, right_index, distCoeffs_right, Size(640, 480), R, T, Rl, Rr, Pl, Pr, Q, CALIB_ZERO_DISPARITY, 0, Size(640, 480), &validROIL, &validROIR);
	initUndistortRectifyMap(left_index, distCoeffs_left, Rl, Pr, img_left_origin.size(), CV_32FC1, Left1, Left2);
	initUndistortRectifyMap(right_index, distCoeffs_right, Rr, Pr, img_right_origin.size(), CV_32FC1, Right1, Right2);
	//输出图像创建
	output.create(h, w * 2, CV_8UC3);   //注意通道
}

void img_remap::myremap()
{

	remap(img_left_origin, img_left_remapped, Left1, Left2, INTER_LINEAR);
	remap(img_right_origin, img_right_remapped, Right1, Right2, INTER_LINEAR);

	//左图像画到画布上
	Mat canvasPart = output(Rect(w * 0, 0, w, h));                                //得到画布的一部分  
	resize(img_left_remapped, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);     //把图像缩放到跟canvasPart一样大小  
	Rect vroiL(cvRound(validROIL.x*sf), cvRound(validROIL.y*sf),                //获得被截取的区域    
		cvRound(validROIL.width*sf), cvRound(validROIL.height*sf));

	cout << "Painted ImageL" << endl;

	//右图像画到画布上
	canvasPart = output(Rect(w, 0, w, h));                                      //获得画布的另一部分  
	resize(img_right_remapped, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);
	Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y*sf),
		cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));

	for (int i = 0; i < output.rows; i += 16)
		line(output, Point(0, i), Point(output.cols, i), Scalar(0, 255, 0), 1, 8);
}