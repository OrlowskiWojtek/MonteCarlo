#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <tuple>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

// aproksymacja całki gausowskiej od 0 do 1

double g(vector<double> x)
{
    double arg = 0;
    // funkcja k argumentów x
   
    for(auto &i : x)
    {
        arg += i;
    }
    return sin(arg);
}

tuple <double,double> MCND(int N, vector <double> a, vector <double> b)
{
    // a i b to punkty początku oraz końca dla pewnego jednego wymiaru
    double V = 0;
    double S=0;
    vector <double> temp(b.size()); 
    vector <double> xiVec(b.size());
    for(int i = 0;i<N;i++)
    {   
        for(unsigned int j = 0; j < temp.size(); j++)
        {
            xiVec[j] = rand()/(RAND_MAX+1.);
            temp[j] = a[j] + (b[j] - a[j])*xiVec[j];
        }
        S += g(temp);
        V += pow(g(xiVec),2);
    }
    
    double MC = S;
    double vVal = V/(N-1.);
    for(auto i = temp.begin(); i != temp.end(); i++)
    {
        MC *= (b[*i]-a[*i]); 
        vVal *= pow(b[*i] - a[*i],2);
    }


    return {MC/N,vVal - N/(N-1.)*MC};
}

int main()
{
    srand(time(NULL));

    // niech to będzie funkcja 5 zmiennych od 0 do 1

    vector <double> a = {0,0,0};
    vector <double> b = {1,1,1};

    tuple <double,double> MCval = MCND(1e6,a,b);

    cout << get<0>(MCval) << " " << get<1>(MCval)<< endl;


    ifstream ifile;
    string filename = "data";

    for(int i = 1; i<=3; i++)
    {
        ifile.open("data"+to_string(i)+".dat");
        if(ifile)
        {
            ifile.close();
            string command ="rm data"+to_string(i)+".dat"; 
            char *cstr = new char[command.length() + 1];
            strcpy(cstr, command.c_str());
            system(cstr);
            delete[] cstr;
            cout << "deleted: data"+to_string(i)+".dat" << endl;  
        }
    }

    return 0;
}

// teraz analiza monte Carlo 1D 
// calka wielowymiarowa z wariancją i przedziałem ufności