#pragma once
#ifndef REMAP_H
#define REMAP_H
#include<opencv2\opencv.hpp>
class img_remap {
private:
	cv::Mat img_left_origin, img_right_origin;			//输入图像
	cv::Mat img_left_remapped, img_right_remapped;		//经校正后的左右图像
	//****************************左右相机内参矩阵****************************/
	cv::Mat left_index = cv::Mat::eye(3, 3, CV_64F);
	cv::Mat right_index = cv::Mat::eye(3, 3, CV_64F);
	cv::Mat distCoeffs_left = cv::Mat::zeros(4, 1, CV_64F);
	cv::Mat distCoeffs_right = cv::Mat::zeros(4, 1, CV_64F);

	cv::Mat Left1, Left2;
	cv::Mat Right1, Right2;
	cv::Mat temp;
	/*******************************极线约束***************************/

	cv::Rect validROIL;//图像校正之后，会对图像进行裁剪，这里的validROI就是指裁剪之后的区域  
	cv::Rect validROIR;

	//校正旋转矩阵R，投影矩阵P 重投影矩阵Q
	cv::Mat T = (cv::Mat_<double>(3, 1)); 
	cv::Mat R = (cv::Mat_<double>(3, 3)); 
	cv::Mat Rl, Rr, Pl, Pr, Q;
	//校正后分割图像所用参数
	double sf;
	int w, h;

	          
public:
	cv::Mat output;   //输出图像




public:
	img_remap(cv::Mat origin);
	void myremap();

	
};
#endif // REMAP_H
