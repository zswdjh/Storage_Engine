//
// Created by Ankitesh Singh on 3/8/18.
//

#ifndef ECE180A_GROUP_PROJECT_TEAM_0_EXTRACTDATAFROMARCHIVE_H
#define ECE180A_GROUP_PROJECT_TEAM_0_EXTRACTDATAFROMARCHIVE_H

#endif //ECE180A_GROUP_PROJECT_TEAM_0_EXTRACTDATAFROMARCHIVE_H

#include <fstream>
#include <iostream>
class ExtractDataFromArchive{
public:
    ExtractDataFromArchive();
    ExtractDataFromArchive(const char* aPath);
    ExtractDataFromArchive& extractAFile(std::istream& requiredFile, int positionToRead,int filesize);
private:
    std::string rootPath;
};
