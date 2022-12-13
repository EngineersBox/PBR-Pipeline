cmake_minimum_required(VERSION 3.10)

project(PBR_Pipeline VERSION 1.0)

# Debug
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CXXFLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include source content
file (GLOB_RECURSE PBR_Pipeline_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE PBR_Pipeline_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set (PBR_Pipeline_INCLUDE_DIRS "")
foreach (_headerFile ${PBR_Pipeline_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PBR_Pipeline_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES PBR_Pipeline_INCLUDE_DIRS)

# Mark executable
add_executable(PBR_Pipeline ${PBR_Pipeline_SOURCES})
target_include_directories(PBR_Pipeline PRIVATE ${PBR_Pipeline_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
target_include_directories(PBR_Pipeline PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(PBR_Pipeline PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(PBR_Pipeline PUBLIC ${OPENGL_LIBRARIES})

# GLFW 3
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(PBR_Pipeline PRIVATE glfw)

# GLAD
find_package(glad REQUIRED)
target_link_libraries(PBR_Pipeline PRIVATE glad::glad)

# GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(PBR_Pipeline PRIVATE glm::glm)

# ImGui
find_package(imgui CONFIG REQUIRED)
target_link_libraries(PBR_Pipeline PRIVATE imgui::imgui)

# spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(PBR_Pipeline PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# boost
find_package(Boost REQUIRED COMPONENTS filesystem iostreams)
if (NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
            INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()
if (NOT TARGET Boost::iostreams)
    add_library(Boost::iostreams IMPORTED INTERFACE)
    set_property(TARGET Boost::iostreams PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::iostreams PROPERTY
            INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()
target_link_libraries(PBR_Pipeline PRIVATE Boost::filesystem Boost::iostreams)

# libpng
find_package(libpng CONFIG REQUIRED)
target_link_libraries(PBR_Pipeline PRIVATE png_static)

# Bullet3
find_package(Bullet CONFIG REQUIRED)
target_link_libraries(PBR_Pipeline PRIVATE BulletSoftBody BulletDynamics BulletCollision Bullet3Common LinearMath)
target_link_directories(PBR_Pipeline PRIVATE ${BULLET_LIBRARY_DIRS})