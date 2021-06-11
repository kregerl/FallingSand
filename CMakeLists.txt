cmake_minimum_required(VERSION 3.19)
project(OpenGLFallingSand)

set(CMAKE_CXX_STANDARD 14)
set(linkers -lglfw -lGL -lX11 -lpthread -lXrandr -ldl)
include_directories(include)

add_executable(OpenGLFallingSand src/main.cpp src/main.h src/glad.c src/util/screen.cpp src/util/screen.h src/util/shader.h src/entity/entity.cpp src/entity/entity.h src/world.cpp src/world.h src/entity/sand.cpp src/entity/sand.h src/entity/water.cpp src/entity/water.h src/entity/rock.cpp src/entity/rock.h src/util/util.h src/entity/wood.cpp src/entity/wood.h src/entity/fire.cpp src/entity/fire.h)
target_link_libraries(OpenGLFallingSand ${linkers})
