import sys
import re
import os

if len(sys.argv) > 1:
    trenutniDirektorijum = sys.argv[1]
else:
    trenutniDirektorijum="."

dSablon = re.compile(r"^(m[mnvrlia]|a[aif])([01]\d|2[01])(00[1-9]|0[1-9]\d|[1-5]\d\d|600)$")
fSablon = re.compile(r"^[1-9]\.(pas|c|cpp|java)$", re.IGNORECASE)

for fajl in os.listdir(trenutniDirektorijum):
    dPutanja = os.path.join(trenutniDirektorijum, fajl)
    poklapanje = dSablon.match(fajl)
    if os.path.isdir(dPutanja) and poklapanje is not None:
        print("\n"+poklapanje.group())
        for sf in os.listdir(dPutanja):
            fPutanja = os.path.join(dPutanja, sf)
            poklapanje = fSablon.match(sf)
            if os.path.isfile(fPutanja) and poklapanje is not None:
                print('\t' + poklapanje.group())