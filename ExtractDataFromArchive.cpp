//
// Created by Ankitesh Singh on 3/8/18.
//

#include "ExtractDataFromArchive.h"

ExtractDataFromArchive::ExtractDataFromArchive() {};

/*
 * Sets rootPath
 */
ExtractDataFromArchive::ExtractDataFromArchive(const char* aPath):rootPath(aPath){}
#define BUFF_Size 512

ExtractDataFromArchive& ExtractDataFromArchive::extractAFile(std::istream& requiredFile, int positionToRead,int filesize) {
    /*
     * Extracts data from archive with a given position and filesize.
     */
    if (filesize > BUFF_Size) {
        char *Buffer = new char[BUFF_Size];
        int noOfChunks = (int)filesize / BUFF_Size;
        int offsetBytesToRead = (int)filesize % BUFF_Size;
        char *leftBytes = new char[offsetBytesToRead];
        requiredFile.seekg(positionToRead);
        while (noOfChunks--) {
                requiredFile.read(Buffer, BUFF_Size);
                std::cout << Buffer;
        }
        requiredFile.read(leftBytes, offsetBytesToRead);
        std::cout << leftBytes;
        delete[] Buffer;
        delete[] leftBytes;
    }
    else {
        char *Buffer = new char[filesize];
        requiredFile.seekg(positionToRead);
        requiredFile.read(Buffer, filesize);
        std::cout << Buffer;
        delete[] Buffer;
    }
    std::cout<<"\n";
    return *this;
}
