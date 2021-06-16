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
  int sum_weight;
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

class MySum : public Summation<Fish, int>
{
protected:
  int func( const Fish& f ) const override
  {
    return f.weight;
  }
  int neutral() const override
  {
    return 0;
  }
  int add( const int& a, const int& b ) const override
  {
    return a + b;
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
    MySum ms;
    ms.addEnumerator( &enor );
    ms.run();

    f.sum_weight = ms.result();
  }
  return is;
}

class MySearch : public LinSearch<Fisherman, false>
{
protected:
  bool cond( const Fisherman& f ) const override
  {
    return f.sum_weight > 10;
  }
};

int main( void )
{

  SeqInFileEnumerator<Fisherman> enor( "input.txt" );

  /*
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().name << " " 
              << enor.current().comp << " " 
              << enor.current().sum_weight << std::endl;
  */

  MySearch ms;
  ms.addEnumerator( &enor );
  ms.run();

  if( ms.found() )
    std::cout << ms.elem().name << " " << ms.elem().comp << std::endl;
  else
    std::cout << "Nem volt ilyen.\n";

  return 0;
}

