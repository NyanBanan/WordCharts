cmake_minimum_required(VERSION 3.27)
project(WordCharts)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)

qt_add_executable(WordCharts main.cpp)

qt_add_qml_module(WordCharts
        VERSION 6.2
        URI WordChartsQml
        QML_FILES
        SOURCES
)

target_link_libraries(WordCharts PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::Qml)
target_include_directories(WordCharts PUBLIC src)
