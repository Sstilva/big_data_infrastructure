# Файлик для удобства компиляции

mkdir compiled
g++ -std=c++20 -g -c database/database.cpp -o compiled/database.o
g++ -std=c++20 -g -c column/column.cpp -o compiled/column.o
g++ -std=c++20 -g -c table/table.cpp -o compiled/table.o
# gcc -c database/database_interfaces.hpp -o compiled/database_interfaces.o
g++ -std=c++20 -g main.cpp -o compiled/db compiled/database.o compiled/column.o compiled/table.o
