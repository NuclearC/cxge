// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#ifndef CXGE_GRAPHICS_GRAPHICS_HPP_
#define CXGE_GRAPHICS_GRAPHICS_HPP_

#include <string>

#include <gui/window.hpp>

namespace cxge {
    namespace graphics {
        struct GraphicsContextDesc {
            // pointer to the target window
            gui::Window* wnd_ptr;

            int backbuffer_width, backbuffer_height;

            bool windowed, vsync;
        };

        class GraphicsContext {
        protected:
            GraphicsContextDesc desc;

        public:
            GraphicsContext(const GraphicsContextDesc& _Desc)
                : desc(_Desc) {}
            virtual ~GraphicsContext() { release(); }

            virtual bool initialize() = 0;
            virtual void begin(float clear_color[]) = 0;
            virtual void end() = 0;
            virtual void release() {}
        };

        template <typename _T>
        struct Vector2D {
            _T x, y;
        };

        class GraphicsObject2D {
        protected:
            GraphicsContext * context;
        public:
            GraphicsObject2D(GraphicsContext* _Context) : context(_Context) {
                initialize();
            }
            virtual ~GraphicsObject2D() { 
                release(); 
            }

            virtual bool initialize() { return true; }

            virtual bool load_texture(std::string filename) = 0;
            virtual bool load_texture(std::wstring wfilename) = 0;
            virtual bool load_texture(const void* buf, size_t len) = 0;

            virtual void draw() = 0;

            virtual void release() {}

            virtual Vector2D<uint32_t> get_texture_size() = 0;

            virtual void set_position(float x, float y) = 0;
            virtual void set_rotation(float x, float y) = 0;
            virtual void set_origin(float x, float y) = 0;
            virtual void set_scale(float x, float y) = 0;
            virtual void set_source_rectangle(const Vector2D<long>& upper,
                const Vector2D<long>& lower) = 0;

            virtual Vector2D<float> get_position() const = 0;
            virtual Vector2D<float> get_rotation() const = 0;
            virtual Vector2D<float> get_origin() const = 0;
            virtual Vector2D<float> get_scale() const = 0;
            virtual Vector2D<long> get_source_rect_upper() const = 0;
            virtual Vector2D<long> get_source_rect_lower() const = 0;

            virtual float get_rotation_x() const = 0;
            virtual float get_scale_x() const = 0;
        };
    } // namespace graphics
} // namespace cxge

#endif // CXGE_GRAPHICS_GRAPHICS_HPP_
