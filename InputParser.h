//
// Created by Ankitesh Singh on 3/7/18.
//

#ifndef ECE180A_GROUP_PROJECT_TEAM_0_INPUTPARSER_H
#define ECE180A_GROUP_PROJECT_TEAM_0_INPUTPARSER_H


#include "ArchiveManager.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#define VERSION "sfarchiver version 1.0 March 11, 2018"

class InputParser {
public:
    InputParser();
    InputParser(int argc,const char* argv[]);
    bool isValidCommand(const std::string &option) const;
    void usage();
private:
    std::vector<std::string> ValidCommandsL1;
};


#endif //ECE180A_GROUP_PROJECT_TEAM_0_INPUTPARSER_H