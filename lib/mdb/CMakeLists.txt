cmake_minimum_required(VERSION 3.1)


project(mdb)
add_library(mdb STATIC
    src/statment.cxx
    src/driver.cxx
)
target_include_directories(mdb
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    /usr/local/mysql/include
)
target_link_directories(
    mdb
    PUBLIC
    /usr/local/mysql/lib
)

target_link_libraries(mdb mysqlclient)
