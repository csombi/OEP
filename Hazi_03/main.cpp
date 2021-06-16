#include "fs.h"

void run()
{
  char c;
  Filesystem* fs = new Filesystem("root");
  do
  {
    // Menu
    std::cout << "1: Create new file in: " << fs->pwd() << std::endl;
    std::cout << "2: Create new directory in: " << fs->pwd() << std::endl;
    std::cout << "3: Delete entry from: " << fs->pwd() << std::endl;
    std::cout << "4: Print out the size of: " << fs->pwd() << std::endl;
    std::cout << "5: Print out the entries of: " << fs->pwd() << std::endl;
    std::cout << "6: Change directory: " << fs->pwd() << std::endl;
    std::cout << "7: Quit" << std::endl;
    std::cin >> c;

    // Create new file
    if( c == '1' )
    {
      std::string name;
      unsigned int size;
      std::cout << "--> Name: ";
      std::cin >> name;
      std::cout << "--> Size: ";
      std::cin >> size;
      //fs->add( new File(name, size) );
      fs->add( name, size );
    }

    // Create new dir
    if( c == '2' )
    {
      std::string name;
      std::cout << "--> Directory name: ";
      std::cin >> name;
      //fs->add( new Dir(name) );
      fs->add( name );
    }

    // Delete entry
    if( c == '3' )
    {
      std::string name;
      std::cout << "--> Entry name: ";
      std::cin >> name;
      fs->del( name );
    }

    // Print out the size
    if( c == '4' )
    {
      std::cout << "--> " << fs->current_dir_size() << std::endl;
    }

    // Print out the entries of dir
    if( c == '5' )
    {
      fs->print_curr_dir();
    }

    // Change dir
    if( c == '6' )
    {
      try
      {
        std::string dirname;
        std::cout << "--> Directory name: ";
        std::cin >> dirname;
        fs->cd( dirname );
      } catch( Filesystem::Errors e )
      {
        if( e == Filesystem::Errors::NO_DIR ) std::cout << "NO_DIR EXCEPTION\n";
        if( e == Filesystem::Errors::ROOT_DIR ) std::cout << "ALREADY IN ROOT DIR\n";
      }
    }

  } while( c != '7' );

  // free
  delete fs;
}


int main( void )
{
  run();
  return 0;
}
