#include "WindowManager.h"

bool WindowManager::Initialize(HINSTANCE hInstance, int nCmdShow) {
    // ウィンドウクラス登録
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = L"GAME_WINDOW";

    if (!RegisterClassEx(&wc)) {
        return false;
    }

    // ウィンドウサイズ調整
    RECT rect = { 0, 0, ClientWidth, ClientHeight };
    DWORD style = WS_OVERLAPPEDWINDOW;
    AdjustWindowRect(&rect, style, FALSE);

    int posX = (GetSystemMetrics(SM_CXSCREEN) - ClientWidth) / 2;
    int posY = (GetSystemMetrics(SM_CYSCREEN) - ClientHeight) / 2;
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // ウィンドウ生成
    m_hWnd = CreateWindowEx(
        0, L"GAME_WINDOW", WindowTitle,
        style, posX, posY, width, height,
        nullptr, nullptr, hInstance, nullptr);

    if (!m_hWnd) return false;

    ShowWindow(m_hWnd, nCmdShow);
    return true;
}

LRESULT CALLBACK WindowManager::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
}
