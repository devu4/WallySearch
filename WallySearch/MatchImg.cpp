#include "MatchImg.h"

MatchImg::MatchImg()
{
}


MatchImg::~MatchImg()
{
}

MatchImg::MatchImg(int pHeight, int pWidth, int cordX, int cordY, LargeImg*& largeImage, BaseImg*& baseImage) : BaseImg(pHeight, pWidth)
{
	X = cordX;
	Y = cordY;

	//create on heap
	data = new double[pWidth*pHeight];
	double* largeData = largeImage->getData(); //get data of clutteredImage
	double* smallData = baseImage->getData(); //get data of templateImage
	int largeWidth = largeImage->getWidth(); //width of clutterImage

	//loop through and get block of largeData for this instance.
	for (int i = cordY; i < (cordY + pHeight); i++)
	{
		for (int j = cordX; j < (cordX + pWidth); j++)
		{
			data[((i - cordY)*pWidth) + (j - cordX)] = largeData[i* largeWidth + j];
			
		}
	}

	//calulate the NNS score
	NNS_Score = LargeImg::SSD2(smallData, data, pWidth*pHeight);
}
