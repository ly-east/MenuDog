set(HEADER_PATH ${CMAKE_SOURCE_DIR}/include/Registry)

add_library(MenuDogRegistry STATIC
  # headers
  ${HEADER_PATH}/ContextMenu.h
  ${HEADER_PATH}/ResourceReader.h

  # sources
  ResourceReader.cpp
)

target_include_directories(MenuDogRegistry PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(MenuDogRegistry
PRIVATE
  Qt::Core
  Qt::CorePrivate
  Qt::Gui
  ulog
)
