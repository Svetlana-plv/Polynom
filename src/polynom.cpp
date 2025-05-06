#include"polynom.h"

Polynom::Polynom() {
	this->polynom.insert_front(Monom());
}

Polynom::Polynom(const Monom& m) {
	this->polynom.insert_front(m);
	this->polynom.insert_front(Monom());
}

Polynom::Polynom(const std::string str) {
	(*this).parse_string(str);
}

bool Polynom::operator==(const Polynom& p)const {

	List<Monom>::Iterator it1 = this->polynom.begin();
	List<Monom>::Iterator it2 = p.polynom.begin();

	while (it1 != this->polynom.end() && it2 != this->polynom.end()) {
		if (it1.value() != it2.value()) {
			return false;
		}
		it1++;
		it2++;
	}
	if (it1 == this->polynom.end() && it2 == this->polynom.end()) return true;
	return false;
}

bool Polynom::operator!=(const Polynom& p)const {

	return !((*this)==p);
}

Polynom Polynom::operator*(const double c)const {
	Monom m(c);
	return (*this) * m;
}

Polynom operator*(double c, const Polynom& p) {
	return p * c;
}

Polynom Polynom::operator+(const Monom& m)const {

	Polynom tmp = (*this);

	tmp.add_monom(m);

	return tmp;
}

Polynom Polynom::operator-(const Monom& m)const {

	Polynom tmp = (*this);

	tmp.add_monom(Monom(-m.get_coef(), m.get_deg()));

	return tmp;
}

Polynom Polynom::operator*(const Monom& m)const {

	Polynom tmp;

	if (m == Monom()) return tmp;

	List<Monom>::Iterator it = this->polynom.begin();
	it++; // because first monom is empty

	while (it != this->polynom.end()) {
		tmp.add_monom(it.value() * m);
		it++;
	}
	
	return tmp;
}

Polynom Polynom::operator+(const Polynom& p)const {

	Polynom tmp;

	List<Monom>::Iterator it1 = this->polynom.begin();
	List<Monom>::Iterator it2 = p.polynom.begin();
	List<Monom>::Iterator it = tmp.polynom.begin();

	while (it1 != polynom.end() && it2 != polynom.end()) {
		if (it1.value() < it2.value()) {
			tmp.add_monom_after(it1.value(), it);
			it1++;
			it++;
		}
		else if (it1.value() > it2.value()) {
			tmp.add_monom_after(it2.value(), it);
			it2++;
			it++;
		}
		else {
			if (abs(it1.value().get_coef() + it2.value().get_coef()) > EPS) {
				tmp.add_monom_after(it1.value() + it2.value(), it);
				it++;
			}
			it1++;
			it2++;
		}
	}

	// Define polinom that has the remaining monoms
	bool flag = true;
	if (it2 != polynom.end()) {
		flag = false;
	}

	// Add remaining monoms from this polinom
	if (flag) {
		while (it1 != polynom.end()) {
			tmp.add_monom_after(it1.value(), it);
			it1++;
			it++;
		}
	}

	// Add remaining monoms from other polinom
	else {
		while (it2 != polynom.end()) {
			tmp.add_monom_after(it2.value(), it);
			it2++;
			it++;
		}
	}

	return tmp;
}

Polynom Polynom::operator-(const Polynom& p)const {

	return (*this) + p * (-1);
}

Polynom Polynom::operator*(const Polynom& p)const {
	Polynom tmp;

	if ((*this) == tmp || p == tmp) return tmp;

	List<Monom>::Iterator it = this->polynom.begin();
	it++; // because first monom is empty

	for (; it != this->polynom.end(); it++) {
		tmp = tmp + p * it.value();
	}

	return tmp;
}

void Polynom::parse_string(std::string str) {
	Parser::lex_analysis(str);
	std::vector<std::pair< double, int>> v;
	v = Parser::snt_analysis(str);
	for (int i = 0; i < v.size(); i++) {
		double coef = v[i].first;
		int deg = v[i].second;
		(*this).add_monom(Monom(coef, deg));
	}
	(*this).add_monom(Monom());
}

double Polynom::point(double x, double y, double z) {
	double result = 0;
	for (List<Monom>::Iterator it = polynom.begin(); it != polynom.end(); it++) {
		result += it->value.get_coef() * pow(x, it->value.deg_x()) * pow(y, it->value.deg_y()) * pow(z, it->value.deg_z());
	}
	return result;
}

void Polynom::print() {
	for (List<Monom>::Iterator it = polynom.begin(); it != polynom.end(); it++) {
		it.value().print();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::string Polynom::get_str() {
	std::string result = "";
	for (List<Monom>::Iterator it = polynom.begin(); it != polynom.end(); ++it) {
		if(it != polynom.begin()) result += " + ";
		result = result + it.value().get_str();
	}
	return result;
}

void Polynom::add_monom(const Monom& m) {
	if (polynom.empty()) {
		polynom.insert_front(m);
		return;
	}
	List<Monom>::Iterator it = polynom.begin();
	List<Monom>::Iterator it1 = it;
	while (it1 != polynom.end() && it1.value() <= m) {
		it = it1;
		it1++;
	}
	if (it.value().get_deg() == m.get_deg()) {
		if (abs(it.value().get_coef() + m.get_coef()) > EPS) {
			this->polynom.set_value(it.value() + m, it);
		}
	}
	else {
		if(it==it1) this->polynom.insert_front(m);
		else this->polynom.insert_after(m, it);
	}

}

void Polynom::add_monom_after(const Monom& m, List<Monom>::Iterator it) {
	if (polynom.empty()) {
		polynom.insert_front(m);
		return;
	}
	if (it.value().get_deg() == m.get_deg()) {
		if (abs(it.value().get_coef() + m.get_coef()) > EPS)
			it.value() += m;
	}
	else {
		this->polynom.insert_after(m, it);
	}

	//(*this).erase_zero();
}

void Polynom::erase_zero() {
	if (this->polynom.get_size() == 1) return;
	else {
		List<Monom>::Iterator it = this->polynom.begin();
		List<Monom>::Iterator it_prev = it++;
		while (it+1 != this->polynom.end()) {
			if (abs(it.value().get_coef()) < EPS) {
				this->polynom.erase_after(it_prev);
				it = it_prev + 1;
			}
			else {
				it = it_prev++;
			}
		}
		if (abs(it.value().get_coef()) < EPS)
			this->polynom.erase_after(it_prev);

	}
}

void Polynom::reset() {
	this->polynom.clear();
}