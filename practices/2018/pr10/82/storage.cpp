#include "storage.h"
#include <fstream>
#include <string>
#include <iostream>
#include "csv.h"
#include "fs.h"

using namespace std;

Composer Storage::rowToComposer(const CsvRow & row)
{
    Composer c;
    c.id = std::stoi(row[0]);
    c.fullname = row[1];
    c.year = std::stoi(row[2]);
    return c;
}

bool Storage::load()
{
    string composers_file_name = this->dir_name_ + "/composers.csv";
    string csv_text = Fs::readTextFromFile(composers_file_name);
    CsvTable table = Csv::createTableFromString(csv_text);
    for (const CsvRow & row : table)
    {
        Composer c = this->rowToComposer(row);
        this->composers_.push_back(c);
    }
    return true;
}

bool Storage::removeComposer(int composer_id)
{ 
    int index = -1;
    for (int i = 0; i < this->composers_.size(); i++)
    {
        if (composers_[i].id == composer_id)
        {
            index = i;
            break;
        }
    }
    if (index >= 0)
    {
        composers_.erase(composers_.begin() + index);
        return true;
    }
    return false;
}

optional<Composer> Storage::getComposerById(int composer_id)
{
    for (int i = 0; i < this->composers_.size(); i++)
    {
        if (composers_[i].id == composer_id)
        {
            return composers_[i];
        }
    }
    return nullopt;
}

int Storage::getNewComposerId()
{
    int max_id = 1;
    for (auto & c: composers_)
    {
        if (c.id > max_id)
        {
            max_id = c.id;
        }
    }
    return max_id;
}

int Storage::insertComposer(const Composer &composer)
{
    int id = this->getNewComposerId();
    Composer copy = composer;
    copy.id = id; 
    this->composers_.push_back(copy);
    return id;
}

bool Storage::save()
{
    // @todo
    return true;
}

vector<Composer> Storage::getAllComposers(void)
{
    return this->composers_;
}

