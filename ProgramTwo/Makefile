CPP=clang++
CPPFLAGS=-std=c++20

BIN_DIR=./bin
BLD_DIR=./build
SRC_DIR=./src
INC_DIR=./include
LIB_DIR=./lib
DAT_DIR=./data

DEP=main.o Vertex.o Graph.o Time.o
DEP_ACT=$(BLD_DIR)/main.o $(BLD_DIR)/Vertex.o $(BLD_DIR)/Graph.o $(BLD_DIR)/Time.o 
HEADERS=$(INC_DIR)/Edge.h $(INC_DIR)/Vertex.h $(INC_DIR)/Graph.h $(INC_DIR)/MST.h $(INC_DIR)/Time.h $(INC_DIR)/DHeap.h $(INC_DIR)/PrimDHeapPQ.h

COMPILE=$(CPP) $(CPPFLAGS)

# Build MST executable
primLazy: $(DEP) DHeap.o primLazy.o prep-script
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/DHeap.o $(BLD_DIR)/primLazy.o -o $(BIN_DIR)/primLazy

prim: $(DEP) PrimDHeapPQ.o prim.o prep-script
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/PrimDHeapPQ.o $(BLD_DIR)/prim.o -o $(BIN_DIR)/prim

kruskal: $(DEP) DHeap.o kruskal.o prep-script
	@mkdir -p $(BIN_DIR)
	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/DHeap.o $(BLD_DIR)/kruskal.o -o $(BIN_DIR)/kruskal

# Compile lib
%.o: $(LIB_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Compile src
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Test kruskal
test-kruskal: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh kruskal 1

# Test prim lazy
test-prim-lazy: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh primLazy 1

# Test prim with k = 2
test-prim-k1: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh prim 1

# Test prim with k = 2
test-prim-k2: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh prim 2

# Test prim with k = 3
test-prim-k3: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh prim 3

# Test prim with k = 4
test-prim-k4: prep-script
	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
	@chmod +x ./scripts/test_mst.sh
	./scripts/test_mst.sh prim 4

# Removes carriage return and makes script executable
prep-script:
	@sed -i -e 's/\r$$//' ./run_mst.sh
	@chmod +x ./run_mst.sh

# Clean build
clean:
	rm $(BIN_DIR)/* $(BLD_DIR)/*