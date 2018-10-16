#pragma once
#include "BaseImg.h"
#include "LargeImg.h"

class MatchImg : public BaseImg
{
public:
	MatchImg();
	~MatchImg();

	/**
	*   Overload Constructor for MatchImg
	*
	*   \param int -  Height of MatchImage
	*	\param int -  Width of MatchImage
	*	\param int - cordinate X of where the top left pixel in largeImg
	*	\param int -  cordinate Y of where the top left pixel in largeImg where this begins
	*	\param LargeImg -  LargeImg to get block using cords
	*	\param BaseImg -  baseImg instance to compare and calculate NNS_score.
	*   \return MatchImg.
	*
	**/
	MatchImg(int pHeight, int pWidth, int cordX, int cordY, LargeImg*& largeImage, BaseImg*& baseImage); //overload constructor

	double getNNS() const { return NNS_Score; };

	int getX() const { return X; };

	int getY() const { return Y; };


private:
	double NNS_Score; //store NNS
	int Y; 
	int X;
};

