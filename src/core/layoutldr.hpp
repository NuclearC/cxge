// Cell Game Engine:
//   Copyright (c) 2017-2018 NuclearC

#ifndef CXGE_CORE_LAYOUTLDR_HPP_
#define CXGE_CORE_LAYOUTLDR_HPP_

#include <core\objectldr.hpp>

namespace cxge {
    namespace core {
        struct CXLayout {
            float width, height;

            std::string abs_path;
            size_t id;

            std::vector<std::shared_ptr<CXObject>> objects;
        };
    } // namespace core
} // namespace cxge

#endif // CXGE_CORE_LAYOUTLDR_HPP_
