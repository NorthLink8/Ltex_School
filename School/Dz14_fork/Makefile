CC := gcc
#CC:= arm-linux-gnueabihf-gcc
#LDFLAGS := -lm

BIN := main
SOURCES1 := ./code/main.c
#SOURCES2 := ./src/getstring.c
HEADERS1 := ./code/main.h
#HEADERS2 := ./inc/getstring.h

.PHONY := clean

all: $(BIN)

$(BIN):	$(SOURCES1) #$(SOURCES2)
		gcc $(SOURCES1) -o $(BIN) -g
		#./$(BIN)
		#rm -rf $(BIN)

$(BIN): $(HEADERS1)

clean: 
		rm -rf $(BIN)
