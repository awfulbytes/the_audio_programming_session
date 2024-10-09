##
# learning stuff
#
# @file
# @version 0.1

TARGET	= bin/test
SRC 	= $(wildcard src/*.c)
OBJ 	= $(patsubst src/%.c, obj/%.o, $(SRC))
FZOBJ 	= $(patsubst src/%.c, fzobj/%.o, $(SRC))

RED_BLD := \033[1;31m
NOC_BLD := \033[1;0m

default: $(TARGET)

bear:
	make clean
	bear -- make
clean:
	rm -rf obj/*.o
	rm -rf fzobj/*.o
	rm -rf bin/*
	rm -rf ./*.bin
	rm -rf ./*.wav

music: $(TARGET)
	@exec python ./tools/txt_to_bin.py
	@exec ffmpeg -f f64le -ar 44100 -ac 1 -i input.bin output.wav

bin_info: $(TARGET)
	@exec echo -e "$(RED_BLD)information of spitted binary file$(NOC_BLD)\n"
	@exec file bin/test
	@exec readelf -h bin/test

$(TARGET): $(OBJ)
	gcc -o $@ $? -lm -lportsf

obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinc -Iventor/include -Iventor/portsf -Wno-implicit-function-declaration -g -Wall
# end

debug_fuzz: $(FZOBJ)
	afl-clang-fast -o $@ $? -lm
fzobj/%.o: src/%.c
	afl-clang-fast -c $< -o $@ -Iinc -Iventor/include -Iventor/portsf -Wno-implicit-function-declaration -g -Wall
