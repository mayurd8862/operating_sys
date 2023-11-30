#!/bin/bash

# Shell Script for Arithmetic Operations using Case

echo "Enter first number:"
read num1

echo "Enter second number:"
read num2

echo "Select operation:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
echo "5. Modulus"

read choice

case $choice in
    1)
        result=$((num1 + num2))
        operation="Addition"
        ;;
    2)
        result=$((num1 - num2))
        operation="Subtraction"
        ;;
    3)
        result=$((num1 * num2))
        operation="Multiplication"
        ;;
    4)
        if [ $num2 -eq 0 ]; then
            echo "Cannot divide by zero!"
            exit 1
        fi
        result=$(echo "scale=2; $num1 / $num2" | bc)
        operation="Division"
        ;;
    5)
        result=$((num1 % num2))
        operation="Modulus"
        ;;
    *)
        echo "Invalid choice!"
        exit 1
        ;;
esac

echo "$operation Result: $result"
