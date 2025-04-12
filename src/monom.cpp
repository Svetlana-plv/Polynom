#include <iostream>
#include "polynom.h"

Monom::Monom() : coef(0), deg(0) {};

Monom::Monom(double cf, size_t dg): coef(cf), deg(dg) {};

Monom::Monom(double cf, size_t x, size_t y, size_t z) : coef(cf) {
	this->deg = x * 100 + y * 10 + z;
};

bool Monom::operator<(const Monom& m)const {
	if (this->deg < m.get_deg())
		return true;
	return false;
}

bool Monom::operator>(const Monom& m)const {
	if (this->deg > m.get_deg())
		return true;
	return false;
}

bool Monom::operator<=(const Monom& m)const {
	return !(*(this)>m);
}

bool Monom::operator>=(const Monom& m)const {
	return !(*(this) < m);
}

bool Monom::operator==(const Monom& m)const {
	return (this->deg==m.get_deg() && this->coef==m.get_coef());
}

bool Monom::operator!=(const Monom& m)const {
	return !((*this)==m);
}

Monom& Monom::operator+=(const Monom& m) {
	if (this->deg != m.deg) throw std::logic_error("Can't add monomials because degrees of the monomials don't match!");
	this->coef += m.coef;
}

Monom Monom::operator+(const Monom& m)const {
	if (this->deg != m.deg) throw std::logic_error("Can't add monomials because degrees of the monomials don't match!");
	Monom tmp;
	tmp.coef = this->coef + m.coef;
	tmp.deg = this->deg;
	return tmp;
}

Monom Monom::operator-(const Monom& m)const {
	if (this->deg != m.deg) throw std::logic_error("Can't sub monomials because degrees of the monomials don't match!");
	Monom tmp;
	tmp.coef = this->coef - m.coef;
	tmp.deg = this->deg;
	return tmp;
}

Monom Monom::operator*(const Monom& m)const {
	if (this->deg_x() + m.deg_x() > 9 || this->deg_y() + m.deg_y() > 9 || this->deg_z() + m.deg_z() > 9) 
		throw std::logic_error("Can't mul monomials because degree more then 9!");
	Monom tmp;
	tmp.coef = this->coef * m.coef;
	tmp.deg = this->deg + m.deg;
	return tmp;
}

Monom Monom::operator*(double c)const {
	Monom tmp = *this;
	tmp.coef = this->coef * c;
	return tmp;
}

Polynom Monom::operator*(const Polynom& p)const {
	return p * (*this);
}


size_t Monom::deg_x()const {
	return this->deg / 100;
}

size_t Monom::deg_y()const {
	return this->deg / 10 % 10;
}
 
size_t Monom::deg_z()const {
	return this->deg % 10;
}

size_t Monom::get_deg()const {
	return this->deg;
}

double Monom::get_coef()const {
	return this->coef;
}


double Monom::point(double x, double y, double z) {
	double result = coef * pow(x, deg_x()) * pow(y, deg_y()) * pow(z, deg_z());
	return result;
}

void Monom::print() {
	std::cout << coef << " x^" << deg_x() << " y^" << deg_y() << " z^" << deg_z();
}