#ifndef Serializable_h
#define Serializable_h

#include<fstream>
#include<iostream>


class Serializable{
	public:
		Serializable(){}
		virtual ~Serializable(){}
		virtual void serialize(std::ostream& stream) = 0;
		virtual void deserialize(std::istream& stream, int pos=0) = 0;
};

#endif
