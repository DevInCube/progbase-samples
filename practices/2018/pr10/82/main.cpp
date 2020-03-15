#include "storage.h"
#include "cui.h"

int main()
{
    Storage storage("../data");
    storage.load();

    Cui cui(&storage);
    cui.show();
}