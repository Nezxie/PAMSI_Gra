

#include "pch.h"
#include<algorithm> 
#include <iostream>
#include <math.h>

using namespace std;
#define PC 1 //stale przypisujace numery graczom
#define GRACZ 2
#define BOK 4 //dlugosc boku planszy

#define PC_RUCH 'O' //komputer stawia kolka
#define GRACZ_RUCH 'X' //gracz krzyzyki

//*********tu jest minimax*********
struct RuchPC
{
	int rzad, kolumna;
};

bool CzyPozostalyRuchy(char plansza[][BOK])
{
	for (int i = 0; i < BOK; i++)
		for (int j = 0; j < BOK; j++)
			if (plansza[i][j] == ' ')
				return(true);
	return(false);
}

int Mysl(char plansza[][BOK]) //funkcja rozdaje punkty
{
	//sprawdzamy rzedy
	int c = 0; //licznik ile w rzedzie jest takich samych znakow
	for (int i = 0; i < BOK; i++)
	{

		for (int j = 1; j < BOK; j++)
		{
			if (plansza[i][0] == plansza[i][j] && plansza[i][0] != ' ') c++; //zabezpieczamy przed wykryciem wyhranej gdy caly rzad pusty

		}
		if (c == BOK - 1)
		{
			if (plansza[i][0] == 'X')
				return(-10);
			else if
				(plansza[i][0] == 'O')
				return(10);
		}
		c = 0;
	}
	//sprawdzamy kolumny
	c = 0; //licznik ile w rzedzie jest takich samych znakow
	for (int i = 0; i < BOK; i++)
	{

		for (int j = 1; j < BOK; j++)
		{
			if (plansza[0][i] == plansza[j][i] && plansza[0][i] != ' ') c++; //zabezpieczamy przed wykryciem wyhranej gdy caly rzad pusty

		}
		if (c == BOK - 1)
		{
			if (plansza[0][i] == 'X')
				return(-10);
			else if
				(plansza[0][i] == 'O')
				return(10);
		}
		c = 0;
	}
//diagonale
c = 0; //licznik ile w przekatnej jest takich samych znakow
	int i = 0;
	int j;
	for (j = BOK - 1; j > 0; j--)
	{
		if (plansza[j][i] == plansza[j - 1][i + 1] && plansza[j][i] != ' ') c++; //lewa-dolna przekatna
		i++;
	
	}
	if (c == BOK - 1)
	{
		if (plansza[j][i] == 'X')
			return(-10);
		else if
			(plansza[j][i] == 'O')
			return(10);
	}
	c = 0;



	i = 0;
	j = 0;
	for (int j = 1; j < BOK; j++)
	{
		if (plansza[i][i] == plansza[j][j] && plansza[j][j] != ' ') c++; //lewa-gorna przekatna
		i++;
	}
	if (c == BOK - 1)
	{
		if (plansza[i][i] == GRACZ_RUCH)
			return(-10);
		else if
			(plansza[i][i] == PC_RUCH)
			return(10);
	}
	c = 0;
	return 0;
}

//minimax

int MiniMax(char plansza[][BOK], int glebokosc, bool CzyMax)
{
	int Wynik = Mysl(plansza);
	//jesli wygral pc
	if (Wynik == 10)
		return Wynik;
	//jesli wygral gracz
	if (Wynik == -10)
		return Wynik;
	//jesli remis
	if (CzyPozostalyRuchy(plansza) == false)
		return 0;

	//jesli szukamy max 
	if (CzyMax)
	{
		int best = -100;
		//dla kazdego pola ktore bedzie dostepne symulujemy ruch
		for (int i = 0; i < BOK; i++)
		{
			for (int j = 0; j < BOK; j++)
			{
				if (plansza[i][j] == ' ')
				{
					plansza[i][j] = PC_RUCH; //symuluje ruch PC
					best = max(best, MiniMax(plansza, glebokosc + 1, !CzyMax)); //szukamy max wartosci dla zasymulowanego ruchu
					//cofamy ten ruch co wykonalismy
					plansza[i][j] = ' ';
				}
			}
		}
		return best;
	}
	else
	{
		//jesli szukamy min
		int best = 100;
		for (int i = 0; i < BOK; i++)
		{
			for (int j = 0; j < BOK; j++)
			{
				if (plansza[i][j] == ' ')
				{
					plansza[i][j] = GRACZ_RUCH; //symuluje ruch gracza
					best = min(best, MiniMax(plansza, glebokosc + 1, !CzyMax)); //szukamy max wartosci dla zasymulowanego ruchu
					//cofamy ten ruch co wykonalismy
					plansza[i][j] = ' ';
				}
			}
		}
		return best;
	}
}

//szukamy najlepszego ruchu PC
RuchPC NajlepszyRuch(char plansza[][BOK])
{
	int best = -100;
	RuchPC Ruch;
	Ruch.rzad = -1; //czyszczenie
	Ruch.kolumna = -1;

	for (int i = 0; i < BOK; i++)
	{
		for (int j = 0; j < BOK; j++)
		{
			if (plansza[i][j] == ' ')
			{
				plansza[i][j] = PC_RUCH; //symuluje ruch PC
				int Wartoscruchu = MiniMax(plansza, 0, false); //uruchamia sprawdzanie najlepszego ruchu
				plansza[i][j] = ' '; //czyscimy
				if (Wartoscruchu > best)
				{
					Ruch.rzad = i; //ustalamy wspolrzedne ruchu  najlepsszego
					Ruch.kolumna = j;
					best = Wartoscruchu;
				}
			}
		}
	}
	return Ruch;
}


//************tu jest kolko i krzyzyk***********

//Instrukcja
void Instrukcja()
{
	if (BOK == 3) {
		printf("\t\t\t Kolko i krzyzyk\n\n"); //\t to akapit \n nowa linia
		printf("Aby wstawic symbol w dana komorke wpisz x i y\n\n");
		printf("\t\t\t  (0,0) | (0,1)  | (0,2)  \n");
		printf("\t\t\t--------------------------\n");
		printf("\t\t\t  (1,0) | (1,1)  | (1,2)  \n");
		printf("\t\t\t--------------------------\n");
		printf("\t\t\t  (2,0) | (2,1)  | (2,2)  \n\n");
	}
	if (BOK == 4) {
		printf("\t\t\t Kolko i krzyzyk\n\n"); //\t to akapit \n nowa linia
		printf("Aby wstawic symbol w dana komorke wpisz x i y\n\n");
		printf("\t\t\t  (0,0) | (0,1)  | (0,2) | (0,3) \n");
		printf("\t\t\t--------------------------------\n");
		printf("\t\t\t  (1,0) | (1,1)  | (1,2) | (1,3)\n");
		printf("\t\t\t---------------------------------\n");
		printf("\t\t\t  (2,0) | (2,1)  | (2,2) | (2,3)\n");
		printf("\t\t\t----------------------------------\n");
		printf("\t\t\t  (3,0) | (3,1)  | (3,2) | (3,3) \n\n");
	}
	if (BOK == 5) {
		printf("\t\t\t Kolko i krzyzyk\n\n"); //\t to akapit \n nowa linia
		printf("Aby wstawic symbol w dana komorke wpisz x i y\n\n");
		printf("\t\t\t  (0,0) | (0,1)  | (0,2) | (0,3) | (0,4) \n");
		printf("\t\t\t-----------------------------------------\n");
		printf("\t\t\t  (1,0) | (1,1)  | (1,2) | (1,3) | (1,4)\n");
		printf("\t\t\t-----------------------------------------\n");
		printf("\t\t\t  (2,0) | (2,1)  | (2,2) | (2,3) | (2,4)\n");
		printf("\t\t\t-----------------------------------------\n");
		printf("\t\t\t  (3,0) | (3,1)  | (3,2) | (3,3) | (3,4) \n");
		printf("\t\t\t-----------------------------------------\n");
		printf("\t\t\t  (4,0) | (4,1)  | (4,2) | (4,3) | (4,4)\n \n");
	}
}
//inicjalizacja planszy
void UtworzPlansze(char plansza[][BOK], int ruchy[])
{
	//czysci plansze ze smieci
	for (int i = 0; i < BOK; i++)
	{
		for (int j = 0; j < BOK; j++)
			plansza[i][j] = ' '; //pusta tablica
	}
	//wypelnienie tab ruchow
	for (int i = 0; i < BOK*BOK; i++)
		ruchy[i] = i;
}
//obecny stan planszy
void PokazPlansze(char plansza[][BOK]) //plansza jest tabilca charow - jak widac
{
	if (BOK == 3)
	{
		printf("\n\n");

		printf("\t\t\t  %c | %c  | %c  \n", plansza[0][0],
			plansza[0][1], plansza[0][2]); // w miejscach c kolejne wartosci z tablicy plansza
		printf("\t\t\t--------------\n");
		printf("\t\t\t  %c | %c  | %c  \n", plansza[1][0],
			plansza[1][1], plansza[1][2]);
		printf("\t\t\t--------------\n");
		printf("\t\t\t  %c | %c  | %c  \n\n", plansza[2][0],
			plansza[2][1], plansza[2][2]);
	}

	if (BOK == 4)
	{
		printf("\n\n");

		printf("\t\t\t  %c | %c  | %c | %c \n", plansza[0][0],
			plansza[0][1], plansza[0][2], plansza[0][3]); // w miejscach c kolejne wartosci z tablicy plansza
		printf("\t\t\t--------------\n");
		printf("\t\t\t  %c | %c  | %c | %c  \n", plansza[1][0],
			plansza[1][1], plansza[1][2], plansza[1][3]);
		printf("\t\t\t--------------\n");
		printf("\t\t\t  %c | %c  | %c | %c  \n", plansza[2][0],
			plansza[2][1], plansza[2][2], plansza[2][3]);
		printf("\t\t\t  %c | %c  | %c | %c \n\n", plansza[3][0],
			plansza[3][1], plansza[3][2], plansza[3][3]);
	}
}
//okreslenie zwyciezcy
void Zwyciezca(int KogoTura) 
{
	if (KogoTura == PC) //sprawdzamy czyja jest tura
		cout << "Komputer wygral!" << endl; 
	else
		cout << "Gracz wygral!" << endl;
}
//funkcje sprawdzajace warunek wygranej - 3 dla 3 kierunkow

//poziomy
bool Poziom(char plansza[][BOK])
{

	int c = 0; //licznik ile w rzedzie jest takich samych znakow
	for (int i = 0; i < BOK; i++)
	{

		for (int j = 1; j < BOK; j++)
		{
			if (plansza[i][0] == plansza[i][j] && plansza[i][0] != ' ') c++; //zabezpieczamy przed wykryciem wyhranej gdy caly rzad pusty

		}
		if (c == BOK - 1)
			return(true);
		c = 0;
	}
	return (false);
	
	
}
//sprawdzanie w pionie
bool Pion(char plansza[][BOK])
{

	int c=0; //licznik ile w kolumnie jest takich samych znakow
	for (int i = 0; i < BOK; i++)
	{

		for (int j = 1; j < BOK; j++)
		{
			if (plansza[0][i] == plansza[j][i] && plansza[0][i] != ' ') c++;

		}
		if (c == BOK-1)
			return(true);
			c = 0;
	}
	return (false);
	
}

//sprawdzanie przekatnych
bool Diag(char plansza[][BOK])
{

	
	int c=0; //licznik ile w przekatnej jest takich samych znakow
	int i = 0;

		for (int j = BOK-1; j >0; j--)
		{
			if (plansza[j][i] == plansza[j-1][i+1] && plansza[j][i] != ' ') c++; //lewa-dolna przekatna
			i++;
		}
		if (c == BOK-1)
			return(true);
		c = 0;
	

	
		i = 0;
		for (int j = 1; j <BOK ; j++)
		{
			if (plansza[i][i] == plansza[j][j] && plansza[j][j] != ' ') c++; //lewa-gorna przekatna
			i++;
		}
		if (c == BOK - 1)
			return(true);
		c = 0;

	return (false);
	
}

//kiedy koniec gry

bool KoniecGry(char plansza[][BOK])
{
	if (Poziom(plansza) || Pion(plansza) || Diag(plansza))
		return(true);
	else
		return(false);
}

// faktyczna gra!!

void Graj(int KogoTura)
{
	char plansza[BOK][BOK];
	int ruchy[BOK*BOK];
	
	UtworzPlansze(plansza, ruchy);
	Instrukcja();
	int licznik = 0; //ktora jest tura
	int x, y; //wspolrzedne na planszy

	while (KoniecGry(plansza) == false && licznik != BOK * BOK)
	{
		if (KogoTura == PC)
		{
			RuchPC ruch = NajlepszyRuch(plansza);
			x = ruch.rzad;
			y = ruch.kolumna;
			plansza[x][y] = PC_RUCH;
			printf("Komputer wstawil %c w pole %d\n", PC_RUCH, ruchy[licznik] + 1);
			PokazPlansze(plansza);
			licznik++;
			KogoTura = GRACZ;
		}
		else if (KogoTura == GRACZ)
		{
			
			cout << "Wpisz x" << endl;
			cin >> x;
			cout << "Wpisz y" << endl;
			cin >> y;
			if (plansza[x][y] == ' ')
			{
				plansza[x][y] = GRACZ_RUCH;
				printf("Wstawiles %c w pole %d\n", GRACZ_RUCH, ruchy[licznik] + 1);
				PokazPlansze(plansza);
				licznik++;
				KogoTura = PC;
			}
			else
				cout << "Pole zajete, sprobuj jeszcze raz" << endl;
		}
	}

	//w przypadku remisu
	if (KoniecGry(plansza) == false && licznik == BOK * BOK)
		cout << "Remis!" << endl;
	else
	{
		if (KogoTura == PC)  //zamiana graczy zeby wpisac zwyciezce
			KogoTura = GRACZ;
		else if (KogoTura == GRACZ)
			KogoTura =PC;
		Zwyciezca(KogoTura);
	}
}


int main()
{

	Graj(PC); //kto zaczyna

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
