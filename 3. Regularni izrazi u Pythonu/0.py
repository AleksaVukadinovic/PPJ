# Uvodni primer za demonstraciju rada sa regexima u Pythonu

import re


message = "Danas je divan dan"
matcher = re.match(
    r"(?i)([a-z]+\s*)+", message
)  # re.match uvek trazi poklapanja od pocetka stringa

if matcher is not None:
    print(matcher.group())
else:
    print("Sablon se ne nalazi u tekstu")

m = re.search(r"\bd([a-z]+)", message, re.S | re.I)

if m is not None:
    print(m.group())
    print(message[m.start() : m.end()])
    print(m.group(1))
    print(m.groups())

m = re.search(
    r"\bd([a-z]+)", message[m.end() :], re.S
)  # re.search uvek trazi samo prvo poklapanje

if m is not None:
    print(m.group())
    print(message[m.start() : m.end()])
    print(m.group(1))
    print(m.groups())

words = re.findall(r"(?i)\b(d([a-z]+))", message)
print(words)
print(re.sub(r"(?i)\b(d([a-z]+))", r"\2-\1", message))
print(message.replace("Danas", "Sutra"))
