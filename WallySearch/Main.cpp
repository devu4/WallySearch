#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <shellapi.h>
#include "BaseImg.h"
#include "MatchImg.h"
#include "LargeImg.h"

using namespace std;

/**
*   Sort Condition for when sorting matchmaking images by NNS Scores
*
*   \param MatchImg s1 -  first matchmaking image.
*	\param MatchImg s2 -  second matchmaking image.
*   \return bool true if s1 is bigger than s2.
*
**/
bool sortCond(const MatchImg* s1, const MatchImg* s2);

bool sortCond(const MatchImg* s1, const MatchImg* s2)
{
	return s1->getNNS() < s2->getNNS();
}

int main()
{

	int count = 1; //number of best fits needed.
	cout << "             *----------------------* David's Wally Finder *----------------------*" << endl << endl;
	
	bool hasInput = false;
	while (!hasInput)
	{
		cout << "How many best fits do you need? (max 100)" << endl;
		cin >> count;

		if ((count <= 100) && (count > 0))
		{
			cout << "Working...Please Wait..." << endl;
			hasInput = true;
		}
		else
		{
			cout << "Invalid value given, please choose a number from 1-100!" << endl << endl;
		}
	}

	//read small wally in
	double* input_data = BaseImg::readTXT("ImageFiles/Wally_grey.txt", 49, 36);

	//create template wally object
	BaseImg* wallySmall = new BaseImg(49, 36, input_data);

	//read larger image in
	input_data = BaseImg::readTXT("ImageFiles/Cluttered_scene.txt", 768, 1024);
	//create clutterimage object
	LargeImg* clutterImage = new LargeImg(768, 1024, input_data);

	delete input_data; //delete temp 1d array.

	//loop through each pixel of clutteredImage and create all MatchImgs
	for (int i = 0; i < (clutterImage->getHeight() - wallySmall->getHeight()); i++)
	{
		for (int j = 0; j < (clutterImage->getWidth() - wallySmall->getWidth()); j++)
		{
			//sort vector to get best fit at top.
			sort(clutterImage->allMatchImages.begin(), clutterImage->allMatchImages.end(), sortCond);

			//create instance of match image in heap
			MatchImg* newMImage = new MatchImg(49, 36, j, i, clutterImage, wallySmall);

			//check if vector is full if so delete last element to save RAM.
			if ((clutterImage->allMatchImages.size() < (double)count )|| (count == 1 && clutterImage->allMatchImages.size() == 1))
			{
				clutterImage->allMatchImages.push_back(newMImage);
			} 
			else
			{
				delete clutterImage->allMatchImages[(clutterImage->allMatchImages.size() - 1)];
				clutterImage->allMatchImages.erase(clutterImage->allMatchImages.end() - 1);
				clutterImage->allMatchImages.push_back(newMImage);
			}
		}

	}

	int fitChosen = 1; bool fitInput = false;
	while (!fitInput)
	{
		cout << "Choose which fit you would like to export! (from 1-" << count << "). If you would like to exit choose 0!" << endl;
		cin >> fitChosen;

		if (fitChosen == 0)
		{
			cout << "Goodbye!" << endl;
			fitInput = true;
		}
		else if ((fitChosen <= count) && (fitChosen > 0))
		{
			int index = fitChosen - 1;
			cout << "Chosen Wally found at X: " << clutterImage->allMatchImages[index]->getX() << ", Y: " << clutterImage->allMatchImages[index]->getY() << " with NNS: " << clutterImage->allMatchImages[index]->getNNS() << ". Saved as ImageFiles/Wally_found.pgm!" << endl;
			BaseImg::WritePGM("ImageFiles/Wally_found.pgm", clutterImage->allMatchImages[index]->getData(), clutterImage->allMatchImages[index]->getHeight(), clutterImage->allMatchImages[index]->getWidth(), 255);
			ShellExecute(NULL, "open", "ImageFiles\\Wally_found.pgm", NULL, NULL, SW_SHOW);
		}
		else
		{
			cout << "Invalid value given, please choose a number from 1-"<< count << "!" << endl << endl;
		}
	}

	delete wallySmall; // delete from heap
	delete clutterImage; 

	system("pause");
	return 0;

}
