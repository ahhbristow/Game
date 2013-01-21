#pragma once

class Volume {

public:
	Volume(void); //constructor
	~Volume(void); //destructor

	int readData(const char* filename);
	unsigned short getValue(int, int, int);
	unsigned short* getVolumeData();
	void prepareVolume();
	SCALAR* getTextureData();

private:
	unsigned short* volumeData;
	unsigned int width, height, depth;
	SCALAR* textureData;

};
