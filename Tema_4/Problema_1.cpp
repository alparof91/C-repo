#include "iostream"

class PRIORITY_QUEUE
{
private:
	int *DATA, SIZE, CAP;

public:
	PRIORITY_QUEUE(int capacitate = 50)
	{
		CAP = capacitate;
		DATA = new int[CAP];
		SIZE = 0;
	}
	
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
			  << "Implementati o coada de prioritati folosind o structura PRIOROTY_QUEUE," << std::endl
			  << "care sa aiba un câmp DATA de tip vector de întregi, care sa stocheze elementele" << std::endl
			  << "cozii sub forma unui heap max si un câmp SIZE - nr. de elemente stocate în" << std::endl
			  << "coada. În plus structura trebuie sa aiba metodele:" << std::endl
			  << "• INSERT - insereaza un nou nod în coada (0.5 p)" << std::endl
			  << "• EXTRACT_MAX - extrage elementul de prioritate maxima din coada (0.5 p)" << std::endl
			  << "• MAX_ELEMENT - returneaza elementul de prioritate maxima (0.5 p)" << std::endl
			  << "• INCREASE_KEY - creste prioritatea unui nod.(0.5 p)" << std::endl
			  << "• MAX_HEAPFY (sau SIFT_DOW) - functia care coboara o cheie pe" << std::endl
			  << "pozitia corespunzatoare din heap. (0.5 p)" << std::endl
			  << "Structura trebuie sa dispuna de constructor. (0.5 p). În functia main se" << std::endl
			  << "declara o variabila de tip PRIORITY_QUEUE si se foloseste un meniu implementat" << std::endl
			  << "cu ajutorul unei instructiuni switch, prin care utilizatorul sa poata" << std::endl
			  << "selecta oricare dintre operatiile de insertie, extragerea maximului, obtinerea" << std::endl
			  << "maximului si afisarea elementelor din heap. (1 p)" << std::endl
			  << std::endl;
}
void citireNumarNatural(int &n)
{
	float a;
	std::cin >> a;
	while (std::cin.fail() || a < 0 || a / int(a) > 1)
	{
		std::cout << "Numarul introdus trebuie sa fie natural!" << std::endl;
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
		std::cout << "Numarul introdus trebuie sa fie intreg!" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "n=";
		std::cin >> a;
	}
	n = int(a);
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
	int imax, aux, p, st, dr;
	for (int i = (SIZE - 1) / 2; i >= 0; i--)
	{
		imax = i;
		while (2 * imax + 1 < SIZE) //cat timp imax are copii (nu este frunza)
		{
			p = imax;
			st = 2 * imax + 1;
			dr = 2 * imax + 2;

			if (st < SIZE && DATA[st] > DATA[imax])
				imax = st;
			if (dr < SIZE && DATA[dr] > DATA[imax])
				imax = dr;
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
}

void PRIORITY_QUEUE::INCREASE_KEY(int k, int val)
{
	DATA[k] = val;
	int p = (k - 1) / 2;
	while (k > 0 && DATA[p] < val)
	{
		DATA[k] = DATA[p];
		k = p;
		p = (k - 1) / 2;
	}
	DATA[k] = val;
}

void PRIORITY_QUEUE::INSERT(int a)
{
	DATA[SIZE] = a;
	//MAX_HEAPFY();
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
		DATA[SIZE - 1] = 0;
		SIZE--;
		MAX_HEAPFY();
	}
}

void PRIORITY_QUEUE::PRINT_QUEUE()
{
	for (int i = 0; i < SIZE; i++)
		std::cout << DATA[i] << ", ";
	std::cout << std::endl;
}

int main()
{
	PRIORITY_QUEUE coada;
	int op = 1;

	afisareProblema();

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
			std::cout << "Nodul la care modificam prioritatea (numarul de ordine din coada): ";
			citireNumarNatural(i);
			while (i > coada.GET_SIZE() || i < 0)
			{
				std::cout << "Ati introdus o valoare gresita! Coda are " << coada.GET_SIZE() << " elemente!" << std::endl
						  << "Alegeti un numar intre 0 si " << coada.GET_SIZE() - 1 << " inclusiv!" << std::endl;
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
