#!/bin/bash

folder_path="."
prefix=""
index=201

# Iterate over image files in the folder
for file_path in "$folder_path"/*.{jpg,jpeg}; do
    # Check if the file is an image
    if [ -f "$file_path" ]; then
        # Get the file extension
        extension="${file_path##*.}"
        
        # Construct the new file name
        new_file_name="${prefix}$(printf "%03d" $index).${extension}"
        
        # Rename the file
        new_file_path="$folder_path/$new_file_name"
        mv "$file_path" "$new_file_path"
        
        index=$((index + 1))
    fi
done

echo "Image renaming completed."
