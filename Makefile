CC=avr-gcc
CFLAGS=-Os -mmcu=atmega328p
LDFLAGS=-Tlink.ld
#LDFLAGS=
PORT=/dev/ttyACM0

MAKEFILE=Makefile
CLANGDINFO=compile_commands.json

SRC=src
SRCS=$(wildcard $(SRC)/*.c)

OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BIN=gbCode
HEX=$(BIN).hex

make: $(CLANGDINFO) $(BIN)

$(HEX): $(BIN)
	avr-objcopy -O ihex -R .eeprom $< $@

upload: $(HEX)
	avrdude -F -V -c arduino -p ATMEGA328P -P$(PORT) -b 115200 -U flash:w:$<

dumpGame: $(BIN)
	avr-objcopy --dump-section .game=game.bin $<

clean:
	rm -r $(OBJ) || true
	rm $(BIN) || true
	rm $(CLANGDINFO) || true
	rm $(HEX) || true

# Rules for compilation

$(BIN): $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ):
	mkdir -p $@


# Create compile commands
makebin: $(BIN)

$(CLANGDINFO): $(MAKEFILE)
	make clean
	bear -- make makebin
