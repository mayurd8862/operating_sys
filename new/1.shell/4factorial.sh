#!/bin/bash

# Function to calculate factorial
calculate_factorial() {
    local num=$1
    local result=1

    for ((i = 1; i <= num; i++)); do
        result=$((result * i))
    done

    echo $result
}

# Main script
echo "Enter a number:"
read number

# Check if the input is a non-negative integer
if [[ $number =~ ^[0-9]+$ ]]; then
    factorial=$(calculate_factorial $number)
    echo "Factorial of $number is: $factorial"
else
    echo "Please enter a non-negative integer."
fi
