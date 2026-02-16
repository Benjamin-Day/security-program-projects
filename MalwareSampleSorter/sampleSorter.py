#!/usr/bin/python

# Benjamin Day

# This script takes a folder as input. It then goes through the contents of the 
# given folder and calculates the hash for each file and sorts them into their 
# respective folders based on the file extension. The hash is used as the new 
# name of the file when it is copied to its respective folder. The program also 
# prints out a directory 'tree' that shows the structure of the entered folder.

import os
import shutil
import hashlib

tab = "\t"

currentDir = os.getcwd()

folder = input("Enter the folder to sort: ")

# Go through all directories in the specified folders and 
# returns a path (root), and lists of the directories and files for each directory.
# Iterate through the files within each directory
for root,directories,files in os.walk(folder):
    for file in files:

        # Get extension from the end of the file name
        extension = file.split(".")[-1]

        # Get the path of the current file
        sourcePath = os.path.join(root, file)

        # Read the contents of the current file (for hash generation)
        with open(sourcePath, "rb") as f:
            fileContents = f.read()
        
        # Generate a hash for the new name of the file
        hash = hashlib.sha256(fileContents).hexdigest()
        
        # Create the path for both the destination directory, and destination file path with hash
        destPath = currentDir + "/" + extension + "/" + hash + "." + extension
        destination = currentDir + "/" + extension

        # Check if the directory extists then copy the file, if not (else) create it, then copy the file
        if os.path.isdir(destination):
            shutil.copy2(sourcePath, destPath)
        else:
            os.mkdir(destination)
            shutil.copy2(sourcePath, destPath)
    
    # Determine how many directories deep 
    level = root.count("/")
    # Get the current directory name
    rootEnd = root.rsplit("/")

    # Print current directory and files at appropriate level in tree output
    if level >= 2:
        print(f'\t  │{tab * (level-1)}  └── {rootEnd[-1]}')
        for file in files:
            print(f'\t  │{tab * (level)}  └── {file}') 
    else:
        print(f'{tab * level}  └── {rootEnd[-1]}')
        for file in files:
            print(f'\t  │{tab * (level)}  └── {file}')