#pragma once
#include "list.h"
#include "ordered_table.h"
#include "unordered_table.h"
#include "AVLtree.h"
#include "chained_hashtable.h"
#include "polynom_parser.h"
#include "structs.h"

#include <variant>

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

	double point(double x, double y, double z);
	void print();
};


class Polynom {
private: 

	using OrderedC = OrderedTable<Monom, double>;
	using UnordC = UnorderedTable<Monom, double>;
	using AVLC = AVLTree<Monom, double>;
	using HashC = HashTable<Monom, double>;

	using VariantC = std::variant<OrderedC>;

	VariantC container;

public:

	Polynom();
	Polynom(containerType type);
	Polynom(const Monom& m, containerType type);
	Polynom(const std::string str, containerType type);

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
	//void add_monom_after(const Monom& m, List<Monom>::Iterator it);
	void erase_zero();
	
	//~Polynom() { polynom.clear(); }

private:
	containerType type;

	void setType(containerType type) {
		this->type = type;
		switch (type) {
		case containerType::ORDER_TABLE:
			container = OrderedC{};
			break;
		case containerType::UNORDER_TABLE:
			//container = UnordC{};
			break;
		case containerType::AVLTREE:
			//container = AVLC{};
			break;
		case containerType::CHAINED_HASHTABLE:
			//container = HashC{};
			break;
		default:
			throw std::invalid_argument("Unknown container type");
		}
	}
};