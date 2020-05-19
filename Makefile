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
INCLUDE_DIR=$(SRC_DIR)/include

CXXFLAGS := -I$(INCLUDE_DIR) $(CUDA_CXXFLAGS) $(NCCL_FLAGS)
LDFLAGS := $(CUDA_LDFLAGS) $(NCCL_LDFLAGS)
LDLIBS := $(CUDA_LDLIBS) $(NCCL_LDLIBS) -lrt

OBJ_DIR := $(BUILD_DIR)/obj

TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/bin/%, $(TEST_SRC_FILES))

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

CU_SRC_FILES := $(wildcard $(SRC_DIR)/*.cu)
CU_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cu, $(OBJ_DIR)/%.o, $(CU_SRC_FILES))

#================================================================================
# Start Makefile
#================================================================================
.PHONY: test

main: $(CU_OBJ_FILES) $(OBJ_FILES)

# Make cuda files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cu
	$(NVCC) $(CXXFLAGS) -arch=sm_70 -c $< -o $@

# Make cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MPICXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf $(BUILD_DIR)/*
	mkdir $(BUILD_DIR)/obj/
	mkdir $(BUILD_DIR)/bin/

test: main $(TEST_FILES)

# Make test files
$(BUILD_DIR)/bin/%: $(TEST_DIR)/%.cpp
		$(MPICXX) $(CXXFLAGS) $< -o $@ $(OBJ_DIR)/* $(LDFLAGS) $(LDLIBS)

check: test
	./scripts/run_tests.sh
