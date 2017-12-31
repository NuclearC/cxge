// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#ifndef CXGE_GUI_WINDOW_HPP_
#define CXGE_GUI_WINDOW_HPP_

#include <string>

namespace cxge {
    namespace gui {
        struct WindowDesc
        {
            std::string window_title,
                window_class;

            uint16_t width, height;

            bool centered = false;
        };

        class Window {
        protected:
            WindowDesc desc;

        public:
            Window(const WindowDesc& _Desc)
                : desc(_Desc) {}
            virtual ~Window() {}

            virtual bool initialize() = 0;
            virtual bool show() = 0;
            virtual bool update() = 0;
            virtual bool close() = 0;

            virtual bool poll_events() = 0;
        };
    } // namespace gui
} // namespace cxge

#endif // CXGE_GUI_WINDOW_HPP_
