#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "air.h"
#include "weather.h"
#include "land.h"

enum Errors { NO_FILE, NEGATIVE_NUMBER_OF_LANDS, NEGATIVE_NUMBER_WATER_SUPPLY, NEGATIVE_NUMBER_OF_HUMIDITY };

//  destruction
void destroy( Air*& air, Weather*& weather, std::vector<Land*>& lands )
{
    delete air;
    delete weather;
    for( std::vector<Land*>::iterator it = lands.begin(); it != lands.end(); it++ ) delete *(it);
}

//  random number generator
int randomize()
{
  srand( time(0) );
  return rand() % ( 100 + 1 );
}

//  setting the weather
void set_weather( Weather*& weather, Air*& air )    // Weather*&& Air*&&
{
  if( air->get_humidity() > 70 )
  {
    weather = Rainy::instance();
    air->set_humidity( 30, false );
  } else if( air->get_humidity() < 40 )
  {
    weather = Sunny::instance();
  } else
  {
    srand( time(NULL) );
    unsigned int random = randomize();
    //  a random szám 1x random, utána mindig azonos marad
    //std::cout << "### " << ( air->get_humidity() - 40 ) * 3.3  << " > " << random << std::endl;
    if( ( (air->get_humidity() - 40) * 3.3) > random )
    {
      weather = Rainy::instance();
    }
    else
    {
      weather = Cloudy::instance();
    }
  }
}

//  reading from file
void input( const std::string& filename, Air*& air, std::vector<Land*>& lands, Weather*& weather )
{
  std::ifstream f( filename );
  if( f.fail() ) throw Errors::NO_FILE;

  //  reading lands
  int n;
  f >> n;
  if( n < 0 ) throw Errors::NEGATIVE_NUMBER_OF_LANDS;
  else
  {
        std::string name;
      char type;
      int water;
      while( n-- )
      {
        f >> name >> type >> water;
        if( water < 0 ) throw Errors::NEGATIVE_NUMBER_WATER_SUPPLY;
        else
        {
          switch( type )
          {
          case 'p':
            lands.push_back( new Desert(name, water) );
            break;
          case 'z':
            lands.push_back( new Forest(name, water) );
            break;
          case 't':
            lands.push_back( new Swamp(name, water) );
            break;
          }
        }
      }

      //  reading initial humidity
      int humidity;
      f >> humidity;
      if( humidity < 0 ) throw Errors::NEGATIVE_NUMBER_OF_HUMIDITY;
      else
      {
        air->set_humidity( humidity, false );

        //  setting initial weather
        set_weather( weather, air );
      }

      /*
      air->set_humidity( humidity, false );

      //  setting initial weather
      set_weather( weather, air );
      */
  }

}

//  print
void print( Air*& air, Weather*& weather, std::vector<Land*>& lands, int round )
{
  std::cout << "============ ROUND " << round << " =============\n";
  std::cout << "WEATHER: " << weather;
  std::cout << "HUMIDITY OF AIR: " << air;
  std::cout << "DESCRIPTION OF LANDS: \n";
  for( std::vector<Land*>::iterator it = lands.begin(); it != lands.end(); it++ ) std::cout << "\t" << (*it);
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

//  print final
void print_final( Air*& air, Weather*& weather, std::vector<Land*>& lands )
{
  std::cout << "============ FINAL STATE =============\n";
  std::cout << "WEATHER: " << weather;
  std::cout << "HUMIDITY OF AIR: " << air;
  std::cout << "DESCRIPTION OF LANDS: \n";
  for( std::vector<Land*>::iterator it = lands.begin(); it != lands.end(); it++ ) std::cout << "\t" << (*it);
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

// optimist linear search
bool every( std::vector<Land*>& lands )
{
  bool l = true;
  std::string t = lands[0]->get_type();
  std::vector<Land*>::iterator it = lands.begin() + 1;
  while( l && it != lands.end() )
  {
    l = l && ( (*it)->get_type() == t );
    it++;
  }
  return l;
}

//  solve
int solve( Air*& air, Weather*& weather, std::vector<Land*>& lands )
{
  int rounds = 1;
  while( !every( lands ) )
  {
    print( air, weather, lands, rounds );
    // lands react to the weather
    for( std::vector<Land*>::iterator it = lands.begin(); it != lands.end(); it++ )
    {
      //  changing humidity of air
      air->change( (*it) );

      //  changing water supply
      (*it) = (*it)->interaction( weather );
    }

    //  setting the weather for the next round
    set_weather( weather, air );

    rounds++;
  }
  return rounds;
}

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main( void )
{
  //  input data
  Air* air = new Air();
  Weather* weather;
  std::vector<Land*> lands;

  //  reading from the input file
  try
  {
    input( "input.txt", air, lands, weather );
  } catch( Errors e )
  {
    if( e == Errors::NO_FILE )
    {
      std::cout << "Could not open the file.\n";
      exit(1);
    }else if( e == Errors::NEGATIVE_NUMBER_OF_LANDS )
    {
      std::cout << "Negative number of lands.\n";
      exit(1);
    }else if( e == Errors::NEGATIVE_NUMBER_WATER_SUPPLY )
    {
      std::cout << "Negative number of water supply.\n";
      exit(1);
    }else if( e == Errors::NEGATIVE_NUMBER_OF_HUMIDITY)
    {
      std::cout << "Negative number of humidity.\n";
      exit(1);
    }

  }

  //lands[0]->template_method();

  //  solve
  int rounds = solve( air, weather, lands );

  //  final state
  print_final( air, weather, lands );

  //  free memory
  destroy( air, weather, lands );

  return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "no input", "randominputname.txt")
{
  Air* air;
  Weather* weather;
  std::vector<Land*> lands;

  CHECK_THROWS( input( "randominputname.txt", air, lands, weather ) );
}
TEST_CASE( "negative number of lands", "i1.txt")
{
  Air* air;
  Weather* weather;
  std::vector<Land*> lands;

  CHECK_THROWS( input( "i1.txt", air, lands, weather ) );
}
TEST_CASE( "negative number of water supply", "i2.txt")
{
  Air* air;
  Weather* weather;
  std::vector<Land*> lands;

  CHECK_THROWS( input( "i2.txt", air, lands, weather ) );
}
TEST_CASE( "negative number of humdity", "i3.txt")
{
  Air* air;
  Weather* weather;
  std::vector<Land*> lands;

  CHECK_THROWS( input( "i3.txt", air, lands, weather ) );
}
TEST_CASE( "one land", "i4.txt" )
{
    Air* air;
    Weather* weather;
    std::vector<Land*> lands;
    input( "i4.txt", air, lands, weather );
    int r = solve( air, weather, lands );
    CHECK( r == 1 );
}
TEST_CASE( "one round only", "i5.txt" )
{
    Air* air;
    Weather* weather;
    std::vector<Land*> lands;
    input( "i5.txt", air, lands, weather );
    int r = solve( air, weather, lands );
    CHECK( r == 2 );
    //destroy( air, weather, lands);
}
TEST_CASE( "rainy", "i6.txt")
{
    Air* air;
    Weather* weather;
    std::vector<Land*> lands;
    input( "i6.txt", air, lands, weather );
    CHECK( weather->get_type() == "Rainy" );
    //destroy( air, weather, lands);
}
TEST_CASE( "napos", "i7.txt")
{
    Air* air;
    Weather* weather;
    std::vector<Land*> lands;
    input( "i7.txt", air, lands, weather );
    CHECK( weather->get_type() == "Sunny" );
    //destroy( air, weather, lands);
}



#endif
