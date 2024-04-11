#pragma once

#include <vector>

struct Vertex {
    float x, y, z;  // Position
    float nx, ny, nz;  // Normal
    float u, v;  // Texture coordinates
};

struct Face {
    std::vector<int> vertexIndices;
    std::vector<int> normalIndices;
    std::vector<int> texcoordIndices;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

bool loadOBJ(const char* filename, Mesh& mesh);
