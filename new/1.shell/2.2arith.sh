#!/bin/bash

while true; do
    echo "Enter first number (or type 'exit' to end):"
    read input

    # Check if the user wants to exit
    if [ "$input" == "exit" ]; then
        echo "Exiting the script."
        break
    fi

    # Check if the input is a valid number
    if ! [[ "$input" =~ ^[0-9]+$ ]]; then
        echo "Invalid input. Please enter a number."
        continue
    fi

    num1=$input

    echo "Enter second number:"
    read num2

    # Check if the input is a valid number
    if ! [[ "$num2" =~ ^[0-9]+$ ]]; then
        echo "Invalid input. Please enter a number."
        continue
    fi

    echo "Select operation:"
    echo "1. Addition"
    echo "2. Subtraction"
    echo "3. Multiplication"
    echo "4. Division"
    echo "5. Modulus"
    echo "6. Exit"

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
                continue
            fi
            result=$(echo "scale=2; $num1 / $num2" | bc)
            operation="Division"
            ;;
        5)
            result=$((num1 % num2))
            operation="Modulus"
            ;;
        6)
            echo "Exiting the script."
            break
            ;;
        *)
            echo "Invalid choice!"
            continue
            ;;
    esac

    echo "$operation Result: $result"
done
