find_package(Qt6 ${minQt6Version}  REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

if (POLICY CMP0087)
  cmake_policy(SET CMP0087 NEW)
endif (POLICY CMP0087)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/lib/UI/Layout)

qt_wrap_ui(UI_HEADERS
  ${CMAKE_SOURCE_DIR}/lib/UI/Layout/MenuDog.ui
)

qt_add_executable(MenuDog
  ${CMAKE_SOURCE_DIR}/include/UI/MenuDog.h
  ${CMAKE_SOURCE_DIR}/include/UI/LegacyMenu/LegacyMenuModel.h

  ${CMAKE_SOURCE_DIR}/lib/UI/LegacyMenu/LegacyMenuModel.cpp
  MenuDog.cpp
  main.cpp

  ${UI_HEADERS}

  ${CMAKE_SOURCE_DIR}/lib/UI/Resource/Loading.qrc
  ${CMAKE_SOURCE_DIR}/lib/UI/Resource/app.manifest
)

# Qt components

target_include_directories(MenuDog PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/third-party/ucrash/include
  ${CMAKE_SOURCE_DIR}/third-party/ulog/include
  ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(MenuDog PRIVATE
  ucrash
  ulog
  Qt::Gui
  Qt::Widgets
)
if(WIN32)
  SET_TARGET_PROPERTIES(MenuDog PROPERTIES
    LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" /SUBSYSTEM:WINDOWS"
  )
endif(WIN32)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set_property(TARGET MenuDog PROPERTY WIN32_EXECUTABLE true)
endif()

set(deploy_tool_options_arg "--pdb --no-opengl-sw")

# build handler before MenuDog
add_dependencies(MenuDog handler)

# set path to crash handler
set(HANDLER_WINDOW_PATH "${CMAKE_BINARY_DIR}/third-party/ucrash/third-party/crashpad/handler/${CMAKE_BUILD_TYPE}/handler")
if(WIN32)
  string(CONCAT HANDLER_WINDOW_PATH ${HANDLER_WINDOW_PATH} ".exe")
endif(WIN32)

qt_generate_deploy_app_script(
  TARGET MenuDog
  OUTPUT_SCRIPT deploy_script
  NO_TRANSLATIONS
  NO_COMPILER_RUNTIME
  NO_UNSUPPORTED_PLATFORM_ERROR
)

install(TARGETS MenuDog
    BUNDLE DESTINATION .
)

install(SCRIPT ${deploy_script})

install(FILES
  ${HANDLER_WINDOW_PATH}
  DESTINATION ${CMAKE_INSTALL_PREFIX}
)
