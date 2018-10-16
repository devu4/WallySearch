#include "BaseImg.h"

BaseImg::BaseImg()
{
}

BaseImg::BaseImg(int pHeight, int pWidth)
{
	height = pHeight;
	width = pWidth;

}

BaseImg::BaseImg(int pHeight, int pWidth, double* input_data)
{
	height = pHeight;
	width = pWidth;

	data = new double[height*width];

	for (int i = 0; i < height*width; i++)
	{
		data[i] = input_data[i];
	}
}

BaseImg::~BaseImg()
{
	delete [] data;
}

// Read .txt file with image of size RxC, and convert to an array of doubles
double* BaseImg::readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
}

void BaseImg::WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}

BaseImg BaseImg::operator=(const BaseImg& other)
{
	delete[] data;
	height = other.height;
	width = other.width;
	//reserve memory for new array
	data = new double[height*width];
	//'this' pointer refers to the current object
	for (int x = 0; x < (height*width); x++)
	{
		data[x] = other.data[x];
	}

	return *this;
}

BaseImg BaseImg::operator*(const BaseImg& other)
{
	BaseImg* temp = new BaseImg();

	temp->height = other.height;
	temp->width = other.width;

	temp->data = new double[temp->height*temp->width];

	for (int x = 0; x < (temp->height*temp->width); x++)
	{
		temp->data[x] = this->data[x] * other.data[x];
	}

	return *temp;
}

BaseImg BaseImg::operator+(const BaseImg& other)
{
	BaseImg* temporary = new BaseImg();
	temporary->height = other.height;
	temporary->width = other.width;
	temporary->data = new double[temporary->height*temporary->width];

	for (int x = 0; x < (temporary->height*temporary->width); x++)
	{
		temporary->data[x] = this->data[x] + other.data[x];
	}

	return *temporary;
}

BaseImg BaseImg::operator-(const BaseImg& other)
{
	BaseImg* temporary = new BaseImg();
	temporary->height = other.height;
	temporary->width = other.width;
	temporary->data = new double[temporary->height*temporary->width];

	for (int x = 0; x < (temporary->height*temporary->width); x++)
	{
		temporary->data[x] = this->data[x] - other.data[x];
	}

	return *temporary;
}

int BaseImg::getWidth()
{
	return width;
}

int BaseImg::getHeight()
{
	return height;
}

double * BaseImg::getData()
{
	return data;
}

double BaseImg::getSum()
{
	double sum = 0;

	for (int i = 0; i < height*width; i++)
		sum += data[i];

	return 0.0;
}
