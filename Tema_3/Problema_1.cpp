#include "iostream"
#include "fstream"
#include "string"
//#include "conio.h"		//am lucrat in Visual Studio CODE care afiseaza direct in terminal si nu aveam nevoie de _getch

using namespace std;

struct NOD
{
	int info;
	NOD *next;
};

struct STIVA
{
	NOD *varf;
	STIVA()
	{
		varf = nullptr;
	}

	int TOP()
	{
		return varf->info;
	}

	bool ISEMPTY()
	{
		return varf == nullptr;
	}

	void PUSH(int k)
	{
		NOD *x = new NOD;
		x->info = k;
		x->next = varf;
		varf = x;
	}

	void POP()
	{
		if (ISEMPTY())
			cout << "Stiva este goala";
		else
		{
			NOD *x = varf;
			varf = varf->next;
			delete x;
		}
	}
};

struct COADA
{
	int S_MAX, BEGIN, END;
	int *DATA;

	COADA()
	{
		BEGIN = END = -1;
		S_MAX;
	}

	bool isEmpty()
	{
		return (BEGIN == -1);
	}

	bool isFull()
	{
		return ((BEGIN == 0 && END == (S_MAX - 1)) || ((END + 1) % S_MAX == BEGIN));
	}

	int FRONT()
	{
		return DATA[BEGIN];
	}

	void PUSH(int k)
	{

		if (isFull())
			cout << "Coada este plina. ";
		else
		{
			if (isEmpty())
				BEGIN = 0;
			END = (END + 1) % S_MAX;
			DATA[END] = k;
		}
	}

	void POP()
	{
		if (isEmpty())
			cout << "Coada este goala. ";
		else if (BEGIN == END)
		{
			DATA[BEGIN] = 0;
			BEGIN = -1;
			END = -1;
		}
		else
		{
			DATA[BEGIN] = 0;
			BEGIN = (BEGIN + 1) % S_MAX;
		}
	}
};

class graf
{
private:
	int nrNod;
	int *lung;
	int **lista;

public:
	graf();
	void citireMatriceFisier(string);
	void citireListaAdiacenta(string);
	void afisareElement(int, int);
	void afisareLista();
	void inputNod(int &n);
	void verifDrum(int, int);
	void verifLant(int, int);
	~graf();
};

graf::graf()
{
	nrNod = 0;
	lung = nullptr;
	lista = nullptr;
}

void graf::citireMatriceFisier(string nfis)
{
	ifstream fisier(nfis);
	if (!fisier.is_open())
	{
		cerr << "Eroare! Nu am putut deschide '" << nfis << "' pt citire" << endl;
		//_getch();
		exit(1);
	}
	else
	{
		fisier >> nrNod;
		lung = new int[nrNod];
		int **mat = new int *[nrNod];
		for (int i = 0; i < nrNod; i++)
		{
			mat[i] = new int[nrNod];
			for (int j = 0; j < nrNod; j++)
			{
				fisier >> mat[i][j];
				cout << mat[i][j];
				if (mat[i][j] == 1)
					lung[i]++;
			}
			cout << endl;
		}
		cout << endl;

		lista = new int *[nrNod];
		for (int i = 0; i < nrNod; i++)
		{
			int ind = 0;
			lista[i] = new int[lung[i]];
			for (int j = 0; j < nrNod; j++)
			{
				if (mat[i][j] == 1)
				{
					lista[i][ind] = j;
					ind++;
				}
			}
		}

		for (int i = 0; i < nrNod; i++)
			delete[] mat[i];
		delete mat;
	}
}

void graf::citireListaAdiacenta(string nfis)
{
	ifstream fisier(nfis);
	if (!fisier.is_open())
	{
		cerr << "Eroare! Nu am putut deschide '" << nfis << "' pt citire" << endl;
		//_getch();
		exit(1);
	}
	else
	{
		fisier >> nrNod;
		lista = new int *[nrNod];
		lung = new int[nrNod];

		for (int i = 0; i < nrNod; i++)
		{
			fisier >> lung[i];
			lista[i] = new int[lung[i]];
			for (int j = 0; j < lung[i]; j++)
			{
				fisier >> lista[i][j];
			}
		}
		cout << endl;
	}
}

void graf::afisareElement(int i, int j)
{
	cout << lista[i][j];
}

void graf::afisareLista()
{
	for (int i = 0; i < nrNod; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < lung[i]; j++)
		{
			cout << lista[i][j] << ", ";
		}
		cout << endl;
	}
	cout << endl;
}

void graf::inputNod(int &n)
{
	float a;
	cin >> a;
	while (cin.fail() || a < 0 || a >= nrNod || a / int(a) > 1)
	{
		cout << "Introduceti un numar nod valid! (0-" << nrNod - 1 << ")" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> a;
	}
	n = int(a);
}

void graf::verifDrum(int x, int y)
{
	COADA c;
	STIVA s, afis;
	c.S_MAX = nrNod;
	c.DATA = new int[c.S_MAX];

	int *marcaj = new int[nrNod];
	for (int i = 0; i < nrNod; i++)
		marcaj[i] = 0;

	int ind = x; // Breadth First Search
	c.PUSH(ind);
	while (!c.isEmpty() && ind != y)
	{
		s.PUSH(ind);
		c.POP();
		for (int i = 0; i < lung[ind]; i++)
		{
			if (marcaj[lista[ind][i]] == 0)

				c.PUSH(lista[ind][i]);
		}
		marcaj[ind] = 1;
		if (!c.isEmpty())
			ind = c.FRONT();
	}

	if (ind == y)
	{
		cout << endl
			 << "Intre " << x << " si " << y << " exista drum: ";

		afis.PUSH(ind);
		while (!s.ISEMPTY())
		{
			for (int i = 0; i < lung[s.TOP()]; i++)
			{
				if (ind == lista[s.TOP()][i]) // daca s.TOP este parinte lui ind adica daca ind se afla pe lista lui s.TOP
				{
					ind = s.TOP();
					afis.PUSH(ind);
				}
			}
			if (ind != s.TOP()) // daca ind NU se afla pe lista lui s.TOP
			{
				s.POP();
				ind = s.TOP();
				afis.PUSH(ind);
			}

			s.POP();
		}

		while (!afis.ISEMPTY())
		{
			cout << afis.TOP() << "-";
			afis.POP();
		}
		cout << "\b ";
	}
	else
	{
		cout << endl
			 << "Intre " << x << " si " << y << " NU exista drum.";
	}

	delete[] c.DATA;
	delete[] marcaj;
}

void graf::verifLant(int x, int y)
{
	COADA c;
	STIVA s, afis;
	int l, e;
	c.S_MAX = nrNod;
	c.DATA = new int[c.S_MAX];

	int *marcaj = new int[nrNod];
	for (int i = 0; i < nrNod; i++)
		marcaj[i] = 0;

	int ind = x;
	c.PUSH(ind);
	while (!c.isEmpty() && ind != y)
	{
		s.PUSH(ind);
		c.POP();
		for (int i = 0; i < lung[ind]; i++) //cazul cu arc direct
		{
			if (marcaj[lista[ind][i]] == 0)

				c.PUSH(lista[ind][i]);
		}
		marcaj[ind] = 1;

		for (int i = 0; i < nrNod; i++) //cazul cu arc invers
		{
			for (int j = 0; j < lung[i]; j++)
			{
				if (lista[i][j] == ind && marcaj[i] == 0)
				{
					c.PUSH(i);
					marcaj[i] = 2;
				}
			}
		}

		if (!c.isEmpty())
			ind = c.FRONT();
	}

	if (ind == y)
	{
		cout << endl
			 << "Intre " << x << " si " << y << " exista lant: ";

		afis.PUSH(ind);
		while (!s.ISEMPTY())
		{

			for (int i = 0; i < lung[s.TOP()]; i++)
			{
				if (ind == lista[s.TOP()][i]) // daca exista legatura directa
				{
					ind = s.TOP();
					afis.PUSH(ind);
				}
			}

			for (int i = 0; i < lung[ind]; i++)
			{
				if (s.TOP() == lista[ind][i]) // daca exista legatura inversa
				{
					ind = s.TOP();
					afis.PUSH(ind);
				}
			}

			if (ind != s.TOP()) // daca nu este legatura
			{
				s.POP();
				ind = s.TOP();
				afis.PUSH(ind);
			}

			s.POP();
		}

		while (!afis.ISEMPTY())
		{
			cout << afis.TOP() << "-";
			afis.POP();
		}
		cout << "\b ";
	}

	else
	{
		cout << endl
			 << "Intre " << x << " si " << y << " NU exista lant." << endl;
	}
	cout << endl;

	delete[] c.DATA;
	delete[] marcaj;
}

graf::~graf()
{
	for (int i = 0; i < nrNod; i++)
		delete[] lista[i];
	delete[] lung;
}

void afisareProblema()
{
	cout << endl
		 << "------------------------------------TEMA NR. 3.1------------------------------------" << endl
		 << "Se considera un graf orientat G = (N, A) memorat prin liste de adiacenta. " << endl
		 << "Sa se verifice pentru orice vârfuri x, y ∈ N daca exista drum de la x la y. (2p)" << endl
		 << "Sa se verifice daca exista lant de la x la y si în caz afirmativ sa se afiseze un" << endl
		 << "astfel de lant.(3p)." << endl
		 << "Se cere utilizarea unei structuri (sau clase) GRAF. " << endl
		 << endl
		 << endl
		 << "Programul a fost testat cu fisierele 'Problema_1_list.txt' si 'Problema_1_mat.txt'" << endl
		 << "Pentru introducerea unui nou graf, trebuie sa luati ca model aceste fisiere." << endl;
}

int main()
{
	afisareProblema();
	graf graf1;
	string nfis;

	cout << endl
		 << "Introduceti forma de citire a grafului orientat:" << endl
		 << "1 - citire din fisier matrice de adiacenta" << endl
		 << "2 - citire din fisier lista de adiacenta" << endl
		 << "0 - iesire" << endl;

	char op = 'x';
	while (op == 'x')
	{
		cin >> op;
		switch (op)
		{
		case '1':
		{
			cout << "Citire din: ";
			cin >> nfis;
			cout << endl
				 << "Matricea citita: " << endl;
			graf1.citireMatriceFisier(nfis);
			//graf1.citireMatriceFisier("Problema_1_mat.txt");
			break;
		}

		case '2':
		{
			cout << "Citire din: ";
			cin >> nfis;
			graf1.citireListaAdiacenta(nfis);
			//graf1.citireListaAdiacenta("Problema_1_list.txt");
			break;
		}

		case '0':
		{
			exit(1);
			break;
		}

		default:
		{
			cout << "Optiune invalida" << endl;
			op = 'x';
		}
		}
	}
	//graf1.citireListaAdiacenta("lista1.txt");			//scurtatura
	cout << "Lista de adiacenta: " << endl;
	graf1.afisareLista();
	int a, b;
	cout << "Dati nodurile intre care se cauta un drum: " << endl
		 << "x = ";
	graf1.inputNod(a);
	cout << "y = ";
	graf1.inputNod(b);
	graf1.verifDrum(a, b);
	graf1.verifLant(a, b);
	cout << "Varianta afisata poate nu este varianta cea mai scurta!" << endl
		 << "La revedere!" << endl;
	return 0;
	//_getch();
}
