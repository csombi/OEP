#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <stack>

class Entry
{
public:
  virtual ~Entry() {};
  virtual unsigned int get_size() const = 0;
  virtual std::string get_name() const = 0;
  virtual void log() const = 0;
  virtual void change_name( const std::string& ) = 0;
};

class File : public Entry
{
private:
  std::string _name;
  unsigned int _size;
public:
  File( const std::string& filename, unsigned int size) : _name(filename), _size(size) {}
  ~File();
  unsigned int get_size() const;
  std::string get_name() const;
  void log() const;
  void change_name( const std::string& );
};

class Dir : public Entry
{
private:
  std::string _name;
  std::vector<Entry*> _entries;
public:
  Dir( const std::string& dirname ) : _name(dirname), _entries(0) {}
  ~Dir();
  unsigned int get_size() const;
  void log() const;
  void change_name( const std::string& );
  void touch( Entry* );
  void rem( unsigned int );
  std::string get_name() const;
  std::vector<Entry*> get_entries() const;
};

class Filesystem
{
private:
  std::string _name;
  Dir* _root;
  std::stack<Dir*> _pwd;
public:
  enum Errors { NO_DIR, ROOT_DIR };
  Filesystem( const std::string& sys ) : _name(sys) { _pwd.push( new Dir(sys) ); _root = _pwd.top(); }
  ~Filesystem();
  void log() const;
  void add( const std::string&, unsigned int size = 0 );
  void del( const std::string& );
  void get_sys_info() const;
  Dir* search_dir( const std::string& ) const;
  void cd( const std::string& );
  std::string pwd() const;
  unsigned int current_dir_size() const;
  void print_curr_dir() const;
};
