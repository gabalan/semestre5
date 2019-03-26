CFLAGS+= -g -D_REENTRANT
LDFLAGS= -lpthread

distribuer: distribuer.o distributeur.o
distribuer.o: distribuer.c distributeur.h 
distributeur.o: distributeur.h distributeur.c 


clean:
	rm *.o distribuer