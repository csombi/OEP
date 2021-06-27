#include "air.h"
#include "land.h"

Air::Air() : _humidity( 0 ) {}
Air::Air( unsigned int h ) : _humidity( h ) {}

unsigned int Air::get_humidity() const { return _humidity; }

void Air::set_humidity( unsigned int h, bool change )
{
  if( change )
  {
    _humidity += h;
  }
  else
  {
    _humidity = h;
  }
}

void Air::change( Land* l )
{
  if( l->get_type() == "Desert" ) _humidity += 3;
  else if( l->get_type() == "Forest" ) _humidity += 7;
  else _humidity += 10;
}

std::ostream& operator<<( std::ostream& os, const Air* a )
{
  os << a->get_humidity() << std::endl;
  return os;
}
