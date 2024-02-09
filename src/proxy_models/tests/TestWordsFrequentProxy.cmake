enable_testing(true)

find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(testWordsFrequentProxy src/WordData.cpp src/proxy_models/tests/TestWordsFrequentProxy.cpp src/proxy_models/WordsFrequentProxy.cpp)

add_test(NAME testWordsFrequentProxy COMMAND testWordsFrequentProxy)

target_link_libraries(testWordsFrequentProxy PRIVATE Qt6::Test)
