#include "./header/video.h"

void reformat_img(cv::Mat &img)
{
	// Convert the img from RGB to GrayLevel
	cv::cvtColor(img, img, CV_BGR2GRAY);

	// Resize the img to 64*64
	cv::Size size(64, 64);
	resize(img, img, size);

	// Adjust the value in the img matrix
	img.convertTo(img, CV_32F);
	img /= 255;
	img *= 16;
	img.convertTo(img, CV_8U);
	img.convertTo(img, CV_32F);
	img /= 16;
}