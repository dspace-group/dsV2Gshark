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
BINARY_FILE = "v2gX509CertInfos.dll"
BINARY=$(BINARY_DIR_OUT)/$(BINARY_FILE)

FLAGS_COMMON = -Wall -O3 -MP -MD -fPIC
FLAGS_LIB	 = -shared -fPIC -static-libstdc++ -static-libgcc 

IFLAGS = -I"../Third_Party/lua/lua-5.2.4/include" -I"../Third_Party/GnuTLS/include" 
LFLAGS = -llua52 -lgnutls-30 -L"C:/Program Files/Wireshark"

dll: $(BINARY)

$(BINARY): prepare_dirs res.o $(OBJECTS)
	$(CC) $(FLAGS_COMMON) $(FLAGS_LIB) $(OBJECTS) -o $(BINARY) $(IFLAGS) $(LFLAGS) res.o

$(OBJ_DIR)/%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CC) -c $(FLAGS_COMMON) $< -o $@ $(IFLAGS)

res.o: main.rc
	windres main.rc -o res.o

prepare_dirs:
	$(MKDIR) $(BINARY_DIR_OUT)

clean:
	$(RM) $(OBJ_DIR) $(BINARY_DIR_OUT) $(BIN) res.o

.PHONY: dll prepare_dirs clean
-include $(DEPS)