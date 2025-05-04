#include"polynom.h"

Polynom::Polynom()
	: type(containerType::ORDER_TABLE)
{
	setType(type);

	visit([&](auto& ctr) {
		ctr.insert(Monom(), 0.0);
		}, container);
}

Polynom::Polynom(containerType type) {
	setType(type);

	visit([&](auto& ctr) {
		ctr.insert(Monom(), 0.0);
	}, container);
}

Polynom::Polynom(const Monom& m, containerType type) {
	setType(type);
	visit([&](auto& ctr) {
		ctr.insert(m, m.get_coef());
		ctr.insert(Monom(), 0.0);
	}, container);
}

Polynom::Polynom(const std::string str, containerType type) {
	setType(type);
	(*this).parse_string(str);
}

bool Polynom::operator==(const Polynom& p) const {
	return visit([&](const auto& ctr1) -> bool{

		using T = decay_t<decltype(ctr1)>;
		if(!holds_alternative<T>(p.container)) return false;
		const auto& ctr2 = get<T>(p.container);

		if (ctr1.size() != ctr2.size()) return false;

		auto it1 = ctr1.begin();
		auto it2 = ctr2.begin();

		while (it1 != ctr1.end() && it2 != ctr2.end()) {
			if (it1->first != it2->first || std::abs(it1->second - it2->second) > EPS) {
				return false;
			}
			++it1;
			++it2;
		}

		if (it1 == ctr1.end() && it2 == ctr2.end()) return true;
		return false;
	}, container);
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

	Polynom tmp(this->type);

	if (m == Monom()) return tmp;

	visit([&](const auto& ctr) {
		auto it = ctr.begin();
		while (it != ctr.end()) {
			if (it->first == Monom()) continue; 
			tmp.add_monom(it->first * m);
			++it;
		}
	}, container);
	
	return tmp;
}

Polynom Polynom::operator+(const Polynom& p)const {

	Polynom tmp(this->type);

	visit([&](const auto& ctr1) {
		using T = decay_t<decltype(ctr1)>;

		if (!holds_alternative<T>(p.container)) return;

		const auto& ctr2 = get<T>(p.container);
		auto& tmp_ctr = get<T>(tmp.container);

		auto it1 = ctr1.begin();
		auto it2 = ctr2.begin();


		while (it1 != ctr1.end() && it2 != ctr2.end()) {
			if (it1->first < it2->first) {
				tmp_ctr.insert(it1->first, it1->second);
				++it1;
			}
			else if (it1->first > it2->first) {
				tmp_ctr.insert(it2->first, it2->second);
				++it2;
			}
			else {
				double sum_coef = it1->second + it2->second;
				if (abs(it1->second + it2->second) > EPS) {
					tmp_ctr.insert(it1->first, sum_coef);
				}
				++it1;
				++it2;
			}
		}

		while (it1 != ctr1.end()) {
			tmp_ctr.insert(it1->first, it1->second);
			++it1;
		}

		while (it2 != ctr2.end()) {
			tmp_ctr.insert(it2->first, it2->second);
			++it2;
		}

	}, container);

	return tmp;

}

Polynom Polynom::operator-(const Polynom& p)const {

	return (*this) + p * (-1);
}

Polynom Polynom::operator*(const Polynom& p) const {
	Polynom tmp(this->type);

	if ((*this) == tmp || p == tmp) return tmp;

	std::visit([&](const auto& ctr1) {
		using T = std::decay_t<decltype(ctr1)>;

		if (!std::holds_alternative<T>(p.container)) return;

		const auto& ctr2 = std::get<T>(p.container);

		std::visit([&](auto& tmp_ctr) {
			for (const auto& [monom1, coef1] : ctr1) {
				for (const auto& [monom2, coef2] : ctr2) {
					Monom product_monom = monom1 * monom2;
					double product_coef = coef1 * coef2;
					tmp_ctr.insert(product_monom, product_coef);
				}
			}
		}, tmp.container);

	}, container);

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
	double result = 0.0;

	std::visit([&](auto const& ctr) {

		for (auto it = ctr.begin(); it != ctr.end(); ++it) {
			const Monom& m = it->first;
			double coef = it->second;

			result += coef
				* pow(x, m.deg_x())
				* pow(y, m.deg_y())
				* pow(z, m.deg_z());
		}
		}, container);

	return result;
}

void Polynom::print() {
	visit([&](auto& ctr) {
		for (auto it = ctr.begin(); it != ctr.end(); ++it) {
			it->first.print();
			std::cout << std::endl;
		}
		std::cout << std::endl;
		}, container);
}

void Polynom::add_monom(const Monom& m) {
	visit([&](auto &ctr) {
		if (ctr.empty()) {
			ctr.insert(m, m.get_coef());
			return;
		}

		auto it = ctr.begin();
		auto it1 = it;
		while (it1 != ctr.end() && it1->first.get_deg() <= m.get_deg()) {
			it = it1;
			++it1;
		}

		if (it->first.get_deg() == m.get_deg()) {
			if (abs(it->first.get_coef() + m.get_coef()) > EPS) {
				it->second = it->second + m.get_coef();
			}
		}

		else {
			if(it == it1) ctr.insert(m, m.get_coef());
			else ctr.insert(m, m.get_coef());
		}

	}, container);
}

//void Polynom::add_monom_after(const Monom& m, List<Monom>::Iterator it) {
//	if (polynom.empty()) {
//		polynom.insert_front(m);
//		return;
//	}
//	if (it.value().get_deg() == m.get_deg()) {
//		if (abs(it.value().get_coef() + m.get_coef()) > EPS)
//			it.value() += m;
//	}
//	else {
//		this->polynom.insert_after(m, it);
//	}
//
//	//(*this).erase_zero();
//}

void Polynom::erase_zero() {
	visit([&](auto& ctr) {
		std::vector<Monom> to_erase;

		for (const auto& [monom, coef] : ctr) {
			if (std::abs(coef) < EPS) {
				to_erase.push_back(monom);
			}
		}

		for (const auto& m : to_erase) {
			ctr.erase(m);
		}

		if (ctr.empty()) {
			ctr.insert(Monom(), 0.0);
		}

	}, container);
}