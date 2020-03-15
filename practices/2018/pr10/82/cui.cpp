#include "cui.h" 
#include <iostream>

using namespace std;

void printCsvTable(const CsvTable & table)
{
    for (int i = 0; i < table.size(); i++)
    {
        const CsvRow & row = table.at(i);
        for (int j = 0; j < row.size(); j++)
        {
            if (i == 0 && j == 0)
            {
                printf("%s", row[j].c_str());
            }
            else if (i != 0 && j == 0)
            {
                printf("%s", row[j].c_str());
            }
            else
            {
                printf(",");
                printf("%s", table[i][j].c_str());
            }
        }
        printf("\n");
    } 
}

void print(const Composer & c)
{
    cout << c.id << " | " << c.fullname << " | " << c.year << endl;
}

void printComposers(const vector<Composer> & composers)
{
    for (auto & c : composers)
    {
        print(c);
    }
}

void Cui::studentCreateMenu()
{
    cout << "Create!" << endl;
}

void Cui::show()
{
    bool is_running = true;
    while (is_running)
    {
        // show all composers
        vector<Composer> composers = storage_->getAllComposers();
        printComposers(composers);
        //
        cout << "enter option:";
        int command;
        cin >> command;
        if (command == 0)
        {
            break;
        }
        else if (command == 1)
        {
            this->studentCreateMenu();
        }
    }

    // this->storage_.removeComposer(2);

    // vector<Composer> composers = storage.getAllComposers();
    // printComposers(composers);

    // optional<Composer> c_opt = storage.getComposerById(4);
    // if (c_opt)
    // {
    //     Composer & c = c_opt.value();
    //     print(c);
    // }
    // else 
    // {
    //     cout << "Not found" << endl;
    // }

    // Composer new_c;
    // new_c.fullname = "Yorke";
    // new_c.year = 1980;
    // int new_id = storage.insertComposer(new_c);
    // new_c.id = new_id;
}