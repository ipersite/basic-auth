CPP = g++
CPPFLAGS = -Wall

all: clean bas_auth
clean:
	rm -f *.o bas_auth

bas_auth: main.o authenticator.o
	$(CPP) $(CPPFLAGS) -o bas_auth main.o authenticator.o

main.o:
	$(CPP) $(CPPFLAGS) -c main.cpp

authenticator.o:
	$(CPP) $(CPPFLAGS) -c authenticator.cpp
