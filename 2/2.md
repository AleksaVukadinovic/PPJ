# Čas 2 - Grep, Sed, Uvod u Python

## Grep

`grep` je alat koji služi za izdvajanje teksta na osnovu regularnog izraza. Nastao je 1980-ih i koristi tzv. "basic regex" koji ne podržava neke moderne operatore (npr. `+`, `?`, `|`).

Zato koristimo `egrep`, koji je novija verzija sa podrškom za većinu modernih operatora.

**Svrha oba alata**: Izdvajanje delova teksta na osnovu datog šablona.

**Sintaksa:**

```bash
egrep [opcije] 'regex' fajl
```

**Najčesće opcije:**

* `-i` — ignorisanje veličine slova (case-insensitive)
* `-c` — samo broj poklapanja
* `-n` — ispisuje broj linije gde se poklapanje nalazi
* `-v` — inverzija, ispisuje linije koje **ne** sadrže poklapanje

## Sed

`sed` je alat za obradu teksta, koristi se kao "find and replace" iz komandne linije. **Ne menja originalni fajl**, već rezultat ispisuje na standardni izlaz.

**Sintaksa:**

```bash
sed -r 's/pattern/zamena/g' fajl
```

* `s` označava substituciju
* separator može biti `/`, `:`, itd.
* `g` označava globalnu zamenu (sva pojavljivanja)
* `-r` aktivira "extended regex"

**Primer:**

```bash
sed -r 's/([0-9]+)\s+([a-z]+)/\2 \1/' <<< "10 abc"
# Rezultat: abc 10
```

> Napomena. Oba ova alata svoj rezultat ispisuju na standardni izlaz, ako zelimo da to preusmerimo u fajl, koristimo preusmeravanje

**Preusmeravanje u fajl:**

```bash
egrep 'regex' fajl.txt > rezultat.txt
sed -r 's/foo/bar/g' fajl.txt > novi_fajl.txt
```

---

## Uvod u Python

U Python-u, kao zamenu za `#include`, koristimo `import`, npr.:

```python
import sys
```

**"Hello, world!" primer:**

```python
print("Hello World!")
```

**Pokretanje:**

```bash
python3 fajl.py
```

**Instalacija biblioteka:**

```bash
pip install naziv
```

**Osobine jezika:**

* Slabo tipiziran: ne navode se tipovi eksplicitno
* Nema `;` na kraju linije
* Nema `{}` — koristi **indentaciju**

**print funkcija:**

```python
print(arg1, arg2, sep="-")  # separator između argumenata
```

**Aritmetički operatori:**

* `+` sabiranje
* `-` oduzimanje
* `*` množenje
* `**` stepenovanje
* `/` deljenje (uvek float)
* `//` celobrojno deljenje
* `%` ostatak

**Kompleksni brojevi:**

```python
x = 2.5 + 3.5j
print(x.real, x.imag)
```

**Višelinijski stringovi:**

```python
print("""
	DOSLOVNI STRING
	sadrži \ \ \ / / /
""")
```

**Indeksiranje:**

```python
arr[-1]       # poslednji element
s[2:8]        # od pozicije 2 do 7
s[:8]         # od početka do pozicije 7
s[2:]         # od pozicije 2 do kraja
s[:]          # kopija stringa
s[0:-2]       # od 0 do pretposlednjeg
s[-7:-3]      # deo od -7 do -4
s[-3:-7]      # prazan string (pošto -3 > -7)
len(s)        # dužina stringa
```

---

## Strukture u Pythonu

### Lista:

```python
lista = [1, 2, 3, 4, 5, 6]
print(lista)
```

### Tuple (nepromenljivi):

```python
t = (1, 2, 3, 4, 5, 6)
```

### Operacije nad listama:

* `L1 + L2` — nadovezivanje
* `L * 4` — ponavljanje
* `L2 = L[:]` — kopiranje
* `L[:0] = [-1, 0]` — dodavanje na početak
* `L2.extend(L1)` — nadovezuje L1 na L2
* `L.append(x)` — dodaje na kraj
* `L.pop()` — uklanja poslednji element
* `L.sort()` — sortiranje u mestu
* `L.sort(reverse=True)` — opadajuće
* `L.sort(key=len)` — sortiranje po dužini stringa

### Skupovi:

```python
s = set("abkradabra")  # {'a', 'b', 'r', 'k', 'd'}
b = ["abrakdabra", "primer", "primer"]
print(set(b))  # {'abrakdabra', 'primer'}
```

### Grananje:

```python
if 'f' not in s:
    s.add('f')
    print(s)
else:
    s.remove('f')
    print(s)

c = set("primer1234")
print(s & c)  # presek
print(s | c)  # unija
print(s - c)  # razlika
print(s ^ c)  # simetrična razlika
```

### Blokovi:

```python
import sys
s = input("Unesite brojeve: ")
s = map(int, s.split())

for x in s:
    if x % 2 == 0:
        print("Paran")
        if x > 1000:
            print("Veći od 1000")
        else:
            print("Manji ili jednak 1000")
    else:
        print("Neparan")
```

---

## Rečnici (mape):

```python
telefoni = {"Pera": 123, "Zika": 230, "Mika": 310}
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
for k, v in parovi:
    print(k, v)

for k, v in telefoni.items():
    print(k, v)
```