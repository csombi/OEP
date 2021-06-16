#include "freq.h"

void solve( const std::string& i, const std::string& o ) {

	try {
		Enor enor( i );
		Outfile y( o );

		y.clear();
		enor.first();
		while( !enor.end() ) {
			y.write( enor.current() );
			enor.next();
		}

	} catch ( Error e ) {
		if( Error::FILE_ERROR == e ) std::cerr << "Error.\n";
	}
}

int main( void ) {
	solve( "input.txt", "output.txt" );
	return 0;
}
