#include <fstream>
#define MAX_N 5000
#define MAX_NR 1000
using namespace std;
int A[MAX_N];
int P, N, K;
void citesteDateleDeIntrare();
void rezolvaCerinta1();
void rezolvaCerinta2();
int main()
{
	citesteDateleDeIntrare();
	if (P == 1)
		rezolvaCerinta1();
	else
		rezolvaCerinta2();
	return 0;
}
void rezolvaCerinta2()
{
	int i, uz[MAX_NR+1], lungimeMaxima, nrSecvente;
	for (i = 0; i <= MAX_NR; i++) uz[i] = 0;
	for (lungimeMaxima = i = 0; i < N-1; i++)
	{
		int minim, maxim, lungime, j;
		minim = maxim = A[i];
		lungime = uz[A[i]] = 1;
		if (lungime > lungimeMaxima)
		{
			lungimeMaxima = lungime;
			nrSecvente = 1;
		}
		else if (lungime == lungimeMaxima)
			nrSecvente++;
		for (j = i+1; j < N; j++)
		{
			if (uz[A[j]])
				break;
			uz[A[j]] = 1;
			if (A[j] < minim)
				minim = A[j];
			if (A[j] > maxim)
				maxim = A[j];
			lungime = j-i+1;
			if (maxim-minim == lungime-1)
			{
				if (lungime > lungimeMaxima)
				{
					lungimeMaxima = lungime;
					nrSecvente = 1;
				}
				else if (lungime == lungimeMaxima)
					nrSecvente++;
			}
		}
		for (j = 0; j <= MAX_NR; j++) uz[j] = 0;
	}
	ofstream scrie("cool.out");
	scrie << lungimeMaxima << '\n' << nrSecvente;
	scrie.close();
}
void rezolvaCerinta1()
{
	int minim, maxim, nrValoriDistincte, i, frecventa[MAX_NR+1];
	for (i = 0; i <= MAX_NR; i++) frecventa[i] = 0;
	minim = maxim = A[0];
	frecventa[A[0]] = 1;
	for (i = 1; i < K; i++)
	{
		frecventa[A[i]]++;
		if (A[i] < minim)
			minim = A[i];
		if (A[i] > maxim)
			maxim = A[i];
	}
	nrValoriDistincte = 0;
	for (i = minim; i <= maxim; i++)
		if (frecventa[i] == 1)
			nrValoriDistincte++;
	ofstream scrie("cool.out");
	if (nrValoriDistincte == K
	    && maxim-minim == K-1)
		scrie << maxim;
	else
		scrie << nrValoriDistincte;
	scrie.close();
}
void citesteDateleDeIntrare()
{
	ifstream citeste("cool.in");
	citeste >> P;
	citeste >> N >> K;
	for (int i = 0; i < N; i++)
		citeste >> A[i];
	citeste.close();
}

