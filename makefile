main : mainsys.c fan ear lib fsend frec msend
	gcc mainsys.c -o main

fan : smallsys.c 
	gcc smallsys.c -o fan
fsend : smallsend.c
	gcc smallsend.c -o fsend

frec : smallrec.c
	gcc smallrec.c -o frec

ear : mainear.c
	gcc mainear.c -o ear
lib : lib.c
	gcc -c lib.c -o lib

msend : mainsend.c
	gcc mainsend.c -o msend
