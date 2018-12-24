#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

const int WIDTH  = 160;
const int HEIGHT = 90;

int main(int argc, char** argv) {
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
	image.set(0, 0, TGAColor(255, 255, 255, 255));
	image.line(0, 0, WIDTH, HEIGHT, white);
	image.line(0, HEIGHT, WIDTH, 0, white);
	image.line(0, 0, WIDTH, 0, white);
	image.line(0, 0, 0, HEIGHT, white);
	image.write_tga_file("output.tga");
	return 0;
}
