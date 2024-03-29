all : tme1_exo1p1 tme1_exo1p2 tme1_exo1p3 tme1_exo2p1 tme1_exo2p2_q5 tme1_exo2p2_q6

tme1_exo1p1 : 
	gcc -o tme1_exo1p1 tme1_exo1p1.c

tme1_exo1p2 : 
	gcc -o tme1_exo1p2 tme1_exo1p2.c

tme1_exo1p3 : 
	gcc -o tme1_exo1p3 tme1_exo1p3.c

fonctions_tableau.o : fonctions_tableau.c fonctions_tableau.h
	gcc -c fonctions_tableau.c

tme1_exo2p1 : tme1_exo2p1.o fonctions_tableau.o
	gcc -Wall -o tme1_exo2p1 tme1_exo2p1.o fonctions_tableau.o

tme1_exo2p1.o : tme1_exo2p1.c fonctions_tableau.h
	gcc -Wall -c tme1_exo2p1.c
	
fonctions_matrice.o : fonctions_matrice.c fonctions_tableau.h fonctions_matrice.h
	gcc -c fonctions_matrice.c

tme1_exo2p2_q5 : tme1_exo2p2_q5.o fonctions_tableau.o fonctions_matrice.o
	gcc -Wall -o tme1_exo2p2_q5 tme1_exo2p2_q5.o fonctions_tableau.o fonctions_matrice.o
	
tme1_exo2p2_q5.o : tme1_exo2p2_q5.c fonctions_tableau.h fonctions_matrice.h
	gcc -Wall -c tme1_exo2p2_q5.c

tme1_exo2p2_q6 : tme1_exo2p2_q6.o fonctions_tableau.o fonctions_matrice.o
	gcc -Wall -o tme1_exo2p2_q6 tme1_exo2p2_q6.o fonctions_tableau.o fonctions_matrice.o

tme1_exo2p2_q6.o : tme1_exo2p2_q6.c fonctions_tableau.h fonctions_matrice.h
	gcc -Wall -c tme1_exo2p2_q6.c

clean :
	rm -f *.o tme1_exo2p1 tme1_exo2p2_q5 tme1_exo2p2_q6 
