# Huffman File Compressor

## Overview
This is a file compression program that utilizes the Huffman encoding algorithm to reduce the size of text files.

## Features
- Huffman encoding for file compression.
- Code table generation for each character in the input file.
- Simple and easy-to-understand implementation in C.

## Implementation Details
The program consists of the following components:

1. **Data Structures**: Defines a structure for nodes in the Huffman tree.
2. **Priority Queue (Min-Heap)**: Implementation for a priority queue to build the Huffman tree efficiently.
3. **Huffman Tree Construction**: Constructs the Huffman tree based on character frequencies.
4. **Code Table Generation**: Generates a code table for each character in the input file.
5. **File Compression**: Encodes the input file using the generated Huffman codes.
6. **Code Printing**: Prints the code table with character frequencies and corresponding Huffman codes.

## Input File Format
- The program expects a text file (`test.txt`) as input.
- Characters in the file will be encoded using Huffman codes, and the output will be written to a binary file.

## Output
- The compressed file is written in binary format.
- The code table with character frequencies and Huffman codes is printed to the console.

## Author
Maitrey Chitale
