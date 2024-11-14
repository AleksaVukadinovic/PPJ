import sys
import re

opcijaAutor = False
opcijaGodina = False
opcijaIzdavac = False
opcijaCena = False
naslovKnjige = None

if len(sys.argv) < 3:
    sys.exit("Nedovoljno argumenata")

for arg in sys.argv[2:]:
    if arg[0] == '-':
        if arg[1] == 'a':
            opcijaAutor = True
        elif arg[1] == 'g':
            opcijaGodina = True
        elif arg[1] == 'i':
            opcijaIzdavac = True
        elif arg[1] == 'c':
            opcijaCena = True
        else:
            sys.exit("Losa opcija")
    else:
        naslovKnjige = arg  

if re.match(r"^.+\.xml$", sys.argv[1], re.IGNORECASE) is None:
    sys.exit("Losa fajl ekstenzija")

try:
    with open(sys.argv[1], "r") as f:
        fajl = f.read()
except IOError:
    sys.exit("Neuspelo citanje fajla")

sablon = re.compile(r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[0-9]+)"\s*>'
                    r'(?=.*?<naslov>\s*(?P<naslov>.*?)\s*</naslov>)'
                    r'(?=.*?<autor>\s*(?P<autor>[A-Z][a-z]+(\s+[A-Z][a-z]+)+)\s*</autor>)'
                    r'(?=.*?<godina_izdanja>\s*(?P<godina>[0-9]{4})\s*</godina_izdanja>)'
                    r'(?=.*?<izdavac>\s*(?P<izdavac>.*?)\s*</izdavac>)'
                    r'(?=.*?<cena\s+valuta\s*=\s*"(?P<valuta>(eur|rsd))"\s*>\s*(?P<cena>[1-9][0-9]*(\.[0-9]+)?)\s*</cena>)'
                    r'.*?</knjiga>', re.S)

biblioteka = {}
for m in sablon.finditer(fajl):
    rbr = m.group('rbr')
    naslov = m.group('naslov')
    autor = m.group('autor')
    god = m.group('godina')
    izdavac = m.group('izdavac')
    cena = m.group('cena')
    valuta = m.group('valuta')
    biblioteka[rbr] = [naslov, autor, god, izdavac, cena, valuta]

vrednosti = None
for k, v in biblioteka.items():
    if naslovKnjige == v[0]:
        vrednosti = v[1:]
        break

if vrednosti:
    if opcijaAutor:
        print(vrednosti[0])
    if opcijaGodina:
        print(vrednosti[1])
    if opcijaIzdavac:
        print(vrednosti[2])
    if opcijaCena:
        print(vrednosti[3], vrednosti[4])

    if not (opcijaAutor or opcijaCena or opcijaGodina or opcijaIzdavac):
        for v in vrednosti:
            print(v)
else:
    print("Knjiga nije pronađena.")
