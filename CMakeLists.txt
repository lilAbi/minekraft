cmake_minimum_required(VERSION 3.28)
project(minekraft)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(CMAKE_HOST_SYSTEM MATCHES Apple)
    add_link_options("-Wl,-no_compact_unwind")
endif()

include_directories(./bindings)
include_directories(src)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(glad REQUIRED)
find_package(entt REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)
find_package(FastNoise2 REQUIRED)
find_package(absl REQUIRED)

include_directories(
        ${glfw3_INCLUDE_DIR}
        ${glad_INCLUDE_DIR}
        ${imgui_INCLUDE_DIR}
        ${EnTT_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}
        ${spdlog_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        ${FastNoise2_INCLUDE_DIR}
        ${absl_INCLUDE_DIR}
)

file(GLOB sources CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.h")

add_executable(minekraft ${sources})

target_link_libraries(minekraft PUBLIC
        imgui::imgui
        glfw
        glad::glad
        EnTT::EnTT
        glm::glm
        spdlog::spdlog
        boost::boost
        FastNoise2::FastNoise
        abseil::abseil
)
