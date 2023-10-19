#include "ArrayQueue.hpp"
#include "LinkedQueue.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#define N_QUEUES 10
#define MAX_EXPONENT 9

static int get_digit(int number, int index);
static void radix(std::vector<int> &vec);

int main()
{
    std::vector<int>input_vec;
    std::string line;

    while(std::cin >> line) {
        input_vec.push_back(std::stoi(line));
    }

    radix(input_vec);

    for (const auto& n : input_vec) {
        std::cout << n << std::endl;
    }

    return 0;
}

static int get_digit(int number, int index) {
    // number divided by nth power of 10 cast to an integer
    // gives us a number x which indicates how many times
    // we can sum the number that we divided by before we
    // reach a number that is higher than our input number
    // by performing a (x mod 10) operation we obtain the 
    // least significant digit which helps us define to 
    // which queue should the number be pushed. 
    return (int)(number / pow(10, index)) % 10;
}

// uncomment the preferred queue implementation
static void radix(std::vector<int> &vec) {
    int vec_size = vec.size();
    ArrayQueue<int>** queues = new ArrayQueue<int>*[N_QUEUES];
    // LinkedQueue<int>** queues = new LinkedQueue<int>*[N_QUEUES];
    

    for (int i = 0; i < N_QUEUES; ++i) {
        // initialising queue with vec_size in case of all numbers
        // having the same digit at some index 
        queues[i] = new ArrayQueue<int>(vec_size);
        // queues[i] = new LinkedQueue<int>(vec_size);

    }

    // iterating through every digit of a number assuming they are <= 10^9
    for (int j = 0; j <= MAX_EXPONENT; j++) {
        for (int k = 0; k < vec_size; k++) {
            int queue_idx = get_digit(vec.at(k), j);
            queues[queue_idx]->push(vec.at(k));
        }

        int it = 0;

        for (int l = 0; l < N_QUEUES; l++) {
            while(!queues[l]->empty()) {
                int popped = queues[l]->pop();
                vec.at(it) = popped;
                it++;
            }
        }
    }

    for (int m = 0; m < N_QUEUES; ++m) {
        delete queues[m];
    }
    delete queues;
}
