import os
import subprocess

    

# Example usage:
input_folder = 'datasets/train/images'
output_folder = 'datasets/train/images'
prog_name = "Augmentation 2"
params = "3.14"

# Get the list of image files in the input folder
image_files = [f for f in os.listdir(input_folder) if f.endswith('.jpg') or f.endswith('.jpeg')]

# Apply the ImageDSP function to each image
for file_name in image_files:
# Construct the input and output paths
	input_image = os.path.join(input_folder, file_name)
	output_image = os.path.join(output_folder, file_name)

	# Construct the command to execute
	command = [
	    './ImageDSP/build/linux/build-ImageDSP-Desktop-Debug/ImageDSP',
	    '--prog-name', prog_name,
	    '--in-img', input_image,
	    '--out-img', output_image,
	    '--params', params
	]

	# Execute the command using subprocess
	subprocess.run(command)

print("Batch processing completed.")

