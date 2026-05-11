CXX := clang++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wno-unknown-pragmas -Wno-deprecated-declarations

SRC_DIR := src/appMG
BUILD_DIR := build
TARGET := bin/appMG

SOURCES := \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/ComplexObject.cpp \
	$(SRC_DIR)/Geometry.cpp \
	$(SRC_DIR)/Torid.cpp

OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJECTS:.o=.d)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDLIBS := -framework OpenGL -framework GLUT
else
	LDLIBS := -lGL -lGLU -lglut
endif

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CXX) $(OBJECTS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR) bin:
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)
