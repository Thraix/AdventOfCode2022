# This Makefile was generated using MakeGen v1.3.1 made by Tim Håkansson
# and is licensed under MIT. Full source of the project can be found at
# https://github.com/Thraix/MakeGen
CC=@g++
CO=@g++ -o
MKDIR_P=mkdir -p
BIN=bin/
OBJPATH=$(BIN)intermediates
INCLUDES=-I src/ 
OBJECTS=$(OBJPATH)/Day01.o $(OBJPATH)/Day02.o $(OBJPATH)/Day03.o $(OBJPATH)/Day04.o $(OBJPATH)/Day05.o $(OBJPATH)/Day06.o $(OBJPATH)/Day07.o $(OBJPATH)/Day08.o $(OBJPATH)/Day09.o $(OBJPATH)/Day10.o $(OBJPATH)/Day11.o $(OBJPATH)/Day12.o $(OBJPATH)/Day13.o $(OBJPATH)/Day14.o $(OBJPATH)/Day15.o $(OBJPATH)/Day16.o $(OBJPATH)/Day17.o $(OBJPATH)/Day18.o $(OBJPATH)/Day19.o $(OBJPATH)/Day20.o $(OBJPATH)/Day21.o $(OBJPATH)/Day22.o $(OBJPATH)/Day23.o $(OBJPATH)/Day24.o $(OBJPATH)/Day25.o $(OBJPATH)/main.o 
CFLAGS=$(INCLUDES) -std=c++17 -c 
LIBDIRS=
LIBS=
LDFLAGS=$(LIBDIRS) $(LIBS) 
OUTPUT=$(BIN)adventofcode2022.out
.PHONY: all directories rebuild clean run
all: directories $(OUTPUT)
directories: $(BIN) $(OBJPATH)
$(BIN):
	$(info Creating output directories)
	@$(MKDIR_P) $(BIN)
$(OBJPATH):
	@$(MKDIR_P) $(OBJPATH)
run: all
	@./$(OUTPUT)
rebuild: clean all
clean:
	$(info Removing intermediates)
	rm -rf $(OBJPATH)/*.o
$(OUTPUT): $(OBJECTS)
	$(info Generating output file)
	$(CO) $(OUTPUT) $(OBJECTS) $(LDFLAGS)
install: all
	$(info Installing AdventOfCode2022 to /usr/bin/)
	@cp $(OUTPUT) /usr/bin/adventofcode2022.out
$(OBJPATH)/Day01.o : src/days/Day01.cpp
	$(info -[3%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day02.o : src/days/Day02.cpp
	$(info -[7%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day03.o : src/days/Day03.cpp
	$(info -[11%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day04.o : src/days/Day04.cpp
	$(info -[15%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day05.o : src/days/Day05.cpp
	$(info -[19%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day06.o : src/days/Day06.cpp
	$(info -[23%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day07.o : src/days/Day07.cpp
	$(info -[26%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day08.o : src/days/Day08.cpp
	$(info -[30%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day09.o : src/days/Day09.cpp
	$(info -[34%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day10.o : src/days/Day10.cpp
	$(info -[38%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day11.o : src/days/Day11.cpp
	$(info -[42%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day12.o : src/days/Day12.cpp
	$(info -[46%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day13.o : src/days/Day13.cpp
	$(info -[50%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day14.o : src/days/Day14.cpp
	$(info -[53%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day15.o : src/days/Day15.cpp
	$(info -[57%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day16.o : src/days/Day16.cpp
	$(info -[61%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day17.o : src/days/Day17.cpp
	$(info -[65%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day18.o : src/days/Day18.cpp
	$(info -[69%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day19.o : src/days/Day19.cpp
	$(info -[73%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day20.o : src/days/Day20.cpp
	$(info -[76%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day21.o : src/days/Day21.cpp
	$(info -[80%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day22.o : src/days/Day22.cpp
	$(info -[84%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day23.o : src/days/Day23.cpp
	$(info -[88%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day24.o : src/days/Day24.cpp
	$(info -[92%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/Day25.o : src/days/Day25.cpp
	$(info -[96%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
$(OBJPATH)/main.o : src/main.cpp src/aoc.h src/lib/Array2D.h src/lib/Array3D.h src/lib/Array4D.h src/lib/Helper.h src/lib/Input.h  src/lib/Mapper.h src/lib/Timer.h
	$(info -[100%]- $<)
	$(CC) $(CFLAGS) -o $@ $<
