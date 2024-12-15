import sys

prelazi = {('ADE', 'a'):'B', 
           ('ADE', 'b'):'C',
           ('ADE', 'c'):'ADE',
           ('B', 'a'):'B'}
pocetno = 'ADE'
zavrsna = ['C']

while True:
    try:
        c = input()
        if(c!='a' and c!= 'b' and c!='c'):
            raise ValueError
        
        if prelazi.get((stanje, c)) is None:
            sys.exit("Nije deo jezika")
        stanje = prelazi[(stanje, c)]
    except EOFError:
        break
    except ValueError:
        sys.exit('alfabet')

if stanje in zavrsna:
    print("Rec je deo jezika")
else:
    print("Rec nije deo jezika")