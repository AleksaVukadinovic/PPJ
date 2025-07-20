# Napisati python-skript koji štampa na standardni izraz autora (−a), cenu
# (−c), izdavača (−i) ili godinu izdanja (−g) knjige koja se navodi kao argument komande
# linije, u zavisnosti od prisutne opcije komandne linije (u slučaju da nema opcija, ispisati
# sve podatke o traženoj knjizi). Informacije o knjigama se nalaze u fajlu knjige.xml koji
# ima sledeći format:
# <?xml version="1.0" encoding="utf-8" ?>
# <lista_knjiga>
# <knjiga rbr="1" >
# <naslov> Yacc </naslov>
# <autor> Filip Maric </autor>
# <godina_izdanja> 2004 </godina_izdanja>
# <izdavac> Matematicki fakultet </izdavac>
# <cena valuta="rsd"> 1000 </cena>
# </knjiga>
# <knjiga rbr="2" >
# <autor> Fredrik Lundh </autor>
# <cena valuta="eur"> 50 </cena>
# <izdavac> O’Reilly & Associates </izdavac>
# <godina_izdanja> 2001 </godina_izdanja>
# <naslov> Python Standard Library </naslov>
# </knjiga>
# </lista_knjiga>
# Primeri pozivanja programa i ispis:
# ./knjiga -a Yacc
# Filip Maric
# $ ./knjiga -c
# 50eur

import re, sys

author = False
price = False
publisher = False
year = False

if len(sys.argv) < 3:
    author = True
    price = True
    publisher = True
    year = True
else:
    for arg in sys.argv:
        if arg == "-a":
            author = True
        if arg == "-c":
            price = True
        if arg == "-i":
            publisher = True
        if arg == "-g":
            year = True

books = sys.argv[len(sys.argv) - 1]

try:
    with open(books, "r") as f:
        data = f.read()
except IOError:
    exit("Failed to read file: " + books)

book_regex = re.compile(
    r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[1-9]\d*)"\s*>\s*'
    + r"<naslov>\s*(?P<naslov>.*?)\s*</naslov>"
    + r"<autor>\s*(?P<autor>.*?)\s*</autor>"
    + r"<godina_izdanja>\s*(?P<godina_izdanja>\d{4})\s*</godina_izdanja>"
    + r"<izdavac>\s*(?P<izdavac>.*?)\s*</izdavac>"
    + r"<cena>\s*(?P<cena>\d+eur)\s*</cena>"
    + r"</knjiga>",
    re.S,
)

books = []

for match in book_regex.finditer(data):
    exit(1)

# TODO
