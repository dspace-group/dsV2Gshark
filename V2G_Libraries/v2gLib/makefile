CC = g++
MKDIR = mkdir -p
RM = rm -rf

LFLAGS_WIRESHARK_DIR ?= -L"C:/Program Files/Wireshark"
LFLAGS_LUA ?= -llua54
IFLAGS_LUA ?= -I"../Third_Party/lua/lua-54/include"
BINARY_OUT_NAME ?= v2gLib.dll

SRC_DIR = src
OBJ_DIR = obj

SOURCE = $(wildcard $(SRC_DIR)/*.cpp)
HEADER = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SOURCE))
DEPS = $(patsubst %.h,$(OBJ_DIR)/%.d,$(HEADER))

BINARY_DIR_OUT = bin
BINARY_OUT = $(BINARY_DIR_OUT)/$(BINARY_OUT_NAME)

FLAGS_COMMON = -Wall -O3 -MP -MD -fPIC
FLAGS_LIB = -shared -static-libstdc++ -static-libgcc

IFLAGS = $(IFLAGS_LUA) -I"../Third_Party/zlib/include" -I"../Third_Party/libxml2/include/libxml2" -I"../Third_Party/GnuTLS/include"
LFLAGS = $(LFLAGS_LUA) -lzlib1 -lxml2 -lgnutls-30 -lzlib1 -L"../Third_Party/lua/bin" $(LFLAGS_WIRESHARK_DIR)

# CBV2G
PATH_CBV2G = ../Third_Party/cbv2g
OBJECTS_CBV2G = $(wildcard $(PATH_CBV2G)/$(OBJ_DIR)/*/*.o)
INCLUDES_CBV2G = $(wildcard $(PATH_CBV2G)/*/.)
IFLAGS_CBV2G = $(foreach d, $(INCLUDES_CBV2G), -I"$(d)")

all: $(BINARY_OUT)

$(BINARY_OUT): prepare_dirs cbv2g res.o $(OBJECTS)
	$(CC) $(FLAGS_COMMON) $(FLAGS_LIB) $(OBJECTS) $(OBJECTS_CBV2G) -o $(BINARY_OUT) $(IFLAGS) $(LFLAGS) res.o

$(OBJ_DIR)/%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CC) -c $(FLAGS_COMMON) $< -o $@ $(IFLAGS) $(IFLAGS_CBV2G)

res.o: main.rc
	windres main.rc -o res.o

cbv2g:
	make -C $(PATH_CBV2G) build

prepare_dirs:
	$(MKDIR) $(BINARY_DIR_OUT)

clean: clean-obj
	$(RM) $(BINARY_DIR_OUT)
	make -C $(PATH_CBV2G) clean

clean-obj:
	$(RM) $(OBJ_DIR) res.o

.PHONY: $(BINARY_OUT) resource cbv2g prepare_dirs clean
-include $(DEPS)