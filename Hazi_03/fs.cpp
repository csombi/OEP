#include "fs.h"

// FILE
unsigned int File::get_size() const
{
  return _size;
}

File::~File()
{

}

void File::log() const
{
  std::cout << "- " << _name << " [" << _size << "]" << std::endl;
}

void File::change_name( const std::string& new_name )
{
  _name = new_name;
}

std::string File::get_name() const
{
  return _name;
}

// DIR
Dir::~Dir()
{
  for( Entry* f : _entries ) delete f;
}

std::string Dir::get_name() const
{
  return _name;
}

unsigned int Dir::get_size() const
{
  unsigned int sum = 0;
  for( Entry* f : _entries )
  {
    sum += f->get_size();
  }
  return sum;
}

void Dir::log() const
{
  std::cout << "\\" << _name << std::endl;
  for( Entry* f : _entries )
  {
    f->log();
  }
}

void Dir::change_name( const std::string& dirname )
{
  _name = dirname;
}

void Dir::touch( Entry* f )
{
  _entries.push_back( f );
}

void Dir::rem( unsigned int index )
{
  _entries.erase( _entries.begin() + index);
}

std::vector<Entry*> Dir::get_entries() const
{
  return _entries;
}

// FILESYSTEM
Filesystem::~Filesystem()
{
  delete _root;
}

void Filesystem::log() const
{
  _root->log();
}

void Filesystem::add( const std::string& name, unsigned int size )
{
  if( size == 0 ) _pwd.top()->touch( new Dir( name ));
  else _pwd.top()->touch( new File( name, size ));
}

void Filesystem::get_sys_info() const
{
  std::cout << "--> Filesystem root: " << _root->get_name() << std::endl;
  unsigned int sum = 0;
  for( Entry* e : _root->get_entries() )
  {
    sum += e->get_size();
  }
  std::cout << "--> Filesystem size: " << sum << std::endl;
}

Dir* Filesystem::search_dir( const std::string& dirname ) const
{
  for( Entry* e : _pwd.top()->get_entries() )
  {
    if( e->get_name() == dirname ) return (Dir*)e;
  }
  return nullptr;
}

void Filesystem::cd( const std::string& dirname )
{
  if( dirname == ".." && _pwd.top() != _root ) _pwd.pop();
  else if( dirname == ".." && _pwd.top() == _root ) throw Errors::ROOT_DIR;
  else
  {
    Dir* dir = search_dir( dirname );
    if( dir == nullptr ) throw Errors::NO_DIR;
    else _pwd.push( dir );
  }
}

std::string Filesystem::pwd() const
{
  return _pwd.top()->get_name();
}

unsigned int Filesystem::current_dir_size() const
{
  return _pwd.top()->get_size();
}

void Filesystem::print_curr_dir() const
{
  const std::type_info& dir_type  = typeid(Dir);
  for( Entry* e : _pwd.top()->get_entries() )
  {
    if( dir_type == typeid(*e) ) std::cout << "\\" << e->get_name() << std::endl;
    else std::cout << "- " << e->get_name() << std::endl;
  }
}

void Filesystem::del( const std::string& name)
{
  std::vector<Entry*> dir = _pwd.top()->get_entries();
  for( unsigned int i = 0; i < dir.size(); i++ )
  {
    if( dir[i]->get_name() == name )
    {
      delete dir[i];
      dir.erase( dir.begin() + i);
      _pwd.top()->rem( i );
      break;
    }
  }
}
