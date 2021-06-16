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

struct Entry
{
  int hour;
  int users;
};

std::istream& operator>>( std::istream& is, Entry& e )
{
  return is >> e.hour >> e.users;
}

struct Server
{
  std::string name;
  int year;
  int month;
  int day;
  int sum_users;
};

class MySum : public Summation<Entry, int>
{
protected:
  int func( const Entry& e ) const override
  {
    return e.users;
  }
  int neutral() const override
  {
    return 0;
  }
  int add( const int& a, const int& b) const override
  {
    return ( a + b );
  }
};


std::istream& operator>>( std::istream& is, Server& s )
{
  std::string line;
  if( getline( is, line ) )
  {
    std::stringstream ss( line );
    ss >> s.name >> s.year >> s.month >> s.day;

    StringStreamEnumerator<Entry> enor( ss );
    MySum ms;
    ms.addEnumerator( &enor );
    ms.run();

    s.sum_users = ms.result();
  }
  return is;
}

class Max : public MaxSearch<Server, int, Greater<int> >
{
protected:
  int func(const Server& s) const override { return s.sum_users; }
  bool cond(const Server& s) const override { return s.month == 3; }
};

//---------------- JELES ---------------

struct Worst
{
  std::string name;
  int sum_users;
};

class MySumWorst : public Summation<Server, int>
{
private:
  std::string _name;
public:
  MySumWorst( const std::string& name ) : _name( name ) {}
protected:
  int neutral() const override
  {
    return 0;
  }
  int func( const Server& s ) const override
  {
    return s.sum_users;
  }
  int add( const int& a, const int& b ) const override
  {
    return a + b;
  }
  bool cond( const Server& s ) const override
  {
    return s.month == 3;
  }
  bool whileCond( const Server& s ) const override
  {
    return s.name == _name;
  }
  void first() override {}
};

class WorstEnor : public Enumerator<Worst>
{
private:
  SeqInFileEnumerator<Server> _t;
  Worst _current;
  bool _end;
public:
  WorstEnor( const std::string& name ) : _t( name ) {}
  enum Errors { NO_FILE };
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
      MySumWorst msw ( _current.name );
      msw.addEnumerator( &_t );
      msw.run();
      _current.sum_users = msw.result();
    }
  }
  Worst current() const override
  {
    return _current;
  }
  bool end() const override
  {
    return _end;
  }
};

class MyMax : public MaxSearch<Worst, int, Greater<int>>
{
protected:
  int func( const Worst& w ) const override
  {
    return w.sum_users;
  }
};

int main( void )
{

  try
  {
    std::string filename = "input.txt";
    //  KÖZEPES
    /*
    SeqInFileEnumerator<Server> enor( filename );
    */
    /*
    for( enor.first(); !enor.end(); enor.next() )
      std::cout << enor.current().name << " "
                << enor.current().year << " "
                << enor.current().month << " "
                << enor.current().day << " "
                << enor.current().sum_users << std::endl;
    */
    /*
    Max m;
    m.addEnumerator( &enor );
    m.run();

    std::cout << m.found() << std::endl;
    if( m.found() )
      std::cout << m.optElem().name << m.optElem().day << std::endl;
    else
      std::cout << "Nem volt ilyen.\n";
    */

    //  JELES
    WorstEnor enor( filename );

    /*
    for( enor.first(); !enor.end(); enor.next() )
      std::cout << enor.current().name << " "
                << enor.current().sum_users << std::endl;
    */

    MyMax mm;
    mm.addEnumerator( &enor );
    mm.run();

    if( mm.found() )
      std::cout << mm.optElem().name << std::endl;
    else
      std::cout << "Nem volt ilyen elem.\n";


  } catch( WorstEnor::Errors e )
  {
    std::cout << "A fájl nem létezik.\n";
  }



  return 0;
}
