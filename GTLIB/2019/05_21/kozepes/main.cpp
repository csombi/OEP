#include <iostream>
#include <string>
#include <sstream>

#include "./library/arrayenumerator.hpp"
#include "./library/counting.hpp"
#include "./library/enumerator.hpp"
#include "./library/intervalenumerator.hpp"
#include "./library/linsearch.hpp"
#include "./library/maxsearch.hpp"
#include "./library/selection.hpp"
#include "./library/seqinfileenumerator.hpp"
#include "./library/stringstreamenumerator.hpp"
#include "./library/summation.hpp"


struct Fisherman
{
  std::string name;
  std::string comp;
  bool small;
};

struct Fish
{
  std::string type;
  int weight;
};

std::istream& operator>>( std::istream& is, Fish& f )
{
  return is >> f.type >> f.weight;
}

class MySearch : public LinSearch<Fish, false>
{
protected:
  bool cond( const Fish& f ) const override
  {
    return ( f.type == "Ponty" && f.weight < 0.8 );
  }
};

std::istream& operator>>( std::istream& is, Fisherman& f )
{
  std::string line;
  if( getline( is, line ) )
  {
    std::stringstream ss( line );
    ss >> f.name >> f.comp;

    StringStreamEnumerator<Fish> enor( ss );
    MySearch ms;
    ms.addEnumerator( &enor );
    ms.run();

    if( ms.found() ) f.small = true;
    else f.small = false;
  }
  return is;
}

class MyCount : public Counting<Fisherman>
{
protected:
  bool cond( const Fisherman& f ) const override
  {
    return f.small;
  }
};

/*
class MyCount : public Summation<Fisherman, int>
{
protected:
  int func( const Fisherman& f ) const override
  {
    return 1;
  }
  int neutral() const override
  {
    return 0;
  }
  int add( const Fisherman& a, const Fisherman& b ) const override
  {
    return 1 + 1;
  }
  bool cond( const Fisherman& f ) const override
  {
    return f.small;
  }
};

*/

int main( void )
{

  //  KÖZEPES
  SeqInFileEnumerator<Fisherman> enor( "input.txt" );

  /*
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().name << " " 
              << enor.current().comp << " " 
              << enor.current().small << std::endl;
  */

  MyCount mc;
  mc.addEnumerator( &enor );
  mc.run();

  std::cout << mc.result() << std::endl;

  return 0;
}