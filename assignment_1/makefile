.PHONY: all
all: valgrind gdb inlining locality data_dependency indirect_addressing io

valgrind: src/valgrind0.c src/valgrind1.c src/valgrind2.c src/valgrind3.c
	gcc -O0 -g -o ./target/valgrind0 src/valgrind0.c
	gcc -O0 -g -o ./target/valgrind1 src/valgrind1.c
	gcc -O0 -g -o ./target/valgrind2 src/valgrind2.c
	gcc -O0 -g -o ./target/valgrind3 src/valgrind3.c

gdb: src/gdb.c
	gcc -O0 -g -o ./target/gdb src/gdb.c

inlining: src/same_file.c ./src/different_file.c ./src/different_file_mul.c
	gcc -O2 src/same_file.c -o ./target/same_file
	gcc -O2 src/different_file.c src/different_file_mul.c -o ./target/different_file
	gcc -O2 ./src/inlined_manually.c -o ./target/inlined_manually

locality: ./src/locality.c
	gcc -O0 ./src/locality.c -o ./target/locality_O0
	gcc -O2 ./src/locality.c -o ./target/locality_O2
	gcc -O2 -march=native ./src/locality.c -o ./target/locality_O2_native

data_dependency: ./src/data_dependency.c
	gcc -O0 ./src/data_dependency.c -o ./target/data_dependency_O0
	gcc -O2 ./src/data_dependency.c -o ./target/data_dependency_O2
	gcc -O2 -march=native ./src/data_dependency.c -o ./target/data_dependency_O2_native

indirect_addressing: ./src/indirect_addressing.c
	gcc -O0 ./src/indirect_addressing.c -o ./target/indirect_addressing_O0
	gcc -O2 ./src/indirect_addressing.c -o ./target/indirect_addressing_O2
	gcc -O2 -march=native ./src/indirect_addressing.c -o ./target/indirect_addressing_O2_native

io: ./src/io.c
	gcc -O2 ./src/io.c -o ./target/io_O2
