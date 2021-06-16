#include <iostream>
#include <sstream>
#include <string>

#include "./library/stringstreamenumerator.hpp"
#include "./library/maxsearch.hpp"
#include "./library/seqinfileenumerator.hpp"
#include "./library/summation.hpp"

struct Line
{
  std::string id;
  int weight;
  bool distance = false;
};

struct Observation
{
  std::string date;
  int weight;
  int distance;
};

std::istream& operator>>( std::istream& is, Observation& o )
{
  is >> o.date >> o.weight >> o.distance;
  return is;
}

class Sum : public Summation<Observation, Line>
{
protected:
  Line func(const Observation& e) const override
  {
    Line l;
    l.weight = e.weight;
    l.distance = e.distance < 3;
    return l;
  }
  Line neutral() const override
  {
    Line l;
    return l;
  }
  Line add( const Line& a, const Line& b) const override
  {
    Line l;
    l.weight = b.weight;
    l.distance = a.distance || b.distance;
    return l;
  }
};

std::istream& operator>>( std::istream& is, Line& l )
{
  std::string line;
  if( getline( is, line ) )
  {
    std::stringstream ss( line );
    ss >> l.id ;

    StringStreamEnumerator<Observation> enor( ss );
    Sum s;
    s.addEnumerator( &enor );
    s.run();

    l.weight = s.result().weight;
    l.distance = s.result().distance;
  }
  return is;
}

class MyMax : public MaxSearch<Line, int, Greater<int>>
{
protected:
  int func( const Line& l ) const override { return l.weight; }
  bool cond( const Line& l) const override { return l.distance; }

};

int main( void )
{
  SeqInFileEnumerator<Line> enor( "input.txt" );

  
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().id << " " << enor.current().weight << " " << ( enor.current().distance ? "TRUE" : "FALSE") << std::endl;
  

  MyMax mm;
  mm.addEnumerator( &enor );
  mm.run();

  if( mm.found() )
    std::cout << mm.optElem().id << " " << mm.optElem().weight << std::endl;
  else
    std::cout << "Nincs ilyen elem.\n";

  return 0;
}
