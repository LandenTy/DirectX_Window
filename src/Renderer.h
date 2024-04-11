#pragma once

#include <d3d9.h>  // Include DirectX 9 header

class Renderer {
public:
    Renderer(HWND hWnd);
    ~Renderer();

    bool Initialize();
    void Render();
    void Cleanup();

private:
    HWND hwnd;
    LPDIRECT3D9 d3d = nullptr;
    LPDIRECT3DDEVICE9 d3dDevice = nullptr;

    bool CreateDevice();
};

