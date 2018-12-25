#include <iostream>
#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255,   0,   0, 255);
const TGAColor green = TGAColor(  0, 255,   0, 255);
const TGAColor blue  = TGAColor(  0,   0, 255, 255);

const int WIDTH  = 1000;
const int HEIGHT = 1000;

Model* model = nullptr;

int main(int argc, char** argv) {
	// Validate commandline arguments
	if (3 != argc) {
		std::cout << "Proper usage: ./main <objectFile> [textureFile]" << std::endl;
		return 1;
	}

	TGAImage texture;
	texture.read_tga_file(argv[2]);
	texture.flip_vertically();

	// Load the model
	model = new Model(argv[1], texture);

	// Render the model
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	model->render(image);
	image.flip_vertically();

	// Output the image
	image.write_tga_file("output.tga");

	// Clean up
	delete model;

	return 0;
}
