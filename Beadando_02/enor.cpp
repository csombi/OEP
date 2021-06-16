#include "enor.h"

Infile::Infile() {}

Infile::Infile( const std::string& filename ) {
	_f.open( filename.c_str() );
	if( _f.fail() )
		throw Error::FILE_OPEN_ERROR;
}

void Infile::read( Result& r, Status& st ) {
	_f >> r;
	if( _f.fail() )
		st = Status::ABNORM;
}

void Infile::close() {
	_f.close();
}

std::ostream& operator<<( std::ostream& os, Competitor& c ) {
	for( std::string s : c.name ) os << s << " ";
	os << "--> sportágak száma: " << c.count << std::endl;
	return os;
}

std::istream& operator>>( std::istream& is, Result& r ) {
	std::string line;
	std::getline( is, line );
	std::istringstream iss( line );
	std::string curr_string;

	//Név beolvasása
	iss >> curr_string;

	while( ((int)(curr_string[0]) > 57 || (int)(curr_string[0]) < 48 ) && iss ) {
		r.name.push_back( curr_string );
		iss >> curr_string;
	}

	//Azonosító beolvasása
	r.id = curr_string;

	//Helyezések beolvasása
	std::string frst;
	unsigned int scnd;

	while( iss >> frst >> scnd ) {
		r.place.push_back( std::make_pair(frst, scnd) );
	}

	return is;
}

Enor::Enor() {}

Enor::Enor( const std::string& filename ) {
	try {
		_x = Infile( filename );
		_st = Status::NORM;
	} catch( Error e ) {
		throw e;
	}
}

Enor::~Enor() { _x.close(); }

void Enor::setEmptyRes() {
	_e.name.clear();
	_e.id.clear();
	_e.place.clear();
}

void Enor::setEmptyComp() {
	_curr.name.clear();
	_curr.count = 0;
}

void Enor::first() {
	setEmptyRes();
	_x.read( _e, _st );
	Enor::next();
}

void Enor::next() {
	setEmptyComp();
	_end = ( _st == Status::ABNORM );
	if( !_end ) {
		_curr.name = _e.name;
		_curr.school = _e.id;
		for( long unsigned int i = 0; i < _e.place.size(); i++ ) _curr.count++;
		setEmptyRes();
		_x.read( _e, _st );
	}
}

Competitor Enor::current() const { return _curr; }

bool Enor::end() const { return _end; }
