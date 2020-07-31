CC := gcc
#CC:= arm-linux-gnueabihf-gcc
#LDFLAGS := -lm

BIN := main
SOURCES1 := ./code/main.c
SOURCES2 := ./src/getstring.c
HEADERS1 := ./code/main.h
HEADERS2 := ./inc/getstring.h

.PHONY := clean

all: $(BIN)

$(BIN):	$(SOURCES1) $(SOURCES2)
		gcc $(SOURCES1) $(SOURCES2) -o $(BIN) -g -lncurses -lpanel
		#./$(BIN)
		#rm -rf $(BIN)

$(BIN): $(HEADERS1) $(HEADERS22)

clean: 
		rm -rf $(BIN)
