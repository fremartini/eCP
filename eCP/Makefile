SRC_DIR=eCP
APP_DIR=eCP_application
BUILD_DIR=build

BIN_DIR=$(BUILD_DIR)/bin
OBJ_DIR=$(BUILD_DIR)/objects

PROG=ecp
CXX=g++
CXXFLAGS=-Wall

# List of all .cpp source files
CPPS= \
	$(wildcard $(SRC_DIR)/*.cpp) \
	$(wildcard $(APP_DIR)/*.cpp)

# Implicit way of finding headers
HEADS=$(CPPS:%.cpp=/%.h)

# All .o files go to build dir
OBJS=$(CPPS:%.cpp=$(OBJ_DIR)/%.o)

# Gcc will create these .d files containing dependencies.
DEPS=$(OBJS:%.o=%.d)

# Default target
all: build $(BIN_DIR)/$(PROG)

# Actual target of the binary - depends on all .o files.
$(BIN_DIR)/$(PROG) : $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build target for every single object file.
# The potential dependency on header files is covered by calling `-include $(DEPS)` below.
# The -MMD flags additionaly creates a .d file with the same name as the .o file.
$(OBJ_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Include all .d dependency files
-include $(DEPS)

.PHONY: all clean build
build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(BIN_DIR)/* $(OBJ_DIR)/*
