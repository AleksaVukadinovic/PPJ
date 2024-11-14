import sys

if len(sys.argv) < 2:
    sys.exit('Nedovoljno argumenata')

for arg in sys.argv:
    print(arg)

try:
    f = open(sys.argv[1], 'r')
except IOError:
    sys.exit('Greska pri otvaranju fajla')

for linija in f:
    print(linija, end="")

f.close()