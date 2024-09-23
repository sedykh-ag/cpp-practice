cmake_minimum_required(VERSION 3.11)

project(ideal)

add_executable(ideal src/ideal.cpp)

target_include_directories(ideal PUBLIC include/)

enable_testing()

set(TESTS ${CMAKE_SOURCE_DIR}/tests)

file(GLOB testfiles "${TESTS}/*.dat")

foreach(file ${testfiles})
  add_test(
    NAME ${file}
    COMMAND ${CMAKE_COMMAND} -E env python ${CMAKE_SOURCE_DIR}/runtest.py ./ideal${SUFFIX} ${file}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:ideal>
  )
  set_tests_properties(${file} PROPERTIES DEPENDS ideal)
endforeach()
