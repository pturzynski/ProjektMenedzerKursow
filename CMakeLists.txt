cmake_minimum_required(VERSION 3.19)
project(MenedzerKursow LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(BusinessLogic_BINARY_DIR ${CMAKE_BINARY_DIR}/BusinessLogic)
add_subdirectory(BusinessLogic ${BusinessLogic_BINARY_DIR})

qt_add_executable(MenedzerKursow
    WIN32 MACOSX_BUNDLE
    main.cpp



    loginwindow.h loginwindow.cpp loginwindow.ui
    studentwindow.h studentwindow.cpp studentwindow.ui
    adminwindow.h adminwindow.cpp adminwindow.ui


)

target_link_libraries(MenedzerKursow
    PRIVATE
        Qt::Core
        Qt::Widgets
        BusinessLogic
)

target_include_directories(MenedzerKursow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic
)

include(GNUInstallDirs)

install(TARGETS MenedzerKursow
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MenedzerKursow
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
