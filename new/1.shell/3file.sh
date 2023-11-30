#!/bin/bash

# Shell Script to Check File Type and Permissions

echo "Enter the file path:"
read filepath

# Check if the file exists
if [ -e "$filepath" ]; then
    echo "File '$filepath' exists."

    # Check file type
    if [ -f "$filepath" ]; then
        echo "File Type: Regular File"
    elif [ -d "$filepath" ]; then
        echo "File Type: Directory"
    else
        echo "File Type: Other"
    fi

    # Check file permissions
    echo "File Permissions:"
    echo "Readable: $( [ -r "$filepath" ] && echo "Yes" || echo "No" )"
    echo "Writable: $( [ -w "$filepath" ] && echo "Yes" || echo "No" )"
    echo "Executable: $( [ -x "$filepath" ] && echo "Yes" || echo "No" )"
else
    echo "File '$filepath' does not exist."
fi
