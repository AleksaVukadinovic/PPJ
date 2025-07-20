# Čas 1 - Regularni izrazi

## 4 osnovna koraka u prevođenju:
1. Leksička analiza
2. Sintaksna analiza
3. Semantička analiza
4. Optimizacija koda

> Napomena: Na ovom predmetu fokusiramo se na prva dva koraka – leksičku i sintaksnu analizu.

---

## Leksička analiza

Leksička analiza predstavlja skup pravila koji omogućava da se niz karaktera prepozna kao reči, odnosno *tokeni*. Obično se sastoji iz dva koraka:

1. **Da li reč pripada jeziku**  
   - Primeri: ključne reči (`if`, `else`, `while`), specijalne vrednosti (`true`, `false`, `null`, itd.)
   - Ove se najčešće proveravaju direktnim poređenjem sa rečnikom jezika.

2. **Identifikacija tipa tokena (tokenizacija)**  
   - Tipovi tokena uključuju:  
     - Ceo broj  
     - Realan broj  
     - Identifikator  
     - Ključna reč  
     - Operator  
     - Boolean vrednost  
     - Simboli (zagrade, zarezi itd.)

Za identifikatore nije moguće unapred znati sve moguće nazive, pa se za njih i druge šablone koristi **regularni izraz (regex)**.

---

## Sintaksna analiza

Ova faza sledi posle leksičke i proverava da li su reči pravilno raspoređene – tj. da li niz tokena poštuje gramatiku jezika.

- Primer validnog izraza: `if (x > 0) { ... }`
- Primer nevalidnog izraza: `if x > 0) { ... }` – nedostaje leva zagrada

---

## Regularni izrazi (regex)

Regularni izrazi služe za opisivanje šablona u tekstu. Koriste se u leksičkoj analizi, parserima, alatima za obradu teksta itd. **Case-sensitive su.**

### Osnovne operacije:

- **Bukvalno poklapanje (literal match)**  
  `while` – traži tačno tu reč

- **Alternacija (`|`)**  
  `cat|dog` – poklapa `"cat"` ili `"dog"`

- **Grupisanje (`( )`)**  
  `baban(a|e)` – poklapa `"banana"` i `"banane"`

- **Pojavljivanje (`?`)**  
  `colou?r` – poklapa `"color"` i `"colour"`  
  (znak `?` se odnosi samo na karakter ili grupu levo od njega)

- **Ponavljanje (`*`, `+`)**  
  - `*` – 0 ili više puta  
  - `+` – 1 ili više puta  
  - Primer: `a+` poklapa `"a"`, `"aa"`, `"aaa"`...

- **Ograničeno ponavljanje (`{}`)**  
  - `a{2,4}` – između 2 i 4 ponavljanja  
  - `a{3}` – tačno 3 ponavljanja

- **Karakterske klase (`[]`)**  
  - `[aeiou]` – bilo koji samoglasnik  
  - `[a-zA-Z]` – bilo koje slovo (malo ili veliko)  
  - `[0-9]` – cifre

- **Negirana karakterska klasa (`[^]`)**  
  - `[^0-9]` – bilo koji karakter koji **nije cifra**

- **Wildcard (`.`)**  
  - Poklapa bilo koji karakter osim novog reda

- **Escape karakter (`\`)**  
  - Koristi se za izbegavanje specijalnog značenja karaktera  
  - Primer: `\.` poklapa tačku

- **Prefiks i sufiks (`^`, `$`)**  
  - `^regex` – poklapa samo ako je regex na početku reda  
  - `regex$` – poklapa samo ako je regex na kraju reda  
  - `^regex$` – poklapa samo ako regex zauzima ceo red

- **Granice reči (`\b`)**  
  - `regex\b` – poklapa kraj reči  
  - `\bregex\b` – poklapa celu reč (odvojenu razmakom, znakom itd.)

- **Pohlepni vs. nepohlepni izrazi**  
  - `.*` – poklapa maksimalno mnogo karaktera  
  - `.*?` – poklapa minimalno koliko mora

- **Backreference (unazadne reference)**  
  - Primer: `<([a-zA-Z]+)(.*?)<\/\1>`  
    - `\1` se odnosi na prvu grupu u zagradama (naziv taga)  
    - Koristi se da bi se osiguralo da se završni tag poklapa sa početnim

- **Unapred definisane klase**  
  - `\d` – cifre (`[0-9]`)  
  - `\w` – reči (`[a-zA-Z0-9_]`)  
  - `\s` – beline (space, tab, newline)  
  - `\D`, `\W`, `\S` – negacije prethodnih

- **Lookahead i lookbehind (preduvidi i postuvidi)**  
  Koriste se da proverimo **da li nešto sledi ili prethodi** delu teksta, bez da se to uključuje u poklapanje.

  - `X(?=Y)` → **pozitivni lookahead** – poklapa `X` samo ako je posle njega `Y`  
    - Primer: `\d(?=%)` poklapa cifru samo ako je posle nje `%`  
      - `"5%"` → ✅ `"5"`  
      - `"5px"` → ❌

  - `X(?!Y)` → **negativni lookahead** – poklapa `X` samo ako **nije** posle njega `Y`  
    - Primer: `\d(?!%)` poklapa cifru samo ako nije posle nje `%`

  - `(?<=Y)X` → **pozitivni lookbehind** – poklapa `X` samo ako je pre njega `Y`  
    - Primer: `(?<=\$)\d+` poklapa broj koji dolazi posle `$`  
      - `"$100"` → ✅ `"100"`  
      - `"100"` → ❌

  - `(?<!Y)X` → **negativni lookbehind** – poklapa `X` samo ako **nije** pre njega `Y`  
    - Primer: `(?<!\$)\d+` poklapa broj ako pre njega **nije** `$`

  > Ne uzimaju karaktere u rezultat – samo proveravaju kontekst.