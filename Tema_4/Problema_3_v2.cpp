#include "iostream"
#include <string>
#include "fstream"
#include "vector"

struct tabelaCod //pentru tabela Cod
{
	char car;
	std::string cod;
};

struct heapNode
{
	std::string info;
	int frecv;
	heapNode *stg, *dr;

	heapNode()
	{
		info = "";
		frecv = 1;
		stg = nullptr;
		dr = nullptr;
	}
};

class MIN_PRIORITY_QUEUE
{
private:
	int SIZE, CAP;
	heapNode *DATA;

public:
	MIN_PRIORITY_QUEUE(int capacitate = 50)
	{
		CAP = capacitate;
		DATA = new heapNode[CAP];
		SIZE = 0;
	}

	void citireFisier(std::string);
	int GET_SIZE();
	struct heapNode MIN_ELEMENT();
	void HEAPFY();
	void INSERT(heapNode);
	void EXTRACT_MIN();
	void PRINT_QUEUE();
	int eFrunza(heapNode *suma);
	void bTree();
	void printbTree(heapNode *suma, struct tabelaCod *coduri, int arr[], int top);

	~MIN_PRIORITY_QUEUE()
	{
		delete[] DATA;
	}
};

void afisareProblema()
{
	std::cout << std::endl
		<< "------------------------------------TEMA NR. 4.3------------------------------------" << std::endl
		<< "Se citeste un text dintr-un fisier. Sa se construiasca arborele de codificare" << std::endl
		<< "Huffmann corespunzator. Sa se afiseze codul corespunzator fiecarui caracter" << std::endl
		<< "si sa se codifica textul. Utilizati o coada de prioritate (min). (5p)" << std::endl
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

int MIN_PRIORITY_QUEUE::GET_SIZE()
{
	return SIZE;
}

struct heapNode MIN_PRIORITY_QUEUE::MIN_ELEMENT()
{
	return DATA[0];
}

void
MIN_PRIORITY_QUEUE::citireFisier(std::string nfis = "Problema_3.txt") //citire fisier pentru constructia heap-ului
{
	std::ifstream fisier(nfis);
	if (!fisier.is_open())
	{
		std::cerr << "Eroare! Nu am putut deschide '" << nfis << "' pt citire" << std::endl;
		//_getch();
		exit(1);
	}
	else
	{
		int i = 0, j, caracter;
		char *ASCII;
		ASCII = new char[128];
		char aux;
		std::string input;
		while (i < CAP && !fisier.eof())
		{
			fisier >> std::noskipws >> aux;
			if (aux == '\n') //pt newline caracter
				aux = '~';
			caracter = int(aux);
			if (ASCII[caracter] != 'p')
			{
				DATA[SIZE].info = aux;
				ASCII[caracter] = 'p';
				SIZE++;
			}
			else
			{
				j = 0;
				while (aux != DATA[j].info[0])
					j++;
				DATA[j].frecv++;
			}
			i++;
		}
		fisier.close();
		delete[] ASCII;
	}
}

std::string codificareFisier(struct tabelaCod *cod, int cap, std::string nfis = "Problema_3.txt")
{
	std::ifstream fisier(nfis);
	if (!fisier.is_open())
	{
		std::cerr << "Eroare! Nu am putut deschide '" << nfis << "' pt citire" << std::endl;
		//_getch();
		exit(1);
	}
	else
	{
		int i = 0;
		char aux;
		std::string input, output;
		while (input.length() < cap && !fisier.eof())
		{
			fisier >> std::noskipws >> aux;
			input += aux;
			i++;
		}
		std::cout << std::endl
			<< "Textul de codificat: " << std::endl
			<< input << std::endl;

		int k;
		for (int j = 0; j < input.length(); j++)
		{
			k = 0;
			while (input[j] != cod[k].car && k < cap - 1)
				k++;
			if (input[j] == cod[k].car)
			{
				output += cod[k].cod;
				output += ',';
			}
			else
			{
				output += input[j]; //pentru cazul in care traducerea se face pentru un text care contine si alte
				output += ',';      //caractere decat inclus in tabela de coduri (in accest program nu o sa fie cazul)
			}
		}
		std::cout << std::endl
			<< "Dupa codificare (cu virgule intre caractere):" << std::endl
			<< output << std::endl;
		fisier.close();
	}
}

void MIN_PRIORITY_QUEUE::HEAPFY()
{
	int imax, p, st, dr;
	heapNode aux;

	for (int i = (SIZE - 1) / 2; i >= 0; i--)
	{
		imax = i;
		while (2 * imax + 1 < SIZE) //cat timp imax are copii (nu este frunza)
		{
			p = imax;
			st = 2 * imax + 1;
			dr = 2 * imax + 2;

			if (st < SIZE && DATA[st].frecv < DATA[imax].frecv)
				imax = st;
			if (dr < SIZE && DATA[dr].frecv < DATA[imax].frecv)
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

void MIN_PRIORITY_QUEUE::INSERT(heapNode a)
{
	DATA[SIZE] = a;
	int k = SIZE;
	int p = (SIZE - 1) / 2;
	while (k > 0 && DATA[p].frecv > DATA[k].frecv)
	{
		DATA[k] = DATA[p];
		k = p;
		p = (k - 1) / 2;
	}
	DATA[k] = a;
	SIZE++;
}

void MIN_PRIORITY_QUEUE::EXTRACT_MIN()
{
	if (SIZE < 1)
	{
		std::cout << "Coada este goala!" << std::endl;
		return;
	}
	else
	{
		DATA[0] = DATA[SIZE - 1];
		DATA[SIZE - 1].info = 'X';
		DATA[SIZE - 1].frecv = 0;
		SIZE--;
		HEAPFY();
	}
}

void MIN_PRIORITY_QUEUE::PRINT_QUEUE()
{
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << DATA[i].info << "(" << DATA[i].frecv << "), ";
	}
	std::cout << std::endl;
}

void MIN_PRIORITY_QUEUE::bTree()
{
	heapNode **adrese = new heapNode *[CAP]; //vector de adrese pentru adresele nodurilor concatenate 
	for (int i = 0; i < CAP; i++)
		adrese[i] = nullptr;
	heapNode *stanga = nullptr, *dreapta = nullptr, *parinte = nullptr;
	while (SIZE != 1)
	{
		if (MIN_ELEMENT().info.length() == 1) //daca e frunza
			stanga = new heapNode(MIN_ELEMENT());
		else //altfel cauta adresa lui MIN_ELEMENT in array-ul de adrese
		{
			int i = 0;
			while (MIN_ELEMENT().info != adrese[i]->info)
				i++;
			stanga = adrese[i];
		}
		EXTRACT_MIN();

		if (MIN_ELEMENT().info.length() == 1) //daca e frunza
			dreapta = new heapNode(MIN_ELEMENT());
		else //altfel cauta adresa lui MIN_ELEMENT in vectorul de adrese
		{
			int i = 0;
			while (MIN_ELEMENT().info != adrese[i]->info)
				i++;
			dreapta = adrese[i];
		}
		EXTRACT_MIN();

		parinte = new heapNode();
		parinte->frecv = stanga->frecv + dreapta->frecv;
		parinte->info = stanga->info + dreapta->info;
		parinte->stg = stanga;
		parinte->dr = dreapta;

		int i = 0;
		while (adrese[i] != nullptr) //cauta primul loc liber in array-ul adrese si insereaza parinte
			i++;
		adrese[i] = parinte;

		INSERT(*parinte); //returnez suma in priority queue

		PRINT_QUEUE();
	}
}

void printArr(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		std::cout << arr[i];
	std::cout << std::endl;
}

std::string printArrToString(int arr[], int n)
{
	std::string cod;
	for (int i = 0; i < n; ++i)
		cod += std::to_string(arr[i]);
	return cod;
}

int MIN_PRIORITY_QUEUE::eFrunza(struct heapNode *suma)

{
	return !(suma->stg) && !(suma->dr);
}

void MIN_PRIORITY_QUEUE::printbTree(struct heapNode *nod, struct tabelaCod *coduri, int arr[], int curent = 0)
{
	static int i = 0;
	std::string aux;
	if (nod->stg)
	{

		arr[curent] = 0;
		printbTree(nod->stg, coduri, arr, curent + 1);
	}

	if (nod->dr)
	{

		arr[curent] = 1;
		printbTree(nod->dr, coduri, arr, curent + 1);
	}

	if (eFrunza(nod))
	{

		std::cout << nod->info << ": ";		//printez codul de tabele
		printArr(arr, curent);		//cand nodul curent ajunge la frunza deja arr[] contine codurile pentru info(litera) din frunza 
		aux = nod->info;        //pentru ca am definit coduri.car ca un char si nu ca string
		coduri[i].car = aux[0];     //coduri[i].car = nod->info
		coduri[i].cod = printArrToString(arr, curent);		//codurile le si salvez in tabela de coduri
		i++;
	}
}

int main()
{
	afisareProblema();
	int n;
	std::cout << "Cate litere sa codificam din fisierul text? n=";
	citireNumarNatural(n);			//definim capacitatea min-heapului
	MIN_PRIORITY_QUEUE coada(n);
	coada.citireFisier();						//citesc din fisier in coada.DATA in ordine statistica
	std::cout << std::endl
		<< "Caractere citite si frecventa lor:" << std::endl;
	coada.PRINT_QUEUE();
	std::cout << std::endl
		<< "Min-heap:" << std::endl;
	coada.HEAPFY();								//le aranjez in ordine min-heap 
	coada.PRINT_QUEUE();
	coada.bTree();          // se prelucreaza min-heapul: se scot stringurile cu frecventele minime si se insereaza concatenat impreuna cu frecventele adunate
	heapNode *radacina = new heapNode(coada.MIN_ELEMENT());     //initializez radacina si in main pentru printbTree
	int *arr = new int[n];              //un vector pentru a tine temporar codul pentru printbTree
	tabelaCod *codurile = new tabelaCod[n];             //pointer catre tabela de litera:cod pentru printbTree
	std::cout << std::endl
		<< "Tabela codurilor:" << std::endl;
	coada.printbTree(radacina, codurile, arr);

	// test pentru tabelaCod
	// for (int i = 0; i < n; i++)
	// 	std::cout << codurile[i].car << " : " << codurile[i].cod << std::endl;

	codificareFisier(codurile, n);			// cu ajutorul tabelei de cod, codific input-ul si printez
	std::cout << "La revedere!" << std::endl;

	delete[] codurile;
	delete[] arr;
	delete radacina;
	//_getch();
	return 0;
}
