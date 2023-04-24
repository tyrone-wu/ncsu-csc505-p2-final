CPP=clang++
CPPFLAGS=-std=c++20 -fopenmp

BIN_DIR=./bin
BLD_DIR=./build
SRC_DIR=./src
INC_DIR=./include
LIB_DIR=./lib
DAT_DIR=./data

DEP=main.o Vertex.o Edge.o Graph.o Time.o
DEP_ACT=$(BLD_DIR)/main.o $(BLD_DIR)/Vertex.o $(BLD_DIR)/Edge.o $(BLD_DIR)/Graph.o $(BLD_DIR)/Time.o 
HEADERS=$(INC_DIR)/Edge.h $(INC_DIR)/Vertex.h $(INC_DIR)/Edge.h $(INC_DIR)/Graph.h $(INC_DIR)/ParseGraph.h $(INC_DIR)/Time.h $(INC_DIR)/GraphComponents.h 

COMPILE=$(CPP) $(CPPFLAGS)

# Build executable
bfs-s: $(DEP) BFSSequential.o
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/BFSSequential.o -o $(BIN_DIR)/bfs-s

bfs-p: $(DEP) BFSParallel.o
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/BFSParallel.o -o $(BIN_DIR)/bfs-p

lp: $(DEP) LabelProp.o
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/LabelProp.o -o $(BIN_DIR)/lp

# Compile lib
%.o: $(LIB_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Compile src
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Tests
gen-test:
	@sed -i -e 's/\r$$//' ./scripts/generate_test.sh
	@chmod +x ./scripts/generate_test.sh
	./scripts/generate_test.sh

test-bfs-s:
	@sed -i -e 's/\r$$//' ./scripts/test_cc.sh
	@chmod +x ./scripts/test_cc.sh
	./scripts/test_cc.sh bfs-s

test-bfs-p:
	@sed -i -e 's/\r$$//' ./scripts/test_cc.sh
	@chmod +x ./scripts/test_cc.sh
	./scripts/test_cc.sh bfs-p

test-lp:
	@sed -i -e 's/\r$$//' ./scripts/test_cc.sh
	@chmod +x ./scripts/test_cc.sh
	./scripts/test_cc.sh lp

# Removes carriage return and makes script executable
prep-script:
	@sed -i -e 's/\r$$//' ./run_cc.sh
	@chmod +x ./run_cc.sh

# Clean build
clean:
	rm $(BIN_DIR)/* $(BLD_DIR)/*