#include "storage.h"
#include "cui.h"

int main(int argc, char * argv[])
{
    Storage storage("./data");
    storage.load();

    Cui cui(&storage);
    cui.show();
}