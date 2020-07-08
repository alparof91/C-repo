#include "iostream"
#include "fstream"

using namespace std;

struct graf1
{
	int **listeAdiacenta; //listele de adiacenta
	int nrNoduri;		  //nr de noduri din graf
	int *lungimiListe;	  //lungimile pentru fiecare lista de adiacenta

	void Citire(std::string fisier)
	{
		std::ifstream file(fisier);
		file >> nrNoduri;

		listeAdiacenta = new int *[nrNoduri];
		lungimiListe = new int[nrNoduri];

		for (int index = 0; index < nrNoduri; index++)
		{
			file >> lungimiListe[index];
			listeAdiacenta[index] = new int[lungimiListe[index]];
			for (int index2 = 0; index2 < lungimiListe[index]; index2++)
			{
				file >> listeAdiacenta[index][index2]; // index = nodul pentru care citesc lista de adiacenta, index2 = al catelea succesor se citeste
			}
		}
	}
	void PrintListe()
	{
		for (int index = 0; index < nrNoduri; index++)
		{
			std::cout << "lista nodului " << index << ": ";
			for (int index2 = 0; index2 < lungimiListe[index]; index2++)
			{
				std::cout << listeAdiacenta[index][index2] << ", ";
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	
	graf1 graf;
	string fis;
	cin >> fis;
	graf.Citire (fis);
	graf.PrintListe ();

	return 0;
}
