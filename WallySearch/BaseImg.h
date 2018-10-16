#pragma once
#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include <vector>

using namespace std;

class BaseImg
{
public:
	BaseImg();
	BaseImg(int M, int N, double* input_data);
	BaseImg(int M, int N);
	~BaseImg();

	static double* readTXT(char *fileName, int sizeR, int sizeC);
	static void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

	BaseImg operator=(const BaseImg & other);

	BaseImg operator*(const BaseImg & other);

	BaseImg operator+(const BaseImg & other);

	BaseImg operator-(const BaseImg & other);

	int getWidth();
	int getHeight();
	double* getData();

	virtual double getSum();

private:
	int height;
	int width;

protected:
	double* data;

};

