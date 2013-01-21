#include "stdafx.h"
#include "Volume.h"

using namespace std;

Volume::Volume(void)
{
}

Volume::~Volume(void)
{
}

int Volume::readData(const char* filename) {

	this->width = 256;
	this->height = 256;
	this->depth = SLICES;
	volumeData = (unsigned short*) calloc(width*height*depth, 2);

	fstream myFile(filename, ios::binary|ios::in);

	if (myFile.fail()) {
		return 1;
	}
	else 
	{
		myFile.read((char*)&volumeData[0], width*height*depth*2);
		myFile.close();
		return 0;
	}	
}


unsigned short Volume::getValue(int x, int y, int z)
{

	int offset = (z*(this->width*this->height)) + (y*this->width + x);
	return volumeData[offset];
}

unsigned short* Volume::getVolumeData()
{
	return this->volumeData;
}

SCALAR* Volume::getTextureData()
{
	return this->textureData;
}



/*
 *	Converts the volume data (intensity values into RGBA texture data)
 */
void Volume::prepareVolume()
{
	unsigned short maxValue = 0;
	textureData = (SCALAR*) malloc(256*256*SLICES*4*sizeof(SCALAR));

	for(int i = 0; i < 256*256*SLICES; i++)
	{
		//Alpha value
		unsigned short val = volumeData[i];
		SCALAR value = ((SCALAR)val/4096);
		textureData[(i*4) + 3] = pow(value,3);

		if(val > maxValue) {
			maxValue = val;
		}

		//RGB Values
		textureData[(i*4)] = 1.0f;
		textureData[(i*4) + 1] = 0.0f;
		textureData[(i*4) + 2] = 0.0f;
	}
	printf("%d", maxValue);
}