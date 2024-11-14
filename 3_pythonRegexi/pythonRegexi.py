import sys
import re

if len(sys.argv) < 2:
    sys.eit('Nedovoljno argumenata')

# re.match(regex, tekst, rezim)
match = re.match(r'^.*\.txt$', sys.argv[1], re.IGNORECASE)

if match is None:
    sys.exit("Los format fajla")
else:
    print('Uspesno citanje')

try:
    f=open(sys.argv[1], 'r')
except:
    sys.exit('Neuspelo otvaranja fajla')

for l in f:
    print(l, end="")

f.close()