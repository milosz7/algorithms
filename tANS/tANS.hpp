#ifndef ANS_H
#define ANS_H
#include <vector>
#include <iostream>
#include <cmath>
#include <utility>
#include <fstream>
#include <map>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <regex>
#include <iterator>
#include <sstream>

class tANS {
    using Pair = std::pair<char, double>;
    using ull = unsigned long long;

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
        void encode_file(std::string filename_in, std::string filename_out);
        void decode_file(std::string filename_in, std::string filename_out);

    private:
        int L, R, state0;
        std::map<char, int> ls_map;
        std::map<char, int> symbol_start;
        std::map<char, int> nb;

        std::vector<DecodingNode*> decoding_table;
        std::vector<int> encoding_table;
        std::vector<char> symbols;
        std::vector<Pair*> symbol_data;

        bool validate_line(std::string &line);
        void set_table_size();
        void quantize_probabilities_fast();
        void quantize_probabilities();
        void spread();
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
        void ull_to_encoded(std::vector<bool> &message, ull line_chunk);
};

#endif