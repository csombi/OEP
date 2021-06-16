#include <iostream>
#include <string>
#include <sstream>

#include "./library/stringstreamenumerator.hpp"
#include "./library/maxsearch.hpp"
#include "./library/seqinfileenumerator.hpp"
#include "./library/summation.hpp"

struct Result
{
  std::string name;
  std::string id;
  int fish = 0;
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

class MySummation : public Summation<Fish, Result>
{
protected:
  Result func(const Fish& e) const override
  {
    Result r;
    if( e.type == "Ponty" ) r.fish = 1;
    else r.fish = 0;
    return r;
  }
  Result neutral() const override
  {
    Result r;
    return r;
  }
  Result add( const Result& a, const Result& b) const override
  {
    Result r;
    r.fish = a.fish + b.fish;
    return r;
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
    MySummation ms;
    ms.addEnumerator( &enor );
    ms.run();

    r.fish = ms.result().fish;
  }
  return is;
}

class MyMax : public MaxSearch<Result, int, Greater<int>>
{
protected:
  int func( const Result& e ) const override { return e.fish; }
};

int main( void )
{
  std::string filename = "input.txt";
  SeqInFileEnumerator<Result> enor( filename );

  /*
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().name << " " << enor.current().id << " " << enor.current().fish << std::endl;
  */

  MyMax mm;
  mm.addEnumerator( &enor );
  mm.run();

  if( mm.found() )
    std::cout << mm.optElem().name << " " << mm.optElem().id << " " << mm.optElem().fish << " " << std::endl;
  else
    std::cout << "Nincs ilyen elem.\n";

  return 0;
}