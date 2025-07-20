# Leksička analiza

**Leksička analiza** je prva faza kompilacije i predstavlja pretvaranje niza karaktera (izvorni kod, veb stranica, skripta...) u niz tokena.
**Token** je niz karaktera koji u gramatici jezika predstavlja jedinstvenu celinu.
Drugim rečima, token je string koji ima dodeljeno značenje pomoću koga se identifikuje u gramatici jezika.

Najčešće se tokeni predstavljaju kao uređeni parovi koji sadrže:

* naziv tokena (leksička kategorija)
* opcionalno: vrednost tokena

Uobičajene leksičke kategorije su:

* identifikator
* separator
* terminator
* ključna reč
* operator
* literal

Program koji vrši leksičku analizu naziva se **leksički analizator** ili **lekser**.
Ulaz za lekser je niz karaktera (npr. izvorni kod programa), a izlaz je niz tokena koji se prosleđuje parseru na sledeću fazu — sintaksnu analizu.

Leksički analizatori se najčešće implementiraju pomoću determinističkih konačnih automata (DKA).

## Definisanje tokena

Prilikom dizajniranja leksera, potrebno je unapred definisati skup tokena i za svaki token navesti odgovarajući regularni izraz.
Na ovaj način omogućava se:

* automatsko prepoznavanje tokena
* detekcija leksičkih grešaka (sve što ne odgovara nijednom tokenu)
* precizno lociranje greške u ulaznom nizu

Pošto broj tokena i složenost izraza mogu biti veliki, ručno pisanje DKA može biti nepraktično. Zato se koriste alati za automatsku generaciju leksičkih analizatora.

Jedan takav alat je **Flex**, koji generiše C kod za lekser.

---

## Generator leksičkih analizatora — Flex

**Flex** je alat koji generiše leksičke analizatore.
Da bismo generisali analizator, potrebno je:

1. napisati specifikaciju u Flex sintaksi
2. uz pomoć Flex-a generisati C kod analizatora

Specifikacija Flex leksera se sastoji iz tri dela razdvojena sa `%%`:

```c
// segment definicija
%%
// segment akcija
%%
// segment korisničkog koda
```

**Napomena**: `%%` mora biti na početku reda (bez vodećih razmaka) i mora biti jedini sadržaj tog reda.

### Segment definicija

Sadrži:

* C kod koji se direktno kopira u generisani program (između `%{` i `%}`)
* definicije regularnih izraza
* direktive za Flex

Primer:

```c
%{
#include <stdio.h>
%}
```

### Segment akcija

Svaka linija sadrži:

* regularni izraz
* blok C koda koji opisuje akciju koja se izvršava kada se izraz prepozna

Primer:

```c
[0-9]+ {
  printf("Broj: %s\n", yytext);
}
```

### Segment korisničkog koda

Opciono: dodatne funkcije, `main()` funkcija i ostalo.

---

## Kreiranje leksičkog analizatora u praksi

1. Napiši Flex skriptu, npr. `lexer.l`
2. Pokreni Flex da generiše `lex.yy.c`:

```bash
flex lexer.l
```

3. Prevedi generisani fajl uz pomoć GCC-a:

```bash
gcc lex.yy.c -o lexer
```

---

## Makefile primer

Radi jednostavnosti možemo koristiti Makefile:

```makefile
lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: lexer.l
	flex lexer.l
```

Kompilaciju zatim pokrećemo jednostavno:

```bash
make
```

---

Dalje ćemo sve videti kroz praktične zadatke.
