## Huffman Compression Tool

A lightweight C++17 implementation of Huffman Coding that can:

compress text files into a binary .huff

decompress .huff back to its original form

display file sizes, compression ratio, and runtime

Planned next steps: wrap the CLI with a React front‑end and Node/Express API.

---

## 🚀 Features

- Compresses plain text files using Huffman Encoding
- Decompresses `.huff` files back to the original
- Displays compression ratio, file sizes, and time taken

---

## 🚀 Quick Start (CLI)

## Build
cd cpp

# Option A — preferred (Makefile outputs to bin/)
make

# Option B — single command build (if you don’t use make)
g++ -std=c++17 *.cpp -o ../bin/huffman_tool.exe
Windows note – add C:\mingw64\bin (or your MinGW‑w64 path) to PATH so g++ and dependent DLLs resolve when you run the program.

## Run
# From project root
bin\huffman_tool.exe        # Windows PowerShell / CMD
./bin/huffman_tool.exe      # Git‑Bash / WSL

You’ll see an interactive menu:

1. Compress a file
2. Decompress a file

Example session:

Enter the file to compress:  data\input.txt
Enter output compressed file:  data\input.huff
Original size: 12 kB
Compressed size: 4.4 kB
Compression ratio: 63.3 %
Time taken: 0.03 s

## ✨ Features Implemented
✅ Priority‑queue Huffman tree construction

✅ Bit‑packing of encoded data (true compression)

✅ Binary header storing frequency map and bit‑length

✅ CLI stats: original size, compressed size, ratio, time
