# Programu se kao prvi argument komandne linije navodi ime HTML datoteke
# koja sadrži tabelu u kojoj se nalaze rezultati ispita. Tabela ima tri kolone. U prvoj se
# nalazi ime i prezime studenta u drugoj broj poena na teorijskom delu ispita i u trećoj
# broj poena na praktičnom delu ispita. Broj poena na svakom delu treba da bude ceo broj
# iz intervala [0,100]. Ne izdvajaju se studenti sa ne ispravnim podacima. Program treba
# da pročita sadržaj tabele u datoteku sortirano.txt da ispiše ime i prezime studenata i
# ukupan broj poena na ispitu. Ukupan broj poena se računa kao aritmetička sredina
# brojeva poena sa oba dela ispita. Izveštaj treba da bude uređen u opadajućem poretku
# prema ukupnom broju poena.
# Na primer, ulazna HTML datoteka bi mogla da sadrži fragment poput ovog:
# <table width="220">
# <tr>
# <td>Savic Marko </td>
# <td> 35 </td> <td> 0 </td>
# </tr> <tr>
# <td>Bogdanovic Vesna</td>
# <td> 68 </td>
# <td> 98 </td>
# </tr>
# <tr>
# <td>Filipovic Vukasin</td><td>96</td> <td> 70 </td>
# </tr>
# <tr> <td>Pavlovic Sofija</td><td>100</td><td> 89 </td> </tr>
# </table>
# Tada bi rezultat programa bio:
# 1. Pavlovic Sofija 94.5
# 2. Filipovic Vukasin 83.0
# 3. Bogdanovic Vesna 83.0
# 4. Savic Marko 17.5

import sys, re

if len(sys.argv) < 2:
    homedir = "index.html"
else:
    homedir = sys.argv[1]
    if re.fullmatch(r".*\.html", homedir, re.I) is None:
        sys.exit("File must be of type .html")

try:
    with open(homedir, "r") as f:
        data = f.read()
except IOError:
    exit("Failed to open file" + homedir)

students = []
points = []

table_data_regex = re.compile(
    r"<tr>"
    + r"\s*<td>\s*(?P<ime >[A-Za-z]+(?: +[A-Za-z]+)+)\s*</td>"
    + r"\s*<td>\s*(?P<zadaci >0|[1-9]\d|100)\s*</td>"
    + r"\s*<td>\s*(?P<teorija >0|[1-9]\d|100)\s*</td>"
    + r"\s*</tr>"
)

for match in table_data_regex.finditer(data):
    total = (int(match.group("zadaci")) + int(match.group("teorija"))) / 2.0

    students.append(match.group("ime"))
    points.append(total)

sorted_points = list(zip(points, students))
sorted_points.sort(reverse=True)

try:
    with open("results.txt", "w") as f:
        for i, (pts, name) in enumerate(sorted_points):
            f.write(str(i + 1) + ". " + name + "\t\t" + str(pts) + "\n")
except IOError:
    sys.stderr.write("Failed to write to file 'results.txt'\n")
