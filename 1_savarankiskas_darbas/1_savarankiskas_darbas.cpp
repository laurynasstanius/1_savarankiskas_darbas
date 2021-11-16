#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <deque>

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
        this->finalAverage = avgCalc();
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

    double getFinalAverage()
    {
        return finalAverage;
    }

    double avgCalc()
    {
        double sum = 0;
        double avg;

        for (int pazymys : pazymiai)
        {
            sum = sum + pazymys;
        }

        try
        {
            avg = (sum / pazymiai.size()) * 0.4 + examRez * 0.6;
        }
        catch (exception &e)
        {
            cout << "Error: Dividing by zero";
        }
        
        return avg;
    }

    double medianCalc()
    {
        sort(pazymiai.begin(), pazymiai.end());

        if (pazymiai.size() % 2 != 0)
            return pazymiai[pazymiai.size() / 2];

        return (pazymiai[(pazymiai.size() / 2) - 1] + pazymiai[pazymiai.size() / 2]) / 2;
    }

    double calculateAvgOrMedian()
    {
        int choice;
        cout << "Ka norite skaiciuoti?:\n";
        cout << "Vidurki?   - 1\n";
        cout << "Mediana?    - 2\n";
        cin >> choice;

        if (choice == 1)
        {
            return avgCalc();
        }
        else if (choice == 2)
        {
            return medianCalc();
        }
        else
        {
            cout << "Error, invalid number\n";
        }
    }

    void outputData()
    {
        cout << left << setw(20) << pavarde << setw(20) << vardas << setw(10) << fixed << setprecision(2) << finalAverage << endl;
    }
};

Studentas createStudentFromConsoleData();
void writeStudentDataFromFile(string file);
void writeStudentDataToConsole();
void splitStudentsIntoTwoGroups(deque<Studentas> studentai);

void writeStudentDataFromFile(string file, bool toFile)
{
    int rowCounter = 0;
    string vardas;
    string pavarde;
    int nd1, nd2, nd3, nd4, nd5, egz;

    vector<int>pazymiai;
    deque<Studentas> studentai;

    // Studentu duomenu nuskaitymas is failo
    auto start = chrono::high_resolution_clock::now();
    ifstream input(file);

    for (string eilute; getline(input, eilute);)
    {
        if (rowCounter == 0) {
            rowCounter++;
            continue;
        }

        stringstream ssin(eilute);
        ssin >> vardas >> pavarde >> nd1 >> nd2 >> nd3 >> nd4 >> nd5 >> egz;
        pazymiai.push_back(nd1);
        pazymiai.push_back(nd2);
        pazymiai.push_back(nd3);
        pazymiai.push_back(nd4);
        pazymiai.push_back(nd5);

        Studentas stud(vardas, pavarde, egz, pazymiai);
        studentai.push_back(stud);
    }
    input.close();
    auto end = chrono::high_resolution_clock::now();
    auto timeTook = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Duomenu nuskaitymas is failo truko laiko milisekundemis: " << timeTook.count() << endl;

    // Studentu rikiavimas pagal varda abecele didejimo tvarka
    sort(studentai.begin(), studentai.end(), [](Studentas& studOne, Studentas& studTwo)
        {
            return studOne.getFirstName() < studTwo.getFirstName();
        });

    if (toFile)
    {
        splitStudentsIntoTwoGroups(studentai);
    }
    else
    {
        cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(10) << "Galutinis(Vid.)\n";
        cout << "----------------------------------------------------------------------------------------\n";

        for (Studentas stud : studentai)
        {
            stud.outputData();
        }
    }
}

Studentas createStudentFromConsoleData()
{
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

void generateStudentsToFile(int studentCount, string file)
{
    srand(time(0));
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0, 10);

    string vardas = "Vardas";
    string pavarde = "Pavarde";
    ofstream outfile(file);

    outfile <<  setw(10) << left << "Vardas" << "\t" << setw(10) << left << "Pavarde\t\t" <<
                setw(10) << left << "ND1" << setw(10) << left << "ND2" << setw(10) << left << "ND3" <<
                setw(10) << left << "ND4" << setw(10) << left << "ND5" << setw(10) << left << "Egzaminas" << endl;

    for (long i = 1; i <= studentCount; i++) {
        outfile <<  setw(10) << left << vardas + to_string(i) << "\t" << setw(10) << left << pavarde + to_string(i) << "\t" <<
                    setw(10) << left << dist6(rng) << setw(10) << left << dist6(rng) << setw(10) << left << dist6(rng) <<
                    setw(10) << left << dist6(rng) << setw(10) << left << dist6(rng) << setw(10) << left << dist6(rng) << endl;
    }

    outfile.close();
}

void writeStudentDataToConsole()
{
    deque<Studentas> studArray;
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

void splitStudentsIntoTwoGroups(deque<Studentas> studentai)
{
    ofstream lievakaiTxt;
    ofstream malaciaiTxt;
    deque<Studentas> malaciai;
    deque<Studentas> lievakai;

    // Studentu rusiavimas i malacius ir lievakus naudojant vektorius
    auto start = chrono::high_resolution_clock::now();
    for (Studentas studentas : studentai)
    {
        if (studentas.getFinalAverage() < 5)
        {
            lievakai.push_back(studentas);
        }
        else
        {
            malaciai.push_back(studentas);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto timeTook = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Studentu rusiavimo i dvi grupes trukme milisekundemis: " << timeTook.count() << endl;

    //////////////////////////////////////////////////
    // Isrikiuotu studentu rasymas i skirtingus failus
    // 1. Lievaku failo irasymas
    start = chrono::high_resolution_clock::now();
    lievakaiTxt.open("lievakai.txt");
    lievakaiTxt << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(10) << "Galutinis(Vid.)\n"
        << "----------------------------------------------------------------------------------------\n";

    for (Studentas lievakas : lievakai)
    {
        lievakaiTxt << left << setw(20) << lievakas.getFirstName() << setw(20) << lievakas.getLastName() << setw(20) << left << fixed << setprecision(2) << lievakas.getFinalAverage() << endl;
    }

    lievakaiTxt.close();

    ///////////////////////////////////////////////////
    // 2. malaciu failo irasymas
    malaciaiTxt.open("malaciai.txt");
    malaciaiTxt << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(10) << "Galutinis(Vid.)\n"
        << "----------------------------------------------------------------------------------------\n";

    for (Studentas malacius : malaciai)
    {
        malaciaiTxt << left << setw(20) << malacius.getFirstName() << setw(20) << malacius.getLastName() << setw(20) << left << fixed << setprecision(2) << malacius.getFinalAverage() << endl;
    }
    malaciaiTxt.close();

    end = chrono::high_resolution_clock::now();
    auto timeTook2 = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Studentu irasymas i skirtingus failus truko milisekundemis: " << timeTook2.count() << endl;
}

int main()
{
    /*bool flag = false;
    int ans;
    
    cout << "Norite duomenis nuskaityti is konsoles?    - 1\n";
    cout << "Norite duomenis nuskaityti is failo?       - 2\n";

    while (!flag)
    {
        cin >> ans;
        system("cls");

        if (ans == 2)
        {
            writeStudentDataToFile("studentuGeneravimoRez.txt");
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
    }*/

    //// generavimo trukmes skaiciavimas
    auto start = chrono::high_resolution_clock::now();
    generateStudentsToFile(1000, "studentuGeneravimoRez1.txt");
    auto end = chrono::high_resolution_clock::now();
    auto trukme1 = chrono::duration_cast<chrono::milliseconds> (end - start);
    cout << "Failo sukurimas truko milisekundemis: " << trukme1.count() << endl;
    writeStudentDataFromFile("studentuGeneravimoRez1.txt", true);

    cout << "\n";

    start = chrono::high_resolution_clock::now();
    generateStudentsToFile(10000, "studentuGeneravimoRez2.txt");
    end = chrono::high_resolution_clock::now();
    auto trukme2 = chrono::duration_cast<chrono::milliseconds> (end - start);
    cout << "Failo sukurimas truko milisekundemis: " << trukme2.count() << endl;
    writeStudentDataFromFile("studentuGeneravimoRez2.txt", true);

    cout << "\n";

    start = chrono::high_resolution_clock::now();
    generateStudentsToFile(100000, "studentuGeneravimoRez3.txt");
    end = chrono::high_resolution_clock::now();
    auto trukme3= chrono::duration_cast<chrono::milliseconds> (end - start);
    cout << "Failo sukurimas truko milisekundemis: " << trukme3.count() << endl;
    writeStudentDataFromFile("studentuGeneravimoRez3.txt", true);

    cout << "\n";

    start = chrono::high_resolution_clock::now();
    generateStudentsToFile(1000000, "studentuGeneravimoRez4.txt");
    end = chrono::high_resolution_clock::now();
    auto trukme4 = chrono::duration_cast<chrono::milliseconds> (end - start);
    cout << "Failo sukurimas truko milisekundemis: " << trukme4.count() << endl;
    writeStudentDataFromFile("studentuGeneravimoRez4.txt", true);

    return 0;
}
