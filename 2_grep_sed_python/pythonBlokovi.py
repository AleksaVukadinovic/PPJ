import sys

s = input('Unesite brojeve: \n')
s = map(int, s.split(' '))

for x in s:
    if(x%2==0):
        print('Paran')
        if x>1000:
            print("Veci od 1000")
        else:
            print('<=1000')
    else:
        print('Neparan')
        if x>1000:
            print("Veci od 1000")
        else:
            print('<=1000')