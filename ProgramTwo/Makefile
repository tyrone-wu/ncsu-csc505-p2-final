CPP=clang++
CPPFLAGS=-std=c++20

BIN_DIR=./bin
BLD_DIR=./build
SRC_DIR=./src
INC_DIR=./include
LIB_DIR=./lib
DAT_DIR=./data

DEP=main.o Vertex.o Graph.o
DEP_ACT=$(BLD_DIR)/main.o $(BLD_DIR)/Vertex.o $(BLD_DIR)/Graph.o
HEADERS=$(INC_DIR)/Edge.h $(INC_DIR)/Vertex.h $(INC_DIR)/Graph.h

COMPILE=$(CPP) $(CPPFLAGS)

# # Build MST executable
# insertion: $(DEP) insertion.o prep-script
# 	@mkdir -p $(BIN_DIR)
# 	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/insertion.o -o $(BIN_DIR)/insertion

# Build MST executable
mst: $(DEP)
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) -o $(BIN_DIR)/main

# Compile lib
%.o: $(LIB_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Compile src
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# # Test insertion
# test-insertion: prep-script
# 	@sed -i -e 's/\r$$//' ./scripts/test_sort.sh
# 	@chmod +x ./scripts/test_sort.sh
# 	./scripts/test_sort.sh insertion

# # Removes carriage return and makes script executable
# prep-script:
# 	@sed -i -e 's/\r$$//' ./run_sort.sh
# 	@chmod +x ./run_sort.sh

# Clean build
clean:
	rm $(BIN_DIR)/* $(BLD_DIR)/*