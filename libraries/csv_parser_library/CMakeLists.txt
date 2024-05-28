add_library (csv_parser_library src/Table.cpp inc/Table.h src/MyException.cpp inc/MyException.h)

target_include_directories(csv_parser_library PUBLIC inc)