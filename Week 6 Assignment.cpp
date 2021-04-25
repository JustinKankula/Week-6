// Week 6 Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string> //for converting string to double

using namespace std;

bool GetBowlingData(string FileName, string Name[], double Scores[][4], const int A_Length, const int R_Length, const int C_Length);
void GetAverageScore(const double Scores[][4], double Averages[], const int R_Length, const int C_Length);
void PrettyPrintResults(const string Name[], const double Averages[], const int A_Length);

int main()
{

    //Display
    cout << "************************************************************" << endl;
    cout << "********************* Bowling Averages *********************" << endl;
    cout << "************************************************************" << endl;
    cout << endl;


    //Variables for FSTREAM
    string FileName = "BowlingScores.txt";
    string File_Open_Error = "Error Oppening File";
    bool F_Open;
    
    //Index counters and Array Lengths
    const int A_Length = 10; //Array Length
    const int R_Length = 10; //Row Length
    const int C_Length = 4; //Colum Length

    //Arrays
    string Name[A_Length];
    double Scores[R_Length][C_Length];
    double Averages[A_Length] = { 0 };


    F_Open = GetBowlingData(FileName, Name, Scores, A_Length, R_Length, C_Length);
    if (F_Open == false)
    {
        cout << File_Open_Error << endl;
        cout << endl;
        return -1;
    }
    else if (F_Open == true)
    {
        GetAverageScore(Scores, Averages, R_Length, C_Length);
        PrettyPrintResults(Name, Averages, A_Length);
        cout << endl;
    }

    system("pause");
    return 0;
}

bool GetBowlingData(string FileName, string Name[], double Scores[][4], const int A_Length, const int R_Length, const int C_Length)//tried to put "C_Length" in place of the "4" but it wouldn't work
{
    //Variables for FSTREAM and Tempholding
    fstream F;
    string Temp_Holding = " ";
    int i;
    int j;

    //Opening File
    F.open(FileName);
    if (F.fail())
    {
        return false;
    }

    //Splitting the loops up below. Tried to do them together, but things got too messy.

    //Looping for Name Array
    for (i = 0; i < A_Length;)
    {
        F >> Temp_Holding;
        if (!isdigit(Temp_Holding[0]))
        {
            Name[i] = Temp_Holding;
            i++;
        }
    }

    //returning to beginning of file
    F.clear();
    F.seekg(0);

    //Looping for Score Array
    for (i = 0; i < R_Length; i++)
    {
        for (j = 0; j < C_Length;)
        {
            F >> Temp_Holding;
            if (isdigit(Temp_Holding[0]))
            {
                Scores[i][j] = stod(Temp_Holding); //string to double. I remember you posting a function to do this, but I couldn't find that anywhere. Found this method online
                j++;
            }
        }
    }

    //Closing File
    F.close();

    return true;
}

void GetAverageScore(const double Scores[][4],double Averages[], const int R_Length, const int C_Length)
{
    int i;
    int j;

    double Average_TMP_Holding = 0; //another temporary holding to do math

    for (i = 0; i < R_Length; i++)
    {
        for (j = 0; j < C_Length; j++)
        {
            Average_TMP_Holding += Scores[i][j];
        }

        Averages[i] = Average_TMP_Holding / C_Length;
        Average_TMP_Holding = 0;
    }
}

void PrettyPrintResults(const string Name[], const double Averages[], const int A_Length)
{
    int i;

    cout << left << setw(15) << "Bowler Name" << left << setw(10) << "Average Score" << endl;
    cout << endl;

    for (i = 0; i < A_Length; i++)
    {
        cout << left << setw(15) << Name[i] << left << setw(10) << Averages[i] << endl;
    }
}