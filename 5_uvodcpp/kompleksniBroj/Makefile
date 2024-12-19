# Target executable
kompleksniBroj: main.o kompleksniBroj.o
	g++ main.o kompleksniBroj.o -o kompleksniBroj

# Object files
main.o: main.cpp kompleksniBroj.h
	g++ -c main.cpp -o main.o

kompleksniBroj.o: kompleksniBroj.cpp kompleksniBroj.h
	g++ -c kompleksniBroj.cpp -o kompleksniBroj.o

# Clean rule to remove generated files
.PHONY: clean

clean:
	rm -rf *.o kompleksniBroj
