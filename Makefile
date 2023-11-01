CC=g++
CFLAGS=-Wall -std=c++11 -O3 -fopenmp
FILES=main.cpp correlate.cpp double_threshold.cpp hysteresis.cpp non_maximum_suppression.cpp get_grad_mag_and_angle.cpp gen_gaussian_filter.cpp
OBJS=$(FILES:.cpp=.o)
OUTPUT=./main

# 'all' target depends on the executable defined by OUTPUT
all: $(OUTPUT)

# The executable depends on object files
$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJS)

# Pattern rule for object file generation.
# This says how to build .o files from .cpp files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf *.o $(OUTPUT)

