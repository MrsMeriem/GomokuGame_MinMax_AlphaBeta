# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(Gomoku)

# Add the executable
add_executable(Gomoku main.c)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -lm>)

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lm ${LIBS})
# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Define a custom target to run the program after compilation
add_custom_target(run
    COMMAND Gomoku
    DEPENDS Gomoku
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

