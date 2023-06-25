#!/bin/bash
dir="../train/labeltemp2"
folder_path="."
prefix="txt"
index=385
cd $dir

# Iterate over image files in the folder
for file_path in *; do
    # Check if the file is an image
        # Get the file extension
        # Construct the new file name
        new_file_name="$(printf "%03d" $index).${prefix}"
        
        # Rename the file
        new_file_path="$new_file_name"
        mv "$file_path" "$new_file_path"
        
        index=$((index + 1))
done

echo "Image renaming completed."
