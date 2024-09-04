CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra -g3

SRC_PATH=./src
TEST_PATH=./tests
BUILD_PATH=./build
BIN_PATH=$(BUILD_PATH)/bin

# Trouve tous les fichiers source, sauf main.cpp pour éviter de l'inclure plusieurs fois
SOURCES=$(shell find $(SRC_PATH) -name '*.cpp' | sort -k 1nr | cut -f2- | awk '!/main.cpp/')
OBJECTS=$(SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)
DEPS=$(OBJECTS:.o=.d)

# Fichiers de test
TEST_SOURCES=$(shell find $(TEST_PATH) -name '*.cpp')
TEST_OBJECTS=$(TEST_SOURCES:$(TEST_PATH)/%.cpp=$(BUILD_PATH)/%.o)
TEST_EXEC=$(BIN_PATH)/test_vector3

INCLUDES=-I./include/

-include $(DEPS)

.PHONY: all clean dirs main tests run_tests

# Compile tout : application principale + tests
all: clean dirs main tests

# Nettoie les fichiers générés
clean:
	rm -fr ./main
	rm -fr $(BUILD_PATH)

# Crée les répertoires nécessaires pour la compilation
dirs:
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(dir $(TEST_OBJECTS))
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(BUILD_PATH)

# Règle pour compiler les fichiers objets du projet principal
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# Règle pour compiler les fichiers objets des tests
$(BUILD_PATH)/%.o: $(TEST_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# Cible pour compiler l'exécutable principal
main: $(OBJECTS) $(BUILD_PATH)/main.o
	$(CXX) $(BUILD_PATH)/main.o $(OBJECTS) -o $@

# Cible pour compiler l'exécutable de test
tests: $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(TEST_OBJECTS) $(OBJECTS) -o $(TEST_EXEC)

# Cible pour exécuter les tests
run_tests: tests
	@echo "Running tests..."
	@$(TEST_EXEC)
