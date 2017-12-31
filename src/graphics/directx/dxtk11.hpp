// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#ifndef CXGE_GRAPHICS_WIN_DXTK11_HPP_
#define CXGE_GRAPHICS_WIN_DXTK11_HPP_

#include <string>
#include <memory>

#include <gui/win/winapi.hpp>
#include <graphics/graphics.hpp>

#include <d3d11.h>
#include <d3d11_4.h>
#include <dxgi.h>
#include <dxgi1_6.h>

#include "SpriteBatch.h"
#include "SimpleMath.h"
#include "WICTextureLoader.h"

namespace cxge {
    namespace graphics {
        namespace win {
            class DX11GraphicsContext
                : public GraphicsContext
            {
                friend class DX11GraphicsObject2D;

            private:
                gui::win::WinApiWindow* wnd_ptr;

                IDXGISwapChain4* swap_chain;
                ID3D11Device5* dev;
                ID3D11DeviceContext4* dev_ctx;
                ID3D11RenderTargetView1* render_target_view;

                D3D11_VIEWPORT viewport;

                std::unique_ptr<DirectX::SpriteBatch> sprite_batch;
            public:
                DX11GraphicsContext(const GraphicsContextDesc& _Desc)
                    : GraphicsContext(_Desc) {}

                bool initialize() override;
                void begin(float clear_color[]) override;
                void end() override;
                void release() override;
            };

            class DX11GraphicsObject2D
                : public GraphicsObject2D
            {
            private:
                ID3D11Resource* resource;
                ID3D11ShaderResourceView1* texture;

                DX11GraphicsContext* dx_ctx;

                DirectX::SimpleMath::Vector2 dx_pos;
                DirectX::SimpleMath::Vector2 dx_scale;
                DirectX::SimpleMath::Vector2 dx_origin;
                DirectX::SimpleMath::Vector2 dx_rotation;

                RECT source_rect;

                Vector2D<uint32_t> texture_size;
            public:
                DX11GraphicsObject2D(GraphicsContext* _Context) :
                    GraphicsObject2D(_Context) {
                    dx_ctx = reinterpret_cast<DX11GraphicsContext*>(_Context);
                }

                bool initialize() override;

                bool load_texture(std::string filename) override;
                bool load_texture(std::wstring wfilename) override;
                bool load_texture(const void* buf, size_t len) override;

                void draw() override;

                void release() override;

                Vector2D<uint32_t> get_texture_size() override;

                void set_position(float x, float y) override;
                void set_rotation(float x, float y) override;
                void set_origin(float x, float y) override;
                void set_scale(float x, float y) override;
                void set_source_rectangle(const Vector2D<long>& upper,
                    const Vector2D<long>& lower) override;

                Vector2D<float> get_position() const override;
                Vector2D<float> get_rotation() const override;
                Vector2D<float> get_origin() const override;
                Vector2D<float> get_scale() const override;
                Vector2D<long> get_source_rect_upper() const override;
                Vector2D<long> get_source_rect_lower() const override;

                float get_scale_x() const override;
                float get_rotation_x() const override;
            };
        } // namespace win
    } // namespace graphics
} // namespace cxge

#endif // CXGE_GRAPHICS_WIN_DXTK11_HPP_
