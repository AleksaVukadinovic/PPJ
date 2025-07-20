# Ovaj zadatak je proširenje prethodnog zadataka. Informacije o studentima
# koji su radili seminarski zadatak se nalaze u datoteci indeksi.txt. U svakoj liniji datoteke
# zapisan je broj indeksa, praćen imenom i prezimenom studenta. Za svakog studenta u
# datoteci indeksi.txt, potrebno je prikazati koje je sve zadatke uradio na osnovu sadržaja
# njegovog direktorijuma. Prikaz treba da bude tabelarni, poput ovog:
# Pera Peric - pas - c
# Ivan Ivanovic c pas - java
# Prva kolona odgovara imenu studenta, naredna prezimenu, potom redom za zadatke
# počevši od zadatka pod rednim brojem 1.

import sys, os, re


if len(sys.argv) < 2:
    homedir = "."
else:
    homedir = sys.argv[1]

students = {}

path_to_indeksi = os.path.join(homedir, "indeksi.txt")
name_regex = re.compile(r"m[mlnrvi]\d{5},\s*[a-zA-Z]+")

try:
    with open(path_to_indeksi, "r") as f:
        for line in f.readlines():
            if name_regex.match(line) is not None:
                info = re.split(r",\s*|\n", line)
                students[info[0]] = info[1]
except IOError:
    sys.exit("Failed to open indeksi.txt")

dir_regex = re.compile(r"^m[mnvrli]\d{5}$")
file_regex = re.compile(r"^(\d)\.(java|pas|c(pp)?)$")

problems = {}
max_problem = 0

for dir in os.listdir(homedir):
    m = dir_regex.match(dir)
    dir_path = os.path.join(homedir, dir)
    if m is not None and os.path.isdir(dir_path) and m.group() in students:
        student_index = m.group()

        for file in os.listdir(dir_path):
            problem_path = os.path.join(dir_path, file)
            m = file_regex.match(file)
            if os.path.isfile(problem_path) and m is not None:
                problem = int(m.group(1))
                problems[(student_index, problem)] = m.group(2)
                problem = max(problem, max_problem)

for index, name in students.items():
    print(name + " ", end=" ")

for i in range(1, max_problem + 1):
    if (index, i) in problems:
        print("\t" + problems[(index, i)], end=" ")
    else:
        print("\t-", end=" ")
print()
