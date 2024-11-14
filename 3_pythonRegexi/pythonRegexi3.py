# Treba izdvojiti greske u kucanju 
# Smatramo da je greska u kucanju da se rec ponovi 2 puta

import re
import sys

if len(sys.argv) < 2:
    sys.exit("Nedovoljno argumenata")

if re.match(r"^.*\.txt$", sys.argv[1], re.IGNORECASE) is None:
    sys.exit("Fajl mora biti .txt")

try:
    f=open(sys.argv[1], "r")
except IOError:
    sys.exit("Neuspelo otvaranje fajla")

ri = re.compile(r"(\b[a-zA-Z]+\b)\s+\1")

for linija in f:
    match = ri.search(linija)
    if match is not None:
        print("Poklapanje: %s\n grupe: %s"%(match.group(), match.groups()))
        print("Linija bez ponavljanja: "+ ri.sub(match.group(1), linija))

f.close()

try:
    f = open(sys.argv[1], "r")
    data =  f.read()
except IOError:
    sys.exit("Greska pri otvaranju")

for m in ri.finditer(data):
    print(m.group())

f.close()