#include <Windows.h>
#include <iostream>
#include "Window.h"
#include "Mesh.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char* windowTitle = "DirectX 9 Window";
    const int windowWidth = 640;
    const int windowHeight = 480;

    Window mainWindow(hInstance, nCmdShow, windowTitle, windowWidth, windowHeight);

    IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d) {
        MessageBox(nullptr, "Direct3D initialization failed!", "Error", MB_OK | MB_ICONERROR);
        return EXIT_FAILURE;
    }

    D3DPRESENT_PARAMETERS d3dpp{};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    IDirect3DDevice9* device = nullptr;
    if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, mainWindow.GetHWND(),
                                  D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device))) {
        MessageBox(nullptr, "Failed to create DirectX device!", "Error", MB_OK | MB_ICONERROR);
        d3d->Release();
        return EXIT_FAILURE;
    }

    // Create and load mesh from OBJ file
    Mesh mesh(device);
    if (!mesh.LoadObj("cube.obj")) {
        MessageBox(nullptr, "Failed to load OBJ file!", "Error", MB_OK | MB_ICONERROR);
        device->Release();
        d3d->Release();
        return EXIT_FAILURE;
    }

    MSG msg;
    while (mainWindow.ProcessMessages()) {
        // Clear the back buffer
        device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(184, 210, 215), 1.0f, 0);

        // Begin the scene
        if (SUCCEEDED(device->BeginScene())) {
            // Render the mesh
            mesh.Render();

            // End the scene
            device->EndScene();
        }

        // Present the back buffer
        device->Present(nullptr, nullptr, nullptr, nullptr);
    }

    // Clean up resources
    device->Release();
    d3d->Release();
    
    return EXIT_SUCCESS;
}
