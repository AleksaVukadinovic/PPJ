#include "Polinom_v2.h"

Polinom_v2::Polinom_v2() : _koeficijenti() {

	/* stampamo poruku da bismo pratili opseg zivota objekta */
	std::cout << "Polinom_v2: Kreiram objekat " << std::endl;
}
Polinom_v2::Polinom_v2(int n, double val) : _koeficijenti(n+1, val) {

	/* stampamo poruku da bismo pratili opseg zivota objekta */
	std::cout << "Polinom_v2: Kreiram objekat " << std::endl;
}
Polinom_v2::Polinom_v2(const std::vector<double>& koef) : _koeficijenti(koef) {

	/* stampamo poruku da bismo pratili opseg zivota objekta */
	std::cout << "Polinom_v2: Kreiram objekat " << std::endl;
}
/* Metod vraca stepen polinoma */
int Polinom_v2::stepen() const {

	/* kao rezultat vracamo duzinu niza umenjenu za jedan,
	 * jer u nizu cuvamo i slobodan clan polinoma
	 */
	return _koeficijenti.size() - 1;
}

/* Metod stampa polinom na ostream s*/
void Polinom_v2::show(std::ostream& s) const {

	/* u petlji prolazimo kroz listu koeficijenata */
	for (int i = 0; i < _koeficijenti.size(); i++) {
		/* ako je koeficijent nula, nema potrebe da ga prikazujemo */
		if (_koeficijenti[i] == 0)
			continue;
		/* stampamo znak koeficijenta*/
		if (_koeficijenti[i] < 0) {
			s << " - ";
		}
		else if (i > 0) {
			s << " + ";
		}

		/* stampamo apsolutnu vrednost koeficijenta */
		s << fabs(_koeficijenti[i]);

		/* i dopisujemo nezavisno promenljivu */
		if (i > 0) {
			s << "*x^" << i;
		}
	}

	/* specijalni slucaj polinoma 0 */
	if (_koeficijenti.size() == 1 && _koeficijenti[0] == 0) {
		s << 0;
	}
}

/* metod dodaje koeficijent najvece tezine u polinom */
void Polinom_v2::dodajKoef(double koef) {

	/* samo pozivamo odgovarajuci metod klase DinamickiNiz */
	_koeficijenti.push_back(koef);
}

/* metod normalizuje polinom, tj. eliminise vodece nule uz najvisi stepen */
void Polinom_v2::normalizuj() {

	while (_koeficijenti.size() > 1 && _koeficijenti[_koeficijenti.size() - 1] == 0) {
		_koeficijenti.pop_back();
	}
}

/* Preoterecujemo operator + tako da ume da sabere dva polinoma */
Polinom_v2 Polinom_v2::operator +(const Polinom_v2& p) const {

	/* stepen rezultujuceg polinoma jednak je vecem stepenu polinoma koji
	 * ucestvuju u izrazu
	 */
	Polinom_v2 result(std::max(_koeficijenti.size(), p._koeficijenti.size()));

	/* prvo sabiramo zajednicke koeficijente */
	int i = 0;
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) {
		result[i] = _koeficijenti[i] + p._koeficijenti[i];
	}

	/* u petlji prepisujemo 'rep' polinoma viseg stepena */
	while (i < _koeficijenti.size()) {
		result[i] = _koeficijenti[i];
		i++;
	}

	while (i < p._koeficijenti.size()) {
		result[i] = p._koeficijenti[i];
		i++;
	}

	/* Ako saberemo dva suprotna polinoma kao rezultat dobicemo nulu,
	 * pa moramo da uklonimo sve koeficijente najviseg stepena koji su 0
	 */
	result.normalizuj();

	/* vracamo rezultat */
	return result;
}

/* Preoterecujemo operator - tako da ume da oduzme dva polinoma */
Polinom_v2 Polinom_v2::operator -(const Polinom_v2& p) const {

	/* stepen rezultujuceg polinoma jednak je vecem stepenu polinoma koji
	 * ucestvuju u izrazu
	 */
	Polinom_v2 result(std::max(_koeficijenti.size(), p._koeficijenti.size()));

	/* prvo oduzimamo zajednicke koeficijente */
	int i = 0;
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) {
		/* BITNO
		 * oduzimanje nije komutativna operaticija, pa moramo da vodimo racuna
		 * o redosledu operanada. Dakle, od implicitnog argumenta oduzimamo prosledjeni
		 * argument.
		 */
		result[i] = _koeficijenti[i] - p._koeficijenti[i];
	}

	/* u petlji prepisujemo 'rep' polinoma viseg stepena */
	while (i < _koeficijenti.size()) {
		result[i] = _koeficijenti[i];
		i++;
	}

	/* ako je umanjilac viseg stepena, onda njegove koeficijente prepisujemo
	 * sa suprotnim znakom
	 */
	while (i < p._koeficijenti.size()) {
		result[i] = -p._koeficijenti[i];
		i++;
	}

	/* Ako oduzmemo dva identicna polinoma kao rezultat dobicemo nulu,
	 * pa moramo da uklonimo sve koeficijente najviseg stepena koji su 0
	 */
	result.normalizuj();

	/* vracamo rezultat */
	return result;
}

/* Preoterecujemo operator * tako da ume da pomnozi dva polinoma */
Polinom_v2 Polinom_v2::operator *(const Polinom_v2& p) const {

	/* stepen rezultujuceg polinoma jednak je zbiru stepena
	 * argumenata
	 */
	Polinom_v2 result(stepen() + p.stepen() + 1);

	/* u petlji izracunamo koeficijente */
	for (int i = 0; i < _koeficijenti.size(); i++) {
		for (int j = 0; j < p._koeficijenti.size(); j++) {
			result._koeficijenti[i + j] += _koeficijenti[i] * p._koeficijenti[j];
		}
	}

	/* normalizujemo polinom */
	result.normalizuj();

	/* vracamo rezultat */
	return result;
}

/* unarni minus - kreira suprotni polinom */
Polinom_v2 Polinom_v2::operator -() const {

	/* odmah pravimo polinom stepena n*/
	Polinom_v2 result(_koeficijenti.size());

	/* u petlji postavljamo vrednosti koeficijenata */
	for (int i = 0; i < _koeficijenti.size(); i++) {
		result[i] = -_koeficijenti[i];
	}

	/* vracamo rezultat */
	return result;
}

/* Indeksiranje */
double& Polinom_v2::operator [](int i) {

	/* indeksiranje se svodi na indeksiranje niza koeficijenata */
	return _koeficijenti[i];
}

/* Const operator indeksiranja */
const double& Polinom_v2::operator [](int i) const {

	/* indeksiranje se svodi na indeksiranje niza koeficijenata */
	return _koeficijenti[i];
}

/* Vrednost polinoma u tacki racunamo Hornerovom semom
 * uz pomoc preopterecenog operatora indeksiranja
 */
double Polinom_v2::operator[](double x) {

	/* vrednost racunamo unazad */
	double result = _koeficijenti[_koeficijenti.size() - 1];

	for (int i = _koeficijenti.size() - 2; i >= 0; i--) {

		result = _koeficijenti[i] + result * x;
	}

	return result;
}

/* uporedjivanje */
bool Polinom_v2::operator ==(const Polinom_v2& p) const {

	/* dva polinoma su jednaka ako su istog stepena i
	 * ako su im svi koeficijenti pookordinatno jednaki
	 */

	 /* proveravamo stepen */
	if (this->stepen() != p.stepen())
		return false;

	/* proveravamo koeficijente */
	for (int i = 0; i < stepen(); i++) {
		if (_koeficijenti[i] != p._koeficijenti[i])
			return false;
	}

	/* ako sve provere prodju, polinomi su jednaki */
	return true;
}

bool Polinom_v2::operator !=(const Polinom_v2& p) const {

	/* mozemo da iskoristimo vec implementirani operator == */
	return !(*this == p);
}

/* Operator dodele i sabiranja
 * Primetite da ovde kao povratnu vrednost vracamo referencu na postojeci
 * objekat. Da biste to bolje razumeli setite se kako se izvrsava obicni operator
 * dodele. Naredba
 *
 * p += q;
 *
 * se prevodi u (na postojeci objekat p primeni operator += sa argumentom q)
 *
 * p.operator+=(q)
 *
 * i kao rezultat izvrsavanja operatora treba da dobijemo izmenjeni (postojeci)
 * objekat p, ciju referencu na kraju vracamo, jer je p implicitni argument.
 *
 */
Polinom_v2& Polinom_v2::operator +=(const Polinom_v2& p) {

	int i = 0;
	/* redom dodajemo vrednosti koeficijenata na p */
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) {

		_koeficijenti[i] += p._koeficijenti[i];
	}

	/* ako je polinom p viseg stepena, moramo da dopisemo njegove
	 * koeficijente na rezultat
	 */
	while (i < p._koeficijenti.size()) {
		_koeficijenti.push_back(p._koeficijenti[i]);
		i++;
	}
	/* normalizujemo dobijeni rezultat */
	normalizuj();

	/* kao rezultat vracamo referencu na tekuci objekat */
	return *this;
}

/* Operator dodele i oduzimanja */
Polinom_v2& Polinom_v2::operator -=(const Polinom_v2& p) {

	int i = 0;
	/* redom dodajemo vrednosti koeficijenata na p */
	for (i = 0; i < std::min(_koeficijenti.size(), p._koeficijenti.size()); i++) {

		_koeficijenti[i] -= p._koeficijenti[i];
	}

	/* ako je polinom p viseg stepena, moramo da dopisemo njegove
	 * koeficijente na rezultat
	 */
	while (i < p._koeficijenti.size()) {
		_koeficijenti.push_back(-p._koeficijenti[i]);
		i++;
	}
	/* normalizujemo dobijeni rezultat */
	normalizuj();

	/* kao rezultat vracamo referencu na tekuci objekat */
	return *this;
}

/* Operator dodele i mnozenje */
Polinom_v2& Polinom_v2::operator *=(const Polinom_v2& p) {

	/* stepen rezultujuceg polinoma jednak je zbiru stepena
	 * argumenata. Cuvamo listu koeficijenata.
	 */
	std::vector<double> result(stepen() + p.stepen() + 1, 0);

	/* u petlji izracunamo koeficijente */
	for (int i = 0; i < _koeficijenti.size(); i++) {
		for (int j = 0; j < p._koeficijenti.size(); j++) {
			result[i + j] += _koeficijenti[i] * p._koeficijenti[j];
		}
	}

	/* polinomu dodeljujemo novu listu koeficijenata */
	_koeficijenti = result;

	/* normalizujemo polinom */
	normalizuj();

	/* kao rezultat vracamo referencu na tekuci objekat */
	return *this;
}

/* Globalni operator za stampanje polinoma */
std::ostream& operator <<(std::ostream& s, const Polinom_v2& p) {

	p.show(s);
	return s;
}