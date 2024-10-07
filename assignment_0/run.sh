# !/bin/sh

make &&
printf "\nStack allocation:\n" && ./target/stack_alloc;
printf "\nHeap allocation:\n" && ./target/heap_alloc;
printf "\nMemory fragmentation 1:\n" && ./target/reducing_memory_fragmentation_1;
printf "\nMemory fragmentation 2:\n" && ./target/reducing_memory_fragmentation_2;
printf "\nWriting to file:\n" && ./target/writing_to_files;
printf "\nReading from file:\n" && ./target/reading_from_files;
printf "\nParsing arguments:\n" && ./target/parse_args -a10 -b2; ./parse_args -a2 -b2;
printf "\nComparing optimization levels:\n"
printf "\n-O0:\n" && ./target/benchmarkingO0;
printf "\n-O1:\n" && ./target/benchmarkingO1;
printf "\n-O2:\n" && ./target/benchmarkingO2;
printf "\n-O3:\n" && ./target/benchmarkingO3;
printf "\n-Os:\n" && ./target/benchmarkingOs;
printf "\n-Og:\n" && ./target/benchmarkingOg;
