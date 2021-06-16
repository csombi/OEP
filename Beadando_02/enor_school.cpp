#include "enor_school.h"

std::ostream& operator<<( std::ostream& os, School& sch ) {
	os << "Iskola azonosítója: " << sch.id << std::endl;
	os << "Minden versenyző legalább 3 sportágban indult: " << (sch.all ? "igen." : "nem.") << std::endl;
	return os;
}

EnorSchool::EnorSchool( const std::string& filename ): _x( filename) {};

void EnorSchool::first() {
	_x.first();
	next();
}

void EnorSchool::next() {
	_end = _x.end();
	if( !_end ) {
		_curr.id = _x.current().school;
		_curr.all = true;
		while( !_x.end() && _x.current().school == _curr.id ) {
			_curr.all = _curr.all && (_x.current().count >= 3 );
			_x.next();
		}
	}
}

School EnorSchool::current() const { return _curr; }

bool EnorSchool::end() const { return _end; }
