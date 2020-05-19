#================================================================================
# MPI
#================================================================================

MPICXX?=mpicxx

#================================================================================
# FLAGS
#================================================================================
BUILD_DIR=$(shell pwd)/build
SRC_DIR=$(shell pwd)/src
TEST_DIR=$(shell pwd)/test

CXXFLAGS := -I$(SRC_DIR)

TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%, $(TEST_SRC_FILES))

#================================================================================
# Start Makefile
#================================================================================
.PHONY: test

main:

# Make cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MPICXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

test: main $(TEST_FILES)

# Make test files
$(BUILD_DIR)/%: $(TEST_DIR)/%.cpp
		$(MPICXX) $(CXXFLAGS) $< -o $@

check: test
	./scripts/run_tests.sh
