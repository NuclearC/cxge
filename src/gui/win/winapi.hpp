// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#ifndef CXGE_GUI_WIN_WINAPI_HPP_
#define CXGE_GUI_WIN_WINAPI_HPP_

#include <string>
#include <Windows.h>

#include <gui/window.hpp>

namespace cxge {
    namespace gui {
        namespace win {
            class WinApiWindow
                : public Window {
                friend class DX11GraphicsContext;
            private:
                MSG msg;

                HINSTANCE hinstance;

                // window class
                WNDCLASSEX wc;

                static LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message,
                    WPARAM wParam, LPARAM lParam);
            public:
                // the native window handle
                HWND hwnd;

                WinApiWindow(const WindowDesc& _Desc) : Window(_Desc) {}
                ~WinApiWindow() override;

                bool initialize() override;
                bool show() override;
                bool update() override;
                bool close() override;

                bool poll_events() override;
            };
        } // namespace win
    } // namespace gui
} // namespace cxge

#endif // CXGE_GUI_WIN_WINAPI_HPP_
