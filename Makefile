CC=g++
SFML_LIBRARIES := sfml-graphics sfml-window sfml-system
SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build

CFLAGS = -I$(PWD)/lib/SFML-2.5.1/include -I$(INCLUDE_DIR) -o $@
LDFLAGS = -L$(PWD)/lib/SFML-2.5.1/lib $(addprefix -l, $(SFML_LIBRARIES)) -Wl,-rpath,'$$ORIGIN' -o $@
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS)

$(BUILD_DIR)/sfml-app: $(OBJS) | $(BUILD_DIR)
	$(CC) $(OBJS) $(LDFLAGS)
	cp $(PWD)/lib/SFML-2.5.1/lib/*.so.2.5 $(BUILD_DIR)/

compile: $(OBJS)

link: $(BUILD_DIR)/sfml-app

run: compile link
	./$(BUILD_DIR)/sfml-app

clean:
	@rm -rf $(BUILD_DIR)