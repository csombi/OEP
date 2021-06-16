#include "halmaz.h"
#include <iostream>
#include <fstream>

Halmaz::Halmaz() { Halmaz::setEmpty(); }

void Halmaz::setEmpty() {
	_vec.clear();
	_even_numbers = 0;
}

bool Halmaz::isEmpty() const {
	if( _vec.size() == 0 ) return true;
	else return false;
}

bool Halmaz::linSearch( const std::vector<int>& v, const int e, unsigned int& index ) const {
	bool l = false;
	unsigned int i = 0;
	while( !l && i < v.size() ) {
		l = (v[i] == e);
		if( l ) index = i;
		i += 1;
	}

	return l;
}

bool Halmaz::isElement( int e, unsigned int& i ) const {
	return Halmaz::linSearch( _vec, e, i);
}

void Halmaz::add( int e ){
	unsigned int ind;

	if( Halmaz::linSearch( _vec, e, ind ) ) std::cerr << "--> Element is already in set! \n";
	else {
		//Ha paros szamot tettunk bele --> _even_numbers++
		if( e % 2 == 0 ) _even_numbers++;

		_vec.insert( _vec.end(), e );
		std::cout << "--> Element added. \n";
	}
}

void Halmaz::del( int e ){
	unsigned int ind;

	if ( !Halmaz::linSearch( _vec, e, ind ) ) std::cerr << "--> Element is not in set! \n";
	else{
		if( e % 2 == 0 ) _even_numbers--;

		_vec.erase( _vec.begin() + ind );
		std::cout << "--> Element deleted. \n";
	}
}

unsigned int Halmaz::countEven( ) const {
	return _even_numbers;
}

void Halmaz::print( ) const {
	std::cout << "===== SET ELEMENTS BY PRINT() =====\n";
	unsigned int index = 1;
	for( auto e : _vec ){
		std::cout << index << ": " << e << "\n";
		index++;
	}
	std::cout << "===================================\n";
}

void Halmaz::fileReader( std::string path) {
	std::ifstream f( path );
	if( f.fail() ) throw( FileOpenError );
	f >> *this;
}

std::ostream& operator<<( std::ostream& os, const Halmaz& h ){
	os << "========== SET ELEMENTS ==========\n";
	os << "{ ";
	for( auto e : h._vec ) os << e << " ";
	os << "}\n";
	os << "==================================\n";
	return os;
}

std::istream& operator>>( std::istream& is, Halmaz& h ) {
	h.setEmpty();
	std::cout << "--> Set is cleared.\n";
	int e;

	while( is >> e ) h.add(e);

	return is;
}
