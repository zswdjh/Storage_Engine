//
// Created by Ankitesh Singh on 3/7/18.
//

/*Functions to be defined here*/


#include "ArchiveManager.h"
bool findinArchive(std::istream& requiredFile, int positionToRead, int filesize, std::string str);

void  ArchiveManager::addToArchive(int argc,const char* argv[]){
    /*
     * Adds a file to archive.
     */

    /*argv[2] is the archive  name, if it doesn't exist create and take argv[3] ....
     * otherwise take argv[3] and add it */
    //write part
    std::string archName= std::string(argv[2]);
    std::string fileName= std::string(argv[3]);
    
	std::ifstream read_file(fileName);
	if(!read_file.good()){
		std::cerr<<"File "<<fileName<<" does not exist or cannot be opened\n";
	}
	else{
	        Header hFile;
		std::ifstream read_arch(archName);
		bool fileNotExist = true;
		if(read_arch.good() ){
			if(fileExists(read_arch, fileName,hFile)){
				std::cerr<<"File "<<parseFileName(fileName)<<" already exists\n";
				read_arch.close();
				fileNotExist = false;
			}
		}
		
		if(fileNotExist){

				read_arch.close();
				Header h(fileName);
				AddDataToArchive d;

				std::ofstream write_file;
				write_file.open(archName,std::ios::binary | std::ios::app);

				if(!write_file.fail()){
					h.serialize(write_file);
					d.addaFile(fileName,write_file);

				}
				else if(write_file.fail()){
					std::cerr<<"Cannot create archive "<<archName<<"\n";
				}
		}


	}
	read_file.close();
}

std::string ArchiveManager::parseFileName(std::string theString){
    /*
     * Parses filename containing directories to extract just filename.
     */
  std::string result;
  std::istringstream theStream(theString);
  while (!theStream.eof()) {     
    std::string theWord;      
    getline( theStream, theWord, '/' );  
    if(theWord.length()){
	  result = theWord;
    }
  }
  return result;
}

void ArchiveManager::extractFromArchive(int argc, const char* argv[]) {
    /*
     * Extracts data from archive and prints to standard output
     */
    std::string archName= std::string(argv[2]);
    std::string fileName= std::string(argv[3]);

    std::ifstream read_file;
    read_file.open(archName);
    if(!read_file.fail()){
        Header h;
        h.deserialize(read_file);
        //fileName = parseFileName(fileName);
        while(h.locationTellg!=-1) { //&& h.type == "txt"
            if(fileName==h.name && h.exists)
            {
                if(h.type == "txt")
                {   //std::cout<<"The requested file exists, with following contents:\n";
                    ExtractDataFromArchive ext;
                    ext.extractAFile(read_file,h.locationTellg,h.fileSize);
                }
                else
                    std::cout<<"File exists but not of .txt type\n";
                break;
            }
            h.deserialize(read_file, h.locationTellg + h.fileSize);//incrementing by file-size to get to next
        }
        if(h.locationTellg==-1){
                std::cout<<"File doesn't exist in Archive\n";
        }
    }
    else if(read_file.fail()){
        std::cout<<"Archive \""<<archName<<"\" does not exist \n";
    }
}

void ArchiveManager::cleanArchive(std::string archName){
    /*
     * Cleans archive
     */
    std::fstream write_arch(archName,std::ios::binary | std::ios::in |std::ios::out |std::ios::ate);
    if(write_arch.good())
    {
        _copyArchive(write_arch,archName,true);
    }
    else
    {
        std::cout<<"Archive error : cannot open "<<archName<<"\n";
    }
}


void ArchiveManager::delFromArchive(int argc,const char* argv[]){
    /*
     * Deletes a given file from the archive
     */
    std::string archName= std::string(argv[2]);
    std::string fileName= std::string(argv[3]);

//    if(fileName != parseFileName(fileName)) {
//        std::cout << "\nEmpty only the file name that exists in the archive\n";
//        std::cout << "Do not enter file path or directory\n";
//    }
//    else
//    {

    fileName = parseFileName(fileName);
    std::ifstream read_arch;
    read_arch.open(archName);
    int loc=-1;
    if(!read_arch.fail()) {
        Header h;
        loc = h.deserializeForDelete(read_arch,fileName, 0);

        while (loc == -1 && h.locationTellg != -1) {
            loc = h.deserializeForDelete(read_arch, fileName, h.locationTellg + h.fileSize);//incrementing by file-size to get to next
        }
        read_arch.close();
        if(loc != -1)
        {
            std::fstream write_arch(archName,std::ios::binary | std::ios::in |std::ios::out |std::ios::ate);
            // Header h now contains the info about the file
            h.exists = false;
            if(write_arch.good()){
                write_arch.seekp(loc);
                h.serialize(write_arch);
                _copyArchive(write_arch,archName,false);
            }
            else{
                write_arch.close();
                std::cerr<<"Cannot open "<<archName<<" archive while overwritting in delFromArchive\n";
            }
        }
        else
        {
            std::cout<<"File does not exist in Archive\n";
        }
    }
    else{
        read_arch.close();
        std::cout<<"Archive \""<<archName<<"\" does not exist \n";
    }
//    }

    //printf ("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__);
}

float ArchiveManager::_percentEmpty(std::fstream& archHandle, std::string archName)
{
    /*
     * Computes the percantage of empty space in archive
     */
    if(archHandle.good())
    {
        Header h;
        archHandle.seekg (0, archHandle.beg);

        size_t emptySize = 0;
        size_t totalSize = 0;
        h.deserialize(archHandle, 0);
        while (h.locationTellg != -1) {
            if(h.exists == false)
            {
                emptySize += h.fileSize;
            }
            totalSize += h.fileSize;
            h.deserialize(archHandle, h.locationTellg + h.fileSize);//incrementing by file-size to get to next
        }
        if(totalSize==0.0)
        {
            std::cerr<<"Error in _percentEmpty. Totalsize cannot be zero.\n";
            return -1.0;
        }
        return float(emptySize)/totalSize;
    }
    else
    {
        std::cerr<<"Fatal error : ArchHandle damaged. Archive "<<archName<<"damaged. In_percentEmpty fn\n";
        return -1.0;
    }
}

void ArchiveManager::_copyArchive(std::fstream& archHandle, std::string archName, bool forceClean)
{
    /*
     * Copies one archive to another, and gets rid of empty space. Used to force clean too.
     */
    float emptyp = ARCH_COPY_EMPTY_THRESHOLD;
    if(forceClean == false)
        emptyp = _percentEmpty(archHandle,archName);

    bool flag = false;
    std::string newArch;

    //float emptyp = 0.3;
    if(emptyp != -1.0)
    {
        if(emptyp < 0 || emptyp >1.0)
        {
            std::cerr<<"Fatal error. Emptyp : "<<emptyp<<". Wrong empty size calculation in _copyArchive from DeletefromArchive\n";
            archHandle.close();
        }
        else if(emptyp >= ARCH_COPY_EMPTY_THRESHOLD)
        {
            newArch = std::string("_")+archName;
            std::ofstream write_new_arch(newArch,std::ios::binary | std::ios::out);

            if(write_new_arch.good())
            {
                flag=true;
                archHandle.clear();
                archHandle.seekg(0,archHandle.beg);
                Header h;
                AddDataToArchive d;
                h.deserialize(archHandle,0);

                while(h.locationTellg != -1) {
                    if(h.exists == true)
                    {
                        h.serialize(write_new_arch);
                        d.ArchtoArch(archHandle,write_new_arch,h.fileSize);
                    }
                    h.deserialize(archHandle, h.locationTellg + h.fileSize);//incrementing by file-size to get to next
                }
            }
            else
            {
                std::cerr<<"Cannot open newArch : "<<newArch<<" archive while overwritting in _copyArchive\n";
            }
            write_new_arch.close();
        }
    }
    else
    {
        std::cout<<"Arch "<<archName<<" doesn't exist\n";
    }
    archHandle.close();
    if(flag == true)
    {
        std::remove(archName.c_str());
        std::rename(newArch.c_str(),archName.c_str());
    }
}


void ArchiveManager::listArchive(int argc,const char* argv[]) {
    /*
     * Lists all the archives present
     */
    //() and "" not assumed
    if (argc == 3) {
        std::string archName = std::string(argv[2]);
        std::ifstream read_file;
        read_file.open(archName);
        if (!read_file.fail()) {
            Header h;
            h.deserialize(read_file);
            bool flag=false;
            while (h.locationTellg != -1) {
                if(h.exists)
                {
                    flag=true;
                    std::cout << h.name << "\t" << h.fileSize << "\t" << h.dateAdded << "\n";
                }
                h.deserialize(read_file, h.locationTellg + h.fileSize);
            }
            if(flag == false)
            {   std::cout<<"Archive is empty\n"; }
        }
        else{
        std::cout<<"Archive \""<<archName<<"\" does not exist \n";
        }
    } else if (argc == 4) {
        std::string archName = std::string(argv[2]);
        std::string fileName = std::string(argv[3]);

        std::ifstream read_file;
        read_file.open(archName);
        if (!read_file.fail()) {
    	    Header h;
	    fileName = parseFileName(fileName);
            if(fileExists(read_file,fileName,h)){
               std::cout << h.name << "\t" << h.fileSize << "\t" << h.dateAdded << "\n";
	    }
            else{
                std::cout<<"No such file exist in '"<<archName<<"' Archive\n";
            }
        }
    } else if(argc < 3){
        std::cout<<"No archive name is given\n";
    }
}

void ArchiveManager::find(int argc,const char* argv[]){
    /*
     * Finds a given string pattern in the archive.
     */
    std::string archName= std::string(argv[2]);
    std::string stringToMatch ;
    for(int ind = 3; ind < argc; ind++){
	stringToMatch += std::string(argv[ind]);
	if(ind != (argc-1)){
		stringToMatch += " ";
	}
    }


    std::ifstream read_file;
    read_file.open(archName);
    if(!read_file.fail()){
        Header h;
        h.deserialize(read_file);
        while(h.locationTellg!=-1) {
            if(h.type == "txt" && h.exists)
            {
                if(findinArchive(read_file,h.locationTellg,h.fileSize,stringToMatch)){
                    std::cout << h.name << "\t" << h.fileSize << "\t" << h.dateAdded << "\n";
                }
            }
            h.deserialize(read_file, h.locationTellg + h.fileSize);//incrementing by file-size to get to next
        }
    }
    else{
        std::cout<<"Archive \""<<archName<<"\" does not exist \n";
    }
}


bool ArchiveManager::findinArchive(std::istream& requiredFile, int positionToRead,int filesize, std::string str) {
    /*
     * Finds a given string pattern in the file with a given position and filesize
     */

    if (filesize > BUFF_Size) {
        char *Buffer = new char[BUFF_Size];
        int noOfChunks = (int)filesize / BUFF_Size;
        int offsetBytesToRead = (int)filesize % BUFF_Size;
        char *leftBytes = new char[offsetBytesToRead];
        requiredFile.seekg(positionToRead);

	std::string stringToFindIn = " ";
	std::string prev = " ";

        while (noOfChunks--) {
		requiredFile.read(Buffer, BUFF_Size);
		stringToFindIn = prev + std::string(Buffer);
		std::size_t found = stringToFindIn.find(str);
		if (found!=std::string::npos){
			return true;
		}
		prev.clear();
		stringToFindIn.clear();
		prev = std::string(Buffer);

        }
        requiredFile.read(leftBytes, offsetBytesToRead);
	stringToFindIn = prev + std::string(leftBytes);
	std::size_t found = stringToFindIn.find(str);
	if (found!=std::string::npos){
		return true;
	}

        delete[] Buffer;
        delete[] leftBytes;
    }
    else {

        char *Buffer = new char[filesize];
        requiredFile.seekg(positionToRead);
        requiredFile.read(Buffer, filesize);

	std::string stringToFindIn = std::string(Buffer);
	std::size_t found = stringToFindIn.find(str);
	if (found!=std::string::npos){
		return true;
	}
        delete[] Buffer;
    }
    return false;
}


bool ArchiveManager::fileExists(std::ifstream& read_file, std::string fileName, Header& h){
    /*
     * Check if a file exists in the archive.
     */
    fileName = parseFileName(fileName);
    h.deserialize(read_file,0);
    while (h.locationTellg != -1) {

        if (fileName == h.name && h.exists) {
            return true;
        }
        h.deserialize(read_file, h.locationTellg + h.fileSize);//incrementing by file-size to get to next
    }

    return false;
}