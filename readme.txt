
								  HANGMAN
								 ---------

Timp alocat rezolvarii: 25 de ore

Citirea tuturor expresiilor din fisiere
---------------------------------------
	
	Programul trebuie sa primeasca ca argumente cel putin un fisier, in caz
contrar acesta va afisa un mesaj de eroare si va iesi cu valoarea 1. Se va lua
fiecare fisier primit ca argument si se va deschide in vederea citirii. Daca un
fisier nu a putut fi deschis, se va afisa un mesaj de eroare, iar programul va
iesi cu valoarea 0. Pentru fiecare fisier deschis se va citi fiecare linie
(o linie reprezentand o expresie), toate literele mici se vor transforma in 
majuscule si se vor elimina din aceasta linie fiecare caracter neprintabil (se 
verifica cu functia "isprint", toate spatiile de la inceputul liniei (daca 
exista), iar daca in interiorul expresiei citite exista doua sau mai multe 
spatii se va pastra doar unul singur. Dupa ce au fost facute toate aceste
modificari expresia optinuta (daca este diferita de NULL) se memoreaza intr-un 
vector de pointeri declarat la inceputul programului, iar daca vectorul nu are
suficienta memorie pentru a mai retine inca o expresie, i se va aloca o memorie
dubla fata de cea anterioara. La final toate expresiile vor fi memorate in acest
vector. De asemenea in timp ce memorez toate expresiile retin intr-o variabila
numarul total de caractere pe care le contin toate expresiile la un loc, precum
si numarul de expresii memorate.


Crearea meniului de joc
-----------------------

	Pentru crearea meniului am creat o noua fereastra numita "menu_win" si un
vector de pointer in care am memorat toate optiunile meniului. 
	Functia "draw_menu" primeste ca argumente fereastra meniului, vectorul de 
poineri in care am memorat optiunile meniului si o variabila de tip intreg ce 
reprezinta pozitia pe care se afla cursorul in meniu. Aceasta functie bordeaza 
fereastra meniului, o pozitioneaza in centrul ecranului principal, afiseaza 
fiecare optiune a meniului in centrul ferestrei si pune un efect de highlight
pe optiunea curenta data de variabila de tip intreg primita ca argument.
	Se asteapta apasarea unei taste (sageata sus, sageata jos sau enter). Daca
a fost apasata tasta "sageata sus" se parcurge meniul in sus, iar daca a fost
apasata tasta "sageata jos" se parcurge meniul in jos. Parcurgerea meniului
se realizeaza in felul urmator: in functie de tasta apasata (sageata sus sau
sageata jos) se apeleaza functia "draw_menu" cu ultimul argument mai mic sau
mai mare cu 1 fata de valoarea pe care a avut-o ultima data cand a fost apelata
functia.

Inceperea unui nou joc
----------------------

	Daca a fost selectata optiunea "New Game" se va incepea un nou joc.
	Prima data se va goli intregul ecran (apelandu-se functia "clear" urmata de
functia "refresh"). Apoi se va genera o expresie aleatoare din cele memorate.
Acest lucru il realizez prin generarea unui numar aleator intre 0 si numarul de
expresii, iar expresia ce va trebui ghicita va fi aceea de pe pozitia care a
fost generata radom. Pentru generarea numarului am folosit functia "rand()" si
functia "srand" din biblioteca "stdlib.h". Functiei "srand" i-am dat ca
argument ora curenta in secunde pentru a ma asigura ca se va genera mereu un 
numar aleator, fara a se repeta.
	Dupa generarea expresiei se creeaza cuvantul ascuns. Pentru generarea
cuvantului ascuns am creat o functie numita "cuvant_ascuns" care primeste ca
argument o expresie si o transforma in cuvantul ascuns dorit. Dupa ce s-a creat
cuvantul ascuns se initializeaza cu "NULL" doua siruri de caractere in care voi
memora caracterele introdu-se corect si caracterele introdu-se gresit.

	Explicarea functiei "cuvant_ascuns"
	-----------------------------------
		Expresia primita ca argument se imparte in cuvinte cu ajutorul functiei
	"strtok". Pentru fiecare cuvant se verifica numarul de caractere, daca
	contine un singur caracter, in locul acestui caracter se pune "_", daca
	are 2 caractere, se va pastra prima litera iar daca contine 3 caractere
	se vor pastra primul si ultimul caracter, in locul celorlalte se va pune
	"_". Dupa ce a fost modificat fiecare cuvant se adauga la sirul in care
	memorez cuvantul ascuns. Deoarece afisarea acestui cuvant o voi face in
	fereastra "game_win" inainte de a adauga un nou cuvant la sir verific
	daca noul sir se va incadra in fereastra, daca nu se incadreaza adaug in
	sir newline urmat de un spatiu (pentru o incadrare mai buna in fereastra).
	Apoi verific daca literele pe care nu le-am ascuns se mai afla si in alte
	locuri ale expresiei, iar daca se afla le voi afisa si acolo.
		Functia va returna cuvantul ascuns creat.

Reluarea unui joc
-----------------
	
	Aceasta optiune poate fi accesata doar daca exista un joc neterminat, de
asemenea aceasta optiune poate fi accesata chiar daca jocul a fost inchis si
a ramas o sesiune de joc neterminata, acest lucru este posibil deoarece toate
datele de care este nevoie se salveaza intr-un fisier care va fi citit la
inceputul programului.
	In cazul in care a fost selectata aceasta optiune se goleste ecranul si se
deseneaza spanzuratoare si omul in stadiul in care se aflau (voi detalia felul
in care aceste elemente vor fi desenate cand voi explica logica jocului).


Logica jocului
--------------
	
	Am creat doua ferestre: una pentru un panou de control (control_win) si una
in care afisez cuvantul ascuns (desfasurarea jocului) (game_win).
	Functia "print_game" primestte ca ultim argument un caracter si verifica
daca acest caracter se afla in expresia ce trebuie ghicita, daca se afla 
se adauga acest caracter la cuvantul ascuns si afiseaza in fereastra "game_win" 
cuvantul ascuns si returneaza 1 daca caracterul se gaseste in expresie sau 0 in
caz contrar.
	Functia "print_control" afiseaza in fereastra "control_win" data si ora
curenta, instructiuni de folosire a aplicatiei si numarul de expresii memorate
precum si numarul de caractere pe care aceste expresii le contin.
	Daca a fost selectata optiunea "New Game" sau "Resume Game" se incepe
constructia jocului. Se afiseaza pe ecran spanzuratoarea si omul (omul se 
afiseaza doar daca au fost facute greseli). Spanzuratoarea se afiseaza intr-o
noua fereastra numita "span_win" cu ajutorul functiei "spanzuratoare". Aceasta
functie deseneaza o spanzuratoare din caractere cu ajutorul functiilor de
desenare puse la dispozitie de biblioteca ncurses. Omul se deseneaza in
fereastra "human_win" cu ajutorul functiei "draw_human", functie ce primeste
ca argumente fereastra in care se deseneaza omul si un numar intreg care
reprezinta numarul de greseli facute pana in acel moment, iar in functie de
acest numar se vor afisa partile corpului.
	Se afiseaza cuvantul ascuns cu ajutorul functiei "print_game".
	Se afiseaza panoul de control cu ajutorul functiei "print_control".
	Se asteapta introducerea unui caracter de la tastatura timp de 7 secunde.
Daca in 7 secunde nu a fost introdus niciun caracter se genereaza aleator un
caracter si se introduce. Daca caracterul introdus este corect se actualizeaza
cuvantul ascuns si sirul in care retin caracterele introduse corect, in caz
contrar se actualizeaza sirul in care retin caracterele gresite, se mareste
numarul de greseli cu 1 si se mai deseneaza inca o parte a omului.
	Daca s-a ghicit cuvantul cu ajutorul functiei "you_won" se afiseaza
mesajul "YOU WON", iar daca s-au facut 6 greseli se afiseaza mesajul "GAME
OVER". In ambele cazuri utilizatorul are posibilitatea sa inceapa o noua
sesiune de joc apasand tasta "N" sau sa se intoarca la meniu apasand tasta "Q".
