# !/bin/sh

make &&
printf "\nvalgrind0:\n\n----------\n" && valgrind --leak-check=yes ./target/valgrind0;
printf "\nvalgrind1:\n\n----------\n" && valgrind --leak-check=yes ./target/valgrind1;
printf "\nvalgrind2:\n\n----------\n" && valgrind --leak-check=yes ./target/valgrind2;
printf "\nvalgrind3:\n\n----------\n" && valgrind --leak-check=yes ./target/valgrind3;
printf "\gdb:\n\n----------\n" && gdb ./target/gdb;
