#include "air.h"
#include "weather.h"
#include "land.h"

//  BASE CLASS
//  constructor
Land::Land( const std::string& name, unsigned int water ) : _name( name ), _water( water ) {}

//  getters
std::string Land::get_name() const { return _name; }
unsigned int Land::get_water() const { return _water; }

//  setters
void Land::set_name( const std::string& name ) { _name = name; }
void Land::set_water( unsigned int n, bool change)
{
  if( change ) _water += n;
  else _water = n;
}

//  tasks
void Land::interaction( Air* a) { a->change( this ); }
//Land* Land::interaction( Weather* w ) { w->change( this ); return this; }

//  communicaton
std::ostream& operator<<( std::ostream& os, const Land* l )
{
  os << l->get_name() << "\t" << l->get_water() << "\t" << l->get_type() << std::endl;
  return os;
}

void Land::template_method() const
{
  std::cout << get_name() << " " << get_water() << " " << get_type() << std::endl;
}

//  DESERT
//  consrtuctor
Desert::Desert( const std::string& name, unsigned int water ) : Land( name, water ) {}

//  getters
std::string Desert::get_type() const { return "Desert"; }

Land* Desert::interaction( Weather* w )
{
  //  change water supply
  w->change( this );

  //  update land

  if( this->get_water() > 15 )
  {
    std::string name = this->get_name();
    unsigned int water = this->get_water();
    delete this;
    return new Forest( name, water );
  }

  return this;
}

//  FOREST
//  consrtuctor
Forest::Forest( const std::string& name, unsigned int water ) : Land( name, water ) {}

//  getters
std::string Forest::get_type() const { return "Forest"; }

Land* Forest::interaction( Weather* w )
{
  w->change( this );

  if( this->get_water() < 16 )
  {
    std::string name = this->get_name();
    unsigned int water = this->get_water();
    delete this;
    return new Desert( name, water );
  } else if( this->get_water() > 50 )
  {
    std::string name = this->get_name();
    unsigned int water = this->get_water();
    delete this;
    return new Swamp( name, water );
  }
  return this;
}

//  SWAMP
//  consrtuctor
Swamp::Swamp( const std::string& name, unsigned int water ) : Land( name, water ) {}

//  getters
std::string Swamp::get_type() const { return "Swamp"; }

Land* Swamp::interaction( Weather* w )
{
  w->change( this );

  if( this->get_water() < 51 )
  {
    std::string name = this->get_name();
    unsigned int water = this->get_water();
    delete this;
    return new Forest( name, water );
  }
  return this;
}
