CC := gcc
#CC:= arm-linux-gnueabihf-gcc
#LDFLAGS := -lm

BIN := main
SOURCES1 := ./code/main.c
SOURCES2 := ./src/getstring.c
SOURCES3 := ./src/getDbList.c
HEADERS1 := ./code/main.h
HEADERS2 := ./inc/getstring.h
HEADERS3 := ./inc/getDbList.h

.PHONY := clean

all: $(BIN)

$(BIN):	$(SOURCES1) $(SOURCES2) $(SOURCES3)
		gcc $(SOURCES1) $(SOURCES2) $(SOURCES3) -o $(BIN) -g
		#./$(BIN)
		#rm -rf $(BIN)

$(BIN): $(HEADERS1) $(HEADERS22) $(HEADERS3)

clean: 
		#rm -rf $(BIN)
