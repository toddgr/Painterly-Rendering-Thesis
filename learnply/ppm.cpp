#include "ppm.h"

//init with default values

void ppm::init() {
	width = 0;
	height = 0;
	max_col_val = 255;
}

//create a ppm object

ppm::ppm() {
	init();
}

//create a ppm object and fill it with data stored in fname

ppm::ppm(const std::string& fname) {
	init();
	read(fname);
}

// create an "empty" ppm image with a given width and height; the R, G, B arrays are filled with zeros

ppm::ppm(const unsigned int _width, const unsigned int _height) {
	init();
	width = _width;
	height = _height;
	nr_lines = height;
	nr_columns = width;
	size = width * height;

	//fill r, g, b with 0
	r.resize(size);
	g.resize(size);
	b.resize(size);
}

//read the ppm image from fname

void ppm::read(const std::string& fname) {
	std::ifstream inp(fname.c_str(), std::ios::in | std::ios::binary);
	if (inp.is_open()) {
		std::string line;
		std::getline(inp, line);
		if (line != "P6") {
			std::cout << "Error. Unrecognized file format." << std::endl;
			return;
		}
		std::getline(inp, line);
		while (line[0] == '#') {
			std::getline(inp, line);
		}
		std::stringstream dimensions(line);

		try {
			dimensions >> width;
			dimensions >> height;
			nr_lines = height;
			nr_columns = width;
		}
		catch (std::exception& e) {
			std::cout << "Header file format error. " << e.what() << std::endl;
			return;
		}

		// May have "255" before the RGB values,
		// don't want that to be a part of the rgb channels.
		// should add an edge case for that here

		size = width * height;

		r.resize(size);
		g.resize(size);
		b.resize(size);

		char aux;
		for (unsigned int i = 0; i < size; ++i) {
			inp.read(&aux, 1);
			// Quick and dirty (temporary) fix for in PPM files
			// When there is a space (' '), it actually should have 
			// a value of 0 -- not 32 like the ascii char implies
			if (aux == ' ') { aux = 0; } 
			r[i] = (unsigned char)aux;
			inp.read(&aux, 1);
			if (aux == ' ') { aux = 0; }
			g[i] = (unsigned char)aux;
			inp.read(&aux, 1);
			if (aux == ' ') { aux = 0; }
			b[i] = (unsigned char)aux;
		}
	}
	else {
		std::cout << "Error. Unable to open " << fname << std::endl;
	}
	inp.close();
}

// write the PPM image in fname

void ppm::write(const std::string& fname) {
	std::ofstream inp(fname.c_str(), std::ios::out | std::ios::binary);
	if (inp.is_open()) {

		inp << "P6\n";
		inp << width;
		inp << " ";
		inp << height << "\n";
		inp << max_col_val << "\n";

		char aux;
		for (unsigned int i = 0; i < size; ++i) {
			aux = (char)r[i];
			inp.write(&aux, 1);
			aux = (char)g[i];
			inp.write(&aux, 1);
			aux = (char)b[i];
			inp.write(&aux, 1);
		}
	}
	else {
		std::cout << "Error. Unable to open " << fname << std::endl;
	}
	inp.close();
}