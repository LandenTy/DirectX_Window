#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

Window::Window(HINSTANCE hInstance, int nCmdShow, const char* windowTitle, int width, int height)
    : hInstance(hInstance), windowTitle(windowTitle), width(width), height(height), hWnd(nullptr) {
    if (!Initialize()) {
        MessageBox(nullptr, "Window Initialization Failed!", "Error", MB_OK | MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
}

Window::~Window() {
    if (hWnd != nullptr) {
        DestroyWindow(hWnd);
    }
}

bool Window::Initialize() {
    if (!InitWindow()) {
        return false;
    }

    return true;
}

bool Window::InitWindow() {
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "WindowClass";

    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    RECT wr = { 0, 0, width, height };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx(
        0,
        "WindowClass",
        windowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        wr.right - wr.left,
        wr.bottom - wr.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd) {
        MessageBox(nullptr, "Window Creation Failed!", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}

bool Window::ProcessMessages() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT) {
            return false;
        }
    }
    return true;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
