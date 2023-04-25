#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

// aproksymacja całki gausowskiej od 0 do 1

double g(double x)
{
    return exp(pow(x,2));
}

double approx1D(int N)
{
    double S=0;
    for(int i = 0;i<N;i++)
    {
        S += g(rand()/(RAND_MAX+1.));
    }
    return (double) S/N;
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


    cout << approx1D(10000) << endl; // int e^x^2 from 0 to 1

    cout << approx2D(10000) << endl; // int e^(x+y)^2 from 0 to 1 dx from 0 to 1 dy


    return 0;
}