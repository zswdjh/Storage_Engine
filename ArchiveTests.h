//
// Created by Srinath Narayanan on 3/11/18.
//

#ifndef ECE180A_GROUP_PROJECT_TEAM_0_ARCHIVETESTS_H
#define ECE180A_GROUP_PROJECT_TEAM_0_ARCHIVETESTS_H

#include "InputParser.h"
#include <iostream>
#include <string>

class ArchiveTests
{
    int ADDT=2,DELT=2;
    public:
    ArchiveTests();
    int addTests();
    bool addingCorrectFile();
    bool addingIncorrectFile();

    int delTests();
    bool delCorrectFile();
    bool delIncorrectFile();

    // To do
//    static bool listTests();
//    static bool extractTests();
//    static bool versionTests();
//    static bool cleanTests();
};


#endif //ECE180A_GROUP_PROJECT_TEAM_0_ARCHIVETESTS_H
