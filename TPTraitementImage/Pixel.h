#pragma once

class Pixel
{
public:
	int red;
	int green;
	int blue;

public:
	Pixel() { ; }
	Pixel(int red, int green, int blue) : red(red), green(green), blue(blue) { ; }

	void setColor(int red, int green, int blue) {
		this->red = red; this->green = green; this->blue = blue;
	}
	
	~Pixel() { ; }
};

