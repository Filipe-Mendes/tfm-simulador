# all: bin/PlatformController.exe
# 
# bin/PlatformController.exe: obj/PlatformController.o
# 	gcc -o bin/PlatformController.exe obj/PlatformController.o -L. -lc_coder_win64
# 
# obj/PlatformController.o: src/c_test.c
# 	gcc -Wall -c $< -o $@
# 
# clean:
# 	rm - f obj/PlatformController.o bin/PlatformController.exe

CC = gcc

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DLL_DIR = bin
INCLUDE_DIRS = -I/include/MATLAB/c_coder_ert_shrlib_rtw 


SOURCE_FILE = $(SRC_DIR)/Controller.c
OBJECT_FILE = $(OBJ_DIR)/PlatformController.o
EXECUTABLE = $(BIN_DIR)/PlatformController.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILE)
	$(CC) -o $@ $< -L$(DLL_DIR) -lc_coder_win64 -lws2_32

$(OBJECT_FILE): $(SOURCE_FILE)
	$(CC) -Wall -c $< -o $@ $(INCLUDE_DIRS)

clean:
#	del $(OBJECT_FILE) $(EXECUTABLE)
	del obj\PlatformController.o bin\PlatformController.exe
