// PROMOTHEE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    cout << "Before running the code please set two parameters in #define Criterias and #define Decision_makers at the top of the code and then you need to also set the Absolute paths of three text input files Data.txt, Quality.txt, Weights.txt and an ouptut text file Results.txt. If the paths have not been configured then by default only current directory will be checked.\n";
    cout << "In case if the file could not be opened or no data exist then it would terminate the code with and error in the below line saying Error:file could not be opened.";
    unsigned short int Criterias = 0, Decision_makers = 0;
    cout << "\nEnter the number of Criterias: ";
    cin >> Criterias;
    cout << "Enter the number of Alternatives: ";
    cin >> Decision_makers;
    long double values, max = -2, sum = 0;
    long double* Decision_Matrix = new long double[Criterias * Decision_makers];
    long double* P = new long double[Criterias * Decision_makers * Decision_makers];
    long double* preference = new long double[Decision_makers * Decision_makers];
    long double* weights = new long double[Criterias];
    long double* outrank = new long double[Decision_makers];
    long double weight1, sum1 = 0;
    unsigned short int* quality = new unsigned short int[Criterias];
    unsigned short int quality1, i = 0, j = 0, k = 0;
    ifstream indata, inquality, inweights;
    ofstream Results;
    inquality.open("Quality.txt");
    inweights.open("Weights.txt");
    indata.open("Data.txt");
    inweights >> weight1;
    inquality >> quality1;
    indata >> values;
    for (int i = 0; i < Criterias; i++)
    {
        quality[i] = quality1;
        weights[i] = weight1;
        for (j = 0; j < Decision_makers; j++)
        {
            if (quality[i] == 0)
            {
                Decision_Matrix[i * Decision_makers + j] = -1 * values;
            }
            else
            {
                Decision_Matrix[i * Decision_makers + j] = values;
            }
            indata >> values;
        }
        inquality >> quality1;
        inweights >> weight1;
    }
    inquality.close();
    inweights.close();
    indata.close();
    for (k = 0; k < Criterias; k++)
    {
        for (i = 0; i < Decision_makers; i++)
        {
            for (j = 0; j < Decision_makers; j++)
            {
                if (Decision_Matrix[k * Decision_makers + i] - Decision_Matrix[k * Decision_makers + j] <= 0)
                {
                    P[(k * Decision_makers * Decision_makers) + i * Decision_makers + j] = 0;
                }
                else
                {
                    P[(k * Decision_makers * Decision_makers) + i * Decision_makers + j] = weights[k];
                }
            }
        }
    }
    for (i = 0; i < Decision_makers; i++)
    {
        for (j = 0; j < Decision_makers; j++)
        {
            sum = 0;
            for (k = 0; k < Criterias; k++)
            {
                sum += P[k * Decision_makers * Decision_makers + i * Decision_makers + j];
            }
            preference[i * Decision_makers + j] = sum;
        }
    }
    for (i = 0; i < Decision_makers; i++)
    {
        sum = 0;
        sum1 = 0;
        for (j = 0; j < Decision_makers; j++)
        {
            sum += preference[i * Decision_makers + j];
            sum1 += preference[j * Decision_makers + i];
        }
        outrank[i] = (sum - sum1) / Decision_makers;
    }
    Results.open("Results.txt");
    k = 0;
    for (i = 0; i < Decision_makers; i++)
    {
        Results << " The outflow rank of Alternative number " << i + 1 << " is: " << outrank[i] << "\n ";
        if (max < outrank[i])
        {
            max = outrank[i];
            k = i + 1;
        }
    }
    Results << "\n" << "The Best Alternative is of number: " << k << " and the value is: " << max;
    Results.close();
    cout << "\n\tThe program has produced a Text file with name Results.txt at the path specified or by default in the same directory.";
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
