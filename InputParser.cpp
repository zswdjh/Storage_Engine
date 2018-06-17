//
// Created by ANKITESH on 3/4/2018.
//

#include "InputParser.h"
#include "ArchiveTests.h"

InputParser::InputParser(){
    /*
     * Adds list of commands
     */
        ValidCommandsL1.push_back("add");
        ValidCommandsL1.push_back("del");
        ValidCommandsL1.push_back("list");
        ValidCommandsL1.push_back("find");
        ValidCommandsL1.push_back("-l");
        ValidCommandsL1.push_back("extract");
        ValidCommandsL1.push_back("clean");
        ValidCommandsL1.push_back("-c");
        ValidCommandsL1.push_back("test");
    }

void InputParser::usage() {
    /*
     * Defines usage specification
     */
    std::cout<<"Usage : sfarchiver command <optimal args>\nList commands : \n";
    for(auto i:ValidCommandsL1)
    {
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
}

InputParser::InputParser(int argc,const char* argv[]):InputParser(){
    /*
     * Parses inputs, and calls the respective function
     */
       if(argc>4) {
           std::cout<<"Too many arguments\n"; usage();
       }
       else if(argc>3) {
            if (isValidCommand(std::string(argv[1]))) {
                if (std::string(argv[1]) == "add") {ArchiveManager::addToArchive(argc, argv);}                // throw error if not enough arguments
                else if (std::string(argv[1]) == "del") { ArchiveManager::delFromArchive(argc, argv); }        // throw
                else if (std::string(argv[1]) == "list"||std::string(argv[1]) == "-l") { ArchiveManager::listArchive(argc, argv); }
                else if (std::string(argv[1]) == "find") { ArchiveManager::find(argc, argv); }
                else if (std::string(argv[1]) == "extract") { ArchiveManager::extractFromArchive(argc, argv); }
            }
            else { std::cout << "Not a valid command"; usage();}
        }

        else if(argc<=3 && argc>1){
            if(std::string(argv[1])=="test"){ ArchiveTests tests;}
            else if(std::string(argv[1])=="-v" || std::string(argv[1])=="version") {std::cout<<VERSION<<std::endl;}
            else if((std::string(argv[1]) == "list"||std::string(argv[1]) == "-l")){ArchiveManager::listArchive(argc, argv);}
            else if((std::string(argv[1]) == "clean"||std::string(argv[1]) == "-c")){ArchiveManager::cleanArchive(std::string(argv[2]));}
            else if(isValidCommand(argv[1])){std::cout<<"Not enough arguments\n";}
            else {std::cout<<"Not a valid command\n"; usage();}
        }
        else{
            std::cout<<"Too few or no commands\n";
           usage();
        }
    }
bool InputParser::isValidCommand(const std::string &option) const{
    /*
     * Checks if valid command
     */
        return std::find(this->ValidCommandsL1.begin(), this->ValidCommandsL1.end(), option)
               != this->ValidCommandsL1.end();
    }

