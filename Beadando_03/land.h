#ifndef LAND_H_INCLUDED
#define LAND_H_INCLUDED

#include <string>
#include <iostream>
class Weather;
class Air;


class Land
{
private:
protected:
  std::string _name;
  unsigned int _water;

  Land( const std::string&, unsigned int );
public:
  //  getters
  std::string get_name() const;
  unsigned int get_water() const;
  virtual std::string get_type() const = 0;

  //  setters
  void set_name( const std::string& );
  void set_water( unsigned int , bool );

  //  destructor
  virtual ~Land() {}

  //  tasks
  void interaction( Air* );
  virtual Land* interaction( Weather* ) = 0;

  //  communication
  friend std::ostream& operator<<( std::ostream&, const Land* );
  void template_method() const;
};

class Desert : public Land
{
private:
protected:
public:
  //  constructor
  Desert( const std::string&, unsigned int );

  //  getters
  std::string get_type() const override;

  //  tasks
  Land* interaction( Weather* ) override;
};

class Forest : public Land
{
private:
protected:
public:
  //  constructor
  Forest( const std::string&, unsigned int );

  //  getters
  std::string get_type() const override;

  //  tasks
  Land* interaction( Weather* ) override;
};

class Swamp : public Land
{
private:
protected:
public:
  //  constructor
  Swamp( const std::string&, unsigned int );

  //  getters
  std::string get_type() const override;

  //  tasks
  Land* interaction( Weather* ) override;
};

#endif
