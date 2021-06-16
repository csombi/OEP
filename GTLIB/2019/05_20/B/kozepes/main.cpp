#include <iostream>
#include <string>
#include <sstream>

#include "./library/stringstreamenumerator.hpp"
#include "./library/maxsearch.hpp"
#include "./library/seqinfileenumerator.hpp"
#include "./library/summation.hpp"
#include "./library/linsearch.hpp"



struct Result
{
  std::string name;
  std::string id;
  bool keszeg;
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

class MyMax : public MaxSearch<Fish, int, Greater<int>>
{
protected:
  int func( const Fish& f ) const override
  {
    return f.weight;
  }
};

std::istream& operator>>( std::istream& is, Result& r )
{
  std::string line;
  if( getline( is, line ) )
  {
    std::stringstream ss( line );
    ss >> r.name >> r.id;

    StringStreamEnumerator<Fish> enor( ss );
    MyMax mm;
    mm.addEnumerator( &enor );
    mm.run();

    if( mm.found() )
    {
      if( mm.optElem().type == "Keszeg" ) r.keszeg = true;
      else r.keszeg = false;
    }
    else
      r.keszeg = false;

  }
  return is;
}

class MyLinSearch : public LinSearch<Result, false>
{
protected:
  bool cond( const Result& r ) const override 
  {
    return r.keszeg;
  }
};

int main( void )
{

  SeqInFileEnumerator<Result> enor( "input.txt" );

  /*
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().name << " " << enor.current().id << " " << ( enor.current().keszeg ? "TRUE" : "FALSE" ) << std::endl;
  */

  MyLinSearch mls;
  mls.addEnumerator( &enor );
  mls.run();

  if( mls.found() )
    std::cout << mls.elem().name << " " << mls.elem().id << std::endl;
  else
    std::cout << "Nincs ilyen elem.\n";

  return 0;
}