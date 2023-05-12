#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

// aproksymacja całki gausowskiej od 0 do 1

double g(double x)
{
    return sin(x);
}

double approx1D(int N, double a, double b)
{
    double S=0;
    for(int i = 0;i<N;i++)
    {
        S += g(a+(b-a)*rand()/(RAND_MAX+1.));
    }
    return (double) S*((b-a)/(double)N);
}

double approx2D(int N)
{
    double S=0;
    for(int i = 0;i<N;i++)
    {
        S += g(rand()/((double)RAND_MAX) + rand()/((double)RAND_MAX));
    }
    return (double) S/N;
}

int main()
{
    srand(time(NULL));

    fstream file;

    file.open("data.dat");


    cout << "Aproksymacja wielu całek dla różnej ilości próbek:" << endl;  

    for(int i = 0; i <1000000; i+= 1000)
    {
        file << i << " " <<approx1D(i,0,M_PI) << " " << 2 << "\n"; 
        cout << "In progress: " << i/10000000.*100 << "%" << "\n";
    }

    file << endl;

    file.close();

    cout << "Aproksymacja jednej całki -> pattern" << endl;
 
    double a = 0; double b = M_PI;
    int N = 100000;

    double S=0;
    for(int i = 1;i<N;i++)
    {
        
        S += g(a+(b-a)*rand()/(RAND_MAX+1.));
        file << i << " " << S*((b-a)/(double)i) << " " << 2 << endl;

    }



    return 0;
}

// teraz analiza monte Carlo 1D 
// calka wielowymiarowa z wariancją i przedziałem ufności