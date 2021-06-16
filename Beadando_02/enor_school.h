#ifndef ENOR_SCHOOL_H_INCLUDED
#define ENOR_SCHOOL_H_INCLUDED

#include "enor.h"

struct School {
	std::string id;
	bool all;

	friend std::ostream& operator<<( std::ostream&, School& );
};

class EnorSchool {
	private:
		Status _st;
		Enor _x;
		Result _e;
		School _curr;
		bool _end;

	public:
		EnorSchool( const std::string& );
		void first();
		void next();
		School current() const;
		bool end() const;
};

#endif
