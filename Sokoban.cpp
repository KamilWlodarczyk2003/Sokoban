#include <iostream>
#include <fstream>

using namespace std;
const int ilosc_poz = 4;
struct punkt {
	int x;
	int y;
};

bool podmien_beczke(short T[][15], short beczka, short otwor, int* m, int* n) {
	bool czy = 0;
	for (int i = 0; i < *m; i++) {
		for (int j = 0; j < *n; j++) {
			if (T[j][i] == otwor) {
				return 0;
			}
		}
	}
	for (int i = 0; i < *m; i++) {
		for (int j = 0; j < *n; j++) {
			if (T[j][i] == beczka) {
				*m = i;
				*n = j;
				return 1;
			}
		}
	}
}

void tablica_powrotu(char* tab, char x) {
	for (int j = 0; j < 9; j++) {
		tab[j] = tab[j + 1];
	}
	tab[9] = x;
}

char dekoder(short x) {
	char x1;
	switch (x) {
	case 1: {
		x1 = 219;
		break;
	}
	case 2: {
		x1 = 176;
		break;
	}
	case 3: {
		x1 = 177;
		break;
	}
	case 4: {
		x1 = 1;
		break;
	}
	case 5: {
		x1 = 3;
		break;
	}
	case 6: {
		x1 = 3;
		break;
	}
	case 7: {
		x1 = 4;
		break;
	}
	case 8: {
		x1 = 4;
		break;
	}
	case 9: {
		x1 = 5;
		break;
	}
	case 0: {
		x1 = 5;
		break;
	}
	case 10: {
		x1 = 6;
		break;
	}
	case 11: {
		x1 = 6;
		break;
	}
	case 12: {
		x1 = 80;
		break;
	}
	case -1: {
		x1 = 88;
		break;
	}
	default: {
		x1 = 0;
		break;
	}
	}
	return x1;
}

void wyswietlanie(short T[][15], int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (T[j][i] == 4) {
				cout << (char)176 << (char)1 << (char)176;
			}
			else if (T[j][i] == 6 || T[j][i] == 8 || T[j][i] == 0 || T[j][i] == 11) {
				cout << (char)218 << dekoder(T[j][i]) << (char)191;
			}
			else cout << dekoder(T[j][i]) << dekoder(T[j][i]) << dekoder(T[j][i]);
		}
		cout << endl;
		for (int j = 0; j < n; j++) {
			if (T[j][i] == 4) {
				cout << (char)218 << (char)193 << (char)191;
			}
			else if (T[j][i] == 6 || T[j][i] == 8 || T[j][i] == 0 || T[j][i] == 11) {
				cout << (char)192 << dekoder(T[j][i]) << (char)217;
			}
			else cout << dekoder(T[j][i]) << dekoder(T[j][i]) << dekoder(T[j][i]);
		}
		cout << endl;
	}
	for (int i = 0; i < 19 - m; i++) {
		cout << "\n";
	}
}

void zwyciestwo(int p, bool* b);

void przegrana(bool* b);

void menu_w_grze(bool* b, int p, int* min);

void graj(short T[][15], punkt pozycja, int m, int n, int min_kroki, int p, bool* b) {

	T[pozycja.x][pozycja.y] = 4;
	int m1 = m, n1 = n;
	char polecenie, C[10] = { 0,0,0,0,0,0,0,0,0,0 }, pchanie[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int i = 0, licznik_r = 0;
	bool czy_wygrana;
	for (int j = 0; j < 10; j++) {
		C[j] = 0;
		pchanie[j] = -2;
	}
	while (true) {
		system("cls");

		//***********************************************  warunki wygranej
		czy_wygrana = 0;
		for (int z = 0; z < m; z++) {
			for (int j = 0; j < n; j++) {
				if (czy_wygrana) break;
				if (T[j][z] == 6 || T[j][z] == 8 || T[j][z] == 0 || T[j][z] == 11) {
					czy_wygrana = 1;
				}
			}
		}
		if (!czy_wygrana) {
			system("cls");
			zwyciestwo(p, b);
		}
		if (min_kroki - i < 0) {
			system("cls");
			przegrana(b);
		}
		//********************************************************** zmmiana wygl¹du beczki
		m1 = m;
		n1 = n;
		if (podmien_beczke(T, 5, 6, &m1, &n1)) {
			T[n1][m1] = -1;
		}
		m1 = m;
		n1 = n;
		if (podmien_beczke(T, 7, 8, &m1, &n1)) {
			T[n1][m1] = -1;
		}
		m1 = m;
		n1 = n;
		if (podmien_beczke(T, 9, 0, &m1, &n1)) {
			T[n1][m1] = -1;
		}
		m1 = m;
		n1 = n;
		if (podmien_beczke(T, 10, 11, &m1, &n1)) {
			T[n1][m1] = -1;
		}

		//**********************************************************
		cout << "pozostale kroki: " << min_kroki - i << "\n";

		//**********************************************************
		wyswietlanie(T, m, n);

		//********************************************************** sterowanie
		cin >> polecenie;
		switch ((int)polecenie) {
		case 'w': {
			if (T[pozycja.x][pozycja.y - 1] != 1 && T[pozycja.x][pozycja.y - 1] != 0 && T[pozycja.x][pozycja.y - 1] != 6 && T[pozycja.x][pozycja.y - 1] != 8 && T[pozycja.x][pozycja.y - 1] != 11 && T[pozycja.x][pozycja.y - 1] != -1) {//czy nad tob¹ sciana lub otwor
				if (T[pozycja.x][pozycja.y - 1] == 5 || T[pozycja.x][pozycja.y - 1] == 7 || T[pozycja.x][pozycja.y - 1] == 9 || T[pozycja.x][pozycja.y - 1] == 10) {//czy nad tob¹ beczka
					if (T[pozycja.x][pozycja.y - 2] != 1) {//czy nad beczk¹ sciana
						if (T[pozycja.x][pozycja.y - 2] == 6 || T[pozycja.x][pozycja.y - 2] == 8 || T[pozycja.x][pozycja.y - 2] == 0 || T[pozycja.x][pozycja.y - 2] == 11) {
							T[pozycja.x][pozycja.y - 2] = 2;
						}
						tablica_powrotu(pchanie, T[pozycja.x][pozycja.y - 1]);
						swap(T[pozycja.x][pozycja.y - 1], T[pozycja.x][pozycja.y - 2]);
						swap(T[pozycja.x][pozycja.y], T[pozycja.x][pozycja.y - 1]);//je¿eli nie to zamieniamy miejscami beczke i przestrzeñ woln¹ nad ni¹ a potem ludzika i mirjsce gdzie wczeœniej sta³a beczka
						pozycja.y = pozycja.y - 1;

					}
				}
				else {
					swap(T[pozycja.x][pozycja.y], T[pozycja.x][pozycja.y - 1]);
					pozycja.y = pozycja.y - 1;//je¿eli nad tob¹ nie ma ani œciany ani beczki
					tablica_powrotu(pchanie, 0);
				}
			}
			break;
		}
		case 's': {
			if (T[pozycja.x][pozycja.y + 1] != 1 && T[pozycja.x][pozycja.y + 1] != 0 && T[pozycja.x][pozycja.y + 1] != 6 && T[pozycja.x][pozycja.y + 1] != 8 && T[pozycja.x][pozycja.y + 1] != 11 && T[pozycja.x][pozycja.y + 1] != -1) {
				if (T[pozycja.x][pozycja.y + 1] == 5 || T[pozycja.x][pozycja.y + 1] == 7 || T[pozycja.x][pozycja.y + 1] == 9 || T[pozycja.x][pozycja.y + 1] == 10) {
					if (T[pozycja.x][pozycja.y + 2] != 1) {
						if (T[pozycja.x][pozycja.y + 2] == 6 || T[pozycja.x][pozycja.y + 2] == 8 || T[pozycja.x][pozycja.y + 2] == 0 || T[pozycja.x][pozycja.y + 2] == 11) {
							T[pozycja.x][pozycja.y + 2] = 2;
						}
						tablica_powrotu(pchanie, T[pozycja.x][pozycja.y + 1]);
						swap(T[pozycja.x][pozycja.y + 1], T[pozycja.x][pozycja.y + 2]);
						swap(T[pozycja.x][pozycja.y], T[pozycja.x][pozycja.y + 1]);
						pozycja.y = pozycja.y + 1;
					}
				}
				else {
					swap(T[pozycja.x][pozycja.y], T[pozycja.x][pozycja.y + 1]);
					pozycja.y = pozycja.y + 1;
					tablica_powrotu(pchanie, 0);
				}
			}
			break;
		}
		case 'd': {
			if (T[pozycja.x + 1][pozycja.y] != 1 && T[pozycja.x + 1][pozycja.y] != 0 && T[pozycja.x + 1][pozycja.y] != 6 && T[pozycja.x + 1][pozycja.y] != 8 && T[pozycja.x + 1][pozycja.y] != 11 && T[pozycja.x + 1][pozycja.y] != -1) {
				if (T[pozycja.x + 1][pozycja.y] == 5 || T[pozycja.x + 1][pozycja.y] == 7 || T[pozycja.x + 1][pozycja.y] == 9 || T[pozycja.x + 1][pozycja.y] == 10) {
					if (T[pozycja.x + 2][pozycja.y] != 1) {
						if (T[pozycja.x + 2][pozycja.y] == 6 || T[pozycja.x + 2][pozycja.y] == 8 || T[pozycja.x + 2][pozycja.y] == 0 || T[pozycja.x + 2][pozycja.y] == 11) {
							T[pozycja.x + 2][pozycja.y] = 2;
						}
						tablica_powrotu(pchanie, T[pozycja.x + 1][pozycja.y]);
						swap(T[pozycja.x + 1][pozycja.y], T[pozycja.x + 2][pozycja.y]);
						swap(T[pozycja.x][pozycja.y], T[pozycja.x + 1][pozycja.y]);
						pozycja.x = pozycja.x + 1;

					}
				}
				else {
					swap(T[pozycja.x][pozycja.y], T[pozycja.x + 1][pozycja.y]);
					pozycja.x = pozycja.x + 1;
					tablica_powrotu(pchanie, 0);
				}
			}
			break;
		}
		case 'a': {
			if (T[pozycja.x - 1][pozycja.y] != 1 && T[pozycja.x - 1][pozycja.y] != 0 && T[pozycja.x - 1][pozycja.y] != 6 && T[pozycja.x - 1][pozycja.y] != 8 && T[pozycja.x - 1][pozycja.y] != 11 && T[pozycja.x - 1][pozycja.y] != -1) {
				if (T[pozycja.x - 1][pozycja.y] == 5 || T[pozycja.x - 1][pozycja.y] == 7 || T[pozycja.x - 1][pozycja.y] == 9 || T[pozycja.x - 1][pozycja.y] == 10) {
					if (T[pozycja.x - 2][pozycja.y] != 1) {
						if (T[pozycja.x - 2][pozycja.y] == 6 || T[pozycja.x - 2][pozycja.y] == 8 || T[pozycja.x - 2][pozycja.y] == 0 || T[pozycja.x - 2][pozycja.y] == 11) {
							T[pozycja.x - 2][pozycja.y] = 2;
						}
						tablica_powrotu(pchanie, T[pozycja.x - 1][pozycja.y]);
						swap(T[pozycja.x - 1][pozycja.y], T[pozycja.x - 2][pozycja.y]);
						swap(T[pozycja.x][pozycja.y], T[pozycja.x - 1][pozycja.y]);
						pozycja.x = pozycja.x - 1;

					}
				}
				else {
					swap(T[pozycja.x][pozycja.y], T[pozycja.x - 1][pozycja.y]);
					pozycja.x = pozycja.x - 1;
					tablica_powrotu(pchanie, 0);
				}
			}
			break;
		}
				//menu w grze
		case 'q': {
			i--;
			menu_w_grze(b, p, &min_kroki);
			break;
		}


		}

		if (polecenie != 'r' && polecenie != 'u' && polecenie != 'q') {
			licznik_r = 0;
			tablica_powrotu(C, polecenie);
			i++;
		}
		//***********************************

	}
}


void poz(int p, bool* b) {
	punkt pozycja;
	int  m, n;
	short x;
	short T[50][15];
	int i = 0, j = 0, min_kroki;
	switch (p) {
	case 1: {
		min_kroki = 20;
		pozycja.x = 1;
		pozycja.y = 1;
		ifstream mapa("mapa1.txt");
		mapa >> m;
		mapa >> n;
		while (j < m) {
			i = 0;
			while (i < n) {
				mapa >> x;
				T[i][j] = x;
				i++;
			}
			j++;
		}
		mapa.close();

		break;
	}
	case 2: {
		min_kroki = 34;
		pozycja.x = 1;
		pozycja.y = 7;
		ifstream mapa("mapa2.txt");
		mapa >> m;
		mapa >> n;
		while (j < m) {
			i = 0;
			while (i < n) {
				mapa >> x;
				T[i][j] = x;
				i++;
			}
			j++;
		}
		mapa.close();
		break;
	}

	case 3: {
		min_kroki = 25;
		pozycja.x = 1;
		pozycja.y = 1;
		ifstream mapa("mapa3.txt");
		mapa >> m;
		mapa >> n;
		while (j < m) {
			i = 0;
			while (i < n) {
				mapa >> x;
				T[i][j] = x;
				i++;
			}
			j++;
		}

		break;
		mapa.close();
	}
	case 4: {
		min_kroki = 6;
		pozycja.x = 1;
		pozycja.y = 1;
		ifstream mapa("mapa4.txt");
		mapa >> m;
		mapa >> n;
		while (j < m) {
			i = 0;
			while (i < n) {
				mapa >> x;
				T[i][j] = x;
				i++;
			}
			j++;
		}
		mapa.close();

		break;
	}
	}
	graj(T, pozycja, m, n, min_kroki, p, b);
}

void menu(bool* dostep) {
	system("cls");
	short x;

	cout
		<< "\tKamil Wlodarczyk 193479 PREZENTUJE:\n"
		<< "\t  _____   ___    __  _    ___    ____     ____   ____  \n"
		<< "\t / ___/  /   \\  |  |/ ]  /   \\  |    \\   /    | |    \\ \n"
		<< "\t(   \\_  |     | |  ' /  |     | |  o  ) |  o  | |  _  |\n"
		<< "\t \\__  | |  O  | |    \\  |  O  | |     | |     | |  |  |\n"
		<< "\t /  \\ | |     | |     \\ |     | |  O  | |  _  | |  |  |\n"
		<< "\t \\    | |     | |  .  | |     | |     | |  |  | |  |  |\n"
		<< "\t  \\___|  \\___/  |__|\\_|  \\___/  |_____| |__|__| |__|__|\n\n\n";
	cout << "1-NOWA GRA\n2-WYBOR POZIOMOW\n";
	while (cin >> x) {
		if (x == 21) {
			dostep[1] = 1;
			dostep[2] = 1;

		}

		if (x == 1) {
			poz(1, dostep);
		}
		if (x == 2) {
			cout << "\n\nWPISZ NUMER POZIOMU 1-4\n";
			while (cin >> x) {
				if (dostep[x - 1]) {
					poz(x, dostep);
				}
				else {
					if (x == 0) {
						break;
					}
					else {
						cout << "\nNIE MASZ DOSTEPU DO TEGO POZIOMU WYBIERZ INNY LUB KLIKNIJ 0 BY WROCIC DO MENU/n";
					}
				}
			}

		}
		if (x == 3) system("pause");
		cout << "\nPOWROT DO MENU\n";


		cout << "1-NOWA GRA\n2-WYBOR POZIOMOW\n";
	}
}


int main() {
	bool dostep[ilosc_poz] = { 1,0,0 };
	menu(dostep);
	return 0;
}

void zwyciestwo(int p, bool* b) {

	cout << "GRATKI! WYGRALES!\nODBLOKOWYWUJESZ POZIOM " << p + 1 << '\n';
	b[p] = 1;
	system("pause");
	cout << "\n\n\n\n\n\n\n\n\n";
	menu(b);
}

void przegrana(bool* b) {
	cout << "\n\n\n\n\n\n\n\n\n PRZEGRALES \nnacisnij cokolwiek\n";
	system("pause");
	cout << "\n\n\n\n\n\n\n\n\n";
	menu(b);
}

void menu_w_grze(bool* b, int p, int* min) {
	system("cls");
	bool czy = 0;
	short x;
	cout << "  _____   ____   ____  __ __ \n"
		<< " /     \\_/ __ \\ /    \\|  |  \\\n"
		<< "|  Y Y  \\  ___/|   |  \\  |  /\n"
		<< "|__|_|  /\\___  >___|  /____/ \n"
		<< "      \\/     \\/     \\/      \n";
	cout << "\n witaj w menu pauzy wybierz dzialanie:\n1-kontynuuj\n2-restartuj\n3-menu glowne\n";
	while (cin >> x) {

		switch (x) {
		case 21: {
			*min = 200;
			break;
		}
		case 1: {
			czy = 1;
			break;
		}
		case 2: {
			poz(p, b);
			break;
		}
		case 3: {
			menu(b);
			break;
		}
		default: {
			cout << "\nblad\n";
			break;
		}
		}
		if (czy) {
			break;
		}
	}

}
