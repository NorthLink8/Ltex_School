CC := gcc
#CC:= arm-linux-gnueabihf-gcc
#LDFLAGS := -lm

BIN := main
SOURCES1 := ./main.c
#SOURCES2 := ./src/*.c
#HEADERS1 := ./code/*.h
#HEADERS2 := ./inc/*.h

.PHONY := clean

all: $(BIN)

$(BIN):	$(SOURCES1) #$(SOURCES2)
		gcc $(SOURCES1) -o $(BIN) -g -lncurses -lpanel -lpthread
		#./$(BIN)
		#rm -rf $(BIN)

#$(BIN): $(HEADERS1) $(HEADERS22)

clean: 
		rm -rf $(BIN)
