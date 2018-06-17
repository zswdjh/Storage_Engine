//
// Created by Srinath Narayanan on 3/11/18.
//

#include "ArchiveTests.h"
#include "ArchiveManager.h"
#include <iostream>

std::ifstream::pos_type filesize(const char* filename)
{
    /*
     * Gets filesize given a string name
     */
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

ArchiveTests::ArchiveTests() {
    /*
     * Runs tests
     */
    std::ofstream testout(std::string("testoutput_sideEffects.txt"));
    std::streambuf* origbuf = std::cout.rdbuf();
    std::cout.rdbuf(testout.rdbuf());
    std::streambuf* cerrbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(testout.rdbuf());

    int addPassed = addTests();
    int delPassed = delTests();

    std::cerr.rdbuf(cerrbuf);
    std::cout.rdbuf(origbuf);
    origbuf = nullptr;
    cerrbuf = nullptr;

    std::cout << "running tests..."  << std::endl;
    std::cout<<"Add tests - Passed : "<<addPassed<<"/"<<ADDT<<"\n";
    std::cout<<"Delete tests - Passed : "<<delPassed<<"/"<<DELT<<"\n";
    std::remove("SFTest");
    std::remove("testoutput_sideEffects.txt");
}

int ArchiveTests::addTests() {
    /*
     * Runs add tests
     */
    return addingCorrectFile()+addingIncorrectFile();
}

bool ArchiveTests::addingCorrectFile() {
    /*
     * Tests correct file addition to archive
     */
    int argc = 4;
    std::remove("SFTest");
    const char *argv[4] = {"./sfarchiver","add","SFTest","contents/alice.txt"};
    InputParser input(argc,argv);
    std::ifstream read_arch(argv[2]);
    Header h;
    std::string filename = ArchiveManager::parseFileName(std::string(argv[3]));
    if(read_arch.good())
    {
        h.deserialize(read_arch,0);
        if(h.name == filename && h.fileSize == (size_t)filesize(argv[3]))
            return true;
    }
    return false;
}

bool ArchiveTests::addingIncorrectFile() {
    /*
     * Tests incorrect file addition to archive.
     */
    int argc = 4;
    std::remove("SFTest");
    const char *argv[4] = {"./sfarchiver","add","SFTest","contents/noFile.txt"};
    InputParser input(argc,argv);
    std::ifstream read_arch(argv[2]);
    Header h;
    std::string filename = ArchiveManager::parseFileName(std::string(argv[3]));
    if(read_arch.fail())
        return true;
    return false;
}

int ArchiveTests::delTests() {
    /*
     * Runs delete tests
     */
    std::remove("SFTest");
    addingCorrectFile();
    bool delCorrect = delCorrectFile();

    std::remove("SFTest");
    addingCorrectFile();
    bool delIncorrect = delIncorrectFile();

    return delCorrect + delIncorrect;
}

bool ArchiveTests::delCorrectFile() {
    /*
     * Tests correct file deletion
     */
    int argc = 4;
    const char *argv[4] = {"./sfarchiver","del","SFTest","alice.txt"};
    InputParser input(argc,argv);
    std::ifstream read_arch(argv[2]);
    Header h;
    std::string filename = ArchiveManager::parseFileName(std::string(argv[3]));
    if(read_arch.good())
        h.deserialize(read_arch,0);
        if(h.locationTellg==-1)
            return true;
    return false;
}

bool ArchiveTests::delIncorrectFile() {
    /*
     * Tests incorrect file deletion
     */
    int argc = 4;
    const char *argv[4] = {"./sfarchiver","del","SFTest","Wrongfile.txt"};
    InputParser input(argc,argv);
    std::ifstream read_arch(argv[2]);
    Header h;
    std::string filename = ArchiveManager::parseFileName(std::string(argv[3]));
    if(read_arch.good())
    {
        h.deserialize(read_arch,0);
        if(h.name == "alice.txt" && h.fileSize == (size_t)filesize("contents/alice.txt"))
            return true;
    }
    return false;
}