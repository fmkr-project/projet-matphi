CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra -g3

SRC_PATH=./src
BUILD_PATH=./build
BIN_PATH=$(BUILD_PATH)/bin

# This code comes from GitHub...
SOURCES=$(shell find $(SRC_PATH) -name '*.cpp' | sort -k 1nr | cut -f2-)
OBJECTS=$(SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)
DEPS=$(OBJECTS:.o=.d)
###

INCLUDES=-I./include/

-include $(DEPS)

.PHONY: all
all: dirs main # TODO remove this

.PHONY: clean
clean:
	rm -fr ./main
	rm -fr $(BUILD_PATH)

.PHONY: dirs
dirs:
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(BUILD_PATH)

main: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
