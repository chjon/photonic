#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255,   0,   0, 255);
const TGAColor green = TGAColor(  0, 255,   0, 255);
const TGAColor blue  = TGAColor(  0,   0, 255, 255);

const int WIDTH  = 1600;
const int HEIGHT = 1600;

Model* model = nullptr;

int main(int argc, char** argv) {
	if (2==argc) {
		model = new Model(argv[1]);
	} else {
		model = new Model("obj/african_head.obj");
	}
	
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
	
	for (int i = 0; i < model->nfaces(); i++) { 
		std::vector<int> face = model->face(i); 
		Vec2i screenCoords[3]; 
		Vec3f worldCoords[3]; 
		
		for (int j=0; j<3; j++) { 
			Vec3f v = model->vert(face[j]); 
			screenCoords[j] = Vec2i((v.x+1.)*WIDTH/2., (v.y+1.)*HEIGHT/2.); 
			worldCoords[j]  = v; 
		} 
		
		Vec3f n = (worldCoords[2]-worldCoords[0])^(worldCoords[1]-worldCoords[0]);
		Vec3f lightDir(0, 0, -1);
		
		n.normalize();
		
		float intensity = n * lightDir; 
		if (intensity > 0) { 
			image.triFill(
				screenCoords[0],
				screenCoords[1],
				screenCoords[2],
				TGAColor(intensity * 255, intensity * 255, intensity * 255, 255)
			);
		} 
	}
		

	//Vec2i t[3] = {Vec2i(10, 10), Vec2i(100,30), Vec2i(190, 160)};

	//image.triFill(t[0], t[1], t[2], white);

	image.flip_vertically();
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}
