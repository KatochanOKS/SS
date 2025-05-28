#pragma once
#include <Windows.h>

class GameEngine;
class WindowManager;
class GraphicsManager;

class ApplicationManager {
public:
    int Run(GameEngine* engine, HINSTANCE hInstance, int nCmdShow);

private:
    HWND m_hWnd = nullptr;
};