

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
	printf("\t\t\t Kolko i krzyzyk\n\n"); //\t to akapit
	printf("Aby wstawic symbol w dana komorke wybierz numer od 1-9");
	printf("\t\t\t  1 | 2  | 3  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  4 | 5  | 6  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  7 | 8  | 9  \n\n");
	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
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

int main()
{
    std::cout << "Hello World!\n"; 
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
