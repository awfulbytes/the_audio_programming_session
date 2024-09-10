##
# learning stuff
#
# @file
# @version 0.1

TARGET	= bin/test
SRC 	= $(wildcard src/*.c)
OBJ 	= $(patsubst src/%.c, obj/%.o, $(SRC))

RED_BLD := \033[1;31m
NOC_BLD := \033[1;0m

default: $(TARGET)

clean:
	rm -rf obj/*.o
	rm -rf bin/*

bin_info: $(TARGET)
	@exec echo -e "$(RED_BLD)information of spitted binary file$(NOC_BLD)\n"
	@exec file bin/test
	@exec readelf -h bin/test

$(TARGET): $(OBJ)
	gcc -static -o $@ $? -lm

obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinc -Wno-implicit-function-declaration -g
# end
