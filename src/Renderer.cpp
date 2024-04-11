#include "Renderer.h"
#include <iostream>

Renderer::Renderer(HWND hWnd) : hwnd(hWnd) {}

Renderer::~Renderer() {
    Cleanup();
}

bool Renderer::Initialize() {
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d) {
        std::cerr << "Direct3D initialization failed!" << std::endl;
        return false;
    }

    if (!CreateDevice()) {
        Cleanup();
        return false;
    }

    return true;
}

bool Renderer::CreateDevice() {
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hwnd;

    if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                                  D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &d3dpp, &d3dDevice))) {
        std::cerr << "Direct3D device creation failed!" << std::endl;
        return false;
    }

    return true;
}

void Renderer::Render() {
    if (d3dDevice) {
        // Clear the backbuffer to a blue color
        d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(184, 210, 215), 1.0f, 0);

        // Begin the scene
        if (SUCCEEDED(d3dDevice->BeginScene())) {
            // Rendering code goes here

            // End the scene
            d3dDevice->EndScene();
        }

        // Present the backbuffer contents to the display
        d3dDevice->Present(NULL, NULL, NULL, NULL);
    }
}

void Renderer::Cleanup() {
    if (d3dDevice) {
        d3dDevice->Release();
        d3dDevice = nullptr;
    }
    if (d3d) {
        d3d->Release();
        d3d = nullptr;
    }
}

