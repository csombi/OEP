#ifndef WEATHER_H_INCLUDED
#define WEATHER_H_INCLUDED

#include <iostream>
#include <string>
class Land;
class Desert;
class Forest;
class Swamp;

class Weather
{
private:
protected:
public:
  //  getters
  virtual std::string get_type() const = 0;
  
  //  destructors
  virtual ~Weather() {}

  //  tasks
  virtual void change( Desert* ) = 0;
  virtual void change( Forest* ) = 0;
  virtual void change( Swamp* )  = 0;

  //  communication
  friend std::ostream& operator<<( std::ostream&, const Weather* );
};

class Sunny : public Weather
{
private:
  static Sunny* _instance;
protected:
  Sunny() {}
public:
  //  getters
  std::string get_type() const override;

  //  tasks
  void change( Desert* ) override;
  void change( Forest* ) override;
  void change( Swamp* )  override;

  //  singleton
  static Sunny* instance();
  static void destroy();
};

class Cloudy : public Weather
{
private:
  static Cloudy* _instance;
protected:
  Cloudy() {}
public:
  //  getters
  std::string get_type() const override;

  //  tasks
  void change( Desert* ) override;
  void change( Forest* ) override;
  void change( Swamp* )  override;

  //  singleton
  static Cloudy* instance();
  static void destroy();
};

class Rainy : public Weather
{
private:
  static Rainy* _instance;
protected:
  Rainy() {}
public:
  //  getters
  std::string get_type() const override;

  //  tasks
  void change( Desert* ) override;
  void change( Forest* ) override;
  void change( Swamp* )  override;

  //  singleton
  static Rainy* instance();
  static void destroy();
};

#endif