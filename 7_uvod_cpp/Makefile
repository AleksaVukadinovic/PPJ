main: main.o complex.o poly_v2.o poly_v1.o dinNiz.o razlomak.o
	g++ main.o complex.o poly_v2.o poly_v1.o dinNiz.o razlomak.o -o main

main.o: Uvod.cpp 
	g++ -c Uvod.cpp -o main.o

complex.o: KompleksniBroj.cpp KompleksniBroj.h
	g++ -c KompleksniBroj.cpp -o complex.o

poly_v2.o: Polinom_v2.cpp Polinom_v2.h
	g++ -c Polinom_v2.cpp -o poly_v2.o

poly_v1.o: Polinom_v1.cpp Polinom_v1.h
	g++ -c Polinom_v1.cpp -o poly_v1.o

dinNiz.o: DinamickiNiz.cpp DinamickiNiz.h
	g++ -c DinamickiNiz.cpp -o dinNiz.o

razlomak.o: Razlomak.cpp Razlomak.h
	g++ -c Razlomak.cpp -o razlomak.o

.PHONY: clean

clean:
	rm -rf *.o main