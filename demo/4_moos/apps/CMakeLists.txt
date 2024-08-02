cmake_minimum_required(VERSION 3.5)
project(moos-dawg-2024 CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(DCCL REQUIRED)
get_target_property(DCCL_INCLUDE_DIR dccl INTERFACE_INCLUDE_DIRECTORIES)

message("Using DCCL in ${DCCL_INCLUDE_DIR}")
include_directories("${DCCL_INCLUDE_DIR}")

set(PROTOS
  ${CMAKE_CURRENT_SOURCE_DIR}/../status.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/../updated_command.proto
  )

set(COMPILED_PROTOS
  ${CMAKE_CURRENT_BINARY_DIR}/status.pb.h
  ${CMAKE_CURRENT_BINARY_DIR}/status.pb.cc
  ${CMAKE_CURRENT_BINARY_DIR}/updated_command.pb.h
  ${CMAKE_CURRENT_BINARY_DIR}/updated_command.pb.cc
)

add_custom_command(OUTPUT ${COMPILED_PROTOS}
  COMMAND protoc
  ARGS --cpp_out ${CMAKE_CURRENT_BINARY_DIR} --dccl_out ${CMAKE_CURRENT_BINARY_DIR}  ${PROTOS} -I ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(pCommand command.cpp ${COMPILED_PROTOS})
target_link_libraries(pCommand MOOS dccl)

add_executable(pStatus status.cpp ${COMPILED_PROTOS})
target_link_libraries(pStatus MOOS dccl)
