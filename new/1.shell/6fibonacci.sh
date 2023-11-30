#!/bin/bash

# Function to generate Fibonacci series up to n terms
generate_fibonacci() {
    local n=$1
    local a=0
    local b=1

    echo "Fibonacci series up to $n terms:"
    
    for ((i = 1; i <= n; i++)); do
        echo -n "$a "
        temp=$((a + b))
        a=$b
        b=$temp
    done

    echo
}

# Main script
echo "Enter the number of terms for Fibonacci series:"
read num_terms

generate_fibonacci "$num_terms"
