CC	 = g++
MKDIR = mkdir -p
RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj

SOURCE = $(wildcard $(SRC_DIR)/*.cpp)
HEADER = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SOURCE))
DEPS = $(patsubst %.h,$(OBJ_DIR)/%.d,$(HEADER))

BINARY_DIR_OUT = bin
BINARY_FILE	= "v2gLuaDecoder.dll"
BINARY=$(BINARY_DIR_OUT)/$(BINARY_FILE)

FLAGS_COMMON = -Wall -O3 -MP -MD -fPIC
FLAGS_LIB	 = -shared -static-libstdc++ -static-libgcc 

IFLAGS = -I"../Third_Party/lua/lua-5.2.4/include" -I"../Third_Party/zlib/include" -I"../Third_Party/libxml2/include/libxml2"
LFLAGS = -llua52 -lzlib1 -lxml2 -L"C:/Program Files/Wireshark"

# CBV2G
PATH_CBV2G = ../Third_Party/CBV2G
OBJECTS_CBV2G = $(wildcard $(PATH_CBV2G)/$(OBJ_DIR)/*/*.o)
INCLUDES_CBV2G = $(wildcard $(PATH_CBV2G)/*/.)
IFLAGS_CBV2G = $(foreach d, $(INCLUDES_CBV2G), -I"$(d)")

dll:$(BINARY)

$(BINARY): prepare_dirs cbv2g res.o $(OBJECTS)
	$(CC) $(FLAGS_COMMON) $(FLAGS_LIB) $(OBJECTS) $(OBJECTS_CBV2G) -o $(BINARY_DIR_OUT)/$(BINARY_FILE) $(IFLAGS) $(LFLAGS) res.o

res.o: main.rc
	windres main.rc -o res.o

$(OBJ_DIR)/%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CC) -c $(FLAGS_COMMON) $< -o $@ $(IFLAGS) $(IFLAGS_CBV2G)

cbv2g:
	make -C $(PATH_CBV2G) build

prepare_dirs:
	$(MKDIR) $(BINARY_DIR_OUT)

clean:
	$(RM) $(OBJ_DIR) $(BINARY_DIR_OUT) $(BIN) res.o
	make -C $(PATH_CBV2G) clean

.PHONY: dll resource cbv2g prepare_dirs clean
-include $(DEPS)