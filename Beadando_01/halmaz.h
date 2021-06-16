#ifndef HALMAZ_H_INCLUDED
#define HALMAZ_H_INCLUDED

#include <vector>
#include <iostream>

class Halmaz {

	private:
		std::vector<int> _vec;
		int _even_numbers;

		bool linSearch( const std::vector<int>&, const int, unsigned int& i ) const;
	public:
		//konstruktor
		Halmaz();

		//hibakezeles
		enum Exception { FileOpenError };

		//tipus-muveletek
		void setEmpty();
		bool isEmpty() const;
		void add( int );
		void del( int );
		bool isElement( int, unsigned int& ) const;
		unsigned int countEven() const;
		void print() const;
		void fileReader( std::string );

		//operatorok tulterhelese
		friend std::ostream& operator<<( std::ostream& os, const Halmaz& h );
		friend std::istream& operator>>( std::istream& is, Halmaz& h);
};

#endif
