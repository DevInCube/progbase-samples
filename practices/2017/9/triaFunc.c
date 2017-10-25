    #include <stdlib.h>
    #include <stdio.h>
    #include <assert.h>

    enum TriangleType
    {
        NEISNUYE,
        RIVNOSTORONNIY,
        RIVNOBEDRENNIY,
        DOVILNIY
    };

    enum TriangleType getTriangleType(int a, int b, int c);
    void printTriangleType(enum TriangleType type);

    int main(void)
    {
        assert(getTriangleType(3, 4, 5) == DOVILNIY);
        assert(getTriangleType(3, 3, 3) == RIVNOSTORONNIY);
        assert(getTriangleType(3, 3, 4) == RIVNOBEDRENNIY);
        assert(getTriangleType(1, 1, 10) == NEISNUYE);
        //
        enum TriangleType t = getTriangleType(3, 4, 5);
        printTriangleType(t);
        return 0;
    }

    enum TriangleType getTriangleType(int a, int b, int c)
    {
        return NEISNUYE;
    }

    void printTriangleType(enum TriangleType type)
    {
        switch (type)
        {
        case NEISNUYE:
            printf("Ne isnuye\n");
            break;
        case RIVNOSTORONNIY:
            printf("Rivnostoronniy\n");
            break;
            //
        }
    }