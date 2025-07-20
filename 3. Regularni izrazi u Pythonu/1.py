# Korisnik kao argument komandne linije prosleđuje putanju do direktorijuma
# u kome se nalaze seminarski radovi studenata. Svakom studentu je dodeljen direktorijum
# čije ime prati alas format. Program treba da izlista zadatke koje su uradili samo oni
# studenti koji su kreirali direktorijum sa ispravnim imenom. Zadaci su opisani jednom
# cifrom i ekstenzijom koja može biti .pas, .java, .c ili .cpp.

import sys, re, os

if len(sys.argv) < 2:
    homedir = "."
else:
    homedir = sys.argv[1]

dir_regex = re.compile(r"^m[mnvlri]\d{5}$")
file_regex = re.compile(r"^(\d)\.(pas|java|c|cpp)$")

for dir in os.listdir(homedir):
    dir_path = os.path.join(homedir, dir)
    m = dir_regex.match(dir)
    if m is not None and os.path.isdir(dir_path):
        print("\n" + m.group())

        for file in os.listdir(dir_path):
            file_path = os.path.join(dir_path, file)
            m = file_regex.match(file)
            if m is not None and os.path.isfile(file_path):
                print("\t" + m.group())
