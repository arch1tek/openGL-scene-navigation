#!/bin/bash

# Specify the name of the output executable
rm main.o
OUTPUT="runthis"

# Compile the source files separately
g++ -c -o main.o main.cpp -lGL -lglut -lGLU

# Link the object files to create the executable
g++ -o $OUTPUT main.o -lGL -lglut -lGLU

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running $OUTPUT..."
    # Run the executable
    ./$OUTPUT
else
    echo "Compilation failed."
fi
