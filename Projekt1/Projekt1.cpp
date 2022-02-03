// Projekt1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <stdio.h>//aby działał exit
#include <windows.h>//aby działa funkcja cls
#include <iomanip>
#include <random>//losowanie
#include <ctime>//losowanie
#include <locale.h> 
#include<string>
#include<fstream>

using namespace std;



void plansza(char tab[])//tworzenie planszy
{
	for (int i = 1; i <= 9; i++)//tworzenie 9 pól
	{
		cout << " " << tab[i] << " ";
		if (i % 3 != 0)
			cout << "|";
		else if (i != 9)
		{
			cout << endl;
			cout << "---+---+---";
			cout << endl;
		}

		else
			cout << endl;
	}

}

void ruch(char tab[], char& symbol)
{
	int numer;//numer pola na planszy

	plansza(tab); //drukujemy planszę
	cout << endl;
	cout << "GRACZ " << symbol << " czas na twój ruch : ";//wywołujemy gracza, który ma zagrać


	do
	{
		cin >> numer;//gracz wpisuje numer, czyli pole na planszy na ktorym chce postawic znak
		cout << endl << "--------------------------------------" << endl << endl;



		while (cin.fail())//sprawdzanie czy wprowadzona wartosc jest rozna od INT, jezeli tak, użytkownik wpisuje nowa wartosc
		{
			cout << "Wprowadziles złą wartość! Wprowadz liczbę od 1 do 9: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> numer;
		}



		if ((numer >= 1) && (numer <= 9) && (tab[numer] == ' '))//jeśli numer mieści się w planszy i podane pole jest puste wprowadź symbol		
		{
			tab[numer] = symbol;//wprowadzenie numeru do odpowidniej rubryki planszy
		}
		else
		{
			cout << "Wprowadziles złą wartość! Wprowadz liczbę od 1 do 9: ";//jezeli numer jest wiekszy od 9 lub mniejszy od 1, uzytkownik musi wpisac liczbe jeszcze raz
		}


	} while (((numer < 1) || (numer > 9) && (tab[numer] != ' ')));


Sleep(100);

if (symbol == 'O') //zamiana uczestników, gracze grają na zmianę
{
	symbol = 'X';
}
else
{
	symbol = 'O';
}
system("cls");//czyszczenie ekranu, aby widoczna byla tylko plansza

}



bool ktoWygrywa(char tab[], char symbol)
{
	bool sprawdz = false;

	//sprawdz przyjmie wartość true, jeśli gracz będzie miał 3 symbole pod rząd w kolumnie, wierszu lub przekątnej

	for (int i = 1; i <= 7; i = i + 3)
	{
		sprawdz = sprawdz | ((tab[i] == symbol) && (tab[i + 1] == symbol) && (tab[i + 2] == symbol));//sprawdzenie wierszy
	}

	for (int i = 1; i <= 3; i++)
	{
		sprawdz |= ((tab[i] == symbol) && (tab[i + 3] == symbol) && (tab[i + 6] == symbol));//sprawdzenie kolumn
	}

	sprawdz = sprawdz | ((tab[1] == symbol) && (tab[5] == symbol) && (tab[9] == symbol));//sprawdzenie przekątnej 1-5-9

	sprawdz = sprawdz | ((tab[3] == symbol) && (tab[5] == symbol) && (tab[7] == symbol));//sprawdzenie przekątnej 3-5-7


	if (sprawdz == true)
	{

		plansza(tab);
		cout << endl;
		cout << "Gracz, posługujący się symbolem " << symbol << " wygrywa!" << endl << endl;

		return true;//funkcja zwraca wartość true, jeśli nastąpiła wygrana któregoś z graczy
	}
	
	return false;

}


bool remis(char tab[])
{
	for (int i = 1; i <= 9; i++)// Jeśli napotkamy spację, to plansza posiada wolne pola, a więc jeszcze istnieje mozliwosc wygranej - zwracamy false
	{
		if (tab[i] == ' ')
			return false;
	}
	plansza(tab);
	cout << endl;
	cout << "Remis!" << endl;

	return true;// Jesli pętla for zakończyła się bez zwrócenia false, to na żadnym polu planszy nie było spacji (wszytskie pola na planszy są zajęte, ale nie mamy wyniku). Mamy do czynienia z remisem - zwracamy true

}

//********************************


void zapiszDoPliku(string nazwaPliku, string imie, int wynik)
{
	fstream plik;
	plik.open(nazwaPliku, ios::app);
	if (plik.is_open())
	{

		plik << "Imie: " << imie << '\t' << "Wynik: " << wynik;
		plik << endl;

	}
	else
	{
		cout << "Nie mozna otworzyc pliku!";
	}
	plik.close();
}
//****************************

struct Gra
{
	int tab1[5]{};
	int tab2[5]{};
	int tab3[5]{};
	int suma = 0;
	string imie1;
	void losuj(int liczba);
	void zliczPunkty(int liczba);
	void zapiszDoPliku(string nazwaPliku, string imie1);
	void odczytajZPliku(string nazwaPliku);
	void wyczyscPlik(string nazwaPliku);

};
void Gra::losuj(int liczba)//losowanie liczb i zapisywanie ich do odpowiedniej tablicy
{


	mt19937 generator(time(nullptr));
	uniform_int_distribution<int> zakres(1, 6);
	if (liczba == 1)
	{

		cout << "Wylosowane przez Ciebie liczby to: ";
		for (int i = 0; i < 5; i++)
		{

			tab1[i] = zakres(generator);
			cout << tab1[i];
			if (i < 4)
			{
				cout << ", ";
			}
			else
			{
				cout << ". ";
			}

		}
		cout << endl;
	}
	if (liczba == 2)
	{

		cout << "Wylosowane przez Ciebie liczby w rundzie 1 to: ";
		for (int i = 0; i < 5; i++)
		{

			tab1[i] = zakres(generator);
			cout << tab1[i];
			if (i < 4)
			{
				cout << ", ";
			}
			else
			{
				cout << ". ";
			}


		}
		cout << endl << endl;
		cout << "Wylosowane przez Ciebie liczby w rundzie 2 to: ";
		for (int i = 0; i < 5; i++)
		{

			tab2[i] = zakres(generator);
			cout << tab2[i];
			if (i < 4)
			{
				cout << ", ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << endl << endl;
	}
	if (liczba == 3)
	{
		cout << "Wylosowane przez Ciebie liczby w rundzie 1 to: ";
		for (int i = 0; i < 5; i++)
		{

			tab1[i] = zakres(generator);
			cout << tab1[i];
			if (i < 4)
			{
				cout << ", ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << endl << endl;
		cout << "Wylosowane przez Ciebie liczby w rundzie 2 to: ";
		for (int i = 0; i < 5; i++)
		{

			tab2[i] = zakres(generator);
			cout << tab2[i];
			if (i < 4)
			{
				cout << ", ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << endl << endl;
		cout << "Wylosowane przez Ciebie liczby w rundzie 3 to: ";
		for (int i = 0; i < 5; i++)
		{

			tab3[i] = zakres(generator);
			cout << tab3[i];
			if (i < 4)
			{
				cout << ", ";
			}
			else
			{
				cout << ". ";
			}


		}

	}
	cout << endl << endl;

}



void Gra::zliczPunkty(int liczba)//zlicza sumę wyrzuconych oczek, jeżeli gracz wyrzucił dwie liczby obok siebie to podaną sumę z danej rundy mnoży x2
{
	int suma1 = 0, suma2 = 0, suma3 = 0;

	if (liczba == 1)
	{

		for (int i = 0; i < 5; i++)
		{

			suma1 = suma1 + tab1[i];


		}
		cout << "Suma punktów z rundy 1: " << suma1 << endl;


		for (int i = 0; i < 5; i++)
		{
			if ((tab1[i] == tab1[i + 1]) && (tab1[i + 1] != tab1[i + 2]))
			{
				suma1 = suma1 * 2;
				cout << "Ponieważ wyrzuciłeś 2 liczby obok siebie, twoja suma zostaje pomnożona x2. Nowa suma wynosi: " << suma1 << endl;
			}

		}
		suma = suma1;
		cout << "Suma wyrzuconych liczb wynosi: " << suma << " !" << endl << endl << endl;
		cout << "********************************" << endl << endl;
	}
	if (liczba == 2)
	{

		for (int i = 0; i < 5; i++)
		{

			suma1 = suma1 + tab1[i];


		}
		cout << "Suma punktów z rundy 1: " << suma1 << endl;


		for (int i = 0; i < 5; i++)
		{
			if ((tab1[i] == tab1[i + 1]) && (tab1[i + 1] != tab1[i + 2]))
			{
				suma1 = suma1 * 2;
				cout << "Ponieważ wyrzuciłeś 2 liczby obok siebie, twoja suma zostaje pomnożona x2. Nowa suma wynosi: " << suma1 << endl;
			}

		}
		cout << endl << endl;


		for (int i = 0; i < 5; i++)
		{

			suma2 = suma2 + tab2[i];


		}
		cout << "Suma punktów z rundy 2: " << suma2 << endl;


		for (int i = 0; i < 5; i++)
		{
			if ((tab2[i] == tab2[i + 1]) && (tab2[i + 1] != tab2[i + 2]))
			{
				suma2 = suma2 * 2;
				cout << "Ponieważ wyrzucił_ś 2 liczby obok siebie, twoja suma zostaje pomnożona x2. Nowa suma wynosi: " << suma2 << endl;
			}

		}
		suma = suma1 + suma2;
		cout << "Suma wszystkich wyrzuconych liczb wynosi: " << suma << " !" << endl << endl << endl;
		cout << "********************************" << endl << endl;

	}
	if (liczba == 3)
	{

		for (int i = 0; i < 5; i++)
		{

			suma1 = suma1 + tab1[i];


		}
		cout << "Suma punktów z rundy 1: " << suma1 << endl;


		for (int i = 0; i < 5; i++)
		{
			if ((tab1[i] == tab1[i + 1]) && (tab1[i + 1] != tab1[i + 2]))
			{
				suma1 = suma1 * 2;
				cout << "Ponieważ wyrzucił_ś 2 liczby obok siebie, twoja suma zostaje pomnożona x2. Nowa suma wynosi: " << suma1 << endl;
			}

		}
		cout << endl << endl;

		for (int i = 0; i < 5; i++)
		{

			suma2 = suma2 + tab2[i];


		}
		cout << "Suma punktów z rundy 2: " << suma2 << endl;


		for (int i = 0; i < 5; i++)
		{
			if ((tab2[i] == tab2[i + 1]) && (tab2[i + 1] != tab2[i + 2]))
			{
				suma2 = suma2 * 2;
				cout << "Ponieważ wyrzuciłeś 2 liczby obok siebie, twoja suma zostaje pomnożona x2. Nowa suma wynosi: " << suma2 << endl;
			}

		}

		cout << endl << endl << endl;
		for (int i = 0; i < 5; i++)
		{

			suma3 = suma3 + tab3[i];


		}
		cout << "Suma punktów z rundy 2: " << suma3 << endl;


		for (int i = 0; i < 5; i++)
		{
			if ((tab3[i] == tab3[i + 1]) && (tab3[i + 1] != tab3[i + 2]))
			{
				suma3 = suma3 * 2;
				cout << "Ponieważ wyrzuciłeś 2 liczby obok siebie, twoja suma zostaje pomnożona x2. Nowa suma wynosi: " << suma3 << endl;
			}

		}
		suma = suma1 + suma2 + suma3;
		cout << "Suma wszystkich wyrzuconych liczb wynosi: " << suma << " !" << endl << endl << endl;
		cout << "********************************" << endl << endl;
	}



}



void Gra::zapiszDoPliku(string nazwaPliku, string imie1)
{
	fstream plik1;
	plik1.open(nazwaPliku, ios::app);
	
	if (plik1.is_open())
	{

		plik1 << "Imie: " << imie1 << '\t' << "Wynik: " << suma;
		plik1 << endl;


	}
	else
	{
		cout << "Nie mozna otworzyc pliku!";
	}
	plik1.close();
}

void Gra::odczytajZPliku(string nazwaPliku)
{
	string linia;
	ifstream plik1;
	plik1.open(nazwaPliku, ios::in);
	if (plik1.is_open())
	{
		while (!plik1.eof())
		{
			getline(plik1, linia);
			cout << linia << endl;
		}

	}
	else
	{
		cout << "Nie mozna otworzyc pliku!";
	}
	plik1.close();
}

void Gra::wyczyscPlik(string nazwaPliku)
{
	fstream plik1;
	plik1.open(nazwaPliku, ios::out | ios::trunc);
	plik1.close();
}

//*************************************

int main()
{
	setlocale(LC_ALL, "polish");


	int wybor = 0;

	cout << "       MENU GŁÓWNE   " << endl;
	cout << "-------------------------" << endl;
	cout << "1. Kółko i krzyżyk" << endl;
	cout << "2. Quiz językowy" << endl;
	cout << "3. Gra w kości" << endl;
	cout << "4. Koniec programu" << endl << endl << endl;

	cout << "Wprowadz liczbe: ";



	do
	{

		cin >> wybor;
		
		while (cin.fail())//sprawdzanie czy wprowadzona wartosc jest rozna od INT, jezeli tak, użytkownik wpisuje nowa wartosc
		{
			cout << "Wprowadziles złą wartość! Wprowadz liczbę od 1 do 4: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> wybor;
		}
		if ((wybor < 0) || (wybor > 4))
		{
			cout << "Wprowadziles złą wartość! Wprowadz liczbę od 1 do 4: ";
			
		}
		else
		{

			system("cls");
			if (wybor == 1)
			{

				char tab[10], symbol, decyzja;

				do
				{

					cout << "'Kółko i krzyżyk' dla dwóch graczy:" << endl;
					cout << "Instrukcja gry: wpisz numer pola(1-9), na którym chesz umieścić symbol. " << endl << endl;
					cout << "Plansza ma postać: " << endl;
					cout << "[1] [2] [3]" << endl << "[4] [5] [6]" << endl << "[7] [8] [9]" << endl << endl;



					cout << "======================================" << endl << endl;
					system("pause");
					cout << endl;
					system("cls");

					cout << "Rozpocznijmy grę!" << endl << endl;

					for (int i = 1; i <= 9; i++)//drukowanie pustej planszy
					{
						tab[i] = ' ';
					}
					symbol = 'X';
					while (!ktoWygrywa(tab, 'X') && !ktoWygrywa(tab, 'O') && !remis(tab))//nie ma wygranego ani remisu, ruch odbywa się dalej
					{
						ruch(tab, symbol);

					}

					cout << "Chcesz zagrać jeszcze raz?: (Jeżeli tak, wpisz t)";
					cin >> decyzja;
					cout << endl << endl << endl << endl;


				} while ((decyzja == 'T') || (decyzja == 't'));


			}
			if (wybor == 2)
			{
				
				int wybor = 0;
				string imie{};
				int wynik = 0;
				char decyzja = 0;

				do
				{



					cout << "Quiz językowy" << endl << endl;
					cout << "Podaj swoje imie:)) : ";
					cin >> imie;
					cout << endl << endl;
					cout << "1 - poziom trudności: łatwy" << endl << "2 - poziom trudności: średni" << endl << "3 - poziom trudności: trudny" << endl << endl;
					cout << "Wybierz poziom trudności poprzez wpisanie odpowiedniego numerka: ";

					do
					{
						cin >> wybor;

						while (cin.fail())//sprawdzanie czy wprowadzona wartosc jest rozna od INT, jezeli tak, użytkownik wpisuje nowa wartosc
						{
							cout << "Wprowadziles złą wartość! Wprowadz liczbę od 1 do 3: ";
							cin.clear();
							cin.ignore(256, '\n');
							cin >> wybor;
						}



						if (wybor == 1)
						{
							system("cls");
							cout << "Twoim zadaniem będzie przetłumaczenie 10 słówek na język angielski."<<endl;
							cout<<"Za każde poprawne tłumaczenie otrzymasz 1pkt. Masz 3 szanse na wpisanie poprawnego słowa, jeżeli się pomylisz, otrzymasz podpowiedź." << endl << endl;
							cout << "*********************" << endl << endl;
							system("pause");
							cout << endl;
							system("cls");
							cout << "Zaczynajmy! " << endl << endl;

							int licznik = 0;
							int k = 0;

							fstream  plik2;
							string wczytaj{};
							plik2.open("slowa1.txt");
							if (plik2.is_open())
							{
								while (!plik2.eof())
								{
									plik2 >> wczytaj;

									licznik++;
								}

							}
							plik2.close();

							string* slowo = nullptr;
							slowo = new string[licznik];

							plik2.open("slowa1.txt");

							if (plik2.is_open())
							{

								while (!plik2.eof())
								{
									plik2 >> wczytaj;



									slowo[k] = wczytaj;
									k++;

								}

							}
							else
							{
								cout << "Nie mozna otworzyc plik!" << endl;
							}



							plik2.close();


							int licznik1 = 0;
							int g = 0;

							fstream  plik3;
							string wczytaj1{};
							plik3.open("tlumaczenie1.txt");
							if (plik3.is_open())
							{
								while (!plik3.eof())
								{
									plik3 >> wczytaj1;

									licznik1++;
								}

							}
							plik3.close();

							string* tlumaczenie = nullptr;
							tlumaczenie = new string[licznik1];

							plik3.open("tlumaczenie1.txt");

							if (plik3.is_open())
							{

								while (!plik3.eof())
								{
									plik3 >> wczytaj1;



									tlumaczenie[g] = wczytaj1;
									g++;

								}

							}
							else
							{
								cout << "Nie mozna otworzyc plik!" << endl;
							}



							plik3.close();

							/*string slowo[10]{ "stary","włosy","sukienka", "pokój", "aparat", "lodówka", "jabłko","drzewo", "okulary", "młody" };*/
							string tab1[10]{ "slowo1","slowo2","slowo3", "slowo4", "slowo5", "slowo6","slowo7", "slowo8", "slowo9", "slowo10" };
							/*string tlumaczenie[10]{ "old", "hair", "dress", "room","camera","fridge","apple","tree","glassess","young" };*/


							int zle = 0, j = 1;
							char znak = 0;

							for (int i = 0; i < 10; i++)
							{
								zle = 0;
								do
								{
									if (zle < 3)
									{
										cout << "Przetłumacz słowo '" << slowo[i] << "' na język angielski: ";

										cin >> tab1[i];
										if (tab1[i] == tlumaczenie[i])
										{

											cout << "Brawo, dobrze Ci poszło";
											Sleep(900);
											wynik = wynik + 1;
										}

										else if (zle < 2)
										{

											cout << "Źle, popełniłeś błąd! Czy chcesz otrzymać podpowiedź? Tak = t, nie = n: ";
											cin >> znak;

											if ((znak == 't') || (znak == 'T'))
											{
												string podNapis = tlumaczenie[i].substr(0, j);
												cout << "Podpowiedź litery: " << podNapis << endl;
												j++;
											}

											
											zle++;
										}
										else
										{
											cout << "Nie masz więcej podpowiedzi!" << endl;
											cout << "Poprawne tłumaczenie to: " << tlumaczenie[i] << endl << endl;
											system("pause");
										
											break;
										}
									}


								} while ((tab1[i] != tlumaczenie[i]) && (zle != 3));
								system("cls");

								cout << endl << endl;


							}
							delete[]slowo;
							delete[]tlumaczenie;

							cout << "Twój wynik to: " << wynik << endl;

						}
						else
						{
							cout << "Wprowadziles zly numer! Sprobuj jeszcze raz: ";
						}



						if (wybor == 2)
						{
							system("cls");
							cout << "Twoim zadaniem będzie przetłumaczenie 10 słówek na język angielski."<< endl;
							cout<<"Za każde poprawne tłumaczenie otrzymasz 1pkt. Masz 2 szanse na wpisanie poprawnego słowa, jeżeli się pomylisz, możesz wykorzystać podpowiedź." << endl << endl;
							cout << "*********************" << endl << endl;
							system("pause");
							cout << endl;
							system("cls");
							cout << "Zaczynajmy! " << endl << endl;


							int licznik = 0;
							int k = 0;

							fstream  plik2;
							string wczytaj{};
							plik2.open("slowa2.txt");
							if (plik2.is_open())
							{
								while (!plik2.eof())
								{
									plik2 >> wczytaj;

									licznik++;
								}

							}
							plik2.close();

							string* slowo2 = nullptr;
							slowo2 = new string[licznik];

							plik2.open("slowa2.txt");

							if (plik2.is_open())
							{

								while (!plik2.eof())
								{
									plik2 >> wczytaj;



									slowo2[k] = wczytaj;
									k++;

								}

							}
							else
							{
								cout << "Nie mozna otworzyc plik!" << endl;
							}



							plik2.close();


							int licznik1 = 0;
							int g = 0;

							fstream  plik3;
							string wczytaj1{};
							plik3.open("tlumaczenie2.txt");
							if (plik3.is_open())
							{
								while (!plik3.eof())
								{
									plik3 >> wczytaj1;

									licznik1++;
								}

							}
							plik3.close();

							string* tlumaczenie2 = nullptr;
							tlumaczenie2 = new string[licznik1];

							plik3.open("tlumaczenie2.txt");

							if (plik3.is_open())
							{

								while (!plik3.eof())
								{
									plik3 >> wczytaj1;



									tlumaczenie2[g] = wczytaj1;
									g++;

								}

							}
							else
							{
								cout << "Nie mozna otworzyc plik!" << endl;
							}



							plik3.close();

							string tab2[10]{ "slowo1","slowo2","slowo3", "slowo4", "slowo5", "slowo6","slowo7", "slowo8", "slowo9", "slowo10" };
							
							int zle = 0;
							char znak = 0;

							for (int i = 0; i < 10; i++)
							{
								zle = 0;
								do {
									if (zle < 2)
									{
										cout << "Przetłumacz słowo '" << slowo2[i] << "' na język angielski: ";

										cin >> tab2[i];
										if (tab2[i] == tlumaczenie2[i])
										{

											cout << "Brawo, dobrze Ci poszło";
											Sleep(900);
											wynik = wynik + 1;
										}

										else if (zle == 0)
										{

											cout << "Źle, popełniłeś błąd! Czy chcesz otrzymać podpowiedź? Tak = t, nie = n: ";
											cin >> znak;

											if ((znak == 't') || (znak == 'T'))
											{
												string podNapis = tlumaczenie2[i].substr(0, 1);
												cout << "Podpowiedź: pierwsza lietra tego wyrazu to: " << podNapis << endl;

											}

											zle++;
										}
										else
										{
											cout << "Nie masz więcej podpowiedzi!" << endl;
											cout << "Poprawne tłumaczenie to: " << tlumaczenie2[i] << endl << endl;
											system("pause");
											break;

										}
									}


								} while ((tab2[i] != tlumaczenie2[i]) && (zle != 2));
								system("cls");

								cout << endl << endl;



							}
							delete[]slowo2;
							delete[]tlumaczenie2;

							cout << "Twój wynik to: " << wynik << endl;


						}
						if (wybor == 3)
						{
							system("cls");
							cout << "Twoim zadaniem będzie przetłumaczenie 10 słówek na język angielski." << endl;
							cout<<"Za każde poprawne tłumaczenie otrzymasz 1pkt. Masz 1 szanse na wpisanie poprawnego słowa." << endl << endl;
							cout << "*********************" << endl << endl;
							system("pause");
							cout << endl;
							system("cls");
							cout << "Zaczynajmy! " << endl << endl;



							int licznik = 0;
							int k = 0;

							fstream  plik2;
							string wczytaj{};
							plik2.open("slowa3.txt");
							if (plik2.is_open())
							{
								while (!plik2.eof())
								{
									plik2 >> wczytaj;

									licznik++;
								}

							}
							plik2.close();

							string* slowo3 = nullptr;
							slowo3 = new string[licznik];

							plik2.open("slowa3.txt");

							if (plik2.is_open())
							{

								while (!plik2.eof())
								{
									plik2 >> wczytaj;



									slowo3[k] = wczytaj;
									k++;

								}

							}
							else
							{
								cout << "Nie mozna otworzyc plik!" << endl;
							}



							plik2.close();


							int licznik1 = 0;
							int g = 0;

							fstream  plik3;
							string wczytaj1{};
							plik3.open("tlumaczenie3.txt");
							if (plik3.is_open())
							{
								while (!plik3.eof())
								{
									plik3 >> wczytaj1;

									licznik1++;
								}

							}
							plik3.close();

							string* tlumaczenie3 = nullptr;
							tlumaczenie3 = new string[licznik1];

							plik3.open("tlumaczenie3.txt");

							if (plik3.is_open())
							{

								while (!plik3.eof())
								{
									plik3 >> wczytaj1;



									tlumaczenie3[g] = wczytaj1;
									g++;

								}

							}
							else
							{
								cout << "Nie mozna otworzyc plik!" << endl;
							}



							plik3.close();

							
							string tab3[10]{ "slowo1","slowo2","slowo3", "slowo4", "slowo5", "slowo6","slowo7", "slowo8", "slowo9", "slowo10" };
							

							for (int i = 0; i < 10; i++)
							{


								cout << "Przetłumacz słowo '" << slowo3[i] << "' na język angielski: ";

								cin >> tab3[i];
								if (tab3[i] == tlumaczenie3[i])
								{

									cout << "Brawo, dobrze Ci poszło";
									Sleep(900);
									wynik = wynik + 1;
								}

								else
								{

									cout << "Źle, popełniłeś błąd!" <<endl;
									cout << "Poprawne tłumaczenie to: " << tlumaczenie3[i] << endl << endl;
									system("pause");
									

								}



								system("cls");

								cout << endl << endl;



							}
							delete[]slowo3;
							delete[]tlumaczenie3;
							cout << "Twój wynik to: " << wynik << endl;



						}


					} while ((wybor != 1) && (wybor != 2) && (wybor != 3));

					zapiszDoPliku("wyniki.txt", imie, wynik);

					cout << "Chcesz zagrać jeszcze raz?: (Jeżeli tak, wpisz t)";
					cin >> decyzja;
					cout << endl << endl << endl << endl;

					
				} while ((decyzja == 'T') || (decyzja == 't'));

			}
			if (wybor == 3)
			{
				Gra kosci;
				setlocale(LC_ALL, "polish");
				string imie1{};
				int rundy = 0;
				char decyzja = 0;
				ifstream instrukcja;
				instrukcja.open("Instrukcja.txt", ios::out);
				if (instrukcja.is_open())
				{
					char tekst[1000]{};
					while (instrukcja.getline(tekst, 1000))
					{
						cout << tekst << endl;
					}
					instrukcja.close();
				}
				else
				{
					cout << "Nie udało się otworzyć pliku!";
				}

				cout << endl;
				cout << "**************************" << endl << endl;
				system("pause");
				cout << endl;
				system("cls");

				do
				{
					system("cls");
					
					kosci.wyczyscPlik("wyniki1.txt");

					for (int i = 0; i < 2; i++)
					{

						cout << "Jesteś gotowy? :) Wpisz swoje imię: ";
						cin >> imie1;

						cout << "wprowadz liczbe rund (od 1 do 3): ";

						do
						{
							cin >> rundy;

							while (cin.fail())//sprawdzanie czy wprowadzona wartosc jest rozna od INT, jezeli tak, użytkownik wpisuje nowa wartosc
							{
								cout << "Wprowadziles złą wartość! Wprowadz liczbę od 1 do 3: ";
								cin.clear();
								cin.ignore(256, '\n');
								cin >> rundy;
							}

							if ((rundy < 1) || (rundy > 3))
							{
								cout << "Wprowadziłeś złą wartość. Wprowadź liczbę od 1 do 3: ";
							}
						} while ((rundy < 1) || (rundy > 3));



						system("cls");



						kosci.losuj(rundy);
						kosci.zliczPunkty(rundy);


						kosci.zapiszDoPliku("wyniki1.txt", imie1);

					}

					system("pause");
					

					system("cls");

					cout << "Wyniki: " << endl;
					kosci.odczytajZPliku("wyniki1.txt");

					cout << endl << endl;
					cout << "Chcesz zagrać jeszcze raz?: (Jeżeli tak, wpisz t)";
					cin >> decyzja;
					cout << endl << endl << endl << endl;
				} while ((decyzja == 'T') || (decyzja == 't'));
			}
			if (wybor == 4)
			{
				exit(0);
				break;
			}
			else
			{
				system("cls");
				cout << "       MENU GŁÓWNE   " << endl;
				cout << "-------------------------" << endl;
				cout << "1. Kółko i krzyżyk" << endl;
				cout << "2. Quiz językowy" << endl;
				cout << "3. Gra w kości" << endl;
				cout << "4. Koniec programu" << endl << endl << endl;

				cout << "Wprowadź liczbę: ";

			}
			
		}
		
	} while (wybor != 4);
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
