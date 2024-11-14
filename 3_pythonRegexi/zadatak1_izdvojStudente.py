import sys
import re

if len(sys.argv) < 2:
    sys.exit("Nedovolnjno argumenata")

if re.match(r"^.+\.html$", sys.argv[1], re.IGNORECASE) is None:
    sys.exit("Fajl mora biti .html")

try:
    with open(sys.argv[1], "r") as f:
        data = f.read()
except IOError:
    sys.exit("Neuspesno otvaranje fajla")

sablon = re.compile(r"<tr>"
                    +r"\s*<td>\s*(?P<ime>[A-Z][a-z]+(\s+[A-Z][a-z]+)+)\s*</td>"
                    +r"\s*<td>\s*(?P<prakticni>[1-9]\d|100)\s*</td>"
                    +r"\s*<td>\s*(?P<usmeni>[1-9]\d|100)\s*</td>"
                    +r"\s*</tr>", re.S)
  
studenti = []
poeni = []

for m in sablon.finditer(data):
    studenti.append(m.group("ime"))
    prakticni = int(m.group("prakticni"))
    usmeni = int(m.group("usmeni"))
    poeni.append((prakticni+usmeni)/2)

parovi = sorted(zip(poeni, studenti))
parovi.reverse()

for p,s in parovi:
    print(s, p)