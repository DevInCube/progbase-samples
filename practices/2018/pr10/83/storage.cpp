#include "storage.h"
#include <fstream>
#include <iostream>

using namespace std;
string readAllFromFile(string const & filename);
void writeAllToFile(string const & filename, string const & text);


bool Storage::load()
{
    string composers_filename = this->dir_name_ + "/data.csv";
    string composers_csv = readAllFromFile(composers_filename);
    CsvTable composers_table = Csv::createTableFromString(composers_csv);
    for (CsvRow & row : composers_table)
    {
        Composer c;
        // cout << row.size() << endl;
        //cout << row[0] << "|" << row[1] << "|" << row[2] << endl;
        c.id = std::stoi(row[0]);
        c.fullname = row[1];
        c.year = std::stoi(row[2]);
        this->composers_.push_back(c);
    }
    return true;
}

bool Storage::save()
{
    string composers_filename = this->dir_name_ + "/data.csv";
    CsvTable t;
    for (Composer & c: this->composers_)
    {
        CsvRow row;
        row.push_back(std::to_string(c.id));
        row.push_back(c.fullname);
        row.push_back(std::to_string(c.year));
        t.push_back(row);
    }
    string csv_text = Csv::createStringFromTable(t);
    writeAllToFile(composers_filename, csv_text);
    return true;
}

vector<Composer> Storage::getAllComposers()
{
    return this->composers_;
}

int Storage::getNewComposerId()
{
    int max_id = 0;
    for (Composer & c: this->composers_)
    {
        if (c.id > max_id)
        {
            max_id = c.id;
        }
    }
    int new_id = max_id + 1;
    return new_id;
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
    for (int i = 0; i < this->composers_.size(); i++)
    {
        if (this->composers_[i].id == composer_id)
        {
            index = i;
            break;
        }
    }
    if (index >= 0)
    {
        this->composers_.erase(this->composers_.begin() + index);
        return true;
    }
    return false;
}

optional<Composer> Storage::getComposerById(int composer_id)
{
    for (Composer & c: this->composers_)
    {
        if (c.id == composer_id)
        {
            return c;
        }
    }
    return nullopt;
}

string readAllFromFile(string const & filename)
{
    ifstream file;
    file.open(filename);
    if (!file.good())
    {
        cerr << "Can't open file: " << filename << endl;
        abort();
    }
    string row_str;
    string text_str;
    while (std::getline(file, row_str))
    {
        text_str += row_str + "\n";
    }
    file.clear();
    return text_str;
}

void writeAllToFile(string const & filename, string const & text)
{
    ofstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "File not open for write: " << filename;
        abort();
    }
    file << text;
    file.close();
}