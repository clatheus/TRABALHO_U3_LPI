cmake_minimum_required(VERSION 3.19)
project(TrabalhoU3 LANGUAGES CXX)
include_directories(include)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(TRABALHO_U3_LPI
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    src/mainwindow.ui
    include/Cidades.h
    src/Cidades.cpp
    include/Gerenciador.h
    src/Gerenciador.cpp
    include/Passageiros.h
    src/Passageiros.cpp
    include/Trajetos.h
    src/Trajetos.cpp
    include/Transporte.h
    src/Transporte.cpp
    src/Viagem.cpp
    include/Viagem.h
)

target_link_libraries(TRABALHO_U3_LPI
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS TRABALHO_U3_LPI
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TRABALHO_U3_LPI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
