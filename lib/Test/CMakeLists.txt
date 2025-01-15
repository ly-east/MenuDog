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
PRIVATE
  Qt::Core
  Qt::CorePrivate
  Qt::Gui
PUBLIC
  MenuDogRegistry
  gtest
  gtest_main
  ulog
)
