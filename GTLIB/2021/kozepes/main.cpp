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

int main( void )
{

  try
  {
    std::string filename = "input.txt";
    SeqInFileEnumerator<Server> enor( filename );

    /*
    for( enor.first(); !enor.end(); enor.next() )
      std::cout << enor.current().name << " "
                << enor.current().year << " "
                << enor.current().month << " "
                << enor.current().day << " "
                << enor.current().sum_users << std::endl;
    */

    Max m;
    m.addEnumerator( &enor );
    m.run();

    std::cout << m.found() << std::endl;
    if( m.found() )
      std::cout << m.optElem().name << m.optElem().day << std::endl;
    else
      std::cout << "Nem volt ilyen.\n";

  } catch( SeqInFileEnumerator<Server>::Exceptions e )
  {
    std::cout << "A fájl nem létezik.\n";
  }



  return 0;
}
