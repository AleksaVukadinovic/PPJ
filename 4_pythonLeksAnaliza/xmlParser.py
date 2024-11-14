import sys
import re

if len(sys.argv) < 2:
    sys.exit("Nedovoljno argumenata")

if re.match(r"^.+\.stn$", sys.argv[1], re.IGNORECASE) is None:
    sys.exit("Losa fajl ekstenzija")

try:
    with open(sys.argv[1], "r") as f:
        fajl = f.read()
except IOError:
    sys.exit("Neuspelo citanje fajla")

sablon = re.compile(r"{(.*?),\.NE\+([a-z]+):[0-9][a-z]}", re.I | re.S)

# for m in sablon.finditer(fajl):
#     print(m.group())

noviTekst = sablon.sub(r"<\2>\1</\2>", fajl)
print(noviTekst)

try:
    with open(sys.argv[1][:-3]+"xml", "w") as fxml:
        fxml.write("<xml>\n")
        fxml.write(noviTekst)
        fxml.write("\n</xml>")
except IOError:
    sys.exit("Neuspelo kreiranje fajla")
    