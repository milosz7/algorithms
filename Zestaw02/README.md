Opisz 3 sposoby obsługi cykliczności bufora:
- 1. Inkrementowanie zarówno head jak i tail i indeksowanie elementów kolejki jako queue[(head++ v tail++) % capacity]. Aby poznać liczbę elementów kolejki wykonujemy operację (tail - head).
- 2. Nadpisywanie head / tail w podobny sposób jak powyżej head/tail = head/tail++ % capacity. Aby poznać liczbę elementów kolejki wykonujemy operację:
size = (head - tail) i dodajemy capacity do size dopóki size < 0.
- 3. Gdy capacity == 2^n to możemy zastosować operację "bitowego or" w następujący sposób: head/tail = (head/tail++) & (capacity - 1). W celu poznania liczby elementów postępujemy analogicznie jak w 2.

Omów przykłady zastosowania kolejki:
 - Wykorzystywana w przydziale np dostępu do dysku/procesora w systemach operacyjnych.
 - Asynchroniczne przekazywanie danych pomiędzy procesami

Co oznaczają akronimy LIFO i FIFO?:
- LIFO - Last in first out (stos)
- FIFO - First in first out (kolejka)
