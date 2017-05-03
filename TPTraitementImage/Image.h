#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "Pixel.h"

using namespace std;


class Image
{
private:
	string path;

	string title = "";
	string author = "";

	int sizeX;
	int sizeY;
	int definition;

	Pixel ** pixels;

public:
	Image(string path) : path(path) { ; };

	void loadPPM();
	void loadTitle(ifstream & file);
	void loadAuthor(ifstream & file);
	void loadSize(ifstream & file);
	void loadDefinition(ifstream & file);
	void loadPixels(ifstream & file);

	void invert();
	void blackAndWhite();
	void seuillage(int seuil);

	void median(int size);
	vector<Pixel> Image::getPixelInRange(int i, int j, int size);
	
	void savePPM(string path);

	~Image() {
		for (int i = 0; i < sizeY; i++)
			delete[] pixels[i];
		delete[] pixels;
	}
};

