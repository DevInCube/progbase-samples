#include "cui.h"

#include <iostream>

void printCsvTable(const CsvTable & table);
void print(const Composer & composer);
void printComposers(const vector<Composer> & composers);

using namespace std;

void Cui::studentCreateMenu()
{
    cout << "create!" << endl;
}

void Cui::show()
{
    while (true)
    {
        system("clear");
        vector<Composer> cs = storage_->getAllComposers();
        printComposers(cs);

        cout << "1. create" << endl;
        cout << "3. delete" << endl;
        cout << "enter option: ";
        int option;
        cin >> option;
        if (option == 1)
        {
            this->studentCreateMenu();
        }
        else if (option == 0)
        {
            this->storage_->save();
            break;
        }
    }

    Composer new_c;
    new_c.fullname = "New";
    new_c.year = 2000;
    int new_id = storage_->insertComposer(new_c);
    new_c.id = new_id;

    storage_->removeComposer(3);

    vector<Composer> cs = storage_->getAllComposers();
    printComposers(cs);

    optional<Composer> c_opt = storage_->getComposerById(3);
    if (c_opt)
    {   
        Composer c = c_opt.value();
        print(c);
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }

    storage_->save();
}


void print(const Composer & c)
{
    std::cout << c.id << " | " << c.fullname << " | " << c.year << std::endl;
}

void printComposers(const vector<Composer> & composers)
{
    for (const Composer & c: composers)
    {
        print(c);
    }
}
