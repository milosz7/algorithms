#ifndef TEMPLATESTACK_HPP
#define TEMPLATESTACK_HPP
#include <stdexcept>
#include <utility>

template <class T, const int N>
class TemplateStack {

public:
    TemplateStack() : _current{0} {}
    ~TemplateStack() { delete[] stack; }
    template<class U>
    void push(U&& x);
    T pop();
    T& top();
    int size();
    bool empty();

private:
    int _current = 0;
    T *stack = new T[N];
};

template <class T, const int N>
template <class U>
void TemplateStack<T, N>::push(U &&x) {
    if (_current == N)
        throw std::out_of_range("Stack overflow!");
    stack[++_current] = std::forward<U>(x);
}

template <class T, const int N>
bool TemplateStack<T, N>::empty() { return _current == 0; }

template <class T, const int N>
int TemplateStack<T, N>::size() { return _current; }

template <class T, const int N>
T &TemplateStack<T, N>::top() { return stack[_current]; }

template <class T, const int N>
T TemplateStack<T, N>::pop() {
    if (empty())
        throw std::out_of_range("Stack is empty.");
    return stack[_current--];
}

#endif