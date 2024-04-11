#pragma once

#include <Windows.h>

class Window {
public:
    Window(HINSTANCE hInstance, int nCmdShow, const char* windowTitle, int width, int height);
    ~Window();

    bool Initialize();
    HWND GetHWND() const { return hWnd; }
    bool ProcessMessages();

private:
    HINSTANCE hInstance;
    const char* windowTitle;
    int width;
    int height;
    HWND hWnd;

    bool InitWindow();
};
