#pragma once
#include "GeneralLib.h"

class Studentas
{
private:
    string vardas;
    string pavarde;
    int examRez;
    double finalAverage;
    int ndCount;
    vector<int> pazymiai;

public:
    Studentas() { }

    Studentas(string vardas, string pavarde, int examRez, vector<int> pazymiai);
    Studentas(const Studentas& stud);
    ~Studentas();
    string getFirstName();
    string getLastName();
    double getFinalAverage();
    double avgCalc();
    double medianCalc();
    double calculateAvgOrMedian();
    void outputData();
};

Studentas createStudentFromConsoleData();
void writeStudentDataFromFile(string, bool);
void generateStudentsToFile(int, string);
void writeStudentDataToConsole();
void splitStudentsIntoTwoGroups(vector<Studentas>);
bool vidurkioLyginimas(Studentas);
vector<Studentas> lievakuIeskojimas(vector<Studentas>&);

