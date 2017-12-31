// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#include <core\objectldr.hpp>

namespace cxge {
    namespace core {
        void ObjectLoader::load_from_file(std::string _Path, CXObject& res)
        {
            std::ifstream in_file(_Path);
            nlohmann::json obj;
            obj << in_file;
            in_file.close();

            res.abs_path = _Path;
            res.id = obj["object"]["id"].get<size_t>();
            res.texture = obj["object"]["texture"].get<std::string>();
            res.name = obj["object"]["name"].get<std::string>();
            
            if (obj["object"]["size"].is_object()) {
                res.width = obj["object"]["size"]["x"].get<float>();
                res.height = obj["object"]["size"]["y"].get<float>();
            }
        }
    } // namespace core
} // namespace cxge
