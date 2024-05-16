C = gcc
MKDIR = mkdir -p
RM = rm -rf

OBJ_DIR = obj

SOURCE = $(wildcard */*.c)
HEADER = $(wildcard */*.h)
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCE))
DEPS = $(patsubst %.h,$(OBJ_DIR)/%.d,$(HEADER))
INCLUDES = $(wildcard */.)
LFLAGS = $(foreach d, $(INCLUDES), -I"$(d)") -MP -MD
FLAGS = -c -Wall -O3 -fPIC

build: $(OBJECTS)

$(OBJ_DIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(C) $(FLAGS) $< -o $@ $(LFLAGS)

clean:
	$(RM) $(OBJ_DIR)

.PHONY: clean build
-include $(DEPS)