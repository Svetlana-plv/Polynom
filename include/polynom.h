#pragma once
#include "list.h"
#include "polynom_parser.h"

const double EPS = 1e-10;


class Polynom;

class Monom {

private:

	double coef = 0; // coefficient

	size_t deg = 0; // degrees of xyz

	// degree of x = deg / 100
	// degree of y = deg / 10 % 10
	// degree of z = deg % 10

public:

	Monom();
	Monom(double cf, size_t dg = 0);
	Monom(double cf, size_t x, size_t y, size_t z);

	bool operator<(const Monom& m)const;
	bool operator>(const Monom& m)const;
	bool operator<=(const Monom& m)const;
	bool operator>=(const Monom& m)const;

	bool operator==(const Monom& m)const;
	bool operator!=(const Monom& m)const;

	Monom& operator+=(const Monom& m);

	Monom operator+(const Monom& m)const;
	Monom operator-(const Monom& m)const;
	Monom operator*(double c)const;
	Monom operator*(const Monom& m)const;
	Polynom operator*(const Polynom& p)const;


	size_t deg_x()const;
	size_t deg_y()const;
	size_t deg_z()const;
	size_t get_deg()const;
	double get_coef()const;
	std::string get_str();

	double point(double x, double y, double z);
	void print();
};


class Polynom {
private: 

	List<Monom> polynom;

public:

	Polynom();
	Polynom(const Monom& m);
	Polynom(const std::string str);

	bool operator==(const Polynom& p)const;
	bool operator!=(const Polynom& p)const;

	Polynom operator*(const double c)const;
	friend Polynom operator*(double c, const Polynom& p);

	Polynom operator+(const Monom& p)const;
	Polynom operator-(const Monom& p)const;
	Polynom operator*(const Monom& p)const;

	Polynom operator+(const Polynom& p)const;
	Polynom operator-(const Polynom& p)const;
	Polynom operator*(const Polynom& p)const;

	double point(double x, double y, double z);
	void print();

	void parse_string(std::string str);

	void add_monom(const Monom& m);
	void add_monom_after(const Monom& m, List<Monom>::Iterator it);
	void erase_zero();
	void reset();
	std::string get_str();

	~Polynom() { polynom.clear(); }
};