import sys
import re
import os

if len(sys.argv) < 2:
    sys.exit("Nedovoljno argumenata")

homedir = sys.argv[1]

studenti = {}

putanja = os.path.join(homedir, 'indeksi.txt')

try:
    with open(putanja, 'r') as f:
        for linija in f.readlines():
            if(linija[-1]=='\n'):
                linija = linija[:-1]
        
            poklpanje = re.match(r"^([A-Za-z ]+)+,\s*((m[mnvlria]|a[aif])([01]\d|2[0-5])(00\d|0\d\d|[1-5]\d\d|600))\s*$", linija)
            if poklpanje is not None:
                indeks = poklpanje.group(2)
                ime = poklpanje.group(1)
                studenti[indeks]=ime
except IOError:
    sys.exit("Neuspelo otvaranje fajla")

print(studenti)

re_dir = re.compile(r"^(m[mnvrlia]|a[aif])([01]\d|2[01])(00[1-9]|0[1-9]\d|[1-5]\d\d|600)$")
re_file = re.compile(r"^[1-9]\.(pas|c|cpp|java)$", re.IGNORECASE)

maxBrZad = 0
zadaci = {}

for f in os.listdir(homedir):
    studDir = os.path.join(homedir, f)
    m = re_dir.match(f)
    if os.path.isdir(studDir) and m is not None and f in studenti:
        indeks = m.group(1)
        for sf in os.listdir(studDir):
            zadatak = os.path.join(studDir, sf)
            m = re_file.match(sf)
            if os.path.isfile(sf) and m is not None:
                zad = int(m.group(1))
                zadaci[(indeks, zad)] = m.group(2)
                if(zad>maxBrZad):
                    maxBrZad=zad

for indeks, ime in studenti.items():
    print('\nIme: ' + ime)
    for i in range(1, maxBrZad):
        if(indeks, i) in zadaci:
            print('\t' + str(i) + "-" + zadaci[(indeks, i)])
        else:
            print('\t'+str(i)+ ".-")