add_executable(csv_parser main.cpp)

target_link_libraries(csv_parser PUBLIC csv_parser_library)

target_include_directories(csv_parser PUBLIC ../../libraries/csv_parser_library/inc)
