#include "functions.h"
#include "GeneralLib.h"

Studentas::Studentas(string vardas, string pavarde, int examRez, vector<int> pazymiai)
{
    this->vardas = vardas;
    this->pavarde = pavarde;
    this->examRez = examRez;
    this->pazymiai = pazymiai;
    this->finalAverage = avgCalc();
}

Studentas::Studentas(const Studentas& stud)
{
    this->vardas = stud.vardas;
    this->pavarde = stud.pavarde;
    this->examRez = stud.examRez;
    this->finalAverage = stud.finalAverage;
}

Studentas::~Studentas() {}

string Studentas::getFirstName()
{
    return vardas;
}

string Studentas::getLastName()
{
    return pavarde;
}

double Studentas::getFinalAverage()
{
    return finalAverage;
}

double Studentas::avgCalc()
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
    catch (exception& e)
    {
        cout << "Error: Dividing by zero";
    }

    return avg;
}

double Studentas::medianCalc()
{
    sort(pazymiai.begin(), pazymiai.end());

    if (pazymiai.size() % 2 != 0)
        return pazymiai[pazymiai.size() / 2];

    return (pazymiai[(pazymiai.size() / 2) - 1] + pazymiai[pazymiai.size() / 2]) / 2;
}

double Studentas::calculateAvgOrMedian()
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

void Studentas::outputData()
{
    cout << left << setw(20) << pavarde << setw(20) << vardas << setw(10) << fixed << setprecision(2) << finalAverage << endl;
}

__declspec(selectany) deque<Studentas> studentai; //__declspec(selectany) kad nesidubliuotu su kitais failaiss

__declspec(selectany) deque<Studentas> lievakai;

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

    outfile << setw(10) << left << "Vardas" << "\t" << setw(10) << left << "Pavarde\t\t" <<
        setw(10) << left << "ND1" << setw(10) << left << "ND2" << setw(10) << left << "ND3" <<
        setw(10) << left << "ND4" << setw(10) << left << "ND5" << setw(10) << left << "Egzaminas" << endl;

    for (long i = 1; i <= studentCount; i++) {
        outfile << setw(10) << left << vardas + to_string(i) << "\t" << setw(10) << left << pavarde + to_string(i) << "\t" <<
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

    for (Studentas stud : studArray) {
        stud.outputData();
    }
}

bool vidurkioLyginimas(Studentas a) {
    if (a.getFinalAverage() < 5.00) { return true; }
    else {
        return false;
    }

}

deque<Studentas> lievakuIeskojimas(deque<Studentas>& studentai) {

    deque<Studentas> lievakai;
    deque<Studentas>::iterator it = studentai.begin();

    while (it != studentai.end())
    {
        if (vidurkioLyginimas(*it))
        {
            lievakai.push_back(*it);
            it = studentai.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return lievakai;
}

void splitStudentsIntoTwoGroups(deque<Studentas> studentai)
{
    ofstream lievakaiTxt;
    ofstream studentaiTxt;
    deque<Studentas> lievakai;
    deque<Studentas>::iterator it;

    // Studentu rusiavimas i malacius ir lievakus naudojant vektorius
    auto start = chrono::high_resolution_clock::now();

    lievakai = lievakuIeskojimas(studentai);

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
    // 2. likusiu studentu failo irasymas
    studentaiTxt.open("studentai.txt");
    studentaiTxt << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(10) << "Galutinis(Vid.)\n"
        << "----------------------------------------------------------------------------------------\n";

    for (Studentas studentas : studentai)
    {
        studentaiTxt << left << setw(20) << studentas.getFirstName() << setw(20) << studentas.getLastName() << setw(20) << left << fixed << setprecision(2) << studentas.getFinalAverage() << endl;
    }
    studentaiTxt.close();

    end = chrono::high_resolution_clock::now();
    auto timeTook2 = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Studentu irasymas i skirtingus failus truko milisekundemis: " << timeTook2.count() << endl;
}