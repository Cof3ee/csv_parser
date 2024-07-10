add_executable(csv_parser_tests Table_tests.cpp Expression_tests.cpp CsvParserException_tests.cpp)

target_link_libraries(csv_parser_tests PUBLIC GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(csv_parser_tests)

target_link_libraries(csv_parser_tests PUBLIC csv_parser_library)

target_include_directories(csv_parser_tests PUBLIC ../../libraries/csv_parser_library/inc)