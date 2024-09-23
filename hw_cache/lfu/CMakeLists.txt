cmake_minimum_required(VERSION 3.11)

project(lfu)

add_executable(lfu src/lfu.cpp)

target_include_directories(lfu PUBLIC include/)

enable_testing()

set(TESTS ${CMAKE_SOURCE_DIR}/tests)

file(GLOB testfiles "${TESTS}/*.dat")

foreach(file ${testfiles})
  add_test(
    NAME ${file}
    COMMAND ${CMAKE_COMMAND} -E env python ${CMAKE_SOURCE_DIR}/runtest.py ./lfu${SUFFIX} ${file}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:lfu>
  )
  set_tests_properties(${file} PROPERTIES DEPENDS lfu)
endforeach()
