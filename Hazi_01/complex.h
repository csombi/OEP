#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <iostream>

class Complex {
	private:
		double _re;
		double _im;

	public:
		Complex() : _re(0), _im(0) {}
		Complex(double r, double i) : _re(r), _im(i) {}

		//getter
		double getRe() const { return _re; }
		double getIm() const { return _im; }

		//communication
		void write() const {
			if (this->getIm() < 0.0)
				std::cout << "c = " << this->getRe() << " - |" << this->getIm() << "| * i\n";
			else
				std::cout << "c = " << this->getRe() << " + " << this->getIm() << " * i\n";
		}

		friend std::ostream& operator<< (std::ostream& os, const Complex& c) {
			if (c.getIm() < 0.0)
				os << "c = " << c.getRe() << "-" << abs(c.getIm()) << "i\n";
			else
				os << "c = " << c.getRe() << "+" << c.getIm() << "i\n";
			return os;
		}

		friend std::istream& operator>> (std::istream& is, Complex& c) {
			char tmp;
			char s;
			is >> c._re >> s >> c._im >> tmp;

			if ( s == '-' ){
				c._im *= (-1);
			}
			return is;
		}

		//calculations
		static Complex add( Complex a, Complex b ) {
			return Complex( a._re + b._re, a._im + b._im );
		}

		static Complex sub( Complex a, Complex b) {
			return Complex( a._re - b._re, a._im - b._im );
		}

		static Complex mul( Complex a, Complex b ) {
			return Complex( a._re * b._re - a._im * b._im, a._re * b._im + a._im * b._re );
		}

		static Complex div( Complex a, Complex b) {
			return Complex( (a._re * b._re + a._im * b._im) / (b._re * b._re  + b._im * b._im), (a._im * b._re - a._re * b._im) / (b._re * b._re + b._im * b._im) );
		}
};


#endif // COMPLEX_H_INCLUDED
