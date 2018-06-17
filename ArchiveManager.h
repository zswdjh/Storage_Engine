//
// Created by Ankitesh Singh on 3/7/18.
//




#ifndef ECE180A_GROUP_PROJECT_TEAM_0_ARCHIVEMANAGER_H
#define ECE180A_GROUP_PROJECT_TEAM_0_ARCHIVEMANAGER_H

#define BUFF_Size 512
#define ARCH_COPY_EMPTY_THRESHOLD 0.3

#include "Header.h"
#include "AddDataToArchive.h"
#include "ExtractDataFromArchive.h"


#include <cstdio>
class ArchiveManager{
public:
    static void addToArchive(int argc,const char* argv[]);
    static void delFromArchive(int argc,const char* argv[]);
    static void _copyArchive(std::fstream& archHandle, std::string archName, bool forceClean);
    static float _percentEmpty(std::fstream& archHandle, std::string archName);
    static void cleanArchive(std::string archName);

    static void listArchive(int argc,const char* argv[]);
    static void find(int argc,const char* argv[]);
    static void extractFromArchive(int argc,const char* argv[]);
    static bool fileExists(std::ifstream& read_file,std::string fileName,Header& h);
    static bool findinArchive(std::istream& requiredFile, int positionToRead,int filesize, std::string str);
    static std::string parseFileName(std::string theString);
};
#endif //ECE180A_GROUP_PROJECT_TEAM_0_ARCHIVEMANAGER_H
