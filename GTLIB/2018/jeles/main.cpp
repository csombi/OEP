#include <iostream>
#include <sstream>
#include <string>

#include "./library/stringstreamenumerator.hpp"
#include "./library/maxsearch.hpp"
#include "./library/seqinfileenumerator.hpp"
#include "./library/summation.hpp"
#include "./library/enumerator.hpp"

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
    std::string tmp;
    std::stringstream ss( line );
    ss >> l.id >> tmp;

    StringStreamEnumerator<Observation> enor( ss );
    Sum s;
    s.addEnumerator( &enor );
    s.run();

    l.weight = s.result().weight;
    l.distance = s.result().distance;
  }
  //std::cout << "( StringStream<Line> ) " << l.id << " " << l.weight << " " << l.distance << std::endl;
  return is;
}

class MyMax : public MaxSearch<Line, int, Greater<int>>
{
protected:
  int func( const Line& l ) const override { return l.weight; }
  bool cond( const Line& l) const override { return l.distance; }

};

//  --------------  JELES ----------------

struct Blackhole
{
  std::string id;
  double avg_weight;
  bool every;
};

struct ResultOfSummation
{
  int sum_weight;
  int count;
  bool every;
};

class MySum : public Summation<Line, ResultOfSummation>
{
private:
  std::string _id;
public:
  MySum( const std::string& id ) : _id( id ) {}
protected:
  ResultOfSummation func( const Line& l ) const override
  {
    ResultOfSummation r;
    r.sum_weight = l.weight;
    r.count = 1;
    r.every = l.distance;
    return r;
  }
  ResultOfSummation neutral() const override
  {
    ResultOfSummation r;
    r.sum_weight = 0;
    r.count = 0;
    r.every = true;
    return r;
  }
  ResultOfSummation add( const ResultOfSummation& a, const ResultOfSummation& b ) const override
  {
    ResultOfSummation r;
    r.sum_weight = a.sum_weight + b.sum_weight;
    r.count = a.count + b.count;
    r.every = a.every && b.every;
    return r;
  }
  bool whileCond( const Line& l ) const override
  {
    return ( l.id == _id );
  }
  void first() override {}
};

class BlackholeEnor : public Enumerator<Blackhole>
{
private:
  Blackhole _current;
  SeqInFileEnumerator<Line> _t;
  bool _end;

public:
  BlackholeEnor( const std::string& filename ) : _t( filename ) {}
  void first() override
  {
    _t.first();
    next();
  }
  void next() override
  {
    if( !(_end = _t.end() ) )
    {
      _current.id = _t.current().id;
      MySum ms( _current.id );
      ms.addEnumerator( &_t );
      ms.run();
      //std::cout << "--" << ms.result().sum_weight << " " << ms.result().count << " " << ms.result().every << std::endl;
      _current.avg_weight = ms.result().sum_weight / (double)ms.result().count;
      _current.every = ms.result().every;
    }
  }
  bool end() const override
  {
    return _end;
  }
  Blackhole current() const override
  {
    return _current;
  }
};

class MyMaxJeles : public MaxSearch<Blackhole, int, Greater<int>>
{
protected:
  int func( const Blackhole& b ) const override { return b.avg_weight; }
};

int main( void )
{
  SeqInFileEnumerator<Line> enor( "input.txt" );

  /*
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().id << " " << enor.current().weight << " " << ( enor.current().distance ? "TRUE" : "FALSE") << std::endl;
  */

  //  KÖZEPES
  /*
  MyMax mm;
  mm.addEnumerator( &enor );
  mm.run();

  if( mm.found() )
    std::cout << mm.optElem().id << " " << mm.optElem().weight << std::endl;
  else
    std::cout << "Nincs ilyen elem.\n";

  */
  
  //  JELES
  BlackholeEnor benor( "input.txt" );

  /*
  for( benor.first(); !benor.end(); benor.next() )
    std::cout << benor.current().id << " "
              << benor.current().avg_weight << " "
              << benor.current().every << std::endl;
  */

  MyMaxJeles mmj;
  mmj.addEnumerator( &benor );
  mmj.run();

  if( mmj.found() )
    std::cout << mmj.optElem().id << " " << mmj.optElem().avg_weight << std::endl;
  else
    std::cout << "Nem volt ilyen elem.\n";

  return 0;
}
