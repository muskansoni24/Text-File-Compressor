#include <iostream>
#include <string>
#include <chrono>
#include <sys/stat.h>
#include "Compressor.h"
#include "Decompressor.h"

using namespace std;

long getFileSize(const string& filename) {
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int main() {
    Compressor compressor;
    Decompressor decompressor;

    int choice;
    cout << "Huffman Compression Tool\n";
    cout << "-------------------------\n";
    cout << "1. Compress a file\n";
    cout << "2. Decompress a file\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    string inputFile, outputFile;

    if (choice == 1) {
        cout << "\nEnter the name of the file to compress: ";
        cin >> inputFile;
        cout << "Enter the name of the output compressed file: ";
        cin >> outputFile;

        long originalSize = getFileSize(inputFile);

        cout << "\nCompressing file..." << endl;
        auto start = chrono::high_resolution_clock::now();

        compressor.compress(inputFile, outputFile);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        long compressedSize = getFileSize(outputFile);

        cout << "\nCompression completed. Output file: " << outputFile << endl;
        cout << "Original File Size: " << originalSize << " bytes\n";
        cout << "Compressed File Size: " << compressedSize << " bytes\n";

        if (originalSize > 0 && compressedSize >= 0) {
            double ratio = 100.0 * (1.0 - ((double)compressedSize / originalSize));
            cout << "Compression Ratio: " << ratio << "%\n";
        }

        cout << "Time taken to compress: " << duration.count() << " seconds\n";

    } else if (choice == 2) {
        cout << "\nEnter the name of the compressed file to decompress: ";
        cin >> inputFile;
        cout << "Enter the name of the output decompressed file: ";
        cin >> outputFile;

        cout << "\nDecompressing file..." << endl;
        auto start = chrono::high_resolution_clock::now();

        decompressor.decompress(inputFile, outputFile);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Decompression completed. Output file: " << outputFile << endl;
        cout << "Time taken to decompress: " << duration.count() << " seconds\n";

    } else {
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }

    return 0;
}

// #include <iostream>
// #include <string>
// #include "Compressor.h"
// #include "Decompressor.h"

// using namespace std;

// int main() {
//     Compressor compressor;
//     Decompressor decompressor;

//     int choice;
//     cout << "Huffman Compression Tool\n";
//     cout << "-------------------------\n";
//     cout << "1. Compress a file\n";
//     cout << "2. Decompress a file\n";
//     cout << "Enter your choice (1 or 2): ";
//     cin >> choice;

//     string inputFile, outputFile;

//     if (choice == 1) {
//         cout << "\nEnter the name of the file to compress: ";
//         cin >> inputFile;
//         cout << "Enter the name of the output compressed file: ";
//         cin >> outputFile;

//         cout << "\nCompressing file..." << endl;
//         compressor.compress(inputFile, outputFile);
//         cout << "Compression completed. Output file: " << outputFile << endl;

//     } else if (choice == 2) {
//         cout << "\nEnter the name of the compressed file to decompress: ";
//         cin >> inputFile;
//         cout << "Enter the name of the output decompressed file: ";
//         cin >> outputFile;

//         cout << "\nDecompressing file..." << endl;
//         decompressor.decompress(inputFile, outputFile);
//         cout << "Decompression completed. Output file: " << outputFile << endl;

//     } else {
//         cout << "Invalid choice. Please enter 1 or 2." << endl;
//     }

//     return 0;
// }
