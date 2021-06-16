#include "enor.h"
#include "enor_school.h"

bool elso( const std::string& input, unsigned int& db, std::vector<std::string>& nev) {
	Enor t( input );

	Competitor elem;

	t.first();
	db = t.current().count;
	elem = t.current();
	t.next();
	while( !t.end() ) {
		if( db < t.current().count ) {
			db = t.current().count;
			elem = t.current();
		}
		t.next();
	}
	nev = elem.name;

	if( db == 0 ) return false;
	else return true;
}

bool masodik( const std::string& input, bool& l, std::string& id ) {
	EnorSchool t( input );
	School elem;

	l = false;
	t.first();
	while( !l && !t.end() ) {
		elem = t.current();
		l = elem.all;
		t.next();
	}

	if( l ) {
		id = elem.id;
		return true;
	} else return false;
}

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main( void ) {

	std::string input;

	std::cout << "------------------------------------\n";
	std::cout << "\tElső feladat\n";
	std::cout << "------------------------------------\n";

	std::cout << "input: ";
	std::cin >> input;

	try {
		unsigned int db;
		std::vector<std::string> nev;

		elso( input, db, nev);

		std::cout << "--> Legtöbb sportágban indult versenyző: ";
		for( std::string s : nev ) std::cout << s << " ";
		std::cout << std::endl;
		std::cout << "--> Ennyi sportágban indult: " << db << std::endl;
	} catch ( Error e ) {
		if( e == Error::FILE_OPEN_ERROR ) std::cerr << "Rossz input\n";
	}


	std::cout << "------------------------------------\n";
	std::cout << "\tMásodik feladat\n";
	std::cout << "------------------------------------\n";

	std::cout << "input: ";
	std::cin >> input;

	try {
		bool l;
		std::string id;

		masodik( input, l, id );

		if( l ) {
			std::cout << "--> Van olyan iskola, ahol minden versenyző legalább 3 sportágban indult.\n";
			std::cout << "--> Iskola: " << id << std::endl;
		} else {
			std::cout << "--> Nem volt olyan iskola, ahol minden versenyző legalább 3 sportágban indult volna.\n";
		}
	} catch( Error e ) {
		if( e == Error::FILE_OPEN_ERROR ) std::cerr << "Rossz input\n";
	}

	return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//ELSO
TEST_CASE("Rossz input", "nincsilyenfajl.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK_THROWS( elso( "nincsilyenfajl.txt", db, nev ) );
}
TEST_CASE("Üres fájl", "in0.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK_FALSE( elso( "in0.txt", db, nev) );
}
TEST_CASE("Egyetlen versenyző", "in1.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK( elso( "in1.txt", db, nev ) );
	CHECK( (nev[0] == "A" && nev[1] == "B") );
}
TEST_CASE("Több versenyző", "in2.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK( elso( "in2.txt", db, nev ) );
	CHECK( (nev[0] == "A" && nev[1] == "B" && nev[2] == "C") );
}
TEST_CASE("Több versenyző, első", "in3.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK( elso( "in3.txt", db, nev ) );
	CHECK( (nev[0] == "A" && nev[1] == "B" && nev[2] == "C" && nev[3] == "D") );
}
TEST_CASE("Több versenyző, utolsó", "in4.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK( elso( "in4.txt", db, nev ) );
	CHECK( (nev[0] == "A" && nev[1] == "B" && nev[2] == "C" && nev[3] == "D") );
}
TEST_CASE("Egy versenyző, ahol nincs helyezés", "in5.txt" )
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK_FALSE( elso( "in5.txt", db, nev ) );
	CHECK( db == 0 );
}
TEST_CASE("Egy versenyző, ahol egy helyezés van", "in6.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK( elso( "in6.txt", db, nev ) );
	CHECK( db == 1 );
}
TEST_CASE("Egy versenyző, ahol több helyezés van", "in7.txt")
{
	unsigned int db;
	std::vector<std::string> nev;
	CHECK( elso( "in7.txt", db, nev ) );
	CHECK( db == 3 );
}

//MASODIK
TEST_CASE("Rossz input2", "nincsilyenfajl.txt")
{
	std::string id;
	bool l;
	CHECK_THROWS( masodik( "nincsilyenfajl.txt", l, id) );
}
TEST_CASE("Üres fájl2", "in0.txt")
{
	std::string id;
	bool l;
	CHECK_FALSE( masodik( "in0.txt", l, id ) );
}
TEST_CASE("Egyetlen iskola", "in8.txt")
{
	std::string id;
	bool l;
	CHECK( masodik( "in8.txt", l , id ) );
	CHECK( id == "0001Suli" );
}
TEST_CASE("Több iskola", "in9.txt")
{
	std::string id;
	bool l;
	CHECK( masodik( "in9.txt" , l, id ) );
	CHECK( id == "0002Suli" );
}
TEST_CASE("Első iskola minden versenyzője min. 3 sportágban indult", "in10.txt" )
{
	std::string id;
	bool l;
	CHECK( masodik( "in10.txt", l, id) );
	CHECK( id == "0001Suli" );
}
TEST_CASE("Utolsó iskola minden versenyzője min. 3 sportágban indult", "in11.txt")
{
	std::string id;
	bool l;
	CHECK( masodik( "in11.txt", l, id ) );
	CHECK( id == "0003Suli" );
}
TEST_CASE("1 iskola, 1 versenyző, 0 indulás", "in12.txt")
{
	std::string id;
	bool l;
	CHECK_FALSE( masodik( "in12.txt", l, id ) );
}
TEST_CASE("1 iskola, 1 versenyző, 1 indulás", "in13.txt")
{
	std::string id;
	bool l;
	CHECK_FALSE( masodik( "in13.txt", l, id ) );
}
TEST_CASE("1 iskola, 1 versenyző, 2 indulás", "in14.txt")
{
	std::string id;
	bool l;
	CHECK_FALSE( masodik( "in14.txt", l, id ) );
}
TEST_CASE("1 iskola, 1 versenyző, 3 indulás", "in15.txt")
{
	std::string id;
	bool l;
	CHECK( masodik( "in15.txt", l, id ) );
}
#endif
