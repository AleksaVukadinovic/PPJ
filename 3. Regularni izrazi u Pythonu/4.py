# Ovaj program je proširenje programa iz prethodnog primera. Proširenje
# se ogleda u tome što se od početne stranice vodi evidencija o broju posećivanja veb
# stranica. Nakon obrade prikazuje se sortiran spisak posećenih stranica od najposećenije
# ka najređe posećivanoj.

import re, sys


def checkout_dir(dir_name):
    if dir_name in checked_dirs:
        return
    checked_dirs.append(dir_name)

    text = dir_name
    try:
        with open(dir_name, "r") as f:
            text = f.read()
    except IOError:
        exit("Failed to open file: " + text)

    link_regex = re.compile(r'<a\s+href\s*=\s*"(.*?)">(.*?)</a>', re.I | re.S)

    for match in link_regex.finditer(text):
        url = match.group(1)

        if url in visits:
            visits[url] += 1
        else:
            visits[url] = 1
        checkout_dir(url)


if len(sys.argv) > 1:
    homepage = sys.argv[1]
else:
    homepage = "index.html"

visits = {}
checked_dirs = []

checkout_dir(homepage)

pairs = list(visits.items())
pairs.sort(reverse=True, key=lambda t: t[1])

for url, number_of_visits in pairs:
    print(url, "\t", number_of_visits)
