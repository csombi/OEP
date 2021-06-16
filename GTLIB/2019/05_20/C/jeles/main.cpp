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

//------------------- JELES ---------------------------

struct Angler
{
  std::string name;
  int sum_weight;
};

class MySumAngler : public Summation<Fisherman, int>
{
private:
  std::string _name;
public:
  MySumAngler( const std::string& name ) : _name( name ) {}
protected:
  int neutral() const override
  {
    return 0;
  }
  int func( const Fisherman& f ) const override
  {
    return f.sum_weight;
  }
  int add( const int& a, const int& b ) const override
  {
    return a + b;
  }
  bool whileCond( const Fisherman& f ) const override
  {
    return f.name == _name;
  }
  void first() override {}
};

class AnglerEnor : public Enumerator<Angler>
{
private:
  SeqInFileEnumerator<Fisherman> _t;
  Angler _current;
  bool _end;
public:
  AnglerEnor( const std::string& filename ) : _t( filename ) {}
  void first() override
  {
    _t.first();
    next();
  }
  void next() override
  {
    if( !( _end = _t.end() ) )
    {
      _current.name = _t.current().name;
      MySumAngler msa( _current.name );
      msa.addEnumerator( &_t );
      msa.run();

      _current.sum_weight = msa.result();
    }
  }
  Angler current() const override
  {
    return _current;
  }

  bool end() const override
  {
    return _end;
  }
};

class MyMin : public MaxSearch<Angler, int, Less<int>>
{
protected:
  int func( const Angler& a ) const override
  {
    return a.sum_weight;
  }
  bool cond( const Angler& a ) const override
  {
    return a.sum_weight > 40;
  }
};

int main( void )
{

  //SeqInFileEnumerator<Fisherman> enor( "input.txt" );

  /*
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().name << " " 
              << enor.current().comp << " " 
              << enor.current().sum_weight << std::endl;
  */

  //  KÖZEPES
  /*
  MySearch ms;
  ms.addEnumerator( &enor );
  ms.run();

  if( ms.found() )
    std::cout << ms.elem().name << " " << ms.elem().comp << std::endl;
  else
    std::cout << "Nem volt ilyen.\n";

  */

  //  JELES
  AnglerEnor enor( "input.txt" );

  /*
  for( enor.first(); !enor.end(); enor.next() )
    std::cout << enor.current().name << " " 
              << enor.current().sum_weight << std::endl;
  */

  MyMin mm;
  mm.addEnumerator( &enor );
  mm.run();

  if( mm.found() )
    std::cout << mm.optElem().name << " " << mm.optElem().sum_weight << std::endl;
  else
    std::cout << "Nem volt ilyen.\n";

  return 0;
}

