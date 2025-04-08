# File Packer Unpacker with encryption

This project provides the facility of packing and unpacking the regular files.
In case of packing activity all the data of multiple regular files gets stored in single file with all
related metadata.
In case of unpacking activity the data from the packed file gets extracted in the separate file
with all necessary details

## Features

- **Packing Module**:
  - Combines multiple `.txt` files from a directory into a single packed file
  - Preserves original filenames and sizes
  - Shows detailed packing statistics

- **Unpacking Module**:
  - Extracts original files from packed archive
  - Recreates files with original names and contents
  - Provides extraction summary

## How to Use

### 1. Compile the Programs:
```bash
javac Packing.java Unpacking.java
