cmake_minimum_required(VERSION 3.11)

project(hw_cache)

enable_testing()

add_subdirectory(ideal)
add_subdirectory(lfu)

add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/compare_results.txt
  COMMAND ${CMAKE_COMMAND} -E env python ${CMAKE_SOURCE_DIR}/compare.py $<TARGET_FILE:ideal> $<TARGET_FILE:lfu>
  DEPENDS ideal lfu
)

add_custom_target(
  compare ALL
  DEPENDS ${CMAKE_SOURCE_DIR}/compare_results.txt
)

set(IDEAL_TESTS ${CMAKE_SOURCE_DIR}/ideal/tests)
set(LFU_TESTS ${CMAKE_SOURCE_DIR}/lfu/tests)

file(GLOB IDEAL_TEST_FILES "${IDEAL_TESTS}/*.dat")
file(GLOB LFU_TEST_FILES "${LFU_TESTS}/*.dat")

foreach(file ${IDEAL_TEST_FILES})
  add_test(
    NAME ${file}
    COMMAND ${CMAKE_COMMAND} -E env python ${CMAKE_SOURCE_DIR}/runtest.py $<TARGET_FILE:ideal> ${file}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:ideal>
  )
  set_tests_properties(${file} PROPERTIES DEPENDS ideal)
endforeach()

foreach(file ${LFU_TEST_FILES})
  add_test(
    NAME ${file}
    COMMAND ${CMAKE_COMMAND} -E env python ${CMAKE_SOURCE_DIR}/runtest.py $<TARGET_FILE:lfu> ${file}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:lfu>
  )
  set_tests_properties(${file} PROPERTIES DEPENDS lfu)
endforeach()
