// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#ifndef CXGE_CORE_CXGE_HPP_
#define CXGE_CORE_CXGE_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

#include <Windows.h>

#include <json.hpp>

#include <core\layoutldr.hpp>
#include <core\objectldr.hpp>

#include <gui/window.hpp>
#include <gui/win/winapi.hpp>
#include <graphics/directx/dxtk11.hpp>

namespace cxge {
    namespace core {
        struct CXDesc {
            std::string input_directory;
            std::string input_file;

            bool is_debug;
        };

        struct CXAppConfig {
            int type_enum;

            std::string type, name, src_dir, 
                entry_file, entry_function, object_dir;

            uint16_t window_width, window_height;
        };

        class CXApplication {
        private:
            CXDesc desc;
            nlohmann::json config_file;
            CXAppConfig config;

            bool is_running;
        public:
            CXApplication(const CXDesc& _Desc);

            void run();
        };

        int _main(int argc,char* argv[]);
    } // namespace core
} // namespace cxge

#endif // CXGE_CORE_CXGE_HPP_
