#include "tANS.hpp"

tANS::~tANS() {
    for (DecodingNode* t : decoding_table)
        delete t;
}

void tANS::read_data(std::string filename) {
    std::ifstream input;
    constexpr double tolerance = 0.01;
    char symbol;
    double proba, proba_sum;
    
    input.open(filename);
    if (input.fail()) {
        std::cerr << "Error while opening symbol input file!" << std::endl;
        exit(1);
    }

    while(input >> symbol && input >> proba) {
        Pair pair;
        pair.first = symbol;
        pair.second = proba;
        proba_sum += proba;
        symbol_data.push_back(pair);
    }

    if (abs(proba_sum - 1.0) > tolerance)
        throw std::invalid_argument("Probabilities of symbols must sum up to approximately 1.0!");
        
    input.close();
    create_tables();
}

void tANS::spread() {
    L = 1;
    R = 0;
    int i = 0;
    int step = (5 * L) / 8 + 3;
    int vocab_size = symbol_data.size();

    while (L < 4 * vocab_size) {
        L *= 2;
        R += 1;
    }
    symbols.resize(L);

    for (Pair pair : symbol_data) {
        char symbol = pair.first;
        double proba = pair.second;
        int L_s = proba * L;
        ls_map[symbol] = L_s;

        for (int j = 0; j < L_s; j++) {
            symbols[i] = symbol;
            i = (i + step) % L;
        }
    }
}

void tANS::generate_states() {
    states.resize(L);
    for (int i = 0; i < L; i++)
        states.at(i) = L + i;
}

void tANS::generate_nb_bits() {
    int vocab_size = symbol_data.size();
    int r = R + 1;

    for (Pair pair : symbol_data) {
        char symbol = pair.first;
        double proba = pair.second;
        int L_s = proba * L;
        int k_s = R - floor(log2(L_s));
        int nb_val = (k_s << r) - (L_s << k_s);
        nb[symbol] = nb_val;
    }

    nb_bits.resize(L);
    for (int i = 0; i < L; i++) {
        nb_bits[i] = (states[i] + nb[symbols[i]]) >> r;
    }
}

void tANS::generate_start() {
    int vocab_size = symbol_data.size();
    for (int i = 0; i < vocab_size; i++) {
        Pair current = symbol_data.at(i);
        double proba = current.second;
        char symbol = current.first;
        int L_r = proba * L;
        int start = -1 * L_r;
        for (int j = i+1; j < vocab_size; j++) {
            double proba_prim = symbol_data.at(j).second;
            int L_r_prim = proba_prim * L;
            start += L_r_prim;
        }
        symbol_start[symbol] = start;
    }
}

void tANS::generate_encoding_table() {
    std::map<char, int> next = ls_map;
    encoding_table.resize(L);

    for (int x = L; x < 2 * L; x++) {
        char s = symbols[x - L];
        encoding_table[symbol_start[s] + (next[s]++)] = x;
    }
}

void tANS::generate_decoding_table() {
    std::map<char, int> next = ls_map;
    decoding_table.resize(L);
    
    for (int x = 0; x < L; x++) {
        DecodingNode* t = new DecodingNode;
        char symbol = symbols[x];
        int n = next[symbol]++;
        int nb_bits = R - floor(log2(n));
        t->symbol = symbol;
        t->nb_bits = nb_bits;
        t->new_x = (n << nb_bits) - L;
        decoding_table[x] = t;   
    }
}

int tANS::get_extractor(int exp) {
    int result = 1;

    for (int i = 0; i < exp; i++)
        result *= 2;
    return result - 1;
}

void tANS::use_bits(std::vector<bool>&message, int state, int nb_bits) {
    int n_to_extract = get_extractor(nb_bits);
    int least_significant_bits = state & n_to_extract;
    for (int i = 0; i < nb_bits; i++, least_significant_bits >>= 1)
        message.push_back((least_significant_bits & 1));
}

void tANS::output_state(std::vector<bool> &message, int state) {
    for (int i = 0; i < R+1; i++, state >>= 1)
        message.push_back((state & 1));
}

std::vector<bool> tANS::encode(std::string message) {
    std::vector<bool> result;
    int r = R + 1;
    int state = states[0];
    int len = message.length();
    
    for (int i = 0; i < len; i++) {
        char symbol = message[i];
        int nb_bits = (state + nb[symbol]) >> r;
        use_bits(result, state, nb_bits);
        state = encoding_table[symbol_start[symbol] + (state >> nb_bits)];
    }

    output_state(result, state);
    return result;
}

int tANS::read_decoding_state(std::vector<bool> &message) {
    int r = R + 1;
    std::vector<bool> state_vec;

    for (int i = 0; i < r; i++) {
        state_vec.push_back(message.back());
        message.pop_back();
    }

    int x_start = std::accumulate(state_vec.begin(), state_vec.end(), 0, 
                   [](int p, int q) 
                   { return (p << 1) + q; }
                  );
    return x_start;
}

int tANS::update_decoding_state(std::vector<bool> &message, int nb_bits, int new_x) {
    constexpr int acc_threshold = 1;
    std::vector<bool> state_vec;
    int x_add;

    for (int i = 0; i < nb_bits; i++) {
        state_vec.push_back(message.back());
        message.pop_back();
    }
    if (state_vec.size() > acc_threshold) {
        x_add = std::accumulate(state_vec.begin(), state_vec.end(), 0, 
                    [](int p, int q)
                    { return (p << 1) + q; }
                  );
    } else {
        x_add = state_vec.at(0);
    }
    
    return new_x + x_add;
}

void tANS::create_tables() {
    spread();
    generate_states();
    generate_nb_bits();
    generate_start();
    generate_encoding_table();
    generate_decoding_table();
}

std::string tANS::decode(std::vector<bool> message) {
    std::string output = "";
    int x_start = read_decoding_state(message);
    DecodingNode* t = decoding_table.at(x_start - L);

    while (message.size()) {
        output.push_back(t->symbol);
        x_start = update_decoding_state(message, t->nb_bits, t->new_x);
        t = decoding_table.at(x_start);
    }

    std::reverse(output.begin(), output.end());
    return output;
}