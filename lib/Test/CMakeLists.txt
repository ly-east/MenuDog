add_executable(tester
  Registry/ResourceReader.cpp
)

add_test(NAME tester COMMAND tester)

target_include_directories(tester
  PUBLIC ${CMAKE_SOURCE_DIR}/include
  PUBLIC ${CMAKE_SOURCE_DIR}/third-party/gtest/include
  ${CMAKE_SOURCE_DIR}/third-party/ulog/include
)

target_link_libraries(tester
  MenuDogRegistry
  Qt::Core
  Qt::CorePrivate
  gtest
  gtest_main
  ulog
)
