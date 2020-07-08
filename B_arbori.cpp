#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void citireGradMinim(int &n)
{
	float a;
	std::cin >> a;
	while (std::cin.fail() || a < 2 || a / int(a) > 1)
	{
		std::cout << "Numarul introdus trebuie sa fie un numar natural minim 2!" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> a;
	}
	n = int(a);
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

struct NOD
{
	int nr;
	char frunza;
	NOD *p;
	std::vector<int> chei;
	std::vector<NOD *> copii;

	NOD()
	{
		nr = 0;
		frunza = 'y';
		p = nullptr;
	}
};

class bArbore
{
private:
	int t; //gradul minim
	NOD *RADACINA;

public:
	bArbore(int T)
	{
		t = T;
		RADACINA = new NOD;
	}

	NOD *getRADACINA();
	int getFIRST();
	char ISEMPTY();
	NOD *SEARCH(NOD *, int k);
	void SPLIT(NOD *);
	void INSERT(int);
	int MAXIM(NOD *);
	int MINIM(NOD *);
	int PREDECESOR(NOD *, int);
	int SUCCESOR(NOD *, int);
	void ROTATIE_DR(NOD *, int);
	void ROTATIE_STG(NOD *, int);
	NOD *FUZIUNE(NOD *, int);
	void DELETE(NOD *, int);
	void afisarePeNiveluri();

	~bArbore()
	{
		delete RADACINA;
	}
};

NOD *bArbore::getRADACINA()
{
	return RADACINA;
}

int bArbore::getFIRST()
{
	return RADACINA->chei[0];
}

char bArbore::ISEMPTY()
{
	if (RADACINA->nr == 0)
		return 'y';
	else
		return 'n';
}

NOD *bArbore::SEARCH(NOD *x, int k) // pseudocod din curs
{
	int i = 0;
	while (i < x->nr && x->chei[i] < k)
		i++;
	if (i < x->nr && x->chei[i] == k) //daca am gasit cheia cautata return
		return x;
	else
	{
		if (x->frunza == 'y') //daca nu s-a gasit si e frunza return
			return nullptr;
		else
			return SEARCH(x->copii[i], k); //daca nu s-a gasit si nu e frunza recurzie in nodul urmator
	}
}

void bArbore::SPLIT(NOD *y)
{
	NOD *x, *z;
	z = new NOD;
	z->nr = t - 1;
	z->frunza = y->frunza;

	int i = (y->nr / 2 + 1); //setez i si j la jumatatea vectorului chei + 1
	int j = i;
	for (i; i < y->nr; i++)
		z->chei.push_back(y->chei[i]);				   //transfer partea dr la z
	y->chei.erase(y->chei.begin() + j, y->chei.end()); //sterg din y ceea ce am transferat

	if (y->frunza != 'y')
	{
		i = ((y->nr + 1) / 2); //setez i si j la jumatatea vectorului copii
		i = j;
		for (i; i < y->nr + 1; i++) //transfer partea dr la z
		{
			z->copii.push_back(y->copii[i]);
			y->copii[i]->p = z;
		}
		y->copii.erase(y->copii.begin() + j, y->copii.end()); //sterg din y ceea ce am transferat
	}
	y->nr = t - 1;

	int sus = y->chei[y->chei.size() - 1]; //ultimul ramas pe care aducem sus

	if (y == RADACINA)
	{
		y->p = new NOD;
		x = y->p;
		RADACINA = x;
		x->chei.push_back(sus);
		y->chei.pop_back();
		x->copii.push_back(y);
		x->copii.push_back(z);
		x->frunza = 'n';
		x->nr++;
	}
	else
	{
		x = y->p;
		i = 0;
		while (i < x->nr && x->chei[i] < sus) //caut locul lui "sus"
			i++;
		x->chei.insert(x->chei.begin() + i, sus);
		y->chei.pop_back();
		x->copii.insert(x->copii.begin() + i, y);
		x->copii.erase(x->copii.begin() + (i + 1));
		x->copii.insert(x->copii.begin() + (i + 1), z);
		x->nr++;
	}
	z->p = x;
}

void bArbore::INSERT(int cheieDeIns)
{
	NOD *curent = RADACINA;
	int i;
	while (curent->frunza != 'y')
	{
		if (curent->nr == (2 * t - 1))
		{
			SPLIT(curent);
			curent = curent->p;
		}
		//cauta copilul potrivit
		i = 0;
		while (i < curent->nr && curent->chei[i] < cheieDeIns)
			i++;
		curent = curent->copii[i];
	}
	//am ajuns la frunza si daca e full, trebuie sa facem SPLIT
	if (curent->nr == (2 * t - 1))
	{
		SPLIT(curent);
		curent = curent->p;
		i = 0;
		while (i < curent->nr && curent->chei[i] < cheieDeIns)
			i++;
		curent = curent->copii[i];
	}
	curent->chei.push_back(cheieDeIns);
	std::sort(curent->chei.begin(), curent->chei.end());
	curent->nr++;
}

int bArbore::MAXIM(NOD *maxDeLa)
{
	int max = maxDeLa->chei[maxDeLa->nr - 1];
	if (maxDeLa->frunza == 'y')
		return max;
	else
		MAXIM(maxDeLa->copii[maxDeLa->nr]);
}

int bArbore::MINIM(NOD *minDeLa)
{
	int min = minDeLa->chei[0];
	if (minDeLa->frunza == 'y')
		return min;
	else
		MINIM(minDeLa->copii[0]);
}

int bArbore::PREDECESOR(NOD *x, int k)
{
	NOD *y;
	int i = 0;
	while (i < x->nr && x->chei[i] < k)
		i++;
	if (x->frunza != 'y') //daca NU e frunza
		return MAXIM(x = x->copii[i]);
	else //daca e frunza (desi nu va fi cazul la stergere)
	{
		if (x->chei[0] != k) //daca nodul e frunza si are mai multe elemente (si k nu este elementul cel mai mic)
		{
			i = 0;
			while (i < x->nr && x->chei[i] < k)
				i++;
			return x->chei[i - 1]; //atunci predecesorul va fi cheia din stanga lui
		}
		else //daca nodul e frunza si are un singur element sau mai multe dar k este cel mai mic
		{
			y = x->p;								 //ma duc mai sus cu y
			while (y != nullptr && x == y->copii[0]) //cat timp x este copilul celui mai mic element din chei ma duc mai sus (poate pana la radacina)
			{
				x = y;
				y = y->p;
			}

			if (y == nullptr) //daca am ajuns la radacina
			{
				std::cout << "Elementul nu are predecesor!\n";
				return k;
			}
			else //cand am ajuns ca x sa nu fie copilul celui mai mic element din chei, returnez cheia vecina din stanga lui y
			{
				i = 0;
				while (i < y->nr && y->chei[i] < k)
					i++;
				return y->chei[i - 1];
			}
		}
	}
}

int bArbore::SUCCESOR(NOD *x, int k)
{
	NOD *y;
	int i = 0;
	while (i < x->nr && x->chei[i] < k)
		i++;
	if (x->frunza != 'y') //daca NU e frunza
		return MINIM(x = x->copii[i + 1]);
	else //daca e frunza (desi nu va fi cazul la stergere)
	{
		if (x->chei[x->nr - 1] != k) //daca nodul e frunza si are mai multe elemente (si k nu este elementul cel mai mare)
		{
			i = 0;
			while (i < x->nr && x->chei[i] < k)
				i++;
			return x->chei[i + 1]; //atunci succesorul va fi cheia din dreapta lui
		}
		else //daca nodul e frunza si are un singur element sau mai multe dar k este cel mai mare
		{
			y = x->p;									 //ma duc mai sus cu y
			while (y != nullptr && x == y->copii[y->nr]) //cat timp x este copilul celui mai mare element din chei ma duc mai sus (poate pana la radacina)
			{
				x = y;
				y = y->p;
			}

			if (y == nullptr) //daca am ajuns la radacina
			{
				std::cout << "Elementul nu are succesor!\n";
				return k;
			}
			else //cand am ajuns ca x sa nu fie copilul celui mai mare element din chei, returnez cheia vecina din dreapta lui y
			{
				i = 0;
				while (i < y->nr && y->chei[i] < k)
					i++;
				return y->chei[i];
			}
		}
	}
}

void bArbore::ROTATIE_DR(NOD *x, int k)
{
	int i = 0;
	while (i < x->nr && x->chei[i] < k)
		i++;
	x->copii[i + 1]->chei.insert(x->copii[i + 1]->chei.begin(), k); // nodul din varf aduc la copil dreapta
	if (x->copii[i]->frunza != 'y')
	{
		x->copii[i + 1]->copii.insert(x->copii[i + 1]->copii.begin(), x->copii[i]->copii[x->copii[i]->nr]); // copilul copilului din stanga ancorez de noul nod din dreapta (adusa din varf)
		x->copii[i]->copii[x->copii[i]->nr]->p = x->copii[i + 1];											//setez ca parintele acestuia nodul adusa din varf
		x->copii[i]->copii.pop_back();																		//sterg ulimul copil al copilului din stanga
	}
	x->chei[i] = x->copii[i]->chei[x->copii[i]->nr - 1]; //aduc cheia maxima din nodul stang, in locul varfului
	x->copii[i]->chei.pop_back();						 //sterg ulima cheie din stanga

	x->copii[i]->nr--;
	x->copii[i + 1]->nr++;
}

void bArbore::ROTATIE_STG(NOD *x, int k)
{
	int i = 0;
	while (i < x->nr && x->chei[i] < k)
		i++;
	x->copii[i]->chei.insert(x->copii[i]->chei.end(), k); // nodul din varf aduc la copil stanga
	if (x->copii[i + 1]->frunza != 'y')
	{
		x->copii[i]->copii.insert(x->copii[i]->copii.end(), x->copii[i + 1]->copii[0]); // copilul copilului din dreapta ancorez de noul nod din stanga (adusa din varf)
		x->copii[i + 1]->copii[0]->p = x->copii[i];										//setez ca parintele acestuia nodul adusa din varf
		x->copii[i + 1]->copii.erase(x->copii[i + 1]->copii.begin());					//sterg primul copil din dreapta
	}
	x->chei[i] = x->copii[i + 1]->chei[0];						//aduc cheia minima din nodul drept, in locul varfului
	x->copii[i + 1]->chei.erase(x->copii[i + 1]->chei.begin()); //sterg prima cheie din stanga

	x->copii[i]->nr++;
	x->copii[i + 1]->nr--;
}

NOD *bArbore::FUZIUNE(NOD *x, int k)
{
	int i = 0;
	while (i < x->nr && x->chei[i] < k)
		i++;
	x->copii[i]->chei.push_back(x->chei[i]); //inserez in copil stang cheia din varf
	x->copii[i]->nr++;

	int j = 0;
	while (j < x->copii[i + 1]->nr)
	{
		x->copii[i]->chei.push_back(x->copii[i + 1]->chei[j]); //transfer chei la stanga
		x->copii[i]->nr++;
		j++;
	}

	if (x->copii[i]->frunza != 'y') //daca copii care se fuzioneaza nu sunt frunze
	{
		j = 0;
		while (j < x->copii[i + 1]->nr + 1)
		{
			x->copii[i]->copii.push_back(x->copii[i + 1]->copii[j]); //transfer copii copiilor la stanga
			x->copii[i + 1]->copii[j]->p = x->copii[i];				 //setez parintii copiilor sa fie nodul stanga
			j++;
		}
	}

	x->chei.erase(x->chei.begin() + i); //sterg cheia din varf
	x->nr--;
	delete x->copii[i + 1];						//stergere nod din dreapta
	x->copii.erase(x->copii.begin() + (i + 1)); //stergere pointer aferent

	if (x == RADACINA && x->nr == 0) //daca dispare radacina
	{
		NOD *aux;
		RADACINA = x->copii[i]; //radacina noua = copilul stang
		x->copii[i]->p = nullptr;
		aux = x->copii[i];
		delete x;
		x = aux;
	}
	return x;
}

void bArbore::DELETE(NOD *curent, int k)
{
	NOD *frate = nullptr;
	NOD *gasit = nullptr;

	int i = 0;
	while (i < curent->nr && curent->chei[i] != k) //caut k in nodul curent
		i++;
	if (i < curent->nr && curent->chei[i] == k)
		gasit = curent;

	if (gasit == curent && curent->frunza == 'y') //Cazul 1: daca k e in nodul curent si nodul curent este frunza
	{
		curent->chei.erase(curent->chei.begin() + i);
		curent->nr--;
	}
	else
	{
		if (gasit == curent && curent->frunza != 'y') //cazul 2: daca x nu e frunza dar k se afla in x
		{
			if (curent->copii[i]->nr >= t)
			{
				int kp = PREDECESOR(curent, curent->chei[i]);
				curent->chei[i] = kp;
				DELETE(curent->copii[i], kp);
			}
			else if (curent->copii[i + 1]->nr >= t)
			{
				int ks = SUCCESOR(curent, curent->chei[i]);
				curent->chei[i] = ks;
				DELETE(curent->copii[i + 1], ks);
			}
			else
			{
				curent = FUZIUNE(curent, curent->chei[i]);
				DELETE(curent, k);
			}
		}
		else if (curent->frunza != 'y' && gasit != curent) //cazul 3: daca x nu e frunza si daca k nu e in x
		{
			i = 0;
			while (i < curent->nr && curent->chei[i] < k)
				i++;
			if (curent->copii[i]->nr < t) // copilul i are prea putine elemente
			{
				if (i > 0 && curent->copii[i - 1]->nr > (t - 1)) //daca are cel putin o frate la partea stanga si daca acesta are mai multe chei decat minimul
				{
					ROTATIE_DR(curent, curent->chei[i - 1]); //rotatie (nod, cheie)
					curent = curent->copii[i];
				}
				else if (i < curent->nr && curent->copii[i + 1]->nr > (t - 1)) //daca are cel putin o frate la partea dreapta si daca acesta are mai multe chei decat minimul
				{
					ROTATIE_STG(curent, curent->chei[i]); //rotatie (nod, cheie)
					curent = curent->copii[i];
				}
				else //daca nici o rotatie nu merge urmeaza fuziunea
				{
					if (i == curent->nr) // daca mergem spre ultimul copil
						curent = FUZIUNE(curent, curent->chei[i - 1]);
					else
						curent = FUZIUNE(curent, curent->chei[i]);
				}
			}
			else
				curent = curent->copii[i];
			DELETE(curent, k);
		}
	}
}

void bArbore::afisarePeNiveluri() //afisare pe niveluri
{
	std::queue<NOD *> coada;
	NOD *curent = RADACINA;
	coada.push(curent);
	while (!coada.empty())
	{
		std::cout << "{ ";
		for (int i = 0; i < curent->chei.size(); i++)
			std::cout << coada.front()->chei[i] << " ";
		if (!curent->copii.empty())
			for (int i = 0; i < curent->copii.size(); i++)
				coada.push(curent->copii[i]);
		coada.pop();
		if (!coada.empty())
			curent = coada.front();
		std::cout << "} ";
	}
}

int main()
{
	int grad;
	std::cout << "Gradul minim: ";
	citireGradMinim(grad);

	bArbore B(grad);

	char op = 'a';
	while (op != 'x')
	{
		std::cout << std::endl
				  << "Optiuni:" << std::endl
				  << "1 - inserare nod" << std::endl
				  << "2 - citire din vector (vector din cod: linia 520)" << std::endl
				  << "3 - cautare nod" << std::endl
				  << "4 - stergere nod" << std::endl
				  << "5 - golire" << std::endl
				  << "6 - afisare arbore (afisare pe niveluri)" << std::endl
				  << "7 - afisare minim/maxim" << std::endl
				  << "8 - afisare predecesor/succesor" << std::endl
				  << "0 - iesire" << std::endl
				  << std::endl;

		std::cout << "Aleg: ";
		std::cin >> op;

		switch (op)
		{
		case '1':
		{
			int ch;
			std::cout << "Dati cheia care vreti sa inserati: ";
			citireNumarNatural(ch);
			B.INSERT(ch);
			break;
		}

		case '2':
		{
			std::vector<int> insert;
			insert = {10, 27, 9, 35, 30, 21, 14, 0, 1, 3};
			for (int i = 0; i < insert.size(); i++)
				B.INSERT(insert[i]);
			break;
		}

		case '3':
		{

			int ch2;
			std::cout << "Dati cheia care cautati: ";
			citireNumarNatural(ch2);

			if (B.SEARCH(B.getRADACINA(), ch2) == nullptr)
				std::cout << "Cheia NU se gaseste in arbore!\n";
			else
				std::cout << "Cheia se gaseste in arbore!\n";
			break;
		}

		case '4':
		{
			int ch3;
			std::cout << "Dati cheia care vreti sa stergeti: ";
			citireNumarNatural(ch3);
			if (B.SEARCH(B.getRADACINA(), ch3) == nullptr)
				std::cout << "Cheia NU se gaseste in arbore!\n";
			else
				B.DELETE(B.getRADACINA(), ch3);
			break;
		}

		case '5':
		{
			while (B.ISEMPTY() == 'n')
				B.DELETE(B.getRADACINA(), B.getFIRST());
			break;
		}

		case '6':
		{
			std::cout << "Pe niveluri: ";
			B.afisarePeNiveluri();
			break;
		}

		case '7':
		{
			int ch7;
			std::cout << "Dati o cheie care se afla in nodul de la care vreti sa gasiti minimul/maximul: ";
			citireNumarNatural(ch7);
			std::cout << "Minim/Maxim: ";
			NOD *gasit = B.SEARCH(B.getRADACINA(), ch7);
			if (gasit == nullptr)
				std::cout << "Cheia NU se gaseste in arbore!\n";
			else
				std::cout << B.MINIM(gasit) << "/" << B.MAXIM(gasit);
			break;
		}

		case '8':
		{
			int ch8;
			std::cout << "Dati o cheie la care se cauta predecesorul/succesorul: ";
			citireNumarNatural(ch8);
			std::cout << "Predecesor/Succesor: ";
			NOD *gasit = B.SEARCH(B.getRADACINA(), ch8);
			if (gasit == nullptr)
				std::cout << "Cheia NU se gaseste in arbore!\n";
			else
				std::cout << B.PREDECESOR(gasit, ch8) << "/" << B.SUCCESOR(gasit, ch8);
			break;
		}

		case '0':
		{
			std::cout << std::endl
					  << "La revedere!" << std::endl;
			exit(1);
			break;
		}

		default:
		{
			std::cout << std::endl
					  << "Optiune invalida!" << std::endl;
		}
		}
	}
}