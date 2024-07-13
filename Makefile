TARGET = main
TARGET_DIR = src/
BIN_DIR = bin/
SDL3_CONFIG = `pkg-config sdl3 --cflags --libs` 
SDL2_CONFIG = `sdl2-config --cflags --libs`

build:
	gcc -o $(BIN_DIR)$(TARGET) $(TARGET_DIR)$(TARGET).c $(SDL3_CONFIG)

run:
	$(BIN_DIR)./main
	# ./$(MAIN)

clean: 
	rm $(MAIN)
