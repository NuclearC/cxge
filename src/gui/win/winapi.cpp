// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#include <gui/win/winapi.hpp>

namespace cxge {
    namespace gui {
        namespace win {
            LRESULT CALLBACK WinApiWindow::WindowProcess(HWND hWnd, UINT message,
                WPARAM wParam, LPARAM lParam)
            {
                switch (message)
                {
                case WM_DESTROY:
                    PostQuitMessage(0);
                    return 0;
                    break;
                }

                return DefWindowProc(hWnd, message, wParam, lParam);
            }

            WinApiWindow::~WinApiWindow()
            {
            }

            bool WinApiWindow::initialize()
            {
                hinstance = GetModuleHandle(0);

                // c++ version of ZeroMemory :P
                wc = {};

                // fill in the struct with the needed information
                wc.cbSize = sizeof(WNDCLASSEX);
                wc.style = CS_HREDRAW | CS_VREDRAW;
                wc.lpfnWndProc = WindowProcess;
                wc.hInstance = hinstance;
                wc.hCursor = LoadCursor(0, IDC_ARROW);
                wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
                wc.lpszClassName = desc.window_class.c_str();

                // register the window class
                RegisterClassEx(&wc);

                // calculate client size of the window
                RECT wr = { 0,0,desc.width, desc.height };

                AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

                int window_x = 300, window_y = 300,
                    window_width = wr.right - wr.left, 
                    window_height = wr.bottom - wr.top;
                if (desc.centered) {
                    RECT desktop_rect;
                    GetWindowRect(GetDesktopWindow(), &desktop_rect);
                    window_x = desktop_rect.right / 2 - window_width / 2;
                    window_y = desktop_rect.bottom / 2 - window_height / 2;
                }

                hwnd = CreateWindowEx(
                    0,
                    desc.window_class.c_str(),
                    desc.window_title.c_str(),
                    WS_OVERLAPPEDWINDOW,
                    window_x, window_y,
                    wr.right - wr.left, wr.bottom - wr.top,
                    0, 0, hinstance, 0);

                if (!hwnd)
                    return false;

                return true;
            }

            bool WinApiWindow::show()
            {
                return ShowWindow(hwnd, SW_SHOW);
            }

            bool WinApiWindow::update()
            {
                return UpdateWindow(hwnd);
            }

            bool WinApiWindow::close()
            {
                return CloseWindow(hwnd);
            }
            bool WinApiWindow::poll_events()
            {
                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);

                    if (msg.message == WM_QUIT)
                        return false;
                }
                return true;
            }
        } // namespace win
    } // namespace gui
} // namespace cxge
