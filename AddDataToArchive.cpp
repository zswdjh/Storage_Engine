//
// Created by Ankitesh Singh on 3/7/18.
//
#include "AddDataToArchive.h"
#include <iostream>
//const int BUFFER_SIZE = 512;
//std::vector<char> buffer (BUFFER_SIZE, 0);


AddDataToArchive::AddDataToArchive(){};
AddDataToArchive& AddDataToArchive::addaFile(std::string aFileName,std::ostream& outfile){
    /*
     * Adds data from aFileName to the archive outfile, byte by byte, since it has a low memory footprint.
     */
    char* smallBuff=new char[1];
    std::ifstream fin(aFileName);
    if(fin.is_open()){
        while(fin.read(smallBuff,1)) {
            outfile.write(smallBuff,1);
        }
        fin.close();
        delete[] smallBuff;
    }
    return *this;
}

AddDataToArchive& AddDataToArchive::ArchtoArch(std::fstream& infile,std::ofstream& outfile, size_t bytes)
{
    /*
     * Transfers [bytes] number of bytes from infile to outfile
     */
    char* smallBuff=new char[1];
    if(infile.good() && outfile.good()){
        for(size_t i=0;i<bytes;i++){
            infile.read(smallBuff,1);
            outfile.write(smallBuff,1);
        }
        delete[] smallBuff;
    }
    else {
        std::cerr<<"Arch error in ArchtoArch()\n";
    }
    return *this;
}

