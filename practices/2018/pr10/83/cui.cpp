#include "cui.h"
#include <iostream>


void print(Composer & c);
void printComposers(vector<Composer> & v);

void Cui::studentCreateMenu()
{
    std::cout << "Hello";
    int i;
    std::cin >> i;
    this->storage_->in
}

void Cui::show()
{
    bool is_running = true;
    while (is_running)
    {
        int command;
        auto cs = this->storage_->getAllComposers();
            printComposers(cs);
        std::cout << "Enter command:";
        std::cin >> command;
        if (command == 0)
        {
            is_running = false;
        }
        else if (command == 1)
        {
            this->studentCreateMenu();
        }
    }

    

    // auto comps = storage.getAllComposers();
    // printComposers(comps);
    // storage.removeComposer(3);
    // Composer new_comp;
    // new_comp.fullname = "Bellamy";
    // new_comp.year = 1980;
    // int new_id = storage.insertComposer(new_comp);
    // cout << new_id << endl;
    // //comps = storage.getAllComposers();
    // //printComposers(comps);
    // storage.save();
    
    // string text_str = readAllFromFile("data.csv");
    // // cout << text_str;
    // CsvTable csv_table = Csv::createTableFromString(text_str);
    // printfStringsTable(csv_table);
    // string text_str_2 = Csv::createStringFromTable(csv_table);
    // cout << text_str_2;
    // writeAllToFile("data2.csv", text_str_2);
    

//     Composer testList[] = {
//         {1, "Johann Bach", 1721, "Brandenburg Concertos", 1126},
//         {2, "Wolfgang Mozart", 1783, "Turkish stop", 498},
//         {3, "Ludwig van Beethoven", 1801, "Moonlight Sonata", 122},
//         {4, "Richard Wagner", 1856, "Ride of the Valkyries", 56},
//     };
//     int testListlength = 4;

//     CsvTable inCsvTable;
//     vector<Composer> composers;

}


void print(Composer & c)
{
    printf("%d,", c.id);
    printf("%s,", c.fullname.c_str());
    printf("%d\n", c.year);
}

void printComposers(vector<Composer> & v)
{
    for (Composer & c : v)
    {
        print(c);
    }
}