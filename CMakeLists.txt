cmake_minimum_required(VERSION 3.9)

PROJECT(ParticleOfLife)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
