.PHONY: all
all: stack_alloc heap_alloc reducing_memory_fragmentation_1 reducing_memory_fragmentation_2 writing_to_files reading_from_files parse_args benchmarking

stack_alloc: src/stack_alloc.c
	gcc -o ./target/stack_alloc src/stack_alloc.c

heap_alloc: src/heap_alloc.c
	gcc -o ./target/heap_alloc src/heap_alloc.c

reducing_memory_fragmentation_1: src/reducing_memory_fragmentation_1.c
	gcc -o ./target/reducing_memory_fragmentation_1 src/reducing_memory_fragmentation_1.c

reducing_memory_fragmentation_2: src/reducing_memory_fragmentation_2.c
	gcc -o ./target/reducing_memory_fragmentation_2 src/reducing_memory_fragmentation_2.c

writing_to_files: src/writing_to_files.c
	gcc -o ./target/writing_to_files src/writing_to_files.c

reading_from_files: src/reading_from_files.c
	gcc -o ./target/reading_from_files src/reading_from_files.c

parse_args: src/parse_args.c
	gcc -o ./target/parse_args src/parse_args.c

benchmarking: src/benchmarking.c
	gcc -O0 -o ./target/benchmarkingO0 src/benchmarking.c
	gcc -O1 -o ./target/benchmarkingO1 src/benchmarking.c
	gcc -O2 -o ./target/benchmarkingO2 src/benchmarking.c
	gcc -O3 -o ./target/benchmarkingO3 src/benchmarking.c
	gcc -Os -o ./target/benchmarkingOs src/benchmarking.c
	gcc -Og -o ./target/benchmarkingOg src/benchmarking.c
