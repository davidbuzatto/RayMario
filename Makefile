# make build script.
# based on: https://makefiletutorial.com/
#
# usage:
#    make: compile the project and run the compiled file
#    make clean: clean compiled file
#    make cleanAndCompile: clean compiled file and compile the project
#    make compile: compile the project
#    make run: run the compiled file
#
# author: Prof. Dr. David Buzatto

# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := $(lastword $(notdir $(shell pwd))).exe

BUILD_DIR := ./build
SRC_DIRS := ./src

all: compile run
compile: $(BUILD_DIR)/$(TARGET_EXEC)
cleanAndCompile: clean compile

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# C flags
#CFLAGS := -O1 -Wall -Wextra -Wno-unused-parameter -pedantic-errors -std=c++23 -Wno-missing-braces

# Linker flags
LDFLAGS := -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lm
#LDFLAGS_LINUX := -L lib/ -lraylib -lopengl32 -lgdi32 -lm -lrt -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CFLAGS := $(INC_FLAGS) -O1 -Wall -Wextra -Wno-unused-parameter -pedantic-errors -std=c99 -Wno-missing-braces
CPPFLAGS := $(INC_FLAGS) -MMD -MP -O1 -Wall -Wextra -Wno-unused-parameter -pedantic-errors -std=c++20 -Wno-missing-braces

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	@rm -f -r $(BUILD_DIR)

.PHONY: run
run:
	./$(BUILD_DIR)/$(TARGET_EXEC)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)