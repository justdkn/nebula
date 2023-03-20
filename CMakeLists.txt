cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

project(nebula)
add_executable(nebula
    src/main.cxx
    src/common/db.cxx
    src/logic/file_logic.cxx
    src/models/file.cxx
)
target_link_libraries(nebula
    PRIVATE
    mdb
    orm
    dotenv
)
file(COPY .env DESTINATION ${PROJECT_BINARY_DIR})