cmake_minimum_required(VERSION 3.10)
project (file_utils)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HDRS
  file_utils.h
  tests/file_utils_tests.h
  tests/test_assert.h
)

set(SRCS
  tests/file_utils_tests.cpp
  tests/test.cpp
  tests/test_assert.cpp
)

add_executable(file_utils_tests ${HDRS} ${SRCS})
source_group("Header Files" FILES ${HDRS})
source_group("Source Files" FILES ${SRCS})
