#include "LargeImg.h"

LargeImg::LargeImg()
{
}

LargeImg::LargeImg(int pHeight, int pWidth, double * input_data) : BaseImg(pHeight, pWidth, input_data)
{

}


LargeImg::~LargeImg()
{
}

double LargeImg::NCC(const double* baseImage, const double* matchImage, int N)
{

	//Declare variables
	double* baseData = new double[N]; double* matchData = new double[N];
	for (int i = 0; i < N; i++)
	{
		baseData[i] = baseImage[i]; //deep copy image data
		matchData[i] = matchImage[i]; //deep copy
	}

	double baseSum = 0, matchSum = 0, baseMean = 0, matchMean = 0, baseSquared = 0, matchSquared = 0, SumofBoth = 0;

	double *Array = new double[N]; //create temp array on heap

								   //add up element in the 2 matrixes
	for (int i = 0; i < N; i++)
	{
		baseSum += baseData[i];
		matchSum += matchData[i];
	}

	//get Means
	baseMean = baseSum / (N);
	matchMean = matchSum / (N);

	for (int i = 0; i < N; i++)
	{
		baseData[i] = baseData[i] - baseMean; //Minus the mean from each matrix element
		matchData[i] = matchData[i] - matchMean;
		Array[i] = baseData[i] * matchData[i]; // Multiplying each array by the corresponding element
		SumofBoth += Array[i]; //Summing up the results of the multiplied matrix
		baseData[i] = baseData[i] * baseData[i]; //square each element after mean is taken away
		matchData[i] = matchData[i] * matchData[i]; //square each element after mean is taken away
		baseSquared += baseData[i];
		matchSquared += matchData[i];
	}

	delete[] Array; delete [] baseData; delete [] matchData;
	return SumofBoth / sqrt(baseSquared*matchSquared); //Return the NCC
}

double LargeImg::SSD(const double* baseImage, const double* matchImage, int N)
{
	double SSD = 0, diff = 0;

	for (int i = 0; i < N; i++)
	{
		diff =  baseImage[i] - matchImage[i];
		SSD += diff*diff;
	}

	return SSD;

}

double LargeImg::SSD2(const double* baseImage, const double* matchImage, int N)
{
	double SSD = 0;

	for (int i = 0; i < N; i++)
	{
		if (baseImage[i] != 255 && matchImage[i] != 255) // ignore whitespace as it skews this type of NNS. 
		{
			double diff = baseImage[i] - matchImage[i]; //minus element of one from the other
			SSD += diff*diff; //square the difference
		}
	}

	return SSD;

}