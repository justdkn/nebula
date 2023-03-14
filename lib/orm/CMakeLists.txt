cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(orm)
add_library(orm STATIC
    src/model.cxx
    src/field_base.cxx
    src/type/uuid.cxx
    src/query_where.cxx
    src/transform.cxx
)
target_include_directories(orm
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(orm mdb)
