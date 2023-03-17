cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

project(nebula)
add_executable(nebula
    src/main.cxx
    src/db.cxx
    src/file_manager.cxx
    src/models/file_model.cxx
)
target_link_libraries(nebula
    PRIVATE
    mdb
    orm
    dotenv
)
file(COPY .env DESTINATION ${PROJECT_BINARY_DIR})