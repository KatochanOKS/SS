#pragma once
#include <Windows.h>

class WindowManager {
public:
    bool Initialize(HINSTANCE hInstance, int nCmdShow);
    HWND GetHWnd() const { return m_hWnd; }

private:
    HWND m_hWnd = nullptr;
    static constexpr LPCWSTR WindowTitle = L"loveDX12";
    static constexpr int ClientWidth = 1280;
    static constexpr int ClientHeight = 720;

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};
