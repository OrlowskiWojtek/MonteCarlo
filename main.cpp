#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <tuple>

using namespace std;

// aproksymacja całki gausowskiej od 0 do 1

double g(double x)
{
    return sin(x);
}

tuple <double,double> MC1D(int N, double a, double b)
{
    double S=0;
    for(int i = 0;i<N;i++)
    {
        S += g(a+(b-a)*rand()/(RAND_MAX+1.));
    }
    return {(double) S*((b-a)/(double)N),0};
}

void approx1D(int N, double a, double b, double intVal)
{
    fstream file;

    system("touch data.dat");
    file.open("data.dat");

    cout << "Aproksymacja wielu całek dla różnej ilości próbek:" << endl;  

    for(int i = 0; i < N; i+= 1000)
    {
        file << i << " " << get<0>(MC1D(i,a,b)) << " " << intVal << "\n"; 
        cout << "In progress: " << (double)i/N*100 << "%" << "\n";
    }

    file << endl;

    file.close();

}

void app1sam(int N, double a, double b, double intVal)
{
    fstream file;

    cout << "Aproksymacja jednej całki -> pattern" << endl;
 
    system("touch data2.dat");
    file.open("data2.dat");
    
    double S=0;
    
    for(int i = 1;i<N;i++)
    {
        S += g(a+(b-a)*rand()/(RAND_MAX+1.));
        file << i << " " << S*((b-a)/(double)i) << " " << intVal << endl;
        cout << "In progress: " << (double)i/N*100 << "%" << "\n";
    }

    file.close();
}

int main()
{
    srand(time(NULL));

    approx1D(1e6,0,M_PI,2);
    app1sam(1e4,0,M_PI,2);
    
    system("gnuplot < script.gnu");
    system("rm data.dat && rm data2.dat");

    return 0;
}

// teraz analiza monte Carlo 1D 
// calka wielowymiarowa z wariancją i przedziałem ufności