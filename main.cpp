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

double approx(int N)
{
    double S=0;
    for(int i = 0;i<N;i++)
    {
        S += g(rand()/(RAND_MAX+1.));
    }
    return (double) S/N;
}

int main()
{
    srand(time(NULL));


    cout << approx(1000) << endl;


    return 0;
}