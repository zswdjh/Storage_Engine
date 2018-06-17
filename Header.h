#ifndef Header_hpp
#define Header_hpp

#include "Serializable.h"
#include<string>
#include<vector>
#include <sstream>
#include<ctime>



#ifndef HEADER_MAX_SIZE       //added max size of header, use NAME_MAX_LEN, ROOTPATH_MAX, TYPE_MAX etc 
#define HEADER_MAX_SIZE 80
#endif


class Header : public Serializable{
	public:
		std::string name;
		std::string type;
		std::string dateAdded;
        	int locationTellg;
		unsigned long fileSize;
		bool exists;	
	
		Header();
		Header(std::string aName);
		std::string dualDigitFormat(int num);
		void parseFileName();
		void headerParser();
		void setType();
		void setDateAdded();
		void setFileSize();
		void transferToString(std::string& str, std::istream& in);
		void serialize(std::ostream& stream);
		void deserialize(std::istream& stream,int pos=0);
		int deserializeForDelete(std::istream& stream,std::string fname, int pos=0);
};


#endif
