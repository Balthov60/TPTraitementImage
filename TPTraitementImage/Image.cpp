#include "Image.h"

void Image::loadPPM() {
	ifstream file(path, ios::in);
	if (!file) {
		cout << "Error while openning file.";
		return;
	}
	
	char line[200];
	try {
		loadTitle(file);
		loadAuthor(file);
		loadSize(file);
		loadDefinition(file);
		loadPixels(file);
	}
	catch (exception & e) {
		cout << "Encoding Exception" << endl;
		return;
	}
	file.close();
}

void Image::loadTitle(ifstream & file) {
	char title[200];

	if (file.eof()) {
		throw new exception("Encoding Error");
		return;
	}
	file.getline(title, 200);

	this->title = title;
}
void Image::loadAuthor(ifstream & file) {
	char author[200];

	if (file.eof()) {
		throw new exception("Encoding Error");
		return;
	}

	file.getline(author, 200, '\n');
	int i = 13;
	while (author[i] != '\0') {
		this->author += author[i];
		i++;
	}
}
void Image::loadSize(ifstream & file) {
	char sizeX[10], sizeY[10];

	if (file.eof()) {
		throw new exception("Encoding Error");
		return;
	}
	file >> sizeX;
	file >> sizeY;

	this->sizeX = atoi(sizeX);
	this->sizeY = atoi(sizeY);

	pixels = new Pixel*[this->sizeY];
	for (int i = 0; i < this->sizeY; i++)
		pixels[i] = new Pixel[this->sizeX];
}
void Image::loadDefinition(ifstream & file) {
	char definition[100];

	if (file.eof()) {
		throw new exception("Encoding Error");
		return;
	}
	file >> definition;

	this->definition = atoi(definition);
}
void Image::loadPixels(ifstream & file) {
	char red[4];
	char green[4];
	char blue[4];

	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			file >> red; 
			file >> green;
			file >> blue;

			pixels[i][j].setColor(atoi(red), atoi(green), atoi(blue));
		}
	}
}

void Image::savePPM(string path) {
	ofstream file(path, ios::trunc);
	if (!file) {
		cout << "Error while openning file.";
		return;
	}

	file << title.c_str() << endl;
	file << "# Created by " << author.c_str() << endl;
	file << sizeX << " " << sizeY << endl;
	file << definition << endl;

	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			file << pixels[i][j].red << " ";
			file << pixels[i][j].green << " ";
			file << pixels[i][j].blue << " ";
		}
	}
	file.close();
}

void Image::invert() {
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			pixels[i][j].red = definition - pixels[i][j].red;
			pixels[i][j].green = definition - pixels[i][j].green;
			pixels[i][j].blue = definition - pixels[i][j].blue;
		}
	}
}

void Image::blackAndWhite() {
	float luminance;
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			luminance = 0.2126 * (float)pixels[i][j].red + 0.7152 * (float)pixels[i][j].green + 0.0722 * (float)pixels[i][j].blue;
			pixels[i][j].red = pixels[i][j].green = pixels[i][j].blue = luminance;
		}
	}
}

void Image::seuillage(int seuil) {
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 > seuil)
				pixels[i][j].red = pixels[i][j].green = pixels[i][j].blue = 255;
			else
				pixels[i][j].red = pixels[i][j].green = pixels[i][j].blue = 0;
		}
	}
}

void Image::median(int size) {
	vector<Pixel> zone;
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			zone = getPixelInRange(i, j, size);

			if (zone.size() == 0)
				continue;

			int averageRed = 0, averageGreen = 0, averageBlue = 0;			
			for (int m = 0; m < zone.size(); m++) {
				averageRed += zone.at(m).red;
				averageGreen += zone.at(m).green;
				averageBlue += zone.at(m).blue;
			}
			pixels[i][j].red = averageRed / zone.size();
			pixels[i][j].green = averageGreen / zone.size();
			pixels[i][j].blue = averageBlue / zone.size();
		}
	}
}

vector<Pixel> Image::getPixelInRange(int i, int j, int size) {
	vector<Pixel> zone;

	for (int y = i - size; y < i + size; y++) {
		for (int x = j - size; x < j + size; x++)
			if (y >= 0 && y < sizeY && 
				x >= 0 && x < sizeX)
				zone.push_back(pixels[y][x]);
	}

	return zone;
}