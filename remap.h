#pragma once
#ifndef REMAP_H
#define REMAP_H
#include<opencv2\opencv.hpp>
class img_remap {
private:
	cv::Mat img_left_origin, img_right_origin;			//����ͼ��
	cv::Mat img_left_remapped, img_right_remapped;		//��У���������ͼ��
	//****************************��������ڲξ���****************************/
	cv::Mat left_index = cv::Mat::eye(3, 3, CV_64F);
	cv::Mat right_index = cv::Mat::eye(3, 3, CV_64F);
	cv::Mat distCoeffs_left = cv::Mat::zeros(4, 1, CV_64F);
	cv::Mat distCoeffs_right = cv::Mat::zeros(4, 1, CV_64F);

	cv::Mat Left1, Left2;
	cv::Mat Right1, Right2;
	cv::Mat temp;
	/*******************************����Լ��***************************/

	cv::Rect validROIL;//ͼ��У��֮�󣬻��ͼ����вü��������validROI����ָ�ü�֮�������  
	cv::Rect validROIR;

	//У����ת����R��ͶӰ����P ��ͶӰ����Q
	cv::Mat T = (cv::Mat_<double>(3, 1)); 
	cv::Mat R = (cv::Mat_<double>(3, 3)); 
	cv::Mat Rl, Rr, Pl, Pr, Q;
	//У����ָ�ͼ�����ò���
	double sf;
	int w, h;

	          
public:
	cv::Mat output;   //���ͼ��




public:
	img_remap(cv::Mat origin);
	void myremap();

	
};
#endif // REMAP_H
