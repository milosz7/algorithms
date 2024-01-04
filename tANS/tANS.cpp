#include "tANS.hpp"

tANS::~tANS() {
    for (DecodingNode* t : decoding_table)
        delete t;
    for (Pair *p : symbol_data)
        delete p;
}

void tANS::read_data(std::string filename) {
    std::ifstream input;
    std::string line;
    constexpr double tolerance = 0.01;
    char symbol;
    double proba, proba_sum = 0;
    
    input.open(filename);
    if (input.fail()) {
        std::cerr << "Error while opening symbol input file!" << std::endl;
        exit(1);
    }

    while (input.peek() != EOF) {
        getline(input, line);
        if (!validate_line(line)) {
            std::cerr << "Input line: " << line << " is invalid!";
            exit(1);
        }

        std::size_t delim = line.find_last_of(",");
        char symbol = line[0];
        double proba = std::stod(line.substr(delim + 1));

        Pair *pair = new Pair;
        pair->first = symbol;
        pair->second = proba;
        proba_sum += proba;
        symbol_data.push_back(pair);
    }

    if (std::abs(proba_sum - 1.0) > tolerance) {
        std::cerr 
            << "Sum of probabilities is outsde the range! (tolerance is: +-" << tolerance << ")" 
            << std::endl;
        exit(1);
    }
        
    input.close();
    create_tables();
}

bool tANS::validate_line(std::string &line) {
    std::regex reg("[ -~],\\d{1,2}\\.\\d+");
    return std::regex_match(line, reg);
}

void tANS::set_table_size() {
    L = 1;
    R = 0;
    int vocab_size = symbol_data.size();

    while (L < 4 * vocab_size) {
        L *= 2;
        R += 1;
    }
}

// https://github.com/JarekDuda/AsymmetricNumeralSystemsToolkit/blob/master/ANStoolkit.cpp
void tANS::quantize_probabilities_fast() {
    int used = 0;
    char max_proba_symbol;
    double max_proba = 0;
    for (Pair *pair : symbol_data) {
        char symbol = pair->first;
        double proba = pair->second;
        ls_map[symbol] = std::round(L * proba);

        if (!ls_map[symbol])
            ls_map[symbol]++;
        used += ls_map[symbol];

        if(proba > max_proba) {
            max_proba = proba;
            max_proba_symbol = symbol;  
        }
    }
    ls_map[max_proba_symbol] += L - used;
}

// https://github.com/JarekDuda/AsymmetricNumeralSystemsToolkit/blob/master/ANStoolkit.cpp
void tANS::quantize_probabilities() {
    int vocab_size = symbol_data.size();
    std::map<char, double> proba_exact;
    std::map<char, double> inverse_proba;
    std::map<char, double> current_cost;
    int used = 0;

    for (Pair *p : symbol_data) {
        char symbol = p->first;
        double proba = p->second;
        proba_exact[symbol] = proba * L;
        inverse_proba[symbol] = 1.0 / proba;
        ls_map[symbol] = std::round(proba_exact[symbol]);
        if (!ls_map[symbol])
            ls_map[symbol]++;
        used += ls_map[symbol];
        current_cost[symbol] = pow(proba_exact[symbol] - ls_map[symbol], 2.0) * inverse_proba[symbol]; 
    }

    if (used != L) {
        int sgn = (used > L) ? -1 : 1;
        std::vector<std::pair<double, char>> v;
        for (Pair *p : symbol_data) {
            char symbol = p->first;
            if (ls_map[symbol] + sgn)
                v.push_back(
                    {current_cost[symbol] - pow(proba_exact[symbol] - (ls_map[symbol] + sgn), 2) * inverse_proba[symbol],
                     symbol}
                    );
        }
        std::make_heap(v.begin(), v.end());

        for( ; used != L; used += sgn) {
            auto pair = v.front();
            std::pop_heap(v.begin(), v.end());
            v.pop_back();
            current_cost[pair.second] -= pair.first;
            if ((ls_map[pair.second] += sgn) + sgn) {
                v.push_back(
                    {current_cost[pair.second] - pow(proba_exact[pair.second] - (ls_map[pair.second] + sgn), 2) * inverse_proba[pair.second], 
                     pair.second}
                    );
                std::push_heap (v.begin(), v.end());
            }
        }
    }
}

void tANS::spread() {
    symbols.resize(L);
    state0 = L;
    int i = 0;
    int step = (L >> 1) + (L >> 3) + 3;
    int mask = L - 1;

    for (Pair *pair : symbol_data) {
        char symbol = pair->first;
        int L_s = ls_map[symbol];
        for (int j = 0; j < L_s; j++) {
            symbols[i] = symbol;
            i = (i + step) & mask;
        }
    }
}

void tANS::generate_nb_bits() {
    int vocab_size = symbol_data.size();
    int r = R + 1;

    for (Pair *pair : symbol_data) {
        char symbol = pair->first;
        double proba = pair->second;
        int L_s = ls_map[symbol];
        int k_s = R - floor(log2(L_s));
        int nb_val = (k_s << r) - (L_s << k_s);
        nb[symbol] = nb_val;
    }
}

void tANS::generate_start() {
    int vocab_size = symbol_data.size();

    for (int i = vocab_size - 1; i >= 0; i--) {
        Pair *current = symbol_data.at(i);
        char symbol = current->first;
        int L_r = ls_map[symbol];
        int start = -1 * L_r;
        for (int j = 0; j < i; j++) {
            char symbol_prim = symbol_data.at(j)->first;
            int L_r_prim = ls_map[symbol_prim];
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
        // std::cout << s << ": " << symbol_start[s] <<std::endl;
        encoding_table[symbol_start[s] + (next[s])++] = x;
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
    int state = state0;
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
    set_table_size();
    quantize_probabilities();
    spread();
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

void tANS::encode_file(std::string filename_in, std::string filename_out) {
    std::ifstream input;
    std::string line;
    std::vector<bool> message;
    std::vector<bool> line_encoded;

    std::ofstream output{filename_out};
    input.open(filename_in);

    if (!output.is_open()) {
        std::cerr << "Error while opening output encode file!" << std::endl;
        exit(1);
    }
    
    if (input.fail()) {
        std::cerr << "Error while opening input encode file!" << std::endl;
        exit(1);
    }

    while(input.peek() != EOF) {
        getline(input, line);

        line_encoded = encode(line);
        auto it = message.begin();
        std::advance(it, message.size());
        std::insert_iterator<std::vector<bool>> insert(message, it);
        std::copy(line_encoded.begin(), line_encoded.end(), insert);
        dump_line(line_encoded, output);
    }

    input.close();
    output.close();
}

void tANS::dump_line(std::vector<bool> &line, std::ofstream &output) {
    int out_bits = 64;
    constexpr int acc_threshold = 1;
    std::vector<bool> chunk_vec;
    ull encoded;
    int current_size;

    while ((current_size = line.size())) {
        int bits_to_dump = min(out_bits, current_size);
        // meaning zero should be the output
        if (line.back() == 0)
            bits_to_dump = 1;

        chunk_vec.resize(bits_to_dump);

        for (int i = 0; i < bits_to_dump; i++) {
            chunk_vec.at(i) = line.back();
            line.pop_back();
        }

        if (bits_to_dump > acc_threshold) {
             encoded = std::accumulate(chunk_vec.begin(), chunk_vec.end(), (ull)0, 
                        [](ull p, ull q)
                        { return (p << 1) + q; }
                      );
        } else {
            encoded = chunk_vec.at(0);
        }
        output << encoded << ((line.size()) ? " " : "\n");
        chunk_vec.clear();
    }
}

int tANS::min(int a, int b) { return (a < b) ? a : b; }

void tANS::decode_file(std::string filename_in, std::string filename_out) {
    std::ifstream input;
    std::string line, line_decoded;
    std::vector<bool> line_bits;
    ull encoded;

    std::ofstream output{filename_out};
    input.open(filename_in);

    if (!output.is_open()) {
        std::cerr << "Error while opening output encode file!" << std::endl;
        exit(1);
    }
    
    if (input.fail()) {
        std::cerr << "Error while opening input encode file!" << std::endl;
        exit(1);
    }

    while (input.peek() != EOF) {
        getline(input, line);
        std::stringstream ss_line(line);

        while (ss_line >> encoded)
            ull_to_encoded(line_bits, encoded);
        line_decoded = decode(line_bits);
        output << line_decoded;
        line_bits.clear();
        output << "\n";
    }

    input.close();
    output.close();
}

void tANS::ull_to_encoded(std::vector<bool> &message, ull line_chunk) {
    std::vector<bool> message_chunk;
    int n_bits = ((line_chunk == 0) ? 0 : std::log2(line_chunk)) + 1;

    for (int i = 0; i < n_bits; i++, line_chunk >>= 1) {
        message_chunk.push_back(line_chunk & 1);
    }
    int size_old = message.size();
    auto it = message.begin();
    std::insert_iterator<std::vector<bool>> insert(message, it);
    std::copy(message_chunk.begin(), message_chunk.end(), insert);
}
