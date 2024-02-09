enable_testing(true)

find_package(Qt6 REQUIRED COMPONENTS Test Qml)

add_executable(testWordCharts src/word_streams/tests/TestFileWordStream.cpp src/word_streams/FileWordStream.cpp)

add_test(NAME testWordCharts COMMAND testWordCharts)

target_link_libraries(testWordCharts PRIVATE Qt6::Test Qt6::Qml)
