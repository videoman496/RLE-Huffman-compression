# Project Documentation

## Task
This project focuses on developing a tool for file compression and decompression using Huffman coding and Run-Length Encoding (RLE) algorithms. The tool provides a command-line interface that allows users to compress and decompress files using these algorithms.

## Functionality
- **Compression**: The program can compress files using either Huffman coding or the RLE algorithm. Huffman coding is efficient for files where certain characters occur more frequently than others, while RLE is simple and efficient for data with a large number of repeating sequences.
- **Decompression**: The program can decompress files previously compressed using the same algorithms, restoring them to their original state.

## Solution Description
- The project is implemented in the C language and consists of multiple modules:
  - `compressor.h` and `compressor.c` contain declarations and implementations of compression and decompression functions.
  - `main.c` implements the main function and the command-line interface.
- Huffman coding is implemented by creating a frequency table, building a Huffman tree based on the frequencies, and generating unique binary codes for each character.
- RLE is implemented by reading sequences of repeating characters and encoding them as a single character followed by its count.

## Operating Conditions
- The program is designed to run on systems with a C compiler such as GCC.
- It requires sufficient memory and storage space to handle file operations involved in compression and decompression processes.
- The program expects command-line arguments to specify the operation (compression or decompression), algorithm (Huffman or RLE), and input/output file names.

## Project Compilation
You can compile the project using the provided `Makefile`. Simply run the following command in the project directory:  
`make`
This command will create an executable file that you can use for file compression or decompression.

## Running the Program
After compilation, you can run the program as follows:  
`./program -c|-d -h|-r input_file output_file`
Where:
- `-c` indicates compression
- `-d` indicates decompression
- `-h` to use Huffman coding
- `-r` to use RLE encoding
- `input_file` is the input file name
- `output_file` is the output file name

## References
- Algorithms for Huffman coding and RLE were based on standard implementations as described in various computer science textbooks and online resources.
- Documentation and tutorials from [cplusplus.com](https://www.cplusplus.com) and [Stack Overflow](https://stackoverflow.com) were used for specific implementation details in the C language.
