#!/bin/bash

g++ -o main main.cpp SportsLayout.cpp

if [ $? -eq 0 ]; then
  echo "Compilation successful."
else
  echo "Compilation failed."
  exit 1
fi