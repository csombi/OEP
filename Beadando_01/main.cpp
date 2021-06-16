#include "halmaz.h"
#include "menu.h"
#include <iostream>

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main(){

	Menu m;
	m.start();

	return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//TEST

TEST_CASE( "Empty set", "[setEmpty, isEmpty, add, del, isElement, countEven]")
{
	Halmaz h;
	CHECK( h.Halmaz::countEven() == 0 );
	CHECK( h.Halmaz::isEmpty() );
	h.add( 2 );
	CHECK( h.Halmaz::countEven() == 1 );
	unsigned int i;
	CHECK( h.Halmaz::isElement( 2, i ) );
	h.del( 2 );
	CHECK( h.Halmaz::isEmpty() );

}

TEST_CASE("6 elem in set", "[add, setEmpty, countEven]")
{
	Halmaz h;

	CHECK( h.Halmaz::isEmpty() );
	CHECK( h.Halmaz::countEven() == 0 );
	h.Halmaz::add( 1 );
	h.Halmaz::add( 2 );
	h.Halmaz::add( 3 );
	CHECK( h.Halmaz::countEven() == 1 );
	h.Halmaz::add( 4 );
	h.Halmaz::add( 5 );
	h.Halmaz::add( 6 );
	CHECK( h.Halmaz::countEven() == 3 );
	h.Halmaz::add( 6 );
	CHECK( h.Halmaz::countEven() == 3 );
	h.Halmaz::setEmpty();
	CHECK( h.Halmaz::isEmpty() );
}

TEST_CASE("Reading from file", "[add, fileReader, countEven, setEmpty]")
{
	Halmaz h;
	CHECK_THROWS( h.Halmaz::fileReader( "nosuchfile.txt" ) );
	CHECK( h.Halmaz::isEmpty() );
	h.Halmaz::fileReader( "t1.txt" ); // 1,2,3,4,5,6,7,8,9
	CHECK( 4 == h.Halmaz::countEven() );
	h.Halmaz::fileReader( "t2.txt" ); // 123213,23423,534,123,5345,534
	CHECK( 1 == h.Halmaz::countEven() );
	h.Halmaz::fileReader( "t3.txt" ); // 1,2,sadadqw,sa,d,qw,sad,2
	CHECK( 1 == h.Halmaz::countEven() );
	h.Halmaz::fileReader( "t4.txt" ); // a,b,c,d,e,f
	CHECK( 0 == h.Halmaz::countEven() );
	CHECK( h.Halmaz::isEmpty() );
}

TEST_CASE("Complex", "[add,del,linSearch,isElement]")
{
	Halmaz h;
	unsigned int i;
	h.Halmaz::add( 1 );
	h.Halmaz::add( 2 );
	h.Halmaz::add( 3 );
	CHECK( h.Halmaz::isElement( 3, i ) );
	CHECK( 1 == h.Halmaz::countEven() );
	h.Halmaz::del( 3 );
	CHECK( false == h.Halmaz::isElement( 3, i ) );
	h.Halmaz::del( 3 );
	CHECK( 1 == h.Halmaz::countEven() );
	h.Halmaz::fileReader( "t5.txt" ); // 3,5
	CHECK( 0 == h.Halmaz::countEven() );
	h.Halmaz::del( 3 );
	h.Halmaz::del( 5 );
	CHECK( h.Halmaz::isEmpty() );
	h.Halmaz::del( 1 );
}

TEST_CASE("1000 numbers", "[fileReader, add, countEven, setEmpty, isEmpty, isElement]")
{
	Halmaz h;
	unsigned int i;
	h.Halmaz::fileReader( "t6.txt" );
	CHECK( h.Halmaz::isElement( 1000, i ) );
	CHECK( 500 == h.Halmaz::countEven() );
	h.Halmaz::setEmpty();
	CHECK( h.Halmaz::isEmpty() );
}

#endif
