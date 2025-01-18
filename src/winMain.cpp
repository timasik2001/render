

#include <iostream>
#include <windows.h>
#include <chrono>


#include <GameWindowBuffer.h>

class WindowStuff
{
public:
    bool running = true;
    BITMAPINFO bitmapInfo = { };
    GameWindowBuffer gameWindowBuffer = { };
};

WindowStuff windowStuff;




LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_CLOSE:
    {
        windowStuff.running = false;
        break;
    }
    case WM_SIZE:
    {

        windowStuff.gameWindowBuffer.ResetWindowBuffer(hwnd, &windowStuff.bitmapInfo);

        break;
    }
    case WM_PAINT:
    {
        //std::cout << uMsg;
        PAINTSTRUCT ps;
        HDC DeviceContext = BeginPaint(hwnd, &ps);
        HDC hdc = GetDC(hwnd);
        StretchDIBits(hdc,
            0, 0, windowStuff.gameWindowBuffer.w, windowStuff.gameWindowBuffer.h,
            0, 0, windowStuff.gameWindowBuffer.w, windowStuff.gameWindowBuffer.h,
            windowStuff.gameWindowBuffer.memory,
            &windowStuff.bitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY
        );

        ReleaseDC(hwnd, hdc);

        EndPaint(hwnd, &ps);
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int main()
{
    // Register the window class.

#pragma region creating window
    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "Sample Window Class";

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        wc.lpszClassName,                     // Window class
        "My window lmao",    // Window text
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,

        NULL,       // Parent window    
        NULL,       // Menu
        wc.hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

#pragma endregion


    windowStuff.gameWindowBuffer.ResetWindowBuffer(hwnd, &windowStuff.bitmapInfo);
    MSG msg = { };
    while (windowStuff.running)
    {

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        windowStuff.gameWindowBuffer.ClearWindow();
        SendMessage(hwnd, WM_PAINT, 0, 0);
        std::cout << windowStuff.gameWindowBuffer.h << ' ' << windowStuff.gameWindowBuffer.w << std::endl;

    }


    return 0;
}