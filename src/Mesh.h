#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

class Mesh {
public:
    Mesh(IDirect3DDevice9* device);
    ~Mesh();

    bool LoadObj(const std::string& filename);
    void Render();

private:
    IDirect3DDevice9* m_device;
    std::vector<D3DXVECTOR3> m_vertices;
    std::vector<D3DXVECTOR3> m_normals;
    std::vector<D3DXVECTOR2> m_texCoords;
    LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
    DWORD m_numVertices;

    bool CreateVertexBuffer();
};

