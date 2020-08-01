CC := gcc
#CC:= arm-linux-gnueabihf-gcc
#LDFLAGS := -lm

BIN := main
OBJECT1 := math
OBJECT2 := main
SOURCES1 := ./code/*.c #./src/*.c
SOURCES2 := ./src/*c
HEADERS1 := ./code/*.h ./inc/*.h
#HEADERS2 := ./inc/getstring.h

.PHONY := clean

all: $(BIN)

$(BIN):	$(SOURCES1) $(SOURCE2)
		gcc $(SOURCES1) -c -o $(OBJECT1).o
		gcc $(SOURCES2) -c -o $(OBJECT2).o
		ar rc libfirst.a main.o math.o
		gcc $(OBJECT1).o $(OBJECT2).o -o $(BIN) -L. -lfirst

		#./$(BIN)
		#rm -rf $(BIN)

$(BIN): $(HEADERS1)

clean: 
		rm -rf $(BIN)
