#include "weather.h"
#include "land.h"

//  SUNNY
Sunny* Sunny::_instance = nullptr;
std::string Sunny::get_type() const { return "Sunny"; }

void Sunny::change( Desert* d ) { d->set_water( -3, true ); }
void Sunny::change( Forest* f ) { f->set_water( -6, true ); }
void Sunny::change( Swamp* s )  { s->set_water( -10, true); }

Sunny* Sunny::instance() { if( _instance == nullptr ) _instance = new Sunny(); return _instance; }
void Sunny::destroy() { if( nullptr != _instance ) { delete _instance; _instance = nullptr; } }

//  CLOUDY
Cloudy* Cloudy::_instance = nullptr;
std::string Cloudy::get_type() const { return "Cloudy"; }

void Cloudy::change( Desert* d ) { d->set_water( -1, true ); }
void Cloudy::change( Forest* f ) { f->set_water( -2, true ); }
void Cloudy::change( Swamp* s )  { s->set_water( -3, true ); }

Cloudy* Cloudy::instance() { if( _instance == nullptr ) _instance = new Cloudy(); return _instance; }
void Cloudy::destroy() { if( nullptr != _instance ) { delete _instance; _instance = nullptr; } }

//  RAINY
Rainy* Rainy::_instance = nullptr;
std::string Rainy::get_type() const { return "Rainy"; }

void Rainy::change( Desert* d ) { d->set_water( 5, true ); }
void Rainy::change( Forest* f ) { f->set_water( 10, true); }
void Rainy::change( Swamp* s )  { s->set_water( 15, true); }

Rainy* Rainy::instance() { if( _instance == nullptr ) _instance = new Rainy(); return _instance; }
void Rainy::destroy() { if( nullptr != _instance ) { delete _instance; _instance = nullptr; } }


//  BASE CLASS
std::ostream& operator<<( std::ostream& os, const Weather* w )
{
  os << w->get_type() << std::endl;
  return os;
}