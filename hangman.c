#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define menu_width		40
#define menu_height		12
#define span_width		39
#define span_height		24
#define human_width		17
#define human_height	14
#define game_width	 	40
#define game_height		17
#define control_width	44
#define control_height	7
#define nr_opt			3   // Numarul de optiuni al meniului


// Functie ce afiseaza meniul pe ecran
void draw_menu ( WINDOW* menu_win, char** menu, int selectie )
{
	int i, x, y; // x si y sunt coordonatele unde va fi printata fiecare optiune din meniu
	// Se bordeaza fereastra meniului
	box ( menu_win, 0, 0 );

	// Se seteaza y astef incat meniul sa fie centrat pe verticala
	y = ( menu_height - nr_opt ) / 2;
	for ( i = 0; i < nr_opt; i++ )
	{
		// Se seteaza x astfel incat meniul sa fie centrat pe orizontala
		x = ( menu_width - strlen ( menu[i] ) ) / 2;

		// Se verifica daca selectia se afla pe optiunea curenta
		if ( selectie == ( i + 1 ) )
		{
			// Optiunei curente i se pune un efect de selectie
			wattron ( menu_win, A_REVERSE );
				mvwprintw ( menu_win, y, x, "%s", menu[i] );
			wattroff ( menu_win, A_REVERSE );
		}
		else
			mvwprintw(menu_win, y, x, "%s", menu[i]);
		y++;
	}
	// Se actualizeaza fereastra meniului
	wrefresh ( menu_win );
}

// Functie ce deseneaza spanzuratoarea
void spanzuratoare ( WINDOW *span_win )
{

	wattron ( span_win, COLOR_PAIR(3) );
	//mvwaddch ( span_win, span_height - 2, 1, '/' );
	wattron ( span_win, A_REVERSE );
		wmove ( span_win, span_height - 2, 2 );
		whline ( span_win, '_', 35 );
	wattroff ( span_win, A_REVERSE );
	//mvwaddch ( span_win, span_height - 2, 37, 92 );

	wattron ( span_win, A_REVERSE );
		wmove ( span_win, span_height - 3, 3 );
		whline ( span_win, ' ',  33 );
	wattroff ( span_win, A_REVERSE );

	//mvwaddch ( span_win, span_height - 3, 2, '/' );
	wmove ( span_win, span_height - 4, 3 );
	whline ( span_win, '_', 33 );
	//mvwaddch ( span_win, span_height - 3, 36, 92 );

	wmove ( span_win, 2 , 27 );
	wvline ( span_win, '|', 19 );

	wattron ( span_win, A_REVERSE );
		wmove ( span_win, 1, 28 );
		wvline ( span_win, ' ', 20 );
	wattroff ( span_win, A_REVERSE );

	wmove ( span_win, 1 , 29 );
	wvline ( span_win, '|', 20 );

	wmove ( span_win, 0 , 12 );
	whline ( span_win, '_', 17 );

	wattron ( span_win, A_REVERSE );
		wmove ( span_win, 1 , 12 );
		whline ( span_win, ' ', 17 );
		wmove ( span_win, 1 , 14 );
		whline ( span_win, '_', 13 );
	wattroff ( span_win, A_REVERSE );

	wmove ( span_win, 1 , 11 );
	wvline ( span_win, '|', 3 );

	wattron ( span_win, A_REVERSE );
		wmove ( span_win, 1 , 12 );
		wvline ( span_win, ' ', 3 );
		mvwaddch ( span_win, 3, 12, '_' );
	wattroff ( span_win, A_REVERSE );

	mvwaddch ( span_win, 2, 13, '|' );	
	mvwaddch ( span_win, 3, 13, '|' );		
	wattroff ( span_win, COLOR_PAIR(3) );

	wrefresh ( span_win );
}

// Deseneaza corpul unui om
void draw_human ( WINDOW *human_win, int nr_greseli )
{
	wclear ( human_win );
	int i;
	for ( i = 1; i <= nr_greseli; i++ )
	{
		switch ( i )
		{
			// Prima greseala
			case 1:
				// Se deseneaza capul
				// Linia 1
				mvwaddch ( human_win, 0, 5, '.' );
				wmove ( human_win, 0 , 6 );
				whline ( human_win, '^', 5 );
				mvwaddch ( human_win, 0, 11, '.' );
				// Linia 2
				mvwaddch ( human_win, 1, 4, '/' );
				mvwaddch ( human_win, 1, 6, '0' );
				mvwaddch ( human_win, 1, 8, '.' );
				mvwaddch ( human_win, 1, 10, '0' );
				mvwaddch ( human_win, 1, 12, '\\' );
				// Linia 3
				mvwaddch ( human_win, 2, 4, '|' );
				wmove ( human_win, 2 , 7 );
				whline ( human_win, '_', 3 );
				mvwaddch ( human_win, 2, 12, '|' );
				// Linia 4
				mvwaddch ( human_win, 3, 5, '\\' );
				wmove ( human_win, 3 , 6 );
				whline ( human_win, '_', 5 );
				mvwaddch ( human_win, 3, 11, '/' );
				break;
			// A doua greseala
			case 2:
				// Se deseneaza corpul
				// Linia 1 == gatul
				mvwaddch ( human_win, 4, 7, '|' );
				mvwaddch ( human_win, 4, 9, '|' );
				// Linia 2
				mvwaddch ( human_win, 5, 5, '/' );
				mvwaddch ( human_win, 5, 11, '\\' );
				wmove ( human_win, 5 , 6 );
				whline ( human_win, '^', 5 );
				// Linia 3
				mvwaddch ( human_win, 6, 4, '/' );
				mvwaddch ( human_win, 6, 12, '\\' );
				// Restul liniilor
				wmove ( human_win, 7 , 4 );
				wvline ( human_win, '|', 3 );
				wmove ( human_win, 7 , 12 );
				wvline ( human_win, '|', 3 );
				wmove ( human_win, 9 , 5 );
				whline ( human_win, '_', 7 );
				break;
			// A treia greseala
			case 3:
				// Se deseneaza mana dreapta
				for ( int i = 5, j = 4; i >= 3 && j >= 2; i--, j-- )
					mvwaddch ( human_win, i, j, '\\' );
				for ( int i = 6, j = 3; i >= 3 && j >= 0; i--, j-- )
					mvwaddch ( human_win, i, j, '\\' );
				mvwaddch ( human_win, 2, 0, '_' );
				mvwaddch ( human_win, 2, 1, '_' );
				break;
			// A patra greseala
			case 4:
				// Se deseneaza mana stanga
				for ( int i = 5, j = 12; i >= 3 && j <= 14; i--, j++ )
					mvwaddch ( human_win, i, j, '/' );
				for ( int i = 6, j = 13; i >= 3 && j <= 16; i--, j++ )
					mvwaddch ( human_win, i, j, '/' );
				mvwaddch ( human_win, 2, 15, '_' );
				mvwaddch ( human_win, 2, 16, '_' );
				break;
			// A cincea greseala
			case 5:
				// Se deseneaza piciorul drept
				for ( int i = 10, j = 4; i <= 13 && j >= 1; i++, j-- )
				{
					mvwaddch ( human_win, i, j, '/' );
					mvwaddch ( human_win, i, j + 2, '/' );
				}
				mvwaddch ( human_win, 13, 2, '_' );
				break;
			// A sasea greseala
			case 6:
				// Se deseneaza piciorul stang
				for ( int i = 10, j = 12; i <= 13 && j <= 15; i++, j++ )
				{
					mvwaddch ( human_win, i, j, '\\' );
					mvwaddch ( human_win, i, j - 2, '\\' );
				}
				mvwaddch ( human_win, 13, 14, '_' );
				break;
		}
	}

	// Actualizarea ferestrei
	wrefresh ( human_win );
}

// Functie ce afiseaza panoul de control
void print_control ( WINDOW *control_win, long nr_exp, long nr_caractere )
{
	// Se goleste fereastra de control
	wclear ( control_win );

	// Aflarea datei si orei curente
	time_t timer;
	struct tm *timp;
	time( &timer );
	timp = localtime ( &timer );
	timp->tm_year += 1900;
	timp->tm_mon++;

	// Bordarea ferestrei de control
	box ( control_win, 0, 0 );
	// Afisarea datei
	mvwprintw ( control_win, 1, 1, "Data: %d-%d-%d", timp->tm_mday, timp->tm_mon, timp->tm_year );
	// Afisarea orei
	mvwprintw ( control_win, 2, 1, "Ora: %d:%d:%d", timp->tm_hour, timp->tm_min, timp->tm_sec );
	// Afisarea comenzilor valide
	mvwprintw ( control_win, 3, 1, "Press 'Q' to return to the menu" );
	// Afisarea numarului de expresii, precum si numarul de caractere pe care acestea le contin
	mvwprintw ( control_win, 5, 1, "%ld expresii, ce contin %ld caractere", nr_exp, nr_caractere );
	// Actualizarea ferestrei
	wrefresh ( control_win );
}

// Crearea cuvantului ascuns
char* cuvant_ascuns ( char* exp )
{
	// Declararea variabilelor
	char *cuv_ascuns, *token, *aux;
	int n = -1, i, j, dim = game_width - 2, flc_d = 50, flc_n = 0;
	// Crearea unui sir de caractere ce va contine prima si ultima litera fiecarui cuvant
	char* flc = ( char* ) malloc ( flc_d * sizeof ( char ) );
	
	// Crearea unei copii a expresiei
	aux = strdup ( exp );
	
	// Alocare de memorie pentru variabila in care voi crea cuvantul ascuns
	cuv_ascuns = ( char* ) malloc ( ( strlen ( exp ) + 1 ) * sizeof ( char ) );
	// Initializarea cuvantului ascuns cu NULL
	cuv_ascuns[0] = '\0';
	// Extragerea primului cuvant din expresie
	token = strtok ( exp, " " );
	// Cat timp exista cuvinte in expresie
	while ( token != NULL )
	{
		// Daca cuvantul ascuns depaseste dimensiunea ferestrei se adauga newline
		if (  strlen ( cuv_ascuns ) + strlen ( token ) + 1  >= dim )
		{
			dim = dim + ( game_width - 2 );
			strcat ( cuv_ascuns, "\n \0");
			n += 2;
		}
		// Se verifica cate caractere contine cuvantul curent
		switch ( strlen ( token ) )
		{
			case 1: // Un singur caracter, se adauga '_'
				strcat ( cuv_ascuns, "_ ");
				n += 2;
				break;
			case 2: // Doua caractere, se adauga prima litera si '_'
				if ( flc_n >= flc_d )
				{
					flc_d += 50;
					flc = ( char* ) realloc ( flc, flc_d * sizeof ( char ) );
				}
				flc[ flc_n ] = token[0];
				flc_n++;
				cuv_ascuns[ n + 1 ] = token[0];
				cuv_ascuns[ n + 2 ] = '_';
				cuv_ascuns[ n + 3 ] = ' ';
				cuv_ascuns[ n + 4 ] = '\0';
				n += 3;
				break;
			// Cuvantul contine mai mult de 2 caractere, se adauga prima si ultima litera
			// Intre prima si ultima litera se adauga '_'
			default:
				if ( flc_n >= flc_d )
				{
					flc_d += 50;
					flc = ( char* ) realloc ( flc, flc_d * sizeof ( char ) );
				} 
				flc[ flc_n ] = token[0];
				flc[ flc_n + 1 ] = token[ strlen ( token ) - 1 ];
				flc_n += 2;
				cuv_ascuns[ n + 1 ] = token[0];
				for ( i = 2; i <= strlen ( token ); i++ )
					cuv_ascuns[ n + i ] = '_';
				n += strlen ( token );
				cuv_ascuns[n] = token [ strlen ( token ) - 1 ];
				cuv_ascuns[ n + 1 ] = ' ';
				n++;
				cuv_ascuns[ n + 1 ] = '\0';
				break;
		}
		// Se extrage urmatorul cuvant din expresie
		token = strtok ( NULL, " " );
	}

	flc[ flc_n ] = '\0';

	// Se verifica daca prima si ultima litera a fiecarui cuvant 
	// se mai gasesc si in alte locuri ale expresiei
	// Daca se mai gasesc se adauga si acolo
	int k;
	for ( i = 0; i < flc_n; i++ )
	{
		k = 0;
		for ( j = 0; j < strlen( cuv_ascuns) - k; j++ )
		{
			if ( cuv_ascuns[ j + k ] == '\n' )
				k += 2;
			if ( aux[j] == flc[i] )
				cuv_ascuns[ j + k ] = flc[i];
		}
	}

	// Eliberarea memoriei
	free ( aux );
	free ( flc );

	// Functia returneaza cuvantul ascuns generat
	return cuv_ascuns;
}

// Afisarea ferestrei de joc
int print_game ( WINDOW *game_win, char* cuv_ascuns, char* expresie, char c )
{
	int i, corect = 0, j = 0;
	// Se verifica daca caracterul 'c' se gaseste in expresie
	// Daca se gaseste se adauga la cuvantul ascuns
	for ( i = 0; i < strlen ( expresie); i++ )
	{
		if ( cuv_ascuns[i + j] == '\n' )
			j += 2;
		if ( expresie[i] == c )
		{
			corect = 1;
			cuv_ascuns[ i + j ] = c;
		}
	}
	// Afisarea cuvantului ascuns
	mvwprintw ( game_win, 1, 5, "Ghiceste un caracter");
	mvwprintw ( game_win, 3, 1, "%s", cuv_ascuns );
	// Actualizarea ferestrei
	wrefresh ( game_win );
	// Returneaza 1 daca caracterul s-a gasit in expresie si 0 in caz contrar
	return corect;
}

// Functie ce afiseaza mesajul "GAME OVER"
void game_over ( WINDOW* game_win, char* cuvant, char* cuv_ascuns )
{
	wclear ( game_win );
	int x = 3, y = 0, i, a = -1, b = 0, t = -2;

	for ( i = 0; i < strlen ( cuvant ); i++ )
	{
		if ( cuv_ascuns[i + t] == '\n' || b % 39 == 0 ) 
		{
			a++;
			b = 0;
			t += 2;
		}
		if ( strchr ( cuv_ascuns, cuvant[i]) )
			mvwaddch ( game_win, a, b, cuvant[i] );
		else
		{
			wattron ( game_win, COLOR_PAIR(1) );
				mvwaddch ( game_win, a, b, cuvant[i] );
			wattroff ( game_win, COLOR_PAIR(1) );
		}
		b++;
	}

	// Colorarea mesajului cu rosu
	wattron ( game_win, COLOR_PAIR(1) );

		mvwprintw ( game_win, x    , y, " {}{}{}}     {}{}    {}      {} {}{}{}{}");
		mvwprintw ( game_win, x + 1, y, "{}          {}  {}   {}}}  {{{} {}" );
		mvwprintw ( game_win, x + 2, y, "{}  {}{}}  {}{}{}{}  {} {}{} {} {}{}{}" );
		mvwprintw ( game_win, x + 3, y, "{}     {} {}      {} {}  {}  {} {}" );
		mvwprintw ( game_win, x + 4, y, " {}{}{}{} {}      {} {}      {} {}{}{}{}" );
		x++;
		y += 2;
		mvwprintw ( game_win, x + 5, y, "  {}{}   {}    {} {}{}{}{}  {}{}{}" );
		mvwprintw ( game_win, x + 6, y, " {}  {}  {}    {} {}        {}   {}" );
		mvwprintw ( game_win, x + 7, y, "{}    {}  {}  {}  {}{}{}    {}{}{}" );
		mvwprintw ( game_win, x + 8, y, " {}  {}    {}{}   {}        {}   {}" );
		mvwprintw ( game_win, x + 9, y, "  {}{}      {}    {}{}{}{}  {}    {}" );

		mvwprintw ( game_win, x + 11, y, "Press 'N' to start a New Game" );
		mvwprintw ( game_win, x + 12, y, "Press 'Q' to go back to the menu" );

	wattroff ( game_win, COLOR_PAIR(1) );

	wrefresh ( game_win );
}

// Functie ce afiseaza mesajul "YOU WIN"
void you_won ( WINDOW* game_win, char* cuvant )
{
	wclear ( game_win );
	int x = 2, y = 6;

	mvwprintw ( game_win, 0, 0, "%s", cuvant );

	// Colorarea mesajului cu verde
	wattron ( game_win, COLOR_PAIR(2) );

		mvwprintw ( game_win, x    ,  y, "{}    {}   {}{}    {}    {}" );
		mvwprintw ( game_win, x + 1,  y, " {}  {}   {}  {}   {}    {}" );
		mvwprintw ( game_win, x + 2,  y, "  {}{}   {}    {}  {}    {}" );
		mvwprintw ( game_win, x + 3,  y, "   {}     {}  {}   {}    {}" );
		mvwprintw ( game_win, x + 4,  y, "   {}      {}{}    {}{}{}{}" );

		y -= 3;
		mvwprintw ( game_win, x + 6,  y, "{}           {}  {}{}   {}      {}" );
		mvwprintw ( game_win, x + 7,  y, "{}    {}     {} {}  {}  {}}}    {}" );
		mvwprintw ( game_win, x + 8,  y, " {}  {}{}   {} {}    {} {}  {}  {}" );
		mvwprintw ( game_win, x + 9,  y, "  {}{}   {}{}   {}  {}  {}    {{{}" );
		mvwprintw ( game_win, x + 10, y, "   {}     {}     {}{}   {}      {}" );

		mvwprintw ( game_win, x + 12, y, "Press 'N' to start a New Game" );
		mvwprintw ( game_win, x + 13, y, "Press 'Q' to go back to the menu" );

	wattroff ( game_win, COLOR_PAIR(2) );

	wrefresh ( game_win );
}

// Sterge primul caracter dintr-un sir
void delete ( char* p )
{
	char* aux;
	aux = strdup ( p + 1 );
	strcpy ( p, aux );
	free ( aux );
}

int main ( int argc, char** argv )
{
	// Se verifica daca s-au transmis parametri programului
	if ( argc == 1 )
	{
		printf("[Eroare]: Nu s-au dat argumente de comanda.\n");
		return 1;
	}
	int i, dimensiune = 10;
	// n va retine nr tuturor expresiilor
	// "nr_caractere" va retine numarul de caractere al tuturor expresiilor
	long n = 0, nr_caractere = 0;
	// Declararea si alocarea de memorie unui vector de pointeri 
	// in care voi retine toate liniile din fisiere
	char** cuvinte = ( char** ) malloc ( dimensiune * sizeof ( char * ) );

	// Voi citi fiecare linie din fisier in aceasta variabila
	char expresie[ 201 ];

	// Parcurgerea fiecarui argument ( fisier )
	for ( i = 1; i < argc; i++ )
	{
		// Se deschide fisierul in vederea citirii
		FILE* pFile;
		pFile = fopen(argv[i] , "r");

		// Daca fisierul nu a putut fi deschis se afiseaza un mesaj de eroare
		// si programul iese cu valoarea 1
		if ( pFile == NULL )
		{
			printf("[Eroare]: Fisierul %s nu poate fi deschis\n", argv[i] );
			return 1;
		}

		// Citirea elementelor din fisier
		while ( fgets ( expresie, 200, pFile ) )
		{
			int j = 0, sw = 0;
			// Daca exista spatii la inceputul expresiei, le elimin pe toate
			while ( expresie[0] == ' ' )
				delete ( expresie );
			// Se elimina toate caracterele neprintabile
			// iar in final vor ramane doar caractere printabile in expresie
			while ( j < strlen ( expresie ) )
			{
				// Verific daca caracterul curent este printabil
				if ( isprint ( expresie[j] ) )
				{
					sw = 1;
					// Verific daca este litera
					if ( isalpha ( expresie[j] ) )
					{
						// Transform litera in litera mica
						expresie[j] = tolower ( expresie [j] );
						j++;
					}
					else
						// Daca in expresie exista mai multe spatii unul dupa altul, pastrez doar unul
						if ( expresie[ j - 1 ] == ' ' && expresie[j] == ' ' && j != 0 ) 
							delete ( expresie + j );
						else
							j++;
				}
				else
					// Daca nu este caracter printabil il elimin
					delete ( expresie + j );
			}
			// Daca expresia contine caractere printabile, se memoreaza
			if ( sw )
			{
				// Daca nu exista suficienta memorie, se aloca mai mai multa
				if ( n >= dimensiune )
				{
					dimensiune = dimensiune * 2;
					cuvinte = ( char** ) realloc ( cuvinte, dimensiune * sizeof ( char* ) );
				}
				cuvinte[n] = strdup ( expresie );
				nr_caractere = nr_caractere + strlen ( expresie );
				n++;
			}		
		}
		// Se inchide fisierul
		fclose ( pFile );
	}

	char *cuvant, *cuv_ascuns;
	int nr_linii, nr_coloane, selectie = 1, option = 0, nr_greseli = 0;
	int c;

	// Se memoreaza toate optiunile meniului
	char* menu[]={
				"New Game",
				"Resume Game",
				"Quit",
				 };

	// Se initializeaza ecranul 
	WINDOW *window = initscr();
	
	// Aflarea numarului maxim de linii si de coloane
	getmaxyx ( window, nr_linii, nr_coloane );

	// Se pot folosi culori
	start_color ();
	init_pair ( 1, COLOR_RED, COLOR_BLACK );
	init_pair ( 2, COLOR_GREEN, COLOR_BLACK );
	init_color(COLOR_YELLOW, 1000, 400, 0);
	init_pair ( 3, COLOR_YELLOW, COLOR_BLACK );

	// Crearea ecranului pentru meniu
	int begin_x, begin_y;
	begin_x = ( nr_coloane - menu_width ) / 2;
	begin_y = ( nr_linii - menu_height ) / 2;
	WINDOW *menu_win = newwin ( menu_height, menu_width, begin_y, begin_x );
	keypad( menu_win, TRUE );

	// Crearea ecranului pentru spanzuratoare
	begin_x = ( nr_coloane - span_width + 1 );
	begin_y = 0;
	WINDOW *span_win = newwin ( span_height, span_width, begin_y, begin_x );

	// Crearea ecranului pentru om
	begin_x = ( nr_coloane - span_width + 5 );
	begin_y = 4;
	WINDOW *human_win = newwin ( human_height, human_width, begin_y, begin_x );

	// Crearea ecranului pentru joc
	begin_x = 0;
	begin_y = 7;
	WINDOW *game_win = newwin ( game_height, game_width, begin_y, begin_x );

	// Crearea ecranului pentru panoul de control
	begin_x = 0;
	begin_y = 0;
	WINDOW *control_win = newwin ( control_height, control_width, begin_y, begin_x );

	// Se șterge ecranul
	clear();
	// Se inhibă afișarea caracterelor introduse de la tastatură
	noecho();
	// Caracterele introduse sunt citite imediat - fără 'buffering'
	cbreak();

	// Se ascunde cursorul	
	curs_set(0);

	// Se afiseaza un mesaj cu instructiunile de navigare in meniu
	char instructiuni[] = "Use arrow keys to go up and down, Press ENTER to select an option";
	mvprintw ( 3, ( nr_coloane - strlen ( instructiuni ) ) / 2, "%s", instructiuni );

	// Se actualizeaza fereastra
	refresh ();

	// Se afiseaza meniul
	draw_menu ( menu_win, menu, selectie );

	int  exit = 0, exit2 = 0, resume = 0, d = 50, eliberez = 0;
	// Toate caracterele introduse vor fi memorate in aceste variabile
	char* caractere_corecte = ( char* ) malloc ( d * sizeof ( char ) );
	char* caractere_gresite = ( char* ) malloc ( 10 * sizeof ( char ) );
	int sfarsit = 0;

	int t = 0;	// Dimensiunea sirului caractere_corecte
	int g = 0;	// Dimensiunea sirului caractere_gresite

	// Daca exista un "savefile" se vor citi toate datele de acolo
	// facandu-se posibila reluarea ultimului joc deschis, chiar daca
	// jocul a fost inchis si deschis iar
	FILE* save_file;
	save_file = fopen ( "save.txt", "r" );
	if ( save_file != NULL )
	{
		fscanf ( save_file, "%d\n", &resume );
		if ( resume )
		{
			fgets ( expresie, 200, save_file );
			expresie[ strlen ( expresie ) - 1 ] = '\0';
			cuvant = strdup ( expresie );

			fgets ( expresie, 200, save_file );
			expresie[ strlen ( expresie ) - 1 ] = '\0';
			cuv_ascuns = strdup ( expresie );

			fgets ( caractere_corecte, 100, save_file );
			caractere_corecte[ strlen ( caractere_corecte ) - 1 ] = '\0';

			fgets ( caractere_gresite, 100, save_file );
			caractere_gresite[ strlen ( caractere_gresite ) - 1 ] = '\0';

			fscanf ( save_file, "%d\n%d\n%d\n", &t, &g, &nr_greseli );
		}
		fclose ( save_file );
	}

	// Se ramane in while pana la selectarea optiunei "Quit"
	while ( !exit )
	{	
		// Se selecteaza optiunea in functie de tasta apasata
		c = wgetch ( menu_win );
		switch ( c )
		{	case KEY_UP: // Parcurgerea meniului in sus
				if(selectie == 1)
					selectie = nr_opt ;
				else
					selectie--;
				break;
			case KEY_DOWN:  // Parcurgerea meniului in jos
				if(selectie == nr_opt )
					selectie = 1;
				else 
					selectie++;
				break;
			case 10:	// 10 = codul ASCII al caracterului new line
						// Se selecteaza optiunea curenta
				if ( selectie == 2 && resume == 0 )
					break;
				option = selectie;
				break;
		}
		// Se actualizeaza meniul
		draw_menu ( menu_win, menu, selectie );

		// Daca a fost selectata o optiune, se verifica care
		while ( option )
		{
			switch ( option )
			{
				case 1:		// New Game

					// Golirea intregului ecran
					clear ();
					refresh ();

			  		sfarsit = 0;
					// Daca se incepe un joc nou cel putin a doua oara
					// se elibereaza memoria folosita de cuvantul ascuns si de expresia anterioara
					if ( eliberez )
					{
						free ( cuvant );
						free ( cuv_ascuns );
					}

					// Alegerea random a unei expresii
					time_t seed;	// Aflarea orei curente
					time ( &seed );	// in secunde
					// Fixarea valorii utilizate in generarea numarului
					srand ( seed );
					// Generarea numarului ca modulo n, unde n este numarul de expresii
					int random = rand () % n;
					// Copierea expresiei generate
					cuvant = strdup ( cuvinte[ random ] );

					eliberez = 1;
					// Asigurarea posibilitatii accesarii optiunii Resume Game
					resume = 1;

					//Crearea cuvantului ascuns
					char* copie = strdup ( cuvant );
					cuv_ascuns = cuvant_ascuns ( copie );
					free ( copie );

					strcpy ( caractere_corecte, "\0" );
					strcpy ( caractere_gresite, "\0" );

					t = 0;	// Dimensiunea sirului caractere_corecte
					g = 0;	// Dimensiunea sirului caractere_gresite

					// Initializarea numarului de greseli cu 0
					nr_greseli = 0;
					break;

				case 2:		// Resume Game

					// Golirea intregului ecran
					clear ();
					refresh ();

					// Se reface desenul cum era inainte
					spanzuratoare ( span_win );
					draw_human ( human_win, nr_greseli );
					break;
				case 3:		// Quit
					option = 0;
					exit = 1;
					FILE* save;
					save = fopen ( "save.txt", "w");
					fprintf ( save, "%d\n", resume );
					if ( resume )
					{
						fprintf ( save, "%s\n%s\n%s\n%s\n", cuvant, cuv_ascuns, caractere_corecte, caractere_gresite );
						fprintf ( save, "%d\n%d\n%d", t, g, nr_greseli );
					}
					fclose ( save );
					break;
			}
			if ( option == 1 || option == 2 )
			{
					// Printarea spanzuratorii
					spanzuratoare ( span_win );
					draw_human ( human_win, nr_greseli );

					// Afisarea ferestrei de joc
					mvwprintw ( game_win, 9, 11, "CARACTERE INTRODUSE" );
					print_game ( game_win, cuv_ascuns, "\0", '\0' );
					
					exit2 = 0;
					
					int counter = 0;
					// Se iese din bucla cand este apasata tasta 'Q'
					while ( !exit2 )
					{
						// Se afiseaza panoul de control
						print_control ( control_win, n, nr_caractere );
						// Se afiseaza toate caracterele folosite
						// Se coloreaza scrisul
						wattron ( game_win, COLOR_PAIR(1) );
							mvwprintw ( game_win, 11, 1, "GRESITE: %s", caractere_gresite );
						wattroff ( game_win, COLOR_PAIR(1) );

						wattron ( game_win, COLOR_PAIR(2) );
							mvwprintw ( game_win, 13, 1, "CORECTE: %s", caractere_corecte );
						wattroff ( game_win, COLOR_PAIR(2) );

						// se asteapta introducerea unui caracter timp de 7 secunde
						// daca nu a fost introdus niciun caracter, functia wgetch va returna "ERR" 
						halfdelay ( 10 );
						c = wgetch ( game_win );
						// Daca nu s-a introdus un caracter timp de 7 secunde se alege un caracter random
						// Se foloseste o structura repetitiva deoarece, este posibil sa se genereze un caracter
						// care se afla deja in sir sau care sa fie o majuscula, in acest caz se genereaza 
						// un nou caracter pana cand se obtine un caracter care nu se afla in sir sau care nu
						// este majuscula
						if ( c == ERR && counter != 7 )
						{
							counter++;
							continue;
						}
						while ( c == ERR && counter == 7 )
						{
							time_t seed;
							// Generez un caracter aleator cu codul ASCII cuprins intre 32 si 126
							time ( &seed );
							srand ( seed );
							c = rand () % 94 + 33;
							if ( strchr  ( cuv_ascuns, c ) || strchr ( caractere_gresite, c ) || strchr ( caractere_corecte, c) )
								c = ERR;
							if ( c >= 65 && c <= 90 )
								c = ERR;
						} 
						if ( counter == 7 )
							counter = 0;
						switch ( c )
						{
							case 'Q':  // Se iese din bucla
								clear ();
								mvprintw ( 3, ( nr_coloane - strlen ( instructiuni ) ) / 2, "%s", instructiuni );
								refresh ();
								draw_menu ( menu_win, menu, selectie );
								option = 0;
								exit2 = 1;
								break;
							default:
								// Daca nu mai exista suficienta memorie pentru memorarea caracterolor
								// folosite, se aloca mai multa memorie
								if ( t >= d )
								{
									d += 50;
									caractere_corecte = ( char* ) realloc ( caractere_corecte, d * sizeof ( char ) );
								}
								// Daca caracterul introdus nu a mai fost folosit pana acum
								if ( !strchr ( caractere_corecte, c ) && !strchr ( caractere_gresite, c ) )
								{
									// Daca nu se gaseste in expresie se deseneaza urmatoarea parte a corpului
									if ( !print_game ( game_win, cuv_ascuns, cuvant, c ) )
									{
										caractere_gresite[g] = c;
										caractere_gresite[ g + 1 ] = ' ';
										caractere_gresite[ g + 2 ] = '\0';
										g += 2;
										nr_greseli++;
										draw_human ( human_win, nr_greseli );
									}
									else
									{
										// Se adauga la lista caracterelor corecte
										caractere_corecte[t] = c;
										caractere_corecte[ t + 1 ] = ' ';
										caractere_corecte[ t + 2 ] = '\0';
										t += 2;
									}
								}
								break;
						}
						if ( nr_greseli == 6 || !strchr ( cuv_ascuns, '_' ) )
						{
							resume = 0;
							sfarsit = 1;
							break;
						}
					}
					if ( nr_greseli == 6 )
						game_over ( game_win, cuvant, cuv_ascuns );
					else
						if ( !strchr ( cuv_ascuns, '_' ) )
							you_won ( game_win, cuvant );
					while ( sfarsit )
					{	
						print_control ( control_win, n, nr_caractere );
						halfdelay ( 10 );
						c = wgetch ( game_win );
						switch ( c )
						{
							case 'Q':  // Se iese din bucla
								clear ();
								mvprintw ( 3, ( nr_coloane - strlen ( instructiuni ) ) / 2, "%s", instructiuni );
								refresh ();
								draw_menu ( menu_win, menu, selectie );
								option = 0;
								exit2 = 1;
								sfarsit = 0;
								break;
							case 'N': //New Game
								option = 1;
								sfarsit = 0;
								break;
						}
					}
			}
		}
	}	

	// Se inchide fereastra
	endwin ();

	// Eliberarea memoriei
	for ( i = 0; i < n; i++ )
		free ( cuvinte[i] );
	free ( cuvinte );
	free ( caractere_corecte );
	free ( caractere_gresite );
	if ( eliberez )
	{
		free ( cuvant );
		free ( cuv_ascuns );
	}

	return 0;
}