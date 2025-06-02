cmake_minimum_required(VERSION 3.19)
project(ProjektMenedzerKursow LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(ProjektMenedzerKursow
    WIN32 MACOSX_BUNDLE
    main.cpp
    loginwindow.cpp
    loginwindow.h
    loginwindow.ui
    adminwindow.h adminwindow.cpp adminwindow.ui
    studentwindow.h studentwindow.cpp studentwindow.ui
)

target_link_libraries(ProjektMenedzerKursow
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS ProjektMenedzerKursow
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ProjektMenedzerKursow
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
add_subdirectory(BusinessLogic)
