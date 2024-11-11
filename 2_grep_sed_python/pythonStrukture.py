import sys

# LISTE 

l=[1, 2, 3, 4, 5, 6] #lista
print(l)

t = (1, 2, 3, 4, 5, 6) #tuple (tuple je imutabilan)
print(t)

l[2]="Neki string"
print(l)

print(l[1:4])
print(l[-1])

print(l+l) # nista od ovoga ne menja orignalnu listu
print(l*4) # nadovezi listu samu na sebe 4 puta

b = l[:] # ovako pravimo kopiju liste
print(b)
b[:0] = ['na', 'pocetak']
print(b)

b.extend(l) # ovo menja listu b, b=b+l
print(b)

b.append('nesto') # i ovo menja listu b
print(b)

b.append(l)
print(b)

b.pop()
print(b)

b=[1,3,2,5,6,4]
b.sort(reverse=True)
print(b)

s=['set','cas','bob','bla']
s.sort()
print(s)

s.sort(key=len)
print(s)

s.reverse()
print(s)

# SKUPOVI

s=set('abrakadabra')
print(s)

b=['abrakadabra','primer', 'primer']
print(set(b))

if 'f' not in s:
    s.add('f')
    print(s)
else:
    s.remove('f')

c = set('primer1234')
print(s & c)
print(s.intersection(c))

print(s | c)
print(s.union(c))

print(s-c)
print(s.difference(c))

print(s^c)
print(s.symmetric_difference(c))

# MAPE (VEOMA BITNO)

telefoni = {"Pera" : 123,
            "Zika" : 230,
            "Mika" : 310}
print(telefoni)

print(list(telefoni.keys()))
print(list(telefoni.values()))

if telefoni.get("Laza") is None:
    print("Unos ne postoji")

if len(telefoni) < 3:
    print(telefoni)
else:
    telefoni["Laza"] = 500

print(telefoni.get("Laza"))

parovi = zip(telefoni.keys(), telefoni.values())

for k,v in parovi:
    print(k, v)

for k, v in telefoni.items():
    print(k, v)