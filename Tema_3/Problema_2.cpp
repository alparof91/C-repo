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
	void citireListaAdiacenta(string);
	void afisareLista();
	void compConexe();
	~graf();
};

graf::graf()
{
	nrNod = 0;
	lung = nullptr;
	lista = nullptr;
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

void graf::compConexe()
{
	COADA c;
	STIVA s, afis;
	c.S_MAX = nrNod;
	c.DATA = new int[c.S_MAX];

	int marker = 1;
	bool test = false;
	int *marcaj = new int[nrNod];
	for (int i = 0; i < nrNod; i++)
		marcaj[i] = 0;

	int ind = 0; // Breadth First Search

	cout << "Componente conexe: " << endl;
	while (test == false)
	{
		test = true;
		c.PUSH(ind);
		while (!c.isEmpty())
		{
			c.POP();
			for (int i = 0; i < lung[ind]; i++) //cazul cu arc direct
			{
				if (marcaj[lista[ind][i]] == 0)

					c.PUSH(lista[ind][i]);
			}
			marcaj[ind] = marker;

			for (int i = 0; i < nrNod; i++) //cazul cu arc invers
			{
				for (int j = 0; j < lung[i]; j++)
				{
					if (lista[i][j] == ind && marcaj[i] == 0)
					{
						c.PUSH(i);
						marcaj[i] = marker;
					}
				}
			}

			if (!c.isEmpty())
				ind = c.FRONT();
		}

		cout << marker << ": ";
		for (int i = 0; i < nrNod; i++)
		{
			if (marcaj[i] == marker)
				cout << i << ",";
			else if (marcaj[i] == 0)
			{
				test = false;
				ind = i;
			}
		}
		cout << "\b " << endl;
		marker++;
	}
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
		 << "------------------------------------TEMA NR. 3.2------------------------------------" << endl
		 << "Se considera un graf orientat G = (N, A). Sa se determine câte componente" << endl
		 << "conexe are si pentru fiecare componenta, care sunt nodurile pe care le contine." << endl
		 << "Se cere utilizarea unei structuri (sau clase) GRAF.(2p)" << endl
		 << endl
		 << endl
		 << "Programul a fost testat cu fisierul 'Problema_2.txt'" << endl
		 << "Pentru introducerea unui nou graf, trebuie sa luati ca model acest fisier." << endl;
}

int main()
{
	afisareProblema();
	graf graf1;
	string nfis;

	cout << endl
		 << "Citire din: ";

	cin >> nfis;
	graf1.citireListaAdiacenta(nfis);
	// graf1.citireListaAdiacenta("Problema_2.txt");

	cout << "Lista de adiacenta: " << endl;
	graf1.afisareLista();

	graf1.compConexe();

	cout << endl
		 << "La revedere!" << endl;
	return 0;
	//_getch();
}