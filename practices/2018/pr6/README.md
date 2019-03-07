1. Створити (або взяти існуючу) просту консольну програму з 2-ма "меню".  
    В програмі виводити її назву, пункти меню мають підписи англійською мовою.  
    Винести всі рядки, що виводяться у консоль у глобальні статичні змінні, наприклад:
    ```c
    static const char * AppName = "My app";
    static const char * MainMenu = "Main menu";
    static const char * SubMenu1 = "Sub menu 1";
    static const char * SubMenu2 = "Sub menu 2";
    static const char * InvalidInputError = "Invalid input";
    
    int main()
    {
        printf("====%s====\n", AppName);
        //..
        return 0;
    }
    ```
    Реалізувати модуль [**StrStrMap**][strstrmap-int] і підключити його в `main` модуль.  
    Створити та ініціалізувати на початку функції `main` екземпляр **StrStrMap** `stringsEn`, занести у нього всі глобальні рядки:
    ```c
    StrStrMap_add(&stringsEn, "AppName", "My app");
    StrStrMap_add(&stringsEn, "MainMenu", "Main menu");
    // ...
    ```
    Створити глобальний вказівник на **StrStrMap** `strings` і присвоїти йому адресу `stringsEn`.   
    Видалити глобальні рядки, а замість них у коді використовувати отримання рядка зі словника `strings`:
    ```c
    static StrStrMap * strings;
    
    int main()
    {
        StrStrMap stringsEn;
        // @todo init and fill stringsEn here
        strings = &stringsEn;
        //
        const char * appNameValue = StrStrMap_get(strings, "AppName");
        printf("====%s====\n", appNameValue);
        //..
        // @todo deinit stringsEn here
        return 0;
    }
    ```
    Створити та ініціалізувати на початку функції `main` екземпляр **StrStrMap** `stringsUa`, занести у нього такі ж ключі, але зі значеннями, що є транслітом української мови:
    ```c
    StrStrMap_add(&stringsUa, "AppName", "Moya programma");
    StrStrMap_add(&stringsUa, "MainMenu", "Holovne menu");
    // ...
    ```
    Переприсвоїти `strings` на адресу `stringsUa` і перевірити роботу програми.
    
    ```c
    static StrStrMap * strings;
    
    int main()
    {
        StrStrMap stringsEn;
        // @todo init and fill stringsEn here
        StrStrMap stringsUa;
        // @todo init and fill stringsUa here
        strings = &stringsUa;
        //
        const char * appNameValue = StrStrMap_get(strings, "AppName");
        printf("====%s====\n", appNameValue);
        //..
        // @todo deinit stringsEn here
        // @todo deinit stringsUa here
        return 0;
    }
    ```
    
    [strstrmap-int]: https://docs.google.com/presentation/d/18PQX143prl8iTkqzjQM7h1_GZQ1swnf17oQ0TLarKpw/edit#slide=id.g50ad2596a1_4_0
