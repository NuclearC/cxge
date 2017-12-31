// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#ifndef CXGE_CORE_OBJECTLDR_HPP_
#define CXGE_CORE_OBJECTLDR_HPP_

#include <string>
#include <fstream>

#include <json.hpp>

#include <graphics\graphics.hpp>

namespace cxge {
    namespace core {
        struct CXObject {
            std::unique_ptr<graphics::GraphicsObject2D> gx_object;

            std::string abs_path, name, texture;
            size_t id;

            float width, height;

            void reset() {
                gx_object->set_origin(0, 0);
                gx_object->set_position(0, 0);
                gx_object->set_rotation(0, 0);
                gx_object->set_scale(1, 1);
            }
        };

        class ObjectLoader {
        public:
            static void load_from_file(std::string _Path, CXObject& obj);
        };
    } // namespace core
} // namespace cxge

#endif // CXGE_CORE_OBJECTLDR_HPP_
