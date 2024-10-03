#!/bin/bash

gcc src/*.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./main
