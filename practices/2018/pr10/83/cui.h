#include "storage.h"

class Cui
{
    Storage * const storage_;

    // students menus
    void studentsMainMenu();
    void studentMenu(int entity_id);
    void studentUpdateMenu(int entity_id);
    void studentDeleteMenu(int entity_id);
    void studentCreateMenu();
    
public:
    Cui(Storage * storage): storage_(storage) {}
    //
    void show();
};