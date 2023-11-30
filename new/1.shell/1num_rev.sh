#!/bin/bash

# Shell Script to Print a Number in Reverse Order

echo "Enter a number:"
read number

reverse=""
len=${#number}

for (( i = len - 1; i >= 0; i-- )); do
    reverse="${reverse}${number:i:1}"
done

echo "Number in Reverse Order: $reverse"

