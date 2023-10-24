Co to jest stos? - Struktura danych w której dane odkładane są na wierzch stosu i z wierzchołka są pobierane (LIFO - last in first out).

Przykłady zastosowania stosu:
 - w implementacji algorytmów np. ONP
 - historia odwiedzonych stron w przeglądarkach
 - wykorzystywane w językach programowania do przechowywania danych programu
 
 Dlaczego operacja pop() z std::stack nie zwraca wartości elementu? - Ponieważ usuwa go ze stosu i nie może zwrócić referencji do niego, co sprawia, że jedyny sposób aby zwrócić wartość to poprzez kopię co jest nieefektywne.
 
 Dlaczego operacja pop() z std::stack nie zwraca referencji do elementu? - ponieważ usuwa go ze stosu.
 
 Do czego służy funkcja std::queue::emplace? - Do dodawania elementu na koniec kolejki.
 
