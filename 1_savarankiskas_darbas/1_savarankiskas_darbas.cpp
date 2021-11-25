#include "GeneralLib.h"
#include "functions.h"

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

    /*cout << "\n";

    start = chrono::high_resolution_clock::now();
    generateStudentsToFile(10000, "studentuGeneravimoRez2.txt");
    end = chrono::high_resolution_clock::now();
    auto trukme2 = chrono::duration_cast<chrono::milliseconds> (end - start);
    cout << "Failo sukurimas truko milisekundemis: " << trukme2.count() << endl;
    writeStudentDataFromFile("studentuGeneravimoRez2.txt", true);*/

    /*cout << "\n";

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
    writeStudentDataFromFile("studentuGeneravimoRez4.txt", true);*/

    return 0;
}
