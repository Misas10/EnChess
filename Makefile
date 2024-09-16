MAIN = main
COMPILED_NAME = en-chess
MAIN_DIR = src/

build:
	gcc -o $(COMPILED_NAME) $(MAIN_DIR)$(MAIN).c `sdl2-config --cflags --libs` -lSDL2_image

run:
	# $(MAIN_DIR)./main
	./$(COMPILED_NAME)

clean: 
	rm $(MAIN)
