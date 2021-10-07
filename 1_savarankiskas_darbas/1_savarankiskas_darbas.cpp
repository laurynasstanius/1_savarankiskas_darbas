#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Studentas
{
private:
    string vardas;
    string pavarde;
    int ndCount;
    int examRez;
    double finalAverage;
    int* pazymiai = new int[10];

public:
    Studentas() { }

    Studentas(string vardas, string pavarde, int ndCount, double examRez, double finalAverage)
    {
        this->vardas = vardas;
        this->pavarde = pavarde;
        this->ndCount = ndCount;
        this->examRez = examRez;
        this->finalAverage = finalAverage;
    }

    Studentas(Studentas& stud)
    {
        this->vardas = stud.vardas;
        this->pavarde = stud.pavarde;
        this->ndCount = stud.ndCount;
        this->examRez = stud.examRez;
        this->finalAverage = stud.finalAverage;
    };

    ~Studentas()
    {
        cout << "destructor called\n";
    }

    void inputData();
    void outputData();
    double finalAvgCalc();
};

void Studentas::outputData()
{
    cout << left << setw(25) << pavarde << setw(25) << vardas << setw(15) << fixed << setprecision(2) << finalAvgCalc() << endl;
}

void Studentas::inputData()
{
    cout << "Iveskite Varda: ";
    cin >> vardas;
    cout << "Iveskite Pavarde: ";
    cin >> pavarde;
    cout << "Iveskite egzamino rezultata: ";
    cin >> examRez;
    cout << "Iveskite pazymiu skaiciu (Didziausias pazymiu kiekis yra 10): ";
    cin >> ndCount;

    for (int i = 0; i < ndCount; i++)
    {
        cout << "Pazymis Nr." << i + 1 << ": ";
        cin >> pazymiai[i];
    }

    // Studentas s(vardas, pavarde, ndCount, examRez, finalAvgCalc());
}

double Studentas::finalAvgCalc()
{   // TODO: vartotojas turi pasirinkti ar skaiciuoja mediana ar vidurki

    double sum = 0;
    for (int i = 0; i < ndCount; i++)
    {
        sum += pazymiai[i];
    }
    return (sum / ndCount) * 0.4 + examRez * 0.6;
}

Studentas* studArray = new Studentas[5];

void createObj()
{
    for (int i = 0; i < 1; i++)
    {
        studArray[i].inputData();
        cout << "Studentas sukurtas!\n\n";
    }

    system("cls");
}

int main()
{
    createObj();

    cout << left << setw(25) << "Pavarde" << setw(25) << "Vardas" << setw(15) << "Galutinis(Vid.)\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < 1; i++)
    {
        studArray[i].outputData();
    }

    return 0;
}