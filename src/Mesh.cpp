#include "Mesh.h"
#include <fstream>
#include <sstream>

Mesh::Mesh(IDirect3DDevice9* device) : m_device(device), m_vertexBuffer(nullptr), m_numVertices(0) {}

Mesh::~Mesh() {
    if (m_vertexBuffer != nullptr) {
        m_vertexBuffer->Release();
        m_vertexBuffer = nullptr;
    }
}

bool Mesh::LoadObj(const std::string& filename) {
    std::string fullPath = "../assets/models/" + filename;
    std::ifstream file(fullPath);
    if (!file.is_open()) {
        return false; // Failed to open file
    }

    std::vector<D3DXVECTOR3> tempVertices;
    std::vector<D3DXVECTOR3> tempNormals;
    std::vector<D3DXVECTOR2> tempTexCoords;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            D3DXVECTOR3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            tempVertices.push_back(vertex);
        }
        else if (type == "vn") {
            D3DXVECTOR3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }
        else if (type == "vt") {
            D3DXVECTOR2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            tempTexCoords.push_back(texCoord);
        }
        else if (type == "f") {
            std::string v1, v2, v3;
            iss >> v1 >> v2 >> v3;

            int vIndex1, vIndex2, vIndex3;
            sscanf_s(v1.c_str(), "%d", &vIndex1);
            sscanf_s(v2.c_str(), "%d", &vIndex2);
            sscanf_s(v3.c_str(), "%d", &vIndex3);

            m_vertices.push_back(tempVertices[vIndex1 - 1]);
            m_vertices.push_back(tempVertices[vIndex2 - 1]);
            m_vertices.push_back(tempVertices[vIndex3 - 1]);

            // For simplicity, we're not handling normals and texture coordinates in this example
        }
    }

    file.close();

    // Create vertex buffer
    return CreateVertexBuffer();
}

bool Mesh::CreateVertexBuffer() {
    m_numVertices = static_cast<DWORD>(m_vertices.size());

    if (FAILED(m_device->CreateVertexBuffer(m_numVertices * sizeof(D3DXVECTOR3),
                                            D3DUSAGE_WRITEONLY,
                                            D3DFVF_XYZ,
                                            D3DPOOL_DEFAULT,
                                            &m_vertexBuffer,
                                            nullptr))) {
        return false; // Failed to create vertex buffer
    }

    void* pVertices;
    if (FAILED(m_vertexBuffer->Lock(0, 0, &pVertices, 0))) {
        return false; // Failed to lock vertex buffer
    }

    memcpy(pVertices, m_vertices.data(), m_numVertices * sizeof(D3DXVECTOR3));
    m_vertexBuffer->Unlock();

    return true;
}

void Mesh::Render() {
    if (m_vertexBuffer != nullptr) {
        m_device->SetFVF(D3DFVF_XYZ);
        m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(D3DXVECTOR3));
        m_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_numVertices / 3);
    }
}
