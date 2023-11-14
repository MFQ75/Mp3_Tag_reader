a.out : main.o mp3edit.o mp3view.o
	gcc -o a.out main.o mp3edit.o mp3view.o
main.o : main.c
	gcc -c main.c
mp3edit.o : mp3edit.c
	gcc -c mp3edit.c
mp3view.o : mp3view.c
	gcc -c mp3view.c
clean :
	rm *.out *.o
