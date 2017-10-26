#include <stdlib.h>
#include <stdio.h>
#include <progbase/console.h>

enum BookCommand
{
    NOTSET,
    BOOK_UP,   // 65
    BOOK_DOWN, // 66
    BOOK_BACK  // 127
};

enum BookCommand getBookCommandUserInput();
void printPage(char pages[][100], int nPages, int page);

int main(void)
{
    char book[][100] = {
        "slkjha dsdlhalhd",
        "asdlihadaksd hgasdkhga",
        "asdkjgad kasdgaskdgaskdjhgasdkjhgsd"};
    const int nPages = sizeof(book) / sizeof(book[0]);
    int currentPageIndex = 0;

    while (1)
    {
        Console_clear();
        printPage(book, nPages, currentPageIndex);

        enum BookCommand command = getBookCommandUserInput();
        switch (command)
        {
        case BOOK_UP:
            currentPageIndex -= 1;
            if (currentPageIndex < 0)
            {
                currentPageIndex = nPages - 1;
            }
            break;
        case BOOK_DOWN:
            currentPageIndex = (currentPageIndex + 1) % nPages;
            break;
        case NOTSET:
        case BOOK_BACK:
            return 0;
        }
    }

    return 0;
}

void printPage(char pages[][100], int nPages, int page) {
    printf("Page %i/%i\n", page + 1, nPages);
    puts("------------------------------------");
    puts(pages[page]);
    puts("------------------------------------");
    puts("Commands: KeyUp | KeyDown | Backspace ");
}

enum BookCommand getBookCommandUserInput()
{
    enum BookCommand command = NOTSET;
    do
    {
        char keyCode = Console_getChar();
        switch (keyCode)
        {
        case 127:
            command = BOOK_BACK;
            break;
        case 65:
            command = BOOK_UP;
            break;
        case 66:
            command = BOOK_DOWN;
            break;
        }
    } while (command == NOTSET);
    return command;
}