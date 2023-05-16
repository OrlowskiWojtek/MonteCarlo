#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <tuple>

using namespace std;

// aproksymacja całki gausowskiej od 0 do 1

// zamienić dla ogólnej funkcji N wymiarowej

double g(double x)
{
    return sin(x);
}

double f(double x1, double x2)
{
    return exp(x1+x2);
}

tuple <double,double> MC1D(int N, double a, double b)
{
    double V = 0;
    double S=0;
    double xi;
    for(int i = 0;i<N;i++)
    {
        xi = rand()/(RAND_MAX+1.);  
        S += g(a+(b-a)*xi);
        V += pow(g(xi),2);
    }
    double MC = (double) S*((b-a)/(double)N); 
    return {MC,pow((b-a),2)/(N-1.)*V - N/(N-1.)*MC};
}

void approx1D(int N, double a, double b, double intVal)
{
    fstream file;

    system("touch data.dat");
    file.open("data.dat");

    cout << "Aproksymacja wielu całek dla różnej ilości próbek:" << endl;  

    double S;
    double V;

    for(int i = 1000; i < N; i+= 1000)
    {
        S = get<0>(MC1D(i,a,b));
        V = get<1>(MC1D(i,a,b));
        file << i << " " << S << " " << intVal << " " << S-2*sqrt(V/i) << " " << S+2*sqrt(V/i) << "\n"; 
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

tuple <double,double> MC2D(int N, double a[2], double b[2])
{
    double V = 0; 
    double S = 0;
    double xi1;
    double xi2;
    for(int i = 0; i < N; i++)
    {
        xi1 = rand()/(RAND_MAX + 1.);
        xi2 = rand()/(RAND_MAX + 1.);
        S += f(b[1]+(b[0]-b[1])*xi1,a[1]+(a[0]-a[1])*xi2);
        V += pow(f(xi1,xi2),2);
    }
    double MC = S*((b[1]-b[0])*(a[1]-a[0])/(double)N);
    return {MC,0}; 
}

int main()
{
    srand(time(NULL));

    //approx1D(1e6,0,M_PI,2);
    //app1sam(1e4,0,M_PI,2);
    
    //system("gnuplot < script.gnu");

    double a[] = {0,1};
    double b[] = {0,1}; 

    cout << get<0>(MC2D(1000000,a,b)) << endl;
    

    ifstream ifile;
    ifile.open("data.dat");

    if(ifile)
    {
        ifile.close();
        system("rm data.dat && rm data2.dat");
    }

    return 0;
}

// teraz analiza monte Carlo 1D 
// calka wielowymiarowa z wariancją i przedziałem ufności