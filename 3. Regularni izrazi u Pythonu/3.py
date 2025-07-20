# Korisnik programu prosleđuje naziv početne HTML datoteke preko argumenta komandne linije.
# Program pronalazi i prati sve linkove počevši od početne HTML datoteke.

import sys, re


def checkout_dir(dir_name):
    if dir_name in checked_dirs:
        return
    checked_dirs.append(dir_name)

    try:
        with open(dir_name, "r") as f:
            dir = f.read()
    except IOError:
        exit("Failed to open dir '" + dir_name + "'")

    link_regex = re.compile(r'<a\s+href\s*=\s*"(.*?)">.*?</a>', re.I | re.S)
    for match in link_regex.finditer(dir):
        url = match.group(1)
        checkout_dir(url)


if len(sys.argv) < 2:
    homedir = "."
else:
    homedir = "index.html"

checked_dirs = []
checkout_dir(homedir)

for dir in checked_dirs:
    print(dir)
