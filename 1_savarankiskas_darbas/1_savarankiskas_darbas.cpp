#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

int n;

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

    Studentas(string vardas, string pavarde, int examRez, vector<int> pazymiai)
    {
        this->vardas = vardas;
        this->pavarde = pavarde;
        this->examRez = examRez;
        this->pazymiai = pazymiai;
        this->finalAverage = medianCalc();
    }

    Studentas(const Studentas& stud)
    {
        this->vardas = stud.vardas;
        this->pavarde = stud.pavarde;
        this->examRez = stud.examRez;
        this->finalAverage = stud.finalAverage;
    }

    ~Studentas() {}

    string getFirstName()
    {
        return vardas;
    }

    string getLastName()
    {
        return pavarde;
    }

    double avgCalc()
    {
        double sum = 0;
        for (int pazymys : pazymiai)
        {
            sum = sum + pazymys;
        }
        return (sum / pazymiai.size()) * 0.4 + examRez * 0.6;
    }

    double medianCalc()
    {
        sort(pazymiai.begin(), pazymiai.end());

        if (pazymiai.size() % 2 != 0)
            return pazymiai[pazymiai.size() / 2];

        return (pazymiai[(pazymiai.size() / 2) - 1] + pazymiai[pazymiai.size() / 2]) / 2;
    }

    void outputData()
    {
        cout << left << setw(20) << pavarde << setw(20) << vardas << setw(10) << fixed << setprecision(2) << finalAverage << endl;
    }
};

Studentas createStudentFromConsoleData();
void writeStudentDataToFile();
void writeStudentDataToConsole();

void writeStudentDataToFile()
{
    ifstream input("kursiokai.txt");

    int eilCounteris = 0;
    string vardas;
    string pavarde;
    int nd1, nd2, nd3, nd4, nd5, exam;

    vector<int>pazymiai;
    vector<Studentas> studentai;
    for(string eilute; getline(input, eilute);) {
        if (eilCounteris == 0) {
            eilCounteris++;
            continue;
        }

        stringstream ssin(eilute);
        ssin >> vardas >> pavarde >> nd1 >> nd2 >> nd3 >> nd4 >> nd5 >> exam;
        pazymiai.push_back(nd1);
        pazymiai.push_back(nd2);
        pazymiai.push_back(nd3);
        pazymiai.push_back(nd4);
        pazymiai.push_back(nd5);

        Studentas stud(vardas, pavarde, exam, pazymiai);
        studentai.push_back(stud);
    }
    input.close();

    sort(studentai.begin(), studentai.end(), [](Studentas& studOne, Studentas& studTwo)
    {
        return studOne.getFirstName() < studTwo.getFirstName();
    });

    cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(10) << "Galutinis(Vid.)\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (Studentas stud : studentai) {
        stud.outputData();
    }
}

Studentas createStudentFromConsoleData() {
    srand(time(0));
    char answer;
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0, 10);

    string vardas;
    string pavarde;
    int examRez;
    int ndCount;
    vector<int> pazymiai;

    cout << "Iveskite Varda: ";
    cin >> vardas;
    cout << "Iveskite Pavarde: ";
    cin >> pavarde;
    cout << "Iveskite egzamino rezultata: ";
    cin >> examRez;
    cout << "Iveskite pazymiu skaiciu: ";
    cin >> ndCount;
    cout << "Automatinis skaiciu generavimas? (y/n) - ";
    cin >> answer;

    switch (answer)
    {
        case 'y':
            for (int i = 0; i < ndCount; i++)
            {
                int temp = dist6(rng);
                pazymiai.push_back(temp);
            }
            break;
        case 'n':
            for (int i = 0; i < ndCount; i++)
            {
                int temp;
                cout << "Pazymis Nr." << i + 1 << ": ";
                cin >> temp;
                pazymiai.push_back(temp);
            }
            break;
    }

    Studentas stud(vardas, pavarde, examRez, pazymiai);
    return stud;
}

void writeStudentDataToConsole() {
    vector<Studentas> studArray;
    cout << "Kiek norite studentu uzregistruoti? - ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        studArray.push_back(createStudentFromConsoleData());
        system("cls");
        cout << "Studentas sukurtas!\n\n";
    }

    system("cls");

    cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(10) << "Galutinis(Vid.)\n";
    cout << "----------------------------------------------------------------------------------------\n";

    sort(studArray.begin(), studArray.end(), [](Studentas& studOne, Studentas& studTwo)
    {
        return studOne.getFirstName() < studTwo.getFirstName();
    });

    for (Studentas stud : studArray) {
        stud.outputData();
    }
}

int main()
{
    bool flag = false;
    int ans;
    
    cout << "Norite duomenis nuskaityti is konsoles?    - 1\n";
    cout << "Norite duomenis nuskaityti is failo?       - 2\n";


    while (!flag)
    {
        cin >> ans;
        system("cls");

        if (ans == 2)
        {
            writeStudentDataToFile();
            flag = true;
        }
        else if (ans == 1)
        {
            writeStudentDataToConsole();
            flag = true;
        }
        else {
            cout << "Neteisingas pasirinkimas\n";
            continue;
        }
    }

    return 0;
}
