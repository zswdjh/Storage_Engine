//
// Created by Ankitesh Singh on 3/7/18.
//

#ifndef ECE180A_GROUP_PROJECT_TEAM_0_ADDDATATOARCHIVE_H
#define ECE180A_GROUP_PROJECT_TEAM_0_ADDDATATOARCHIVE_H

#include <fstream>
#include <vector>



class AddDataToArchive{
public:

    AddDataToArchive();
    AddDataToArchive& addaFile(std::string aFileName,std::ostream& outfile);
    AddDataToArchive& ArchtoArch(std::fstream& infile,std::ofstream& outfile, size_t bytes);
    /* returns file size before even file is read*/

};
#endif //ECE180A_GROUP_PROJECT_TEAM_0_ADDDATATOARCHIVE_H
