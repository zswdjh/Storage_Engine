#include "Header.h"


/*
 * Constructor to header
 */
Header::Header(){}

Header::Header(std::string aName):name(aName){
	/*
	 * Parameterized constructor to update fileName
	 */
	headerParser();
	exists = true;		// File Exists
}	

void Header::headerParser(){
	/*
	 * Parses the header info
	 */
	setType();	
	setDateAdded();
	setFileSize();
	parseFileName();
}

void Header::parseFileName(){
	/*
	 * Parses filename
	 */

  std::string theString = name;
  std::istringstream theStream(theString);

  while (!theStream.eof()) {     
    std::string theWord;      
    getline( theStream, theWord, '/' );  
    if(theWord.length()){
		name = theWord;
    }
  }

}

void Header::setType(){
	/*
	 * Sets type
	 */
	std::string delimiter = ".";
	size_t pos = name.find(delimiter);
	if(pos != std::string::npos)
		type = name.substr(pos+1, name.size());
	else
		type = "";  // Handles files with no type names
}


std::string Header::dualDigitFormat(int num){
	/*
	 * Sets date,month and year in dualDigitalFormat
	 */
	std::string aResult;
	if(num<10){ aResult.push_back('0'); }
	aResult += std::to_string(num);
	return aResult;
}

void Header::setDateAdded(){
	/*
	 * Sets date
	 */
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	dateAdded = dualDigitFormat(timeinfo->tm_mon+1) + "/"
                + dualDigitFormat(timeinfo->tm_mday) +"/"
                + std::to_string(timeinfo->tm_year + 1900);

}
void Header::setFileSize(){
	/*
	 * Sets filesize
	 */
	std::ifstream source(name, std::ios::binary);
	if(source.good()){
		source.seekg(0, std::ios::end);
		fileSize = source.tellg();
		source.seekg (0, source.beg);
	}
	else
	{
		std::cerr<<"Cannot open file "<<name<<" in Header::setFileSize(). Fatal error";
	}
    source.close();
}

void Header::serialize(std::ostream& stream){
	/*
	 * Serializes and writes header into stream
	 */
	stream <<",";
	stream <<name.size();
	stream <<",";
	stream << name;
	stream <<",";
	stream << type.size();
	stream <<",";
	stream<< type;
	stream <<",";
	stream << dateAdded.size();
	stream <<",";
	stream << dateAdded;
	stream <<",";
	stream << fileSize;
	stream <<",";
	stream << exists;
}

void Header::transferToString(std::string& str, std::istream& in){
	/*
	 * Transfers contents from string to header
	 */
	char comma;
	int length;
	in >> length;
	in >> comma;
	if (in && length) {
	    std::vector<char> temp(length);
	    in.read(temp.data() , length); 
	    str.assign(temp.data(), length);
	}
	in >> comma;
}

void Header::deserialize(std::istream& stream, int pos){
	/*
	 * Deserializes the contents of the stream
	 */
    stream.seekg(pos);
	char comma;
	stream >> comma;
	transferToString(name, stream);			// Retrieve name
	transferToString(type, stream);			// Retrieve type
	transferToString(dateAdded, stream);	// Retrieve date added
	stream >> fileSize;						// Retrieve Size
	stream >> comma;
	stream >> exists;						// Retrieve Exists
    locationTellg=stream.tellg();
}

int Header::deserializeForDelete(std::istream& stream,std::string fname,int pos) {
	/*
	 * Deserializes the content of files for delete() function
	 */
    stream.seekg(pos);
    int currLoc = -1;
    char comma;
    stream >> comma;
    transferToString(name, stream);			// Retrieve name
    transferToString(type, stream);			// Retrieve type
    transferToString(dateAdded, stream);	// Retrieve date added
    stream >> fileSize;						// Retrieve Size
    stream >> comma;
    stream >> exists;						// Retrieve Exists
    locationTellg=stream.tellg();
    if(name == fname && exists && locationTellg!=-1)
        currLoc = pos;
    return currLoc;
}