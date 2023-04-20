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

# # Build MST executable
# primLazy: $(DEP) DHeap.o primLazy.o prep-script
# 	@mkdir -p $(BIN_DIR)
# 	$(COMPILE) $(DEP_ACT) $(BLD_DIR)/DHeap.o $(BLD_DIR)/primLazy.o -o $(BIN_DIR)/primLazy

# Compile lib
%.o: $(LIB_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# Compile src
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BLD_DIR)
	$(COMPILE) -c $< -o $(BLD_DIR)/$@

# # Test kruskal
# test-kruskal: prep-script
# 	@sed -i -e 's/\r$$//' ./scripts/test_mst.sh
# 	@chmod +x ./scripts/test_mst.sh
# 	./scripts/test_mst.sh kruskal 1

# Removes carriage return and makes script executable
prep-script:
	@sed -i -e 's/\r$$//' ./run_mst.sh
	@chmod +x ./run_mst.sh

# Clean build
clean:
	rm $(BIN_DIR)/* $(BLD_DIR)/*