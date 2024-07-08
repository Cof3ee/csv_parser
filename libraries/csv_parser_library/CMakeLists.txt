add_library (csv_parser_library src/Table.cpp inc/Table.h src/CsvParserException.cpp inc/CsvParserException.h src/Expression.cpp inc/Expression.h)

target_include_directories(csv_parser_library PUBLIC inc)