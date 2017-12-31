cmake_minimum_required(VERSION 2.6)
project (CXGE)

file(GLOB CXGE_APP_FILES 
${PROJECT_SOURCE_DIR}/src/app/*.*
)

file(GLOB CXGE_CORE_FILES 
${PROJECT_SOURCE_DIR}/src/core/*.*
)

if (WIN32)
file(GLOB CXGE_GUI_FILES 
${PROJECT_SOURCE_DIR}/src/gui/*.*
${PROJECT_SOURCE_DIR}/src/gui/win/*.*
)
else()
file(GLOB CXGE_GUI_FILES 
${PROJECT_SOURCE_DIR}/src/gui/*.*
${PROJECT_SOURCE_DIR}/src/gui/unix/*.*
)
endif()

if (WIN32)
file(GLOB CXGE_GX_FILES 
${PROJECT_SOURCE_DIR}/src/graphics/*.*
${PROJECT_SOURCE_DIR}/src/graphics/directx/*.*
${PROJECT_SOURCE_DIR}/src/graphics/vulkan/*.*
)
else()
file(GLOB CXGE_GX_FILES 
${PROJECT_SOURCE_DIR}/src/graphics/*.*
${PROJECT_SOURCE_DIR}/src/graphics/vulkan/*.*
)
endif()

set(EXTRA_LIBS ${EXTRA_LIBS} CXcore CXgui CXgx vulkan-1 VKstatic.1)

set(JSON_DIR "" CACHE PATH "Path to JSON include files")
set(DXTK_INCLUDE_DIR "" CACHE PATH "Path to DirectXTK include files")
set(DXTK_LIBRARY_DIR "" CACHE PATH "Path to DirectXTK library files")
set(VK_INCLUDE_DIR "" CACHE PATH "Path to Vulkan include files")
set(VK_LIBRARY_DIR "" CACHE PATH "Path to Vulkan library files")

link_directories(${VK_LIBRARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${JSON_DIR})
include_directories(${DXTK_INCLUDE_DIR})
include_directories(${VK_INCLUDE_DIR})

add_library(CXcore ${CXGE_CORE_FILES})
add_library(CXgui ${CXGE_GUI_FILES})
add_library(CXgx ${CXGE_GX_FILES})
add_executable(CXGE ${CXGE_APP_FILES})
target_link_libraries(CXGE ${EXTRA_LIBS})

if (WIN32)
target_link_libraries(CXGE d3d11.lib dxgi.lib)
target_link_libraries(CXGE debug ${DXTK_LIBRARY_DIR}/Debug/DirectXTK.lib)
target_link_libraries(CXGE optimized ${DXTK_LIBRARY_DIR}/Release/DirectXTK.lib)
endif()