import sys

# TODO

prelazi = {('AC', 'a'): 'B', ('AC', 'b'): 'AC',
           ('B', 'a'): 'B', ('B', 'b'): 'D',
           ('D', 'a'): 'B', ('D', 'b'): 'E',
           ('E', 'a'): 'B', ('E', 'b'): 'AC',}

stanje = 'AC'
zavrsna = ['E']

while True:
    try:
        c=input("Unesi a ili b\n")
        if(c!='a' and c!='b'):
            raise ValueError("Alfabet je [a, b]")
    except EOFError:
        break
    except ValueError as e:
        print(e)
        sys.exit()

    stanje = prelazi[(stanje, c)]
    print('\t' + stanje)

if stanje in zavrsna:
    print("Rec je deo jezika")
else:
    print("Rec nije deo jezika")