#ifndef AIR_H_INCLUDED
#define AIR_H_INCLUDED

#include <iostream>
class Land;

class Air
{
private:
  unsigned int _humidity;
protected:
public:
  //  constructor
  Air();
  Air( unsigned int );

  //  getter
  unsigned int get_humidity() const;

  //  setter
  void set_humidity( unsigned int, bool = false );

  //  tasks
  void change( Land* );

  //  communication
  friend std::ostream& operator<<( std::ostream&, const Air* );
};

#endif
