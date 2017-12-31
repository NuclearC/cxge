// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#include "core/cxge.hpp"

namespace cxge {
    namespace core {
        int _main(int argc, char * argv[]) {
            if (argc < 2)
                return -1;

            CXDesc desc = {};

            for (int i = 0; i < argc; i++) {
                if (!strncmp(argv[i], "--debug", 7))
                    desc.is_debug = true;
                if (!strncmp(argv[i], "--inzip", 7))
                    desc.input_file = argv[i + 1];
                if (!strncmp(argv[i], "--in", 4))
                    desc.input_directory = argv[i + 1];
            }

            CXApplication app(desc);

            app.run();

            return 0;
        }

        CXApplication::CXApplication(const CXDesc & _Desc) : desc(_Desc)
        {
            if (_Desc.input_file.empty()) {
                std::ifstream infile(_Desc.input_directory + "/config.json");
                config_file << infile;
                infile.close();
            }

            // don't catch expections so application will crash anyway
            // if it wont be able to read field

            config = {};
            config.type = config_file["application"]["type"].get<std::string>();
            config.type_enum = config_file["application"]["typeEnum"].get<int>();
            config.name = config_file["application"]["name"].get<std::string>();
            config.src_dir = 
                config_file["application"]["sourceDirectory"].get<std::string>();
            config.object_dir =
                config_file["application"]["objectDirectory"].get<std::string>();
            config.entry_file =
                config_file["application"]["Entry"]["entryFile"].get<std::string>();
            config.entry_function =
                config_file["application"]["Entry"]["entryFunction"].get<std::string>();
            config.window_width =
                config_file["application"]["UserInterface"]["windowWidth"].get<uint16_t>();
            config.window_height =
                config_file["application"]["UserInterface"]["windowHeight"].get<uint16_t>();
        }

        void CXApplication::run()
        {
            is_running = true;

            auto win_desc = gui::WindowDesc{
                config.name,
                "GXWindow",
                config.window_width,
                config.window_height,
                true
            };

            gui::win::WinApiWindow window(win_desc);

            auto gx_desc = graphics::GraphicsContextDesc{
                &window, win_desc.width, win_desc.height, true, true};

            graphics::win::DX11GraphicsContext ctx(gx_desc);

            CXObject obj;
            obj.gx_object = std::make_unique<graphics::win::DX11GraphicsObject2D>(&ctx);

            ObjectLoader::load_from_file(desc.input_directory + "/" + 
                config.object_dir + "/test.json", obj);

            obj.gx_object->load_texture(desc.input_directory + "/" + obj.texture);

            window.initialize();
            window.show();
            window.update();

            ctx.initialize();

            float clear_color [4] = { 0.0f, 0.0f, 0.0f, 1.0f };
            while (is_running) {
                is_running = window.poll_events();
                ctx.begin(clear_color);
                obj.gx_object->draw();
                ctx.end();
            }

            ctx.release();
            return;
        }
    } // namespace core
} // namespace cxge
