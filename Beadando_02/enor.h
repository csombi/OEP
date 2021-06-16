#ifndef ENOR_H_INCLUDED
#define ENOR_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct Competitor {
	std::vector<std::string> name;
	std::string school;
	unsigned int count;

	friend std::ostream& operator<<( std::ostream&, Competitor& );
};

struct Result {
	std::vector<std::string> name;
	std::string id;
	std::vector<std::pair<std::string,unsigned int>> place;

	friend std::istream& operator>>( std::istream&, Result& );
};

enum Status{ NORM, ABNORM };
enum Error{ FILE_OPEN_ERROR };

//INFILE
class Infile {
	private:
		std::ifstream _f;

	public:
		Infile();
		Infile( const std::string& );
		void read( Result&, Status& );
		void close();
};

class Enor {
	private:
		Status _st;
		Infile _x;
		Result _e;
		Competitor _curr;
		bool _end;

	public:
		Enor();
		Enor( const std::string& );
		~Enor();
		void setEmptyComp();
		void setEmptyRes();
		void first();
		void next();
		Competitor current() const;
		bool end() const;
};

#endif
