#include <fstream>
#define MAX_N 5000
#define MAX_NR 1000
using namespace std;
void citesteDateleDeIntrare(int & P, int & N, int & K, int A[]);
bool esteSecventaCool(int vector[], int pozitieInceput, int lungime,
                      int & minim, int & maxim, int & nrValoriDistincte);
int main()
{
	int P, N, K, A[MAX_N];
	citesteDateleDeIntrare(P, N, K, A);
	ofstream scrie("cool.out");
	int minim, maxim, nrValoriDistincte;
	if (P == 1)
	{
		if(esteSecventaCool(A, 0, K, minim, maxim, nrValoriDistincte))
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
				if (esteSecventaCool(A, i, lungime, minim, maxim, nrValoriDistincte))
				{
					nrSecvente++;
					if (!lungimeMaxima)
						lungimeMaxima = lungime;
					if (!amGasitSolutie)
						amGasitSolutie = 1;
				}
		scrie << lungimeMaxima << '\n' << nrSecvente;
	}
	scrie.close();
	return 0;
}
bool esteSecventaCool(int vector[], int pozitieInceput, int lungime,
                      int & minim, int & maxim, int & nrValoriDistincte)
{
	// verifica daca secventa care incepe la pozitia 'pozitieInceput'
	// de lungime 'lungime' din vectorul 'vector' este o secventa cool
	// si furnizeaza valoarea minima, maxima, respectiv numarul de valori
	// distincte din secventa 
	bool esteCool = 1;
	if (lungime == 1)
	{
		minim = maxim = vector[pozitieInceput];
		nrValoriDistincte = 1;
	}
	else
	{
		int frecventa[MAX_NR+1], i;
		for (i = 0; i <= MAX_NR; i++) frecventa[i] = 0;
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
		frecventa[minim]++;
		frecventa[maxim]++;
		for (i = pozitieInceput + 2; i < pozitieInceput + lungime; i++)
		{
			frecventa[vector[i]]++;
			if (vector[i] < minim)
				minim = vector[i];
			if (vector[i] > maxim)
				maxim = vector[i];
		}
		nrValoriDistincte = 0;
		for (i = minim; i <= maxim; i++)
		{
			if (frecventa[i] > 1)
				esteCool = 0;
			else
				if (frecventa[i] == 1)
					nrValoriDistincte++;
		}
		if (maxim != (minim + lungime-1))
			esteCool = 0;
		else
			if (nrValoriDistincte != lungime)
				esteCool = 0;
	}
	return esteCool;
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

