#include "iostream"

class PRIORITY_QUEUE
{
private:
	int *DATA, d, SIZE, CAP;

public:
	PRIORITY_QUEUE(int capacitate = 50)
	{
		d = 2;
		CAP = capacitate;
		DATA = new int[CAP];
		SIZE = 0;
	}

	void SET_d(int);
	int GET_SIZE();
	int MAX_ELEMENT();
	int RANDOM_ELEMENT(int);
	void MAX_HEAPFY();
	void INCREASE_KEY(int, int);
	void INSERT(int);
	void EXTRACT_MAX();
	void PRINT_QUEUE();

	~PRIORITY_QUEUE()
	{
		delete[] DATA;
	}
};

void afisareProblema()
{
	std::cout << std::endl
			  << "------------------------------------TEMA NR. 4.1------------------------------------" << std::endl
			  << "Implementarea unui heap d-ar cu aceleasi operatii ca pentru heap-ul binar." << std::endl
			  << "Un heap d-ar este un arbore d-ar cu proprietatile de heap cunoscute. (2p)" << std::endl
			  << std::endl;
}

void citireNumarNatural(int &n)
{
	float a;
	std::cin >> a;
	while (std::cin.fail() || a < 0 || a / int(a) > 1)
	{
		std::cout << "Numarul introdus trebuie sa fie un numar natural!" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> a;
	}
	n = int(a);
}

void citireNumarIntreg(int &n)
{
	float a;
	std::cin >> a;
	while (std::cin.fail() || a / int(a) > 1)
	{
		std::cout << "Numarul introdus trebuie sa fie un numar intreg!" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "n=";
		std::cin >> a;
	}
	n = int(a);
}

void PRIORITY_QUEUE::SET_d(int k)
{
	d = k;
}

int PRIORITY_QUEUE::GET_SIZE()
{
	return SIZE;
}

int PRIORITY_QUEUE::MAX_ELEMENT()
{
	return DATA[0];
}

int PRIORITY_QUEUE::RANDOM_ELEMENT(int k)
{
	return DATA[k];
}

void PRIORITY_QUEUE::MAX_HEAPFY() // SIFT_DOWN (iterativ)
{
	int imax, aux, p, *copii;
	copii = new int[d];
	for (int i = (SIZE - 1) / d; i >= 0; i--)
	{
		imax = i;
		while (d * imax + 1 < SIZE) //cat timp imax are copii (nu este frunza)
		{
			p = imax;
			for (int j = 0; j < d; j++) //daca numarul copiilor e mai mic decat d, se compara si cu valorile mai mari decat size-ul (de aceea INT8_MIN in EXTRACT_MAX)
			{
				copii[j] = d * p + j + 1;
				if (copii[j] < SIZE && DATA[copii[j]] > DATA[imax])
					imax = copii[j];
			}

			if (imax != p)
			{
				aux = DATA[imax];
				DATA[imax] = DATA[p];
				DATA[p] = aux;
			}
			else
				break;
		}
	}
	delete[] copii;
}

void PRIORITY_QUEUE::INCREASE_KEY(int i, int val)
{
	if (val < DATA[i])
		std::cout << "Valoare prea mica!";
	else
	{
		DATA[i] = val;
		int p = (i - 1) / d;
		while (i > 0 && DATA[p] < val)
		{
			DATA[i] = DATA[p];
			i = p;
			p = (i - 1) / d;
		}
		DATA[i] = val;
	}
}

void PRIORITY_QUEUE::INSERT(int a)
{
	DATA[SIZE] = a;
	//MAX_HEAPFY();	//merge si cu aceasta functie
	INCREASE_KEY(SIZE, a);
	SIZE++;
}

void PRIORITY_QUEUE::EXTRACT_MAX()
{
	if (SIZE < 1)
	{
		std::cout << "Coada este goala!" << std::endl;
		return;
	}
	else
	{
		DATA[0] = DATA[SIZE - 1];
		DATA[SIZE - 1] = INT8_MIN;
		SIZE--;
		MAX_HEAPFY();
	}
}

void PRIORITY_QUEUE::PRINT_QUEUE()
{
	std::cout << "Coada: ";
	for (int i = 0; i < SIZE; i++)
		std::cout << DATA[i] << ", ";
	std::cout << std::endl;
}

int main()
{

	PRIORITY_QUEUE coada;
	int d, op = 1;

	afisareProblema();

	std::cout << "Introduceti 'd'-ul pentru un arbore d-ar: " << std::endl
			  << "d=";
	citireNumarNatural(d);
	while (d == 0)
	{
		std::cout << "Numarul introdus nu poate sa fie 0! Reintroduceti!" << std::endl
				  << "d=";
		citireNumarNatural(d);
	}
	coada.SET_d(d);

	while (op != 0)
	{
		std::cout << std::endl
				  << "Optiuni:" << std::endl
				  << "1 - inserare un nou nod in coada" << std::endl
				  << "2 - extrage elementul de prioritate maxima" << std::endl
				  << "3 - returneaza elementul de prioritate maxima" << std::endl
				  << "4 - creste prioritatea unui nod" << std::endl
				  << "0 - iesire" << std::endl
				  << std::endl
				  << "Aleg: ";
		citireNumarNatural(op);

		switch (op)
		{
		case 1:
		{
			int nod;
			std::cout << "Valoarea nodului care se introduce in coada: ";
			citireNumarIntreg(nod);
			coada.INSERT(nod);
			coada.PRINT_QUEUE();
			break;
		}

		case 2:
		{
			coada.EXTRACT_MAX();
			coada.PRINT_QUEUE();
			break;
		}

		case 3:
		{
			std::cout << "Elementul de prioritate maxima este: " << coada.MAX_ELEMENT() << std::endl;
			coada.PRINT_QUEUE();
			break;
		}

		case 4:
		{
			int i, val;
			std::cout << "Nodul la care modificam prioritatea: (Numarul de ordine din coada, incepand de la 0):" << std::endl
					  << "i=";
			citireNumarNatural(i);
			while (i > coada.GET_SIZE() || i < 0)
			{
				std::cout << "Ati introdus o valoare gresita! Coda are " << coada.GET_SIZE() << " elemente!" << std::endl
						  << "Alegeti un numar intre 0 si " << coada.GET_SIZE() - 1 << " inclusiv!" << std::endl
						  << "i=";
				citireNumarNatural(i);
			}
			std::cout << "Valoarea curenta al nodului " << i << " este: " << coada.RANDOM_ELEMENT(i) << std::endl;
			std::cout << "Modificam la: ";
			citireNumarIntreg(val);
			coada.INCREASE_KEY(i, val);
			coada.PRINT_QUEUE();
			break;
		}

		case 0:
		{
			std::cout << "La revedere!" << std::endl;
			exit(0);
			break;
		}

		default:
		{
			std::cout << "Optiune invalida!" << std::endl
					  << "Aleg: ";
			op = 'x';
			break;
		}
		}
	}
	coada.PRINT_QUEUE();
	return 0;
}
