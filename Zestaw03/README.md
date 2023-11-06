1. Jakie są zalety implementacji wskaźnikowej, a jakie implementacji tablicowej?
    - implementacja wskaźnikowa ma mniejszą złożoność dla operacji usuwania i dodawania elementów w środek listy
    - implementacja tablicowa zapewnia szybszy dostęp do poszczególnych elementów w tablicy gdyż nie skaczemy po adresach w pamięci
    - implementacja tablicowa jest łatwiejsza w implementacji
2. Jak zaimplementować listę dwukierunkową zapamiętując tylko jeden wskaźnik?
    Należy zainicjować listę z jednym węzłem, którego pole next to head a pole prev to tail. Przy inicjacji oba pola powinny wskazywać na ten węzeł. W ten sposób pozbywamy sie różnych przypadków dodawania i usuwania elementów z listy w zależności od jej zapełnienia.