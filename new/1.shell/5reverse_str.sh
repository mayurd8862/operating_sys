#!/bin/bash

# Function to reverse a string
reverse_string() {
    local input=$1
    local reversed=""

    for ((i = ${#input} - 1; i >= 0; i--)); do
        reversed="${reversed}${input:$i:1}"
    done

    echo "$reversed"
}

# Main script
echo "Enter a string:"
read user_input

reversed_result=$(reverse_string "$user_input")

echo "Reversed string: $reversed_result"
