cmake_minimum_required(VERSION 3.1)

project(dotenv)
add_library(dotenv STATIC
    src/dotenv.cxx
)
target_include_directories(dotenv
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
