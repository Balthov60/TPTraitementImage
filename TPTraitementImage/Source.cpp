#pragma once

#include "Image.h"

using namespace std;


int main() {

	Image image("C:\\temp\\Image.ppm");
	image.loadPPM();
	image.blackAndWhite();
	image.median(2);
	image.savePPM("C:\\temp\\Image_seuillage.ppm");

	return 0;
}