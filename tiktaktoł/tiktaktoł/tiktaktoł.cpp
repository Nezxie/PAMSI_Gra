

#include "pch.h"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define PC 1; //stale przypisujace numery graczom
#define GRACZ 2;
#define BOK 3; //dlugosc boku planszy

#define PC_RUCH 'O' //komputer stawia kolka
#define GRACZ_RUCH 'X' //gracz krzyzyki

//Instrukcja
void Instrukcja()
{
	printf("\t\t\t Kolko i krzyzyk\n\n"); //\t to akapit \n nowa linia
	printf("Aby wstawic symbol w dana komorke wybierz numer od 1-9");
	printf("\t\t\t  1 | 2  | 3  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  4 | 5  | 6  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  7 | 8  | 9  \n\n");
	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
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
//okreslenie zwyciezcy
void Zwyciezca(int KogoTura) 
{
	if (KogoTura == PC) //sprawdzamy czyja jest tura
		cout << "Komputer wygrał!" << endl; 
	else
		cout << "Gracz wygrał!" << endl;
}
//funkcje sprawdzajace warunek wygranej - 3 dla 3 kierunkow

//poziomy
bool Poziom(char plansza[][BOK])
{
	int c; //licznik ile w rzedzie jest takich samych znakow
	for (int i = 0; i < BOK; i++)
	{
	
		for (int j = 1; j < BOK; j++)
		{
			if (plansza[i][0] == plansza[i][j] && plansza[i][0]!=' ') c++; //zabezpieczamy przed wykryciem wyhranej gdy caly rzad pusty
			
		}
		if (c == BOK-1)
			return(true);
	}
	return (false);
}
//sprawdzanie w pionie
bool Pion(char plansza[][BOK])
{
	int c; //licznik ile w kolumnie jest takich samych znakow
	for (int i = 0; i < BOK; i++)
	{

		for (int j = 1; j < BOK; j++)
		{
			if (plansza[0][i] == plansza[j][i] && plansza[0][i] != ' ') c++;

		}
		if (c == BOK-1)
			return(true);
	}
	return (false);
}

//sprawdzanie przekatnych
bool Diag(char plansza[][BOK])
{
	int c; //licznik ile w przekatnej jest takich samych znakow
	int i = 0;

		for (int j = BOK; j >0; j--)
		{
			if (plansza[j][i] == plansza[j-1][i+1] && plansza[j][i] != ' ') c++; //lewa-dolna przekatna
			i++;
		}
		if (c == BOK-1)
			return(true);

	

	
		i = 0;
		for (int j = 1; j <BOK ; j++)
		{
			if (plansza[i][i] == plansza[j][j] && plansza[j][j] != ' ') c++; //lewa-gorna przekatna
			i++;
		}
		if (c == BOK - 1)
			return(true);

	return (false);
}

//kiedy koniec gry

bool KoniecGry(char plansza[][BOK])
{
	if (Poziom || Pion || Diag)
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
	int licznik = 0, x, y; //??????

	while (KoniecGry(plansza) == false && licznik != BOK * BOK)
	{
		if (KogoTura == PC)
		{
			x = ruchy[licznik] / BOK;
			y = ruchy[licznik] % BOK;
			plansza[x][y] = PC_RUCH;
			printf("Komputer wstawił %c w pole %d\n", PC_RUCH, ruchy[licznik] + 1);
			PokazPlansze(plansza);
			licznik++;
			KogoTura = GRACZ;
		}
		else if (KogoTura == GRACZ)
		{
			x = ruchy[licznik] / BOK;
			y = ruchy[licznik] % BOK;
			plansza[x][y] = GRACZ_RUCH;
			printf("Wstawiłeś %c w pole %d\n", PC_RUCH, ruchy[licznik] + 1);
			PokazPlansze(plansza);
			licznik++;
			KogoTura = PC;
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
