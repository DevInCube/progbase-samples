#include "storage.h"

#include <fstream>
#include <iostream>
using namespace std;

string readTextFromFile(const string & filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "Can't open file: " << filename << endl;
        abort();
    }
    string text;
    string line;
    while (std::getline(file, line))
    {
        text += line + "\n";
    }
    //
    file.close();
    return text;
}

void writeTextToFile(const string & filename, const string & text)
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

bool Storage::load()
{
    string composers_filename = this->dir_name_ + "/composers.csv";
    string csv_text = readTextFromFile(composers_filename);
    //cout << csv_text << endl;
    CsvTable table = Csv::createTableFromString(csv_text);
    //printCsvTable(table);
    for (CsvRow & row: table)
    {
        Composer c = csvRowToComposer(row);
        this->composers_.push_back(c);
    }
}

int Storage::getNewComposerId()
{
    int max_id = 0;
    for (Composer & c: composers_)
    {
        if (c.id > max_id)
        {
            max_id = c.id;
        }
    }
    return max_id + 1;
}

int Storage::insertComposer(const Composer &composer)
{
    int new_id = this->getNewComposerId();
    Composer copy = composer;
    copy.id = new_id;
    this->composers_.push_back(copy); 
    return new_id;
}

bool Storage::removeComposer(int composer_id)
{
    int index = -1;
    for (int i = 0; i < composers_.size(); i++)
    {
        if (composers_.at(i).id == composer_id)
        {
            index = i;
            break;
        }
    }
    if (index == -1) { return false; }
    composers_.erase(composers_.begin() + index);
    return true;
}

optional<Composer> Storage::getComposerById(int composer_id)
{
    for (Composer & c: composers_)
    {
        if (c.id == composer_id)
        {
            return c;
        }
    }
    return nullopt;
}

vector<Composer> Storage::getAllComposers(void)
{
    return this->composers_;
}

bool Storage::save()
{
    string composers_filename = this->dir_name_ + "/composers.csv";
    CsvTable table;
    for (Composer & c: composers_)
    {
        CsvRow row = composerToCsvRow(c);
        table.push_back(row);
    }
    string csv_text = Csv::createStringFromTable(table);
    writeTextToFile(composers_filename, csv_text);
    return true;
}

Composer Storage::csvRowToComposer(const CsvRow & row)
{
    Composer c;
    c.id = std::stoi(row.at(0));
    c.fullname = row.at(1);
    c.year = std::stoi(row.at(2));
    return c;
}

CsvRow Storage::composerToCsvRow(const Composer & c)
{
    CsvRow row;
    row.push_back(std::to_string(c.id));
    row.push_back(c.fullname);
    row.push_back(std::to_string(c.year));
    return row;
}