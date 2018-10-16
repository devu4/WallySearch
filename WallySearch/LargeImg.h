#pragma once
#include "BaseImg.h"

class MatchImg;

class LargeImg : public BaseImg
{
public:
	LargeImg();
	LargeImg(int M, int N, double* input_data);
	~LargeImg();

	static double NCC(const double* baseImage, const double* matchImage, int N);

	static double SSD(const double * baseImage, const double * matchImage, int N);

	static double SSD2(const double * baseImage, const double * matchImage, int N);

	vector<MatchImg*> allMatchImages;

};

