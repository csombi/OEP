#ifndef FREQ_H_INCLUDED
#define FREQ_H_INCLUDED

#include <iostream>
#include <fstream>


struct F {
	int number;
	unsigned int freq;

	friend std::ostream& operator<<( std::ostream&, const F& );
	friend std::istream& operator>>( std::istream&, F& );
};

enum Status { NORM, ABNORM };
enum Error { FILE_ERROR };

class Infile {
	private:
		std::ifstream f_;

	public:
		Infile();
		Infile( const std::string& );
		void read( int& , Status& );
		void close();
};

class Outfile {
	private:
		std::ofstream f_;

	public:
		Outfile( const std::string& );
		void write( const F& );
		void close();
		void clear();
};

class Enor {
	private:
		Status st_;
		F act_;
		Infile x_;
		int e_;
		bool done_;

	public:
		Enor( const std::string& );
		~Enor();
		void first();
		void next();
		bool end() const;
		F current() const;
};

#endif
