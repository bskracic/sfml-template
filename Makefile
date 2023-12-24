CC=g++
SFML_LIBRARIES := sfml-graphics sfml-window sfml-system
BUILD_DIR=build

CFLAGS=-c src/main.cpp -I$(PWD)/lib/SFML-2.5.1/include -I$(PWD)/include -o $(BUILD_DIR)/main.o
LFLAGS=$(BUILD_DIR)/main.o -o $(BUILD_DIR)/sfml-app -L$(PWD)/lib/SFML-2.5.1/lib  $(addprefix -l, $(SFML_LIBRARIES))

$(BUILD_DIR):
	mkdir -p $@

compile: src/main.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) 

link: $(BUILD_DIR)/main.o
	$(CC) $(LFLAGS) -Wl,-rpath,'$$ORIGIN';
	cp $(PWD)/lib/SFML-2.5.1/lib/*.so.2.5 $(BUILD_DIR)/

run: compile link
	./$(BUILD_DIR)/sfml-app 

clean:
	@rm -rf $(BUILD_DIR)