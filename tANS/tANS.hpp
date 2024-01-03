#ifndef ANS_H
#define ANS_H
#include <vector>
#include <iostream>
#include <math.h>
#include <utility>
#include <stdexcept>
#include <fstream>
#include <map>
#include <algorithm>
#include <numeric>
#include <stdlib.h>
#include <regex>
#include <iterator>
#include <sstream>

class tANS {
    using Pair = std::pair<char, double>;

    public:
        struct DecodingNode {
            char symbol;
            int nb_bits;
            int new_x;
        };

        ~tANS();
        void read_data(std::string filename);
        std::vector<bool> encode(std::string message);
        std::string decode(std::vector<bool> message);
        void encode_file(std::string filename);
        void decode_file(std::string filename);

    private:
        int L, R;
        std::map<char, int> ls_map;
        std::map<char, int> symbol_start;
        std::map<char, int> nb;

        std::vector<DecodingNode*> decoding_table;
        std::vector<int> new_x;
        std::vector<int> encoding_table;
        std::vector<int> states;
        std::vector<char> symbols;
        std::vector<int> states_temp;
        std::vector<int> nb_bits;
        std::vector<Pair*> symbol_data;

        bool validate_line(std::string &line);
        void spread();
        void generate_states();
        void generate_nb_bits();
        void generate_start();
        void generate_encoding_table();
        void generate_decoding_table();
        int get_extractor(int exp);
        void use_bits(std::vector<bool>&message, int state, int nb_bits);
        void output_state(std::vector<bool>&message, int state);
        int read_decoding_state(std::vector<bool>&message);
        int update_decoding_state(std::vector<bool> &message, int nb_bits, int x_old);
        void create_tables();
        void dump_line(std::vector<bool> &line, std::ofstream &output);
        int min(int a, int b);
        void ull_to_encoded(std::vector<bool> &message, unsigned long long line_chunk);
};

#endif