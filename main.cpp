#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255,   0,   0, 255);
const TGAColor green = TGAColor(  0, 255,   0, 255);
const TGAColor blue  = TGAColor(  0,   0, 255, 255);

const int WIDTH  = 200;
const int HEIGHT = 200;

Model* model = nullptr;

int main(int argc, char** argv) {
	if (2==argc) {
		model = new Model(argv[1]);
	} else {
		model = new Model("obj/african_head.obj");
	}
	
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
	/*	
	for (int i=0; i<model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
        	for (int j=0; j<3; j++) {
			Vec3f v0 = model->vert(face[j]);
            		Vec3f v1 = model->vert(face[(j+1)%3]);
            		int x0 = (v0.x+1.)*WIDTH/2.;
            		int y0 = (v0.y+1.)*HEIGHT/2.;
            		int x1 = (v1.x+1.)*WIDTH/2.;
            		int y1 = (v1.y+1.)*HEIGHT/2.;
            		image.line(x0, y0, x1, y1, white);
        	}
    	}
	*/	

	Vec2i t[3] = {Vec2i(10, 10), Vec2i(100,30), Vec2i(190, 160)};

	image.triFill(t[0], t[1], t[2], white);

	//image.flip_vertically();
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}
