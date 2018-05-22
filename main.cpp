#include "conio2.h"
#include <stdio.h>
#include <math.h>
#include <cstdlib>

using namespace std;

#define pocz_x 49
#define pocz_y 2
#define enter 13

class element_stosu {
	friend class stos;
private:
	int ** tablica;
	element_stosu *nastepny;
	int szerokosc_tab;
public:
	element_stosu(int **tab, int szer, int dlug) {
		szerokosc_tab = szer;
		int ** tablica1 = new int *[szer];
		for (int i = 0; i < szer; i++)
			tablica1[i] = new int[dlug];
		for (int i = 0; i < szer; i++) {
			for (int j = 0; j < dlug; j++)
				tablica1[i][j] = tab[i][j];
		}
		this->tablica = tablica1;
		nastepny = NULL;
	}
	void destruktor() {
		for (int i = 0; i < szerokosc_tab; i++)
			delete[] tablica[i];
		delete[] tablica;
	}
	~element_stosu(){}
};

class stos {
private:
	element_stosu *glowa;
	int ilosc_elementow;
public:
	stos() {
		this->glowa = NULL;
		this->ilosc_elementow = 0;
	}
	void dodaj(element_stosu *nowy) {
		nowy->nastepny = glowa;
		glowa = nowy;
		ilosc_elementow++;
	}
	int **zabierz() {
		if (ilosc_elementow > 0) {
			int **zwr_tab = glowa->tablica;
			element_stosu *do_usuniecia = glowa;
			glowa = this->glowa->nastepny;
			ilosc_elementow--;
			delete do_usuniecia;
			return zwr_tab;
		}
		return NULL;
	}
	bool czypusty() {
		if (glowa == NULL)
			return true;
		else
			return false;
	}
	~stos() {
		element_stosu *wskaznik = glowa;
		while (wskaznik != NULL) {
			wskaznik->destruktor();
			element_stosu *do_usuniecia = wskaznik;
			wskaznik = wskaznik->nastepny;
			delete do_usuniecia;
		}
	}
};

char *wczytajchar(int poczatek_napisu_x, int poczatek_napisu_y) {
	static char wczytany[31];
	int licznik = 0;
	char z_klawiatury;
	bool prawidlowa = false;
	do {
		do {
			z_klawiatury = getch();
			if (((z_klawiatury >= '0' && z_klawiatury <= '9') || z_klawiatury == '.' || (z_klawiatury >= 'A' && z_klawiatury <= 'Z') || (z_klawiatury >= 'a' && z_klawiatury <= 'z')) && licznik < 30) {
				wczytany[licznik] = z_klawiatury;
				licznik++;
				wczytany[licznik] = '\0';
			}
			else if (z_klawiatury == '\b') {
				licznik--;
				wczytany[licznik] = 0;
			}
			gotoxy(poczatek_napisu_x, poczatek_napisu_y);
			cputs(wczytany);
		} while (z_klawiatury != enter);
		int kropki = 0;
		if (wczytany[licznik - 1] == 'd' && wczytany[licznik - 2] == 'e' && wczytany[licznik - 3] == '.')
			prawidlowa = true;
		for (int i = 0; i < licznik; i++) {
			if (wczytany[i] == '.')
				kropki++;
			if (kropki > 1) {
				prawidlowa = false;
				break;
			}
		}
	} while (prawidlowa != true);
	wczytany[licznik] = '\0';
	return wczytany;
}

int wczytajliczbe(int poczatek_napisu_x, int poczatek_napisu_y) {
	int cyfry[3] = { 0 };
	int il_cyfr = 0;
	int z_klawiatury;
	do {
		z_klawiatury = getch();
		if (il_cyfr < 3 || z_klawiatury==8 || z_klawiatury==enter) {
			switch (z_klawiatury)
			{
			case '0':
				cyfry[il_cyfr] = 0;
				il_cyfr++;
				break;
			case '1':
				cyfry[il_cyfr] = 1;
				il_cyfr++;
				break;
			case '2':
				cyfry[il_cyfr] = 2;
				il_cyfr++;
				break;
			case '3':
				cyfry[il_cyfr] = 3;
				il_cyfr++;
				break;
			case '4':
				cyfry[il_cyfr] = 4;
				il_cyfr++;
				break;
			case '5':
				cyfry[il_cyfr] = 5;
				il_cyfr++;
				break;
			case '6':
				cyfry[il_cyfr] = 6;
				il_cyfr++;
				break;
			case '7':
				cyfry[il_cyfr] = 7;
				il_cyfr++;
				break;
			case '8':
				cyfry[il_cyfr] = 8;
				il_cyfr++;
				break;
			case '9':
				cyfry[il_cyfr] = 9;
				il_cyfr++;
				break;
			case enter:
				break;
			case 8:
				if (il_cyfr > 0) {
					cyfry[il_cyfr - 1] = 0;
					il_cyfr--;
				}
				break;
			}
		}
		char* liczba = new char[il_cyfr + 1];
		liczba[il_cyfr] = '\0';
		for (int i = 0; i < il_cyfr; i++)
			liczba[i] = cyfry[i] + 48;
		gotoxy(poczatek_napisu_x, poczatek_napisu_y);
		cputs("   ");
		gotoxy(poczatek_napisu_x, poczatek_napisu_y);
		cputs(liczba);
		delete[] liczba;
	} while (z_klawiatury != enter);
	int wprowadzona_liczba = 0;
	for (int i = 0; i < il_cyfr; i++)
		wprowadzona_liczba += cyfry[i] * (int)pow(10,il_cyfr - 1 - i);
	return wprowadzona_liczba;
}

void wypelnij_obok(int x_tab, int y_tab, int **tab, int kolor, int szer_tab, int dlug_tab) {
	tab[x_tab][y_tab] = kolor;
	if (x_tab - 1 >= 0) {
		if (tab[x_tab - 1][y_tab] == BLACK) {
			tab[x_tab - 1][y_tab] = kolor;
			wypelnij_obok(x_tab - 1, y_tab, tab, kolor, szer_tab, dlug_tab);
		}
	}
	if (y_tab - 1 >= 0) {
		if (tab[x_tab][y_tab-1] == BLACK) {
			tab[x_tab][y_tab-1] = kolor;
			wypelnij_obok(x_tab, y_tab-1, tab, kolor, szer_tab, dlug_tab);
		}
	}
	if (x_tab + 1 < szer_tab) {
		if (tab[x_tab + 1][y_tab] == BLACK) {
			tab[x_tab + 1][y_tab] = kolor;
			wypelnij_obok(x_tab + 1, y_tab, tab, kolor, szer_tab, dlug_tab);
		}
	}
	if (y_tab + 1 >= 0) {
		if (tab[x_tab][y_tab + 1] == BLACK) {
			tab[x_tab][y_tab + 1] = kolor;
			wypelnij_obok(x_tab, y_tab + 1, tab, kolor, szer_tab, dlug_tab);
		}
	}
}

void wczytaj(FILE *plik, int *szer, int *dlug, int **tablica) {
	if ((plik = fopen("default.ed", "r")) != NULL) {
		fscanf(plik, "%i", szer);
		fscanf(plik, "%i", dlug);
		char tymczasowa[51];
		fscanf(plik, "%s", &tymczasowa);
		for (int i = 0; i < *dlug; i++) {
			fscanf(plik, "%s", &tymczasowa);
			for (int j = 0; j < *szer; j++) {
				if (tymczasowa[j] <= '9') {
					tablica[j][i] = tymczasowa[j] - '0';
				}
				else
					tablica[j][i] = tymczasowa[j] - 'A' + 10;
			}
		}
		fclose(plik);
	}
}

void wczytaj(FILE *plik, int *szer, int *dlug, int **tablica, char *nazwa_pliku) {
	if ((plik = fopen(nazwa_pliku, "r")) != NULL) {
		fscanf(plik, "%i", szer);
		fscanf(plik, "%i", dlug);
		char tymczasowa[51];
		fscanf(plik, "%s", &tymczasowa);
		for (int i = 0; i < *dlug; i++) {
			fscanf(plik, "%s", &tymczasowa);
			for (int j = 0; j < *szer; j++) {
				if (tymczasowa[j] <= '9') {
					tablica[j][i] = tymczasowa[j] - '0';
				}
				else
					tablica[j][i] = tymczasowa[j] - 'A' + 10;
			}
		}
		fclose(plik);
	}
}

void zapisz(FILE *plik, int szer, int dlug, int **tablica) {
	if ((plik = fopen("default.ed", "w+")) != NULL) {
		fprintf(plik, "%i,%i\n", szer, dlug);
		for (int i = 0; i < dlug; i++) {
			for (int j = 0; j < szer; j++) {
				char zn_do_pliku[2];
				if (tablica[j][i] < 10)
					zn_do_pliku[0] = '0' + tablica[j][i];
				else
					zn_do_pliku[0] = 'A' + tablica[j][i] - 10;
				zn_do_pliku[1] = '\0';
				fprintf(plik, "%s", zn_do_pliku);
			}
			fprintf(plik, "\n");
		}
		fclose(plik);
	}
}

void zapisz(FILE *plik, int szer, int dlug, int **tablica, char *nazwa_pliku) {
	if ((plik = fopen(nazwa_pliku, "w+")) != NULL) {
		fprintf(plik, "%i,%i\n", szer, dlug);
		for (int i = 0; i < dlug; i++) {
			for (int j = 0; j < szer; j++) {
				char zn_do_pliku[2];
				if (tablica[j][i] < 10)
					zn_do_pliku[0] = '0' + tablica[j][i];
				else
					zn_do_pliku[0] = 'A' + tablica[j][i] - 10;
				zn_do_pliku[1] = '\0';
				fprintf(plik, "%s", zn_do_pliku);
			}
			fprintf(plik, "\n");
		}
		fclose(plik);
	}
}

int main()
{
	int zn, x = pocz_x, y = pocz_y, attr = WHITE, x_prost, y_prost, x_linii, y_linii, x_kop, y_kop, szer_kop, dlug_kop;
	bool rys_prost = false, koniec_programu = false, rys_linii = false, kopiowanie = false;
	FILE *p = NULL;
	int **schowek = NULL;
	stos stos_schowek;
	settitle("Gustaw Ohler");
	textbackground(BLACK);
	gotoxy(1, 1);
	cputs("Jakie wymiar ma miec Twoj obrazek?");
	gotoxy(1, 2);
	cputs("Szerokosc:");
	int szerokosc = wczytajliczbe(12, 2);
	gotoxy(1, 3);
	cputs("Dlugosc:");
	int dlugosc = wczytajliczbe(10, 3);
	int ** tablica_obrazka = new int *[szerokosc];
	for (int i = 0; i < szerokosc; i++)
		tablica_obrazka[i] = new int[dlugosc];
	for (int i = 0; i < szerokosc; i++) {
		for (int j = 0; j < dlugosc; j++)
			tablica_obrazka[i][j] = BLACK;
	}
		do {
		clrscr();
		textcolor(WHITE);
		gotoxy(1, 1);
		cputs("esc = wyjscie");
		gotoxy(1, 2);
		cputs("strzalki = poruszanie");
		gotoxy(1, 3);
		cputs("klawisze 1-0, q-t = zmiana koloru");
		gotoxy(1, 4);
		cputs("i = wczytanie domyslnego obrazka");
		gotoxy(1, 5);
		cputs("o = wczytanie pliku");
		gotoxy(1, 6);
		cputs("n = nowy plik");
		gotoxy(1, 7);
		cputs("s = zapis pliku");
		gotoxy(1, 8);
		cputs("l = rysowanie linii");
		gotoxy(1, 9);
		cputs("k = rysowanie prostokata");
		gotoxy(1, 10);
		cputs("backspace = cofnij");
		gotoxy(1, 11);
		cputs("alt+strzalki zaznaczanie obszaru do skopiowania");
		gotoxy(1, 12);
		cputs("c = kopiowanie zaznaczonego obszaru");
		gotoxy(1, 13);
		cputs("p = wklejenie schowka");
		gotoxy(1, 14);
		cputs("f = wypelnienie obszaru od punktu");
		gotoxy(1, 16);
		cputs("polozenie kursora:");
		char x_znak[3], y_znak[3];
		if (x - pocz_x < 10) {
			x_znak[0] = '0' + x - pocz_x;
			x_znak[1] = '\0';
		}
		else {
			int liczba_dzies= (x - pocz_x) / 10;
			x_znak[0] = '0' + liczba_dzies;
			x_znak[1] = '0' + (x-pocz_x-liczba_dzies*10);
			x_znak[2] = '\0';
		}
		if (y - pocz_y < 10) {
			y_znak[0] = '0' + y - pocz_y;
			y_znak[1] = '\0';
		}
		else {
			int liczba_dziesy = (x - pocz_x) / 10;
			y_znak[0] = '0' + liczba_dziesy;
			y_znak[1] = '0' + (y - pocz_y - liczba_dziesy * 10);
			y_znak[2] = '\0';
		}
		gotoxy(20,16);
		cputs(x_znak);
		gotoxy(22, 16);
		putch(',');
		gotoxy(23, 16);
		cputs(y_znak);
		gotoxy(1, 18);
		if (stos_schowek.czypusty() == false) {
			cputs("mozliwe cofniecie");
			gotoxy(1, 19);
		}
		if (schowek != NULL) {
			cputs("mozliwe skopiowanie elementu ze schowka");
		}
		for (int i = 0; i < szerokosc; i++) {
			gotoxy(pocz_x + i, pocz_y-1);
			putch('_');
			gotoxy(pocz_x + i, pocz_y+dlugosc);
			putch('_');
		}
		for (int i = 0; i < dlugosc+1; i++) {
			gotoxy(pocz_x - 1, pocz_y+i);
			putch('|');
			gotoxy(pocz_x+szerokosc, pocz_y+i);
			putch('|');
		}
		for (int i = 0; i < szerokosc; i++) {
			for (int j = 0; j < dlugosc; j++) {
				gotoxy(pocz_x + i, pocz_y + j);
				textcolor(tablica_obrazka[i][j]);
				putch(254);
			}
		}
		textcolor(attr);
		if (rys_prost == true || kopiowanie == true) {
			char znak;
			int x_rys, y_rys;
			if (rys_prost == true) {
				znak = 254;
				x_rys = x_prost;
				y_rys = y_prost;
			}
			else {
				znak = '*';
				x_rys = x_kop;
				y_rys = y_kop;
			}
			for (int i = 0; i <= abs(x - pocz_x - x_rys); i++) {
				if (x - pocz_x - x_rys > 0) {
					gotoxy(x_rys + pocz_x + i, y_rys + pocz_y);
					putch(znak);
					gotoxy(x_rys + pocz_x + i, y);
					putch(znak);
				}
				else {
					gotoxy(x_rys + pocz_x - i, y_rys + pocz_y);
					putch(znak);
					gotoxy(x_rys + pocz_x - i, y);
					putch(znak);
				}
			}
			for (int i = 0; i <= abs(y - pocz_y - y_rys) - 2; i++) {
				if (y - pocz_y - y_rys > 0) {
					gotoxy(x_rys + pocz_x, y_rys + pocz_y + i + 1);
					putch(znak);
					gotoxy(x, y_rys + pocz_y + i + 1);
					putch(znak);
				}
				else {
					gotoxy(x_rys + pocz_x, y_rys + pocz_y - i - 1);
					putch(znak);
					gotoxy(x, y_rys + pocz_y - i - 1);
					putch(znak);
				}
			}
		}
		else if (rys_linii == true) {
			if (abs(y - pocz_y - y_linii) > abs(x - pocz_x - x_linii)) {
				float a = (float)((x - pocz_x) - x_linii) / (float)abs((y - pocz_y) - y_linii);
				for (int i = 0; i <= abs(y - pocz_y - y_linii); i++) {
					if ((y - pocz_y) - y_linii >= 0) {
						gotoxy(pocz_x + x_linii + (int)round(a*((float)i)), pocz_y + y_linii + i);
						putch(254);
					}
					else {
						gotoxy(pocz_x + x_linii + (int)round(a*((float)i)), pocz_y + y_linii - i);
						putch(254);
					}
				}
			}
			else {
				float a = (float)((y - pocz_y) - y_linii) / (float)abs((x - pocz_x) - x_linii);
				for (int i = 0; i <= abs(x - pocz_x - x_linii); i++) {
					if ((x - pocz_x) - x_linii >= 0) {
						gotoxy(pocz_x+x_linii + i, pocz_y + y_linii + (int)round(a*((float)i)));
						putch(254);
					}
					else {
						gotoxy(pocz_x + x_linii - i, pocz_y + y_linii + (int)round(a*((float)i)));
						putch(254);
					}
				}
			}
		}
		gotoxy(x, y);
		putch('*');
		zn = getch();
		switch (zn) {
		case 0:
			zn = getch();
			if (zn == 0x48 && y > pocz_y) {
				y--;
				kopiowanie = false;
			}
			else if (zn == 0x50 && y < pocz_y + dlugosc - 1) {
				y++;
				kopiowanie = false;
			}
			else if (zn == 0x4b && x > pocz_x) {
				x--;
				kopiowanie = false;
			}
			else if (zn == 0x4d && x < pocz_x + szerokosc - 1) {
				x++;
				kopiowanie = false;
			}
			else if (zn == 152 && y > pocz_y) {
				if (kopiowanie == false) {
					x_kop = x - pocz_x;
					y_kop = y - pocz_y;
					y--;
					kopiowanie = true;
				}
				else
					y--;
			}
			else if (zn == 157 && x < pocz_x + szerokosc - 1) {
				if (kopiowanie == false) {
					x_kop = x - pocz_x;
					y_kop = y - pocz_y;
					x++;
					kopiowanie = true;
				}
				else
					x++;
			}
			else if (zn == 160 && y < pocz_y + dlugosc - 1) {
				if (kopiowanie == false) {
					x_kop = x - pocz_x;
					y_kop = y - pocz_y;
					y++;
					kopiowanie = true;
				}
				else
					y++;
			}
			else if (zn == 155 && x > pocz_x) {
				if (kopiowanie == false) {
					x_kop = x - pocz_x;
					y_kop = y - pocz_y;
					x--;
					kopiowanie = true;
				}
				else
					x--;
			}
			break;

		case '0':
			attr = 0;
			break;
		case '1':
			attr = 1;
			break;
		case '2':
			attr = 2;
			break;
		case '3':
			attr = 3;
			break;
		case '4':
			attr = 4;
			break;
		case '5':
			attr = 5;
			break;
		case '6':
			attr = 6;
			break;
		case '7':
			attr = 7;
			break;
		case '8':
			attr = 8;
			break;
		case '9':
			attr = 9;
			break;
		case 'q':
			attr = 10;
			break;
		case 'w':
			attr = 11;
			break;
		case 'e':
			attr = 12;
			break;
		case 'r':
			attr = 13;
			break;
		case 't':
			attr = 14;
			break;
		case 'y':
			attr = 15;
			break;

		case 'a':
			if (rys_prost == false && rys_linii == false) {
				element_stosu *nowy = new element_stosu(tablica_obrazka, szerokosc, dlugosc);
				stos_schowek.dodaj(nowy);
				tablica_obrazka[x - pocz_x][y - pocz_y] = attr;
			}
			kopiowanie = false;
			break;

		case 'l':
			if (rys_prost == false) {
				if (rys_linii == false) {
					x_linii = x - pocz_x;
					y_linii = y - pocz_y;
					rys_linii = true;
				}
				else {
					element_stosu *nowy = new element_stosu(tablica_obrazka, szerokosc, dlugosc);
					stos_schowek.dodaj(nowy);
					if (abs(y - pocz_y - y_linii) > abs(x - pocz_x - x_linii)) {
						float a = (float)((x - pocz_x) - x_linii) / (float)abs((y - pocz_y) - y_linii);
						for (int i = 0; i <= abs(y - pocz_y - y_linii); i++) {
							if ((y - pocz_y) - y_linii >= 0)
								tablica_obrazka[x_linii + (int)round(a*((float)i))][y_linii + i] = attr;
							else
								tablica_obrazka[x_linii + (int)round(a*((float)i))][y_linii - i] = attr;
						}
					}
					else {
						float a = (float)((y - pocz_y) - y_linii) / (float)abs((x - pocz_x) - x_linii);
						for (int i = 0; i <= abs(x - pocz_x - x_linii); i++) {
							if ((x - pocz_x) - x_linii >= 0)
								tablica_obrazka[x_linii + i][y_linii + (int)round(a*((float)i))] = attr;
							else
								tablica_obrazka[x_linii - i][y_linii + (int)round(a*((float)i))] = attr;
						}
					}
					rys_linii = false;
				}
			}
			kopiowanie = false;
			break;

		case 'k':
			if (rys_linii == false) {
				if (rys_prost == false) {
					x_prost = x - pocz_x;
					y_prost = y - pocz_y;
					rys_prost = true;
				}
				else {
					element_stosu *nowy = new element_stosu(tablica_obrazka, szerokosc, dlugosc);
					stos_schowek.dodaj(nowy);
					for (int i = 0; i <= abs(x - pocz_x - x_prost); i++) {
						if (x - pocz_x - x_prost > 0) {
							tablica_obrazka[x_prost + i][y_prost] = attr;
							tablica_obrazka[x_prost + i][y - pocz_y] = attr;
						}
						else {
							tablica_obrazka[x_prost - i][y_prost] = attr;
							tablica_obrazka[x_prost - i][y - pocz_y] = attr;
						}
					}
					for (int i = 0; i <= abs(y - pocz_y - y_prost) - 2; i++) {
						if (y - pocz_y - y_prost > 0) {
							tablica_obrazka[x_prost][y_prost + i + 1] = attr;
							tablica_obrazka[x - pocz_x][y_prost + i + 1] = attr;
						}
						else {
							tablica_obrazka[x_prost][y_prost - i - 1] = attr;
							tablica_obrazka[x - pocz_x][y_prost - i - 1] = attr;
						}
					}
					rys_prost = false;
				}
			}
			kopiowanie = false;
			break;

		case '\b':
			if (stos_schowek.czypusty() == false) {
				int **do_skasowania = tablica_obrazka;
				tablica_obrazka = stos_schowek.zabierz();
				for (int i = 0; i < szerokosc; i++)
					delete[] do_skasowania[i];
				delete[] do_skasowania;
			}
			kopiowanie = false;
			break;

		case 's':
		{
			clrscr();
			gotoxy(1, 1);
			cputs("Gdzie zapisac obrazek?");
			char* nazwa = wczytajchar(1, 2);
			zapisz(p, szerokosc, dlugosc, tablica_obrazka, nazwa);
		}
			break;

		case 'i':
			wczytaj(p, &szerokosc, &dlugosc, tablica_obrazka);
			break;

		case 'o': {
			clrscr();
			gotoxy(1, 1);
			cputs("Jaki obrazek wczytac?");
			char* nazwa = wczytajchar(1, 2);
			wczytaj(p, &szerokosc, &dlugosc, tablica_obrazka, nazwa);
		}
			break;

		case 'n': {
			int ** do_kas = tablica_obrazka;
			for (int i = 0; i < szerokosc; i++)
				delete[] do_kas[i];
			delete[] do_kas;
			clrscr();
			gotoxy(1, 1);
			cputs("Jakie wymiar ma miec Twoj obrazek?");
			gotoxy(1, 2);
			cputs("Szerokosc:");
			szerokosc = wczytajliczbe(12, 2);
			gotoxy(1, 3);
			cputs("Dlugosc:");
			dlugosc = wczytajliczbe(10, 3);
			tablica_obrazka = new int *[szerokosc];
			for (int i = 0; i < szerokosc; i++)
				tablica_obrazka[i] = new int[dlugosc];
			for (int i = 0; i < szerokosc; i++) {
				for (int j = 0; j < dlugosc; j++)
					tablica_obrazka[i][j] = BLACK;
			}
		}
			break;

		case 'f':
			if (rys_prost == false && rys_linii == false) {
				element_stosu *nowy = new element_stosu(tablica_obrazka, szerokosc, dlugosc);
				stos_schowek.dodaj(nowy);
				wypelnij_obok(x - pocz_x, y - pocz_y, tablica_obrazka, attr, szerokosc, dlugosc);
			}
			kopiowanie = false;
			break;

		case 'c':
			if (kopiowanie == true) {
				if (schowek != NULL) {
					int ** usuwana = schowek;
					for (int i = 0; i < szerokosc; i++)
						delete[] usuwana[i];
					delete[] usuwana;
				}
				szer_kop = abs(x - pocz_x - x_kop) + 1;
				dlug_kop = abs(y - pocz_y - y_kop) + 1;
				schowek = new int *[szer_kop];
				for (int i = 0; i < szer_kop; i++) {
					schowek[i] = new int[dlug_kop];
				}
				for (int i = 0; i < szer_kop; i++) {
					for (int j = 0; j < dlug_kop; j++) {
						if (x_kop >= x - pocz_x) {
							if (y_kop >= y - pocz_y)
								schowek[i][j] = tablica_obrazka[x - pocz_x + i][y - pocz_y + j];
							else
								schowek[i][j] = tablica_obrazka[x - pocz_x + i][y_kop + j];
						}
						else {
							if (y_kop >= y - pocz_y)
								schowek[i][j] = tablica_obrazka[x_kop + i][y - pocz_y + j];
							else
								schowek[i][j] = tablica_obrazka[x_kop + i][y_kop + j];
						}
					}
				}
				kopiowanie = false;
			}
			break;

		case 'p':
			if (rys_linii == false && rys_prost == false && schowek != NULL) {
				for (int i = 0; i < szer_kop; i++) {
					for (int j = 0; j < dlug_kop; j++) {
						if (x - pocz_x + i < szerokosc && y - pocz_y + j < dlugosc)
						tablica_obrazka[x - pocz_x + i][y - pocz_y + j] = schowek[i][j];
					}
				}
			}
			break;

		case 27:
			if (rys_prost == true)
				rys_prost = false;
			else if (rys_linii == true)
				rys_linii = false;
			else
				koniec_programu = true;
			kopiowanie = false;
			break;
		}
	} while (koniec_programu != true);
	if (schowek != NULL) {
		for (int i = 0; i < szer_kop; i++)
			delete[] schowek[i];
		delete[] schowek;
	}
	for (int i = 0; i < szerokosc; i++)
		delete[] tablica_obrazka[i];
	delete[] tablica_obrazka;
	return 0;
}