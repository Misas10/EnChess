MAIN = main
MAIN_DIR = src/

build:
	gcc -o $(MAIN) $(MAIN_DIR)$(MAIN).c `sdl2-config --cflags --libs`

run:
	# $(MAIN_DIR)./main
	./$(MAIN)

clean: 
	rm $(MAIN)
