#include <fstream>
#define MAX_N 5000
#define MAX_NR 1000
using namespace std;
void citesteDateleDeIntrare(int & P, int & N, int & K, int A[]);
bool esteSecventaCool(int vector[], int pozitieInceput, int lungime, int & maxim, int & nrValoriDistincte);
int main()
{
	int P, N, K, A[MAX_N];
	citesteDateleDeIntrare(P, N, K, A);
	ofstream scrie("cool.out");
	if (P == 1)
	{
		int maxim, nrValoriDistincte;
		if(esteSecventaCool(A, 0, K, maxim, nrValoriDistincte))
			scrie << maxim;
		else
			scrie << nrValoriDistincte;
	}
	else
	{
		int nrSecvente, lungimeMaxima;
		bool amGasitSolutie;
		nrSecvente = lungimeMaxima = amGasitSolutie = 0;
		for (int lungime = N; lungime >= 1 && !amGasitSolutie; lungime--)
			for (int i = 0; i <= N-lungime; i++)
			{
				int maxim, nrValoriDistincte;
				if (esteSecventaCool(A, i, lungime, maxim, nrValoriDistincte))
				{
					nrSecvente++;
					if(!lungimeMaxima)
						lungimeMaxima = lungime;
					if (!amGasitSolutie)
						amGasitSolutie = 1;
				}
			}
		scrie << lungimeMaxima << '\n';
		scrie << nrSecvente;
	}
	scrie.close();
	return 0;
}
bool esteSecventaCool(int vector[], int pozitieInceput, int lungime, int & maxim, int & nrValoriDistincte)
{
	// verifica daca secventa care incepe la pozitia 'pozitieInceput'
	// de lungime 'lungime' din vectorul 'vector' este o secventa cool
	// si furnizeaza valoarea maxima, respectiv numarul de valori
	// distincte din secventa prin parametrii 'maxim' si 'nrValoriDistincte'
	if (lungime == 1)
	{
		maxim = vector[pozitieInceput];
		nrValoriDistincte = 1;
		return 1;
	}
	else
	{
		int frecventa[MAX_NR+1], esteNevoieDe[MAX_NR+1];
		int i, minim;
		bool esteCool = 1;
		for (i = 0; i <= MAX_NR; i++) frecventa[i] = esteNevoieDe[i] = 0;
		if (vector[pozitieInceput] < vector[pozitieInceput+1])
		{
			minim = vector[pozitieInceput];
			maxim = vector[pozitieInceput+1];
		}
		else
		{
			minim = vector[pozitieInceput+1];
			maxim = vector[pozitieInceput];
		}
		frecventa[minim]++, lungime--;
		frecventa[maxim]++, lungime--;
		if (frecventa[minim] > 1 || frecventa[maxim] > 1)
			esteCool = 0;
		for (i = minim+1; i < maxim; i++) esteNevoieDe[i] = 1;
		for (i = pozitieInceput+2; lungime > 0; i++, lungime--)
		{
			frecventa[vector[i]]++;
			if (frecventa[vector[i]] > 1)
				esteCool = 0;
			if (vector[i] > minim && vector[i] < maxim)
			{
				if (esteNevoieDe[vector[i]])
					esteNevoieDe[vector[i]] = 0;
			}
			else
			{
				int j;
				if (vector[i] < minim)
				{
					for (j = minim-1; j > vector[i]; j--)
						esteNevoieDe[j] = 1;
					minim = vector[i];
				}
				if (vector[i] > maxim)
				{
					for (j = maxim+1; j < vector[i]; j++)
						esteNevoieDe[j] = 1;
					maxim = vector[i];
				}
			}
		}
		nrValoriDistincte = 0;
		for (i = minim; i <= maxim; i++)
		{
			if (frecventa[i] == 1)
				nrValoriDistincte++;
			if (esteNevoieDe[i])
				esteCool = 0;
		}
		return esteCool;
	}
}
void citesteDateleDeIntrare(int & P, int & N, int & K, int A[])
{
	ifstream citeste("cool.in");
	citeste >> P;
	citeste >> N >> K;
	for (int i = 0; i < N; i++)
		citeste >> A[i];
	citeste.close();
}

