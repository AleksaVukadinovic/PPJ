#include <iostream>
#include "Razlomak.h"
#include "DinamickiNiz.h"
#include "Polinom_v1.h"
#include "Polinom_v2.h"
#include "KompleksniBroj.h"

void testirajRazlomak(void);
void testirajDinamickiNiz(void);
void testirajPolinomV1(void);
void testirajPolinomV2(void);
void testirajKompleksniBroj(void);


void testirajRazlomak(void) {
    Razlomak p, q; // ovde se poziva podrazumevani konstruktor automatski
    std::cout << "Unesite prvi razlomak: " << std::endl;
    std::cin >> p;

    std::cout << "Unesite drugi razlomak: " << std::endl;
    std::cin >> q;

    Razlomak s(12, 18); // parametrizovan konstruktor

    std::cout << "P: " << p << std::endl;
    std::cout << "Q: " << q << std::endl;
    std::cout << "S: " << s << std::endl;

    Razlomak* t = new Razlomak(7, 21);

    std::cout << "T: " << (*t) << std::endl;

    Razlomak r = p + q;
    std::cout << p << " + " << q << " = " << r << std::endl;
    r = p - q;
    std::cout << p << " - " << q << " = " << r << std::endl;
    r = p * q;
    std::cout << p << " * " << q << " = " << r << std::endl;
    r = p / q;
    std::cout << p << " / " << q << " = " << r << std::endl;

    std::cout << "Suprotni(" << p << ") = " << (-p) << std::endl;
    std::cout << "Reciprocni(" << p << ") = " << (~p) << std::endl;

    std::cout << "P: " << p << std::endl;
    std::cout << "Prefiksni(++): " << (++p) << " Posle: " << p << std::endl;
    std::cout << "P: " << p << std::endl;
    std::cout << "Prefiksni(--): " << (--p) << " Posle: " << p << std::endl;

    std::cout << "P: " << p << std::endl;
    std::cout << "Postfiksni(++): " << (p++) << " Posle: " << p << std::endl;
    std::cout << "P: " << p << std::endl;
    std::cout << "Postfiksni(--): " << (p--) << " Posle: " << p << std::endl;

    if (p == q) 
        std::cout << p << " == " << q << std::endl;
    if (p != q) 
        std::cout << p << " != " << q << std::endl;
    if (p <= q) 
        std::cout << p << " <= " << q << std::endl;
    if (p >= q) 
        std::cout << p << " >= " << q << std::endl;
    if (p < q) 
        std::cout << p << " < " << q << std::endl;
    if (p > q) 
        std::cout << p << " > " << q << std::endl;

    delete t;
}

void testirajDinamickiNiz(void) {

    DinamickiNiz dn;
    for (int i = 0; i < 200; i++)
        dn.dodajNaKraj(i);

    DinamickiNiz dn2;
    dn2 = dn;
    for (int i = 500; i < 700; i++)
        dn2.dodajNaKraj(i);

    std::cout << "Prvi niz" << std::endl;
    for (int i = 0; i < dn.size(); i++)
        std::cout << dn[i] << " ";
    std::cout << std::endl;

    dn2[0] = 50000;
    std::cout << "Drugi niz" << std::endl;
    for (int i = 0; i < dn2.size(); i++)
        std::cout << dn2[i] << " ";
    std::cout << std::endl;
}

void testirajPolinomV1(void) {

    /* kreiramo prvi polinom*/
    Polinom_v1 p;
    int n = 0;

    std::cout << "Unesite stepen polinoma P: " << std::endl;
    std::cin >> n;

    std::cout << "Unesite koeficijente polinoma P" << std::endl;
    for (int i = 0; i <= n; i++) {
        double k = 0;
        std::cin >> k;
        p.dodajKoef(k);
    }

    std::cout << "Unesite stepen polinoma Q: " << std::endl;
    std::cin >> n;
    /* odmah kreiramo 0 polinom stepena n */
    Polinom_v1 q(n);

    std::cout << "Unesite koeficijente polinoma Q" << std::endl;
    for (int i = 0; i <= n; i++) {
        /* direktno upisujemo u niz koeficijenata */
        std::cin >> (q[i]);
    }

    /* prikazujemo polinome */
    std::cout << "P = " << p << std::endl;
    std::cout << "Q = " << q << std::endl;

    std::cout << "Unesite x u kojem treba izracunati vrednost polinoma: " << std::endl;
    double x;
    std::cin >> x;

    std::cout << "P[" << x << "] = " << (p[x]) << std::endl;
    std::cout << "P[" << x << "] = " << (q[x]) << std::endl;


    /* Na ovom mestu se kreira pomocni Polinom objekat koji se dodeljuje
     * polinomu r. Iako ocekujemo da move-semantics ne radi nikakvo kopiranje,
     * to se ipak nece u potpunosti desiti, jer u pozadini nasa klasa koristi dinamicki
     * resurs. Move-semantics ce da premesti objekat polinom, ali ce u pozadini biti
     * pozvan konstruktor kopije dinamickog niza. U trenutku premestanja polinoma ne
     * postoji atribut _koeficijenti, pa se on prvo mora kreirati. Dakle, mora se pozvati
     * konstruktor kopije.
     * Postoji nacin da ovakva nepotrebna kopiranja izbegnemo uz pomoc move konstruktora
     * i move assingment operatora, ali o tome nece biti reci ovde, jer je to deo
     * standarda c++11.
     */
    Polinom_v1 r = p + q;
    std::cout << "(" << p << ")+(" << q << ") = " << r << std::endl;
    /* Ovde se takodje oslanjamo na podrazumevane implementacije konstruktora kopije
     * i operatora dodele. Takvo ponasanje dovodi do cak dva nepotrebna kopiranja. Redosled
     * izvrsavanja je sledeci:
     * 1. Kreira se Polinom kao povratna vrednosti.
     *         1.1. Kreiranje polinoma znaci da se u pozadini prvo kreira DinamickiNiz
     *              _koeficijenti, pa onda i ceo objekat Polinom
     * 2. Polinom se vraca preko vrednosti, dakle mora se pozvati konstruktor kopije.
     *          2.1 Prvo se kopiraju svi atributi, zbog cega se u pozadini prvo poziva
     *              konstruktor kopije atributa _koeficijenti.
     *          2.2 Move-semantics pomera povratni objekat. (samo se kopira atribut, ne ceo
     *              objekat Polinom)
     * 3. Zavrsava se vracanje objekta, pa se onaj prvobitni niz unistava i ostaje nam samo
     *    kopija niza iz koraka 2.1.
     * 4. Polinom r vec postoji, pa se prilikom dodele vrednosti moze koristi operator dodele.
     *    Default operator dodele ce samo pozvati operator dodele za niz r._koeficijenti sa
     *    nizom iz koraka 2.1 kao argumentom.
     * 5. Nakon izvrsavanja operatora dodele, niz iz koraka 2.1 se unistava.
     *
     * Jasno vam je iz objasnjenja da je ovaj niz koraka vrlo neefikasan i da moze da se
     * znacajno ubrza eliminacijom nepotrebnih kopiranja. Upravo zbog toga su uvedeni
     * move konstruktor i move assignment operator. Klasa std::vector<> je po definiciji
     * RAII i podrzava move operacije na ispravan nacin, pa cemo nju koristiti u sledecoj
     * verziji Polinoma.
     */
    r = p - q;
    std::cout << "(" << p << ")-(" << q << ") = " << r << std::endl;
    r = p * q;
    std::cout << "(" << p << ")*(" << q << ") = " << r << std::endl;
    r = -r;
    std::cout << "-(" << p << ") = " << r << std::endl;

    if (p == q) {
        std::cout << "(" << p << ") == (" << q << ")" << std::endl;
    }
    else {
        std::cout << "(" << p << ") != (" << q << ")" << std::endl;
    }

    /* testiranje ralicitih operatora dodele
     * Primetite da ovde nema instanciranja novih objekata, vec samo menjamo stanje
     * postojeceg objekta p
     */
    p += q;
    std::cout << "P = " << p << std::endl;
    p -= q;
    std::cout << "P = " << p << std::endl;
    /* U pozadini bice kreiran pomocni objekat DinamickiNiz
     * koji ce biti dodeljen kao novi niz koeficijenata polinomu p
     */
    p *= q;
    std::cout << "P = " << p << std::endl;
}

void testirajPolinomV2(void) {

    /* kreiramo prvi polinom*/
    Polinom_v2 p;
    int n = 0;

    std::cout << "Unesite stepen polinoma P: " << std::endl;
    std::cin >> n;

    std::cout << "Unesite koeficijente polinoma P" << std::endl;
    for (int i = 0; i <= n; i++) {
        double k = 0;
        std::cin >> k;
        p.dodajKoef(k);
    }

    std::cout << "Unesite stepen polinoma Q: " << std::endl;
    std::cin >> n;
    /* odmah kreiramo 0 polinom stepena n */
    Polinom_v2 q(n);

    std::cout << "Unesite koeficijente polinoma Q" << std::endl;
    for (int i = 0; i <= n; i++) {
        /* direktno upisujemo u niz koeficijenata */
        std::cin >> (q[i]);
    }

    /* prikazujemo polinome */
    std::cout << "P = " << p << std::endl;
    std::cout << "Q = " << q << std::endl;

    std::cout << "Unesite x u kojem treba izracunati vrednost polinoma: " << std::endl;
    double x;
    std::cin >> x;

    std::cout << "P[" << x << "] = " << (p[x]) << std::endl;
    std::cout << "P[" << x << "] = " << (q[x]) << std::endl;


    /* ovde nece biti nepotrebnih kopiranja, jer std::vector koji se nalazi
     * iza ove verzije polinoma podrzava move operacije
     */
    Polinom_v2 r = p + q;
    std::cout << "(" << p << ")+(" << q << ") = " << r << std::endl;
    /*  ovde nece biti nepotrebnih kopiranja, jer std::vector koji se nalazi
     * iza ove verzije polinoma podrzava move operacije 
     */
    r = p - q;
    std::cout << "(" << p << ")-(" << q << ") = " << r << std::endl;
    r = p * q;
    std::cout << "(" << p << ")*(" << q << ") = " << r << std::endl;
    r = -r;
    std::cout << "-(" << p << ") = " << r << std::endl;

    if (p == q) {
        std::cout << "(" << p << ") == (" << q << ")" << std::endl;
    }
    else {
        std::cout << "(" << p << ") != (" << q << ")" << std::endl;
    }

    /* testiranje ralicitih operatora dodele
     * Primetite da ovde nema instanciranja novih objekata, vec samo menjamo stanje
     * postojeceg objekta p
     */
    p += q;
    std::cout << "P = " << p << std::endl;
    p -= q;
    std::cout << "P = " << p << std::endl;
    /* U pozadini bice kreiran pomocni objekat std::vector<>
     * koji ce biti dodeljen kao novi niz koeficijenata polinomu p
     */
    p *= q;
    std::cout << "P = " << p << std::endl;
}

void testirajKompleksniBroj(void) {

    KompleksniBroj w(1,3);
    KompleksniBroj z(-3,-4);

    std::cout << "w: " << w << std::endl;
    std::cout << "z: " << z << std::endl;

    KompleksniBroj rez = w+z;
    std::cout << "(" << w << ") + (" << z << ") = " << rez << std::endl;

    rez = w-z;
    std::cout << "(" << w << ") - (" << z << ") = " << rez << std::endl;

    rez = w*z;
    std::cout << "(" << w << ") * (" << z << ") = " << rez << std::endl;

    rez = w/z;
    std::cout << "(" << w << ") / (" << z << ") = " << rez << std::endl;

    rez = -w;
    std::cout << "-(" << w <<  ") = " << rez << std::endl;

    rez = ~w;
    std::cout << "~(" << w <<  ") = " << rez << std::endl;

    std::cout << "Moduo(" << w <<  ") = " << w.Moduo() << std::endl;
    std::cout << "Arg(" << w <<  ") = " << w.Arg() << std::endl;
}


int main()
{
    testirajRazlomak();
    testirajDinamickiNiz();
    testirajPolinomV1();
    return 0;
}
