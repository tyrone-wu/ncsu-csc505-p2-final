CPP=clang++
CPPFLAGS=-std=c++20

BIN_DIR=./bin
BLD_DIR=./build
SRC_DIR=./src
INC_DIR=./include
LIB_DIR=./lib
DAT_DIR=./data

DEP=main.o Vertex.o Edge.o Graph.o Time.o
DEP_ACT=$(BLD_DIR)/main.o $(BLD_DIR)/Vertex.o $(BLD_DIR)/Edge.o $(BLD_DIR)/Graph.o $(BLD_DIR)/Time.o 
HEADERS=$(INC_DIR)/Edge.h $(INC_DIR)/Vertex.h $(INC_DIR)/Edge.h $(INC_DIR)/Graph.h $(INC_DIR)/Time.h 

COMPILE=$(CPP) $(CPPFLAGS)

# Build executable
bfs-cc: $(DEP) BFS.o
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/BFS.o -fopenmp -o $(BIN_DIR)/bfs-cc

lp-cc: $(DEP) LabelProp.o
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/LabelProp.o -fopenmp -o $(BIN_DIR)/lp-cc

# Compile lib
%.o: $(LIB_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Compile src
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Tests
test-bfs-cc:
	@sed -i -e 's/\r$$//' ./scripts/test_cc.sh
	@chmod +x ./scripts/test_cc.sh
	./scripts/test_cc.sh bfs-cc

test-lp-cc:
	@sed -i -e 's/\r$$//' ./scripts/test_cc.sh
	@chmod +x ./scripts/test_cc.sh
	./scripts/test_cc.sh lp-cc

# Removes carriage return and makes script executable
prep-script:
	@sed -i -e 's/\r$$//' ./run_cc.sh
	@chmod +x ./run_cc.sh

# Clean build
clean:
	rm $(BIN_DIR)/* $(BLD_DIR)/*