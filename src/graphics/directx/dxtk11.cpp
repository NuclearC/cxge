// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#include <graphics/directx/dxtk11.hpp>

namespace cxge {
    namespace graphics {
        namespace win {
            bool DX11GraphicsContext::initialize()
            {
                wnd_ptr = reinterpret_cast<gui::win::WinApiWindow*>(desc.wnd_ptr);

                if (!wnd_ptr)
                    return false;

                HRESULT hr;
                DXGI_MODE_DESC mode_desc = {};
                mode_desc.Width = desc.backbuffer_width;
                mode_desc.Height = desc.backbuffer_height;
                mode_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                mode_desc.RefreshRate.Denominator = 1;
                mode_desc.RefreshRate.Numerator = 60;
                mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
                mode_desc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED;

                DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};

                swap_chain_desc.BufferDesc = mode_desc;
                swap_chain_desc.SampleDesc.Count = 1;
                swap_chain_desc.SampleDesc.Quality = 0;
                swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                swap_chain_desc.BufferCount = 1;
                swap_chain_desc.OutputWindow = wnd_ptr->hwnd;
                swap_chain_desc.Windowed = desc.windowed;
                swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

                assert((hr = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0,
                    D3D11_SDK_VERSION, &swap_chain_desc, (IDXGISwapChain**)&swap_chain, (ID3D11Device**)&dev, 0, (ID3D11DeviceContext**)&dev_ctx)) >= 0);

                ID3D11Texture2D1* back_buffer;
                assert((hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D1), (void**)&back_buffer)) >= 0);

                assert((hr = dev->CreateRenderTargetView(back_buffer, 0, (ID3D11RenderTargetView**)&render_target_view)) >= 0);
                back_buffer->Release();

                dev_ctx->OMSetRenderTargets(1, (ID3D11RenderTargetView**)&render_target_view, 0);

                viewport.Width = desc.backbuffer_width;
                viewport.Height = desc.backbuffer_height;
                viewport.MaxDepth = 1.0f;
                viewport.MinDepth = 0.0f;
                viewport.TopLeftX = 0.0f;
                viewport.TopLeftY = 0.0f;

                dev_ctx->RSSetViewports(1, &viewport);

                sprite_batch = std::make_unique<DirectX::SpriteBatch>(dev_ctx);

                return true;
            }
            void DX11GraphicsContext::begin(float clear_color[])
            {
                dev_ctx->ClearRenderTargetView(render_target_view, clear_color);

                sprite_batch->Begin();
            }
            void DX11GraphicsContext::end()
            {
                sprite_batch->End();

                swap_chain->Present(desc.vsync, 0);
            }
            void DX11GraphicsContext::release()
            {
                swap_chain->Release();
                dev->Release();
                dev_ctx->Release();
            }

            bool DX11GraphicsObject2D::initialize()
            {
                return true;
            }

            bool DX11GraphicsObject2D::load_texture(std::string filename)
            {
                wchar_t* wfilename;
                auto size_needed = MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), filename.length(), 0, 0);
                wfilename = new wchar_t[size_needed + 1];

                MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), filename.length(), wfilename, size_needed);
                wfilename[size_needed] = 0;

                DirectX::CreateWICTextureFromFile(
                    (ID3D11Device*)dx_ctx->dev,
                    wfilename,
                    &resource,
                    (ID3D11ShaderResourceView**)&texture);

                ID3D11Texture2D1* texture = (ID3D11Texture2D1*)resource;

                D3D11_TEXTURE2D_DESC1 desc;

                texture->GetDesc1(&desc);

                texture_size.x = desc.Width;
                texture_size.y = desc.Height;

                return true;
            }

            bool DX11GraphicsObject2D::load_texture(std::wstring wfilename)
            {
                DirectX::CreateWICTextureFromFile(
                    (ID3D11Device*)dx_ctx->dev,
                    wfilename.c_str(),
                    &resource,
                    (ID3D11ShaderResourceView**)&texture);

                ID3D11Texture2D1* texture = (ID3D11Texture2D1*)resource;

                D3D11_TEXTURE2D_DESC1 desc;

                texture->GetDesc1(&desc);

                texture_size.x = desc.Width;
                texture_size.y = desc.Height;

                source_rect.left = 0;
                source_rect.right = desc.Width;
                source_rect.top = 0;
                source_rect.bottom = desc.Height;

                return true;
            }

            bool DX11GraphicsObject2D::load_texture(const void * buf, size_t len)
            {
                DirectX::CreateWICTextureFromMemory(
                    (ID3D11Device*)dx_ctx->dev,
                    (const uint8_t*)buf, len,
                    &resource,
                    (ID3D11ShaderResourceView**)&texture);

                ID3D11Texture2D1* texture = (ID3D11Texture2D1*)resource;

                D3D11_TEXTURE2D_DESC1 desc;

                texture->GetDesc1(&desc);

                texture_size.x = desc.Width;
                texture_size.y = desc.Height;

                return true;
            }

            void DX11GraphicsObject2D::draw()
            {
                dx_ctx->sprite_batch->Draw(texture, dx_pos, &source_rect, DirectX::Colors::White,
                    dx_rotation.x, dx_origin, dx_scale);
            }

            void DX11GraphicsObject2D::release()
            {
                resource->Release();
                texture->Release();
            }

            Vector2D<uint32_t> DX11GraphicsObject2D::get_texture_size()
            {
                return texture_size;
            }

            void DX11GraphicsObject2D::set_position(float x, float y)
            {
                dx_pos.x = x;
                dx_pos.y = y;
            }

            void DX11GraphicsObject2D::set_rotation(float x, float y)
            {
                dx_rotation.x = x;
                dx_rotation.y = y;
            }

            void DX11GraphicsObject2D::set_origin(float x, float y)
            {
                dx_origin.x = x;
                dx_origin.y = y;
            }

            void DX11GraphicsObject2D::set_scale(float x, float y)
            {
                dx_scale.x = x;
                dx_scale.y = y;
            }

            void DX11GraphicsObject2D::set_source_rectangle(const Vector2D<long>& upper,
                const Vector2D<long>& lower)
            {
                source_rect.left = upper.x;
                source_rect.top = upper.y;
                source_rect.right = lower.x;
                source_rect.bottom = lower.y;
            }

            Vector2D<float> DX11GraphicsObject2D::get_position() const
            {
                return { dx_pos.x, dx_pos.y };
            }

            Vector2D<float> DX11GraphicsObject2D::get_rotation() const
            {
                return { dx_rotation.x, dx_rotation.y };
            }

            Vector2D<float> DX11GraphicsObject2D::get_origin() const
            {
                return { dx_origin.x, dx_origin.y };
            }

            Vector2D<float> DX11GraphicsObject2D::get_scale() const
            {
                return { dx_scale.x, dx_scale.y };
            }
            Vector2D<long> DX11GraphicsObject2D::get_source_rect_upper() const
            {
                return { source_rect.left, source_rect.top };
            }
            Vector2D<long> DX11GraphicsObject2D::get_source_rect_lower() const
            {
                return { source_rect.right, source_rect.bottom };
            }
            float DX11GraphicsObject2D::get_scale_x() const
            {
                return dx_scale.x;
            }
            float DX11GraphicsObject2D::get_rotation_x() const
            {
                return dx_rotation.x;
            }
        } // namespace win
    } // namespace graphics
} // namespace cxge

