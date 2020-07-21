CC := gcc
#CC:= arm-linux-gnueabihf-gcc
#LDFLAGS := -lm

BIN := izi
SOURCES := izi.c
HEADERS := izi.h

.PHONY := clean

all: $(BIN)

$(BIN):	$(SOURCES)
		gcc $(SOURCES) -o $(BIN)
		./$(BIN)
		rm -rf $(BIN)

$(BIN): $(HEADERS)

clean: 
		rm -rf $(BIN)
