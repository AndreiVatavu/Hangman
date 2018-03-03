build: hangman

hangman: hangman.o
	gcc -Wall hangman.o -o hangman -lncurses

hangman.o: hangman.c
	gcc -Wall -c hangman.c -o hangman.o -lncurses

run: hangman
	./hangman

clean:
	rm -fr hangman hangman.o
