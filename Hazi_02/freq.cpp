#include "freq.h"

std::ostream& operator<<( std::ostream& os, const F& f ) {
	os << "(" << f.number << "," << f.freq << ")";
	return os;
}

std::istream& operator>>( std::istream& is, F& f ) {
	is >> f.number;
	f.freq = 0;
	return is;
}

Infile::Infile() {}

Infile::Infile( const std::string& fname ) {
	f_.open( fname.c_str() );
	if( f_.fail() ) throw Error::FILE_ERROR;
}

void Infile::read( int& e, Status& st ) {
	f_ >> e;
	if( f_.fail() ) st = Status::ABNORM;
}

void Infile::close() { f_.close(); }

Outfile::Outfile( const std::string& fname ) {
	f_.open( fname.c_str() );
	if( f_.fail() ) {
		throw Error::FILE_ERROR;
	}
}

void Outfile::clear() { f_.clear(); }

void Outfile::write( const F& f ) {
	f_ << f << std::endl;
}

void Outfile::close() { f_.close(); }

Enor::Enor( const std::string& fname ) {
	try {
		x_ = Infile( fname );
		st_ = Status::NORM;
	} catch ( Error e ) {
		throw e;
	}
}

Enor::~Enor() { x_.close(); }

void Enor::first() {
	x_.read( e_, st_ );
	next();
}

void Enor::next() {
	done_ = st_ == Status::ABNORM;
	if( !done_ ) {
		act_.number = e_;
		act_.freq = 0;
		while( st_ == Status::NORM && e_ == act_.number ) {
			act_.freq++;
			x_.read( e_, st_ );
		}
	}
}

bool Enor::end() const { return done_; }

F Enor::current() const { return act_; }
