#include <iostream>
#include <fstream>

using namespace std;

void readFileSample() {
    cout << ">>> Reading from file" << endl;
    string str;
    ifstream stream;
    stream.open("/home/devincube/projects/qt/qt-console-1/data.txt");
    if (stream.is_open()) {
        cout << ">>> File opened" << endl;
        while (getline(stream, str)) {
            cout << str << endl;
        }
        stream.close();
        cout << ">>> File closed" << endl;
    } else {
        cout << ">>> Error" << endl;
    }
}

void writeFileSample() {
    cout << ">>> Writing to file" << endl;
    ofstream stream;
    stream.open("test.txt");
    if (stream.is_open()) {
        cout << ">>> File opened" << endl;
        stream << "Some" << 5678 << endl << " number";
        stream.close();
        cout << ">>> File closed" << endl;
        cout << ">>> Check file in 'cat':" << endl;
        system("cat test.txt");
        cout << endl;
    } else {
        cout << ">>> Error" << endl;
    }
}

int main(void)
{

    readFileSample();
    writeFileSample();
    return 0;
}

