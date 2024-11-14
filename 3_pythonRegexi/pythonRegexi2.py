import sys
import re

poruka = "Danas je divan dan "
match = re.match(r"(\w+\s+)(\w+\s+)*", poruka)

if match is None:
    sys.exit("Neuspelo poklapanje")
else:
    print(match.group())
    print(match.groups())

m = re.search(r"\bd[a-z]+", poruka, re.IGNORECASE)
offset = 0

if m is not None:
    print(m.group())
    print(poruka[m.start(): m.end()])
    offset = m.end()

m = re.search(r"\bd[a-z]+", poruka[offset: ], re.IGNORECASE)
if m is not None:
    print(m.group())
    print(poruka[offset+m.start(): offset+m.end()])

m = re.findall(r"\bd[a-z]+", poruka, re.IGNORECASE)
print(m)

np = poruka.replace("Danas", "Sutra")
print(np)
