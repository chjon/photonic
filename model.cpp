#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename, TGAImage &textureMap) : verts_(), faces_(), norms_(), uv_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f n;
            for (int i=0;i<3;i++) iss >> n[i];
            norms_.push_back(n);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f uv;
            for (int i=0;i<2;i++) iss >> uv[i];
            uv_.push_back(uv);
        }  else if (!line.compare(0, 2, "f ")) {
            std::vector<Vec3i> f;
            Vec3i tmp;
            iss >> trash;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                for (int i=0; i<3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
                f.push_back(tmp);
            }

            faces_.push_back(f);
        }
    }

    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << " vt# " << uv_.size() << " vn# " << norms_.size() << std::endl;
    this->textureMap = textureMap;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    std::vector<int> face;
    for (int i=0; i<(int)faces_[idx].size(); i++) face.push_back(faces_[idx][i][0]);
    return face;
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

TGAColor Model::diffuse(Vec2f uv) {
    return textureMap.get(uv.x, uv.y);
}

Vec2i Model::uv(int iface, int nvert) {
    int idx = faces_[iface][nvert].y;
    return Vec2i(
        uv_[idx].x * textureMap.get_width(),
        uv_[idx].y * textureMap.get_height()
    );
}

/**
 * Draw the model to an image
 *
 * @param image the image to draw to
 */
void Model::render (TGAImage &image) {
    // Iterate through each face
    for (int i = 0; i < nfaces(); i++) {
        std::vector<int> face = this->face(i);

        Vec3f screenCoords[3];
        Vec3f worldCoords[3];
        Vec2i textureCoords[3];

        // Get the 3D coordinates as well as the 2D mapping for each vertex
        for (int j = 0; j < 3; j++) {
            Vec3f v = vert(face[j]);
            worldCoords [j] = v;
            screenCoords[j] = Vec3f(
                (v.x + 1.) * image.get_width()  / 2.,
                (v.y + 1.) * image.get_height() / 2.,
                (v.z)
            );
        }

        // Get the normal to the face
        Vec3f n = (worldCoords[2] - worldCoords[0]) ^ (worldCoords[1] - worldCoords[0]);
        n.normalize();

        // Get texture coords
        for (int j = 0; j < 3; j++) {
            textureCoords[j] = uv(i, j);
        }

        // Calculate the intensity of the lighting based on the normal
        Vec3f lightDir(0, 0, -1);
        float intensity = n * lightDir;

        if (intensity > 0) {
            image.triFill(
                screenCoords,
                textureCoords,
                textureMap,
                intensity
            );
        }
    }
}