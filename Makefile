CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wconversion -Wshadow
CPPFLAGS ?= -Iinclude

BUILD_DIR := build
TARGET := $(BUILD_DIR)/potencia_fpr
TEST_TARGET := $(BUILD_DIR)/test_potencia

LIB_SOURCES := src/CallCounter.cpp src/PrimitiveRecursiveFunctions.cpp src/CommandLineParser.cpp
LIB_OBJECTS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(LIB_SOURCES))
APP_OBJECT := $(BUILD_DIR)/main.o
TEST_OBJECT := $(BUILD_DIR)/test_potencia.o

.PHONY: all clean test help

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_OBJECT): tests/test_potencia.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(LIB_OBJECTS) $(APP_OBJECT)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(LIB_OBJECTS) $(TEST_OBJECT)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TARGET) $(TEST_TARGET)
	./$(TEST_TARGET)
	bash tests/test_cli.sh ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)
	touch $(BUILD_DIR)/.gitkeep

help:
	@echo "Objetivos disponibles:"
	@echo "  make       Compila el ejecutable en $(TARGET)"
	@echo "  make test  Ejecuta las pruebas automáticas"
	@echo "  make clean Elimina los artefactos generados"