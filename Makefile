SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

main: $(OBJ_FILES)
	g++ -std=c++11 -g -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++11 -g -c -o $@ $<

clean:
	rm Result.csv; rm Emp0; rm Emp1; rm Dept0; rm main; rm $(OBJ_DIR)/*.o
