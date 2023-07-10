cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME "SDL_Project")
project(${PROJECT_NAME})



# Add the C++17 standard flag
set(CMAKE_CXX_STANDARD 17)

# Set the path to SDL2 and libs
set(SDL2_DIR "libs/SDL2/cmake")
set(sdl2_image_DIR "libs/SDL2_image/cmake")
set(sdl2_mixer_DIR "libs/SDL2_mixer/cmake")
set(sdl2_ttf_DIR "libs/SDL2_ttf/cmake")

add_subdirectory("libs/glew/build/cmake")
add_subdirectory("libs/glfw")
add_subdirectory("libs/glm")

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Find SDL2_image package
find_package(sdl2_image REQUIRED)

# Find SDL2_mixer package
find_package(sdl2_mixer REQUIRED)

# Find SDL2_ttf package
find_package(sdl2_ttf REQUIRED)

# Set the path to your source files
set(SOURCE_DIR src)

# Add all source files from the 'src' directory
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Add the search include directory for ${PROJECT_NAME} target
target_include_directories(${PROJECT_NAME} PRIVATE libs/glew/include)

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Link additional libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf glew glfw glm)


# Set the source and destination directories
set(destination_dir "${CMAKE_BINARY_DIR}/Debug")
set(source_dir_bin "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(source_dir_res "${CMAKE_CURRENT_SOURCE_DIR}/res")

# Create a custom command to copy files
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${source_dir_bin}"
            "${destination_dir}"
    COMMENT "Copying files from ${source_dir_bin} to ${destination_dir}"
)

# Create a custom command to copy files
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${source_dir_res}"
            "${destination_dir}"
    COMMENT "Copying files from ${source_dir_res} to ${destination_dir}"
)