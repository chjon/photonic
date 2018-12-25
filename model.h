#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"
#include "tgaimage.h"

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<Vec3i>> faces_;
	std::vector<Vec3f> norms_;
	std::vector<Vec2f> uv_;
	TGAImage textureMap;
public:
	Model(const char *filename, TGAImage &textureMap);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<int> face(int idx);
	TGAColor diffuse(Vec2f uvf);
	Vec2i uv(int iface, int nvert);
    void render(TGAImage &image);
};

#endif //__MODEL_H__