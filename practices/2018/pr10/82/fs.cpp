#include "fs.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string Fs::readTextFromFile(const string & filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "Can't open file for reading: " << filename << endl;
        abort();
    }
    string line;
    string text;
    while (std::getline(file, line))
    {
        text += line + "\n";
    }
    file.close();
    return text;
}

void Fs::writeTextToFile(const string & filename, const string & text)
{
    ofstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "Can't open file for writing: " << filename << endl;
        abort();
    }
    file << text;
    file.close();
}