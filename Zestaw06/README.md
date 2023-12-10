Jakie operacje są relatywnie szybko wykonywane na drzewie BST, porównaj złożoności czasowe z innymi strukturami danych.
- Search - Średnio O(log(n)), pesymistycznie O(n),
- Insert - Średnio O(log(n)), pesymistycznie O(n),
- Delete - Średnio O(log(n)), pesymistycznie O(n)

W przypadku np. listy wiązanej te złożoności wynoszą:
- Search - Średnio O(n), pesymistycznie O(n)
- Insert - Średnio O(n), pesymistycznie O(n)
- Delete Średnio O(n), pesymistycznie O(n)

Różnica wynika z faktu, że aby wykonać każdą z operacji w liście wiązanej musimy iterować po całej liście, a struktura drzewa binarnego sprawia, że poruszamy się po nim w określony sposób co umożliwia szybsze realizowanie powyższych operacji.

Na czym polega iteracyjne przechodzenie drzewa bez użycia rekurencji?

Iteracyjne przechodzenie drzewa BST polega na wykorzystaniu pętli while z warunkiem (current != nullptr) i dodatkowych warunków w zależności od wykonywanej czynności. W pętli zmieniamy wartość zmiennej current na wskaźnik znajdujący się w polu left lub right obecnego węzła przechodząc w ten sposób do głębszych warstw drzewa.

W jaki sposób można użyć drzewo BST do sortowania elementów? Wskaż podobieństwo do wcześniej poznanego algorytmu sortowania. Omów wady takiego rozwiązania.

Aby użyć drzewo BST do sortowania należy umieścić wszystkie elementy w drzewie i wypisać je w porządku inorder. Z poznanych algorytmów sortowania najbardziej podobny w działaniu jest InsertionSort. Złożoność obliczeniowa takiego rozwiązania wynosi:
- średnia - n razy wykonujemy operację insert tak więc średnia złożoność wynosi O(nlog(n))
- pesymistyczna - n razy wykonujemy operację insert, która ma pesymistyczną złożoność O(n) więc otrzymujemy całkowitą złożoność O(n^2)

Na czym polega przechodzenie drzewa preorder?

Przechodzenie drzewa preorder polega na wypisywaniu wartości korzenia, a następnie wypisaniu wartości lewego i prawego poddrzewa.

Na czym polega przechodzenie drzewa inorder?

Przechodzenie drzewa inorder polega na wypisaniu wartości lewego poddrzewa, następnie wartości korzenia, a ostatecznie wartości prawego poddrzewa.

Na czym polega przechodzenie drzewa postorder?

Przechodzenie drzewa postorder polega na wypisaniu wartości lewego poddrzewa, prawego poddrzewa i ostatecznie wartości korzenia.
