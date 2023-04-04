CPP=clang++
CPPFLAGS=-std=c++20

BIN_DIR=./bin
BLD_DIR=./build
SRC_DIR=./src
INC_DIR=./include
LIB_DIR=./lib
DAT_DIR=./data

DEP=main.o Vertex.o Graph.o BinaryHeap.o Time.o
DEP_ACT=$(BLD_DIR)/main.o $(BLD_DIR)/Vertex.o $(BLD_DIR)/Graph.o $(BLD_DIR)/BinaryHeap.o $(BLD_DIR)/Time.o
HEADERS=$(INC_DIR)/Edge.h $(INC_DIR)/Vertex.h $(INC_DIR)/Graph.h $(INC_DIR)/BinaryHeap.h $(INC_DIR)/MST.h $(INC_DIR)/Time.h

COMPILE=$(CPP) $(CPPFLAGS)

# Build MST executable
prim: $(DEP) prim.o prep-script
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/prim.o -o $(BIN_DIR)/prim

kruskal: $(DEP) kruskal.o prep-script
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/kruskal.o -o $(BIN_DIR)/kruskal

# Compile lib
%.o: $(LIB_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Compile src
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Test prim
test-prim: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh prim

# Test kruskal
test-kruskal: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh kruskal

# Removes carriage return and makes script executable
prep-script:
	@sed -i -e 's/\r$$//' ./run_mst.sh
	@chmod +x ./run_mst.sh

# Clean build
clean:
	rm $(BIN_DIR)/* $(BLD_DIR)/*