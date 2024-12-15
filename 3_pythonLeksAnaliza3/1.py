import sys
import re

if len(sys.argv) < 2:
    sys.exit("Nedovoljno argumenata")

if re.match(r'^.+\.xml$', sys.argv[1], re.I) is None:
    sys.exit("Losa ekstenzija")

try:
    with open(sys.argv[1], 'r') as f:
        podaci = f.read()
except IOError:
    sys.exit("Neuspelo citanje fajla")

ri = re.compile(r'<televizor\s+id\s*="\s*(?P<rbr>[0-9]+)\s*"\s*>'
                +r'(?=.*?<rmarka>\s*(?P<rmarka>[A-Za-z0-9]+)\s*</rmarka>)'
                +r'(?=.*?<model>\s*(?P<model>[A-Za-z0-9 ,:;-]+)\s*</model>)'
                +r'(?=.*?<godina>\s*(?P<godina>[0-9]{4})\s*</godina>)'
                +r'(?=.*?<diag>\s*(?P<diag>[1-9][0-9](\.\d)?)\s*</diag>)'
                +r'(?=.*?<kolicina>\s*(?P<kolicina>[0-9]+)\s*</kolicina>)'
                +r'(?=.*?<panel>\s*(?P<panel>(TN|IPS|VA|LED)-(HD|FHD|UHD))\s*</panel>)'
                +r'(?=.*?<cena>\s*(?P<cena>[1-9][0-9]*)\s*</cena>)'
                +r'.*?'
                +r'</televizor>', re.S)

televizori = {}

for m in ri.finditer(podaci):
    rbr = m.group('rbr')
    marka = m.group("rmarka")
    model = m.group("model")
    godina = int(m.group('godina'))
    diag = float(m.group('diag'))
    panel = m.group('panel')
    cena = int(m.group('cena'))
    kolicina = int(m.group('kolicina'))

    televizori[rbr] = [marka, model, godina, diag, panel, cena, kolicina]

if len(sys.argv) == 2:
    for k, v in televizori.items():
        print(k+':')
        print(v)
else:
    if sys.argv[2] == '-r' and len(sys.argv) == 4:
        rmarka = sys.argv[3]
        for k, v in televizori.items():
            if v[0] == rmarka:
                print(v)
    elif sys.argv[2] =='-g' and len(sys.argv) == 4:
        godina = int(sys.argv[3])
        for k, v in televizori.items():
            if v[2] == godina:
                print(v)
    elif sys.argv[2] =='-c' and len(sys.argv) == 5:
        cmin = int(sys.argv[3])
        cmax = int(sys.argv[4])
        for k, v in televizori.items():
            if (v[5] >= cmin and v[5] <= cmax):
                print(v)
    elif sys.argv[2] =='-d' and len(sys.argv) == 5:
        dmin = int(sys.argv[3])
        dmax = int(sys.argv[4])
        for k, v in televizori.items():
            if (v[3] >= dmin and v[3] <= dmax):
                print(v)
    else:
        sys.exit("Losa opcija")