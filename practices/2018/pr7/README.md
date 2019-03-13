1. [Згенерувати][gen] послідовність цілих чисел. Намалювати на листочку бінарне дерево пошуку (БДП) з відповідними ключами.
2. Створити [АТД бінарне дерево][bin-key] (лише з цілочисельним ключем).  
Вручну побудувати бінарне дерево пошуку з нод з ключами згенерованої випадкової послідовності цілих чисел з (1).  
Використати дану функцію **in-order** обходу бінарного дерева для перевірки відсортованості ключів у дереві:
    ```c
    void traverseInOrder(BinTree *node)
    {
        if (node == NULL)
            return;
        traverseInOrder(node->left);
        printf("%i, ", node->key);
        traverseInOrder(node->right);
    }
    ```
    Реалізувати **preorder** та **postorder** обходи дерева:
    ```c
    void traversePreOrder(BinTree *node);
    void traversePostOrder(BinTree *node);
    ```
    Реалізувати функцію звільнення пам'яті дерева і перевірити роботу програми на Valgrind.
    ```c
    void clearBinTree(BinTree *node);
    ```
3. Аналогічно (2) але реалізувати функцію вставки ключа у бінарне дерево пошуку і послідовно додати до пустого бінарного дерева ноди з ключами згенерованої випадкової послідовності цілих чисел з (1).   
Реалізувати функцію для форматованого виводу бінарного дерева у консоль зі збереженням інформацію про зв'язки між нодами дерева.
1. Реалізувати операції `lookup` та `delete` в БДП.

[gen]: https://www.random.org/integers/?num=10&min=-50&max=50&col=1&base=10&format=html&rnd=new
[bin-key]: https://docs.google.com/presentation/d/18PQX143prl8iTkqzjQM7h1_GZQ1swnf17oQ0TLarKpw/edit#slide=id.g51b6482251_100_317
