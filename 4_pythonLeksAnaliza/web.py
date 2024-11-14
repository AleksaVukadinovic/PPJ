import sys
import re

def obradi_stranice(dat):
    if dat in obradjenje_datoteke:
        return
    
    obradjenje_datoteke.append(dat)
    
    try:
        with open(dat, "r") as f:
            podaci = f.read()
    except IOError:
        sys.exit("Greska pri otvaranju fajla")
    
    ri = re.compile(r'<a\s+href\s*=\s*"([^"]+)"\s*>(.*?)</a>', re.S | re.I)

    for m in ri.finditer(podaci):
        url = m.group(1)

        if url in statistika:
            statistika[url]+=1
        else:
            statistika[url]=1
        
        obradi_stranice(url)



if len(sys.argv) < 2:
    pocetna = sys.argv[1]
else:
    pocetna = 'prva.html'

obradjenje_datoteke = []
statistika = {}

obradi_stranice(pocetna)

popularnost = sorted(zip(statistika.values(), statistika.keys()))
popularnost.reverse()

for no, url in popularnost:
    print(url, no, sep=": ")