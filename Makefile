
HDR_DIR   = headers
SRC_DIR   = sources
OBJ_DIR   = objects
MAIN_FILE = main
CC        = gcc

HDR = $(wildcard $(HDR_DIR)/*.h)  # header files
SRC = $(wildcard $(SRC_DIR)/*.c)   # source files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))  # object files
DIRS = $(HDR_DIR) $(SRC_DIR) $(OBJ_DIR)
CFLAGS = -g -I$(HDR_DIR) #-L$(OBJ_DIR)

$(MAIN_FILE).exe: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/$(MAIN_FILE).o: $(SRC_DIR)/$(MAIN_FILE).c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(MAIN_FILE).exe

clean:
	del $(OBJ_DIR)\*.o $(MAIN_FILE).exe
