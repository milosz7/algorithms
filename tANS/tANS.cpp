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
    double tolerance = 0.01;
    char symbol;
    double proba, proba_sum = 0;
    alphabet = "";
    
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

        Pair *pair = new Pair{symbol, proba};
        proba_sum += proba;
        symbol_data.push_back(pair);
        alphabet.push_back(symbol);
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
        encoding_table[symbol_start[s] + (next[s])++] = x;
    }        
}

void tANS::generate_decoding_table() {
    std::map<char, int> next = ls_map;
    decoding_table.resize(L);
    
    for (int x = 0; x < L; x++) {
        char symbol = symbols[x];
        int n = next[symbol]++;
        int nb_bits = R - floor(log2(n));
        int new_x = (n << nb_bits) - L;
        DecodingNode* t = new DecodingNode(symbol, nb_bits, new_x);
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
        if (alphabet.find(symbol) == std::string::npos) {
            std::cerr << "Character: " << symbol << " is not in the alphabet!" << std::endl;
            exit(1);
        }
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

    int x_start = bits_to_int(state_vec);
    return x_start;
}

int tANS::update_decoding_state(std::vector<bool> &message, int nb_bits, int new_x) {
    int accumulate_threshold = 1;
    std::vector<bool> state_vec;
    int x_add;

    for (int i = 0; i < nb_bits; i++) {
        state_vec.push_back(message.back());
        message.pop_back();
    }

    if (state_vec.size() > accumulate_threshold) {
        x_add = bits_to_int(state_vec);
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

    std::ofstream output{filename_out, std::ios::binary};
    input.open(filename_in);

    if (!output.is_open()) {
        std::cerr << "Error while opening output encode file!" << std::endl;
        exit(1);
    }
    
    if (input.fail()) {
        std::cerr << "Error while opening input encode file!" << std::endl;
        exit(1);
    }

    getline(input, line);
    
    if (input.peek() != EOF) {
        std::cerr << "File to encode has to have only one line!" << std::endl;
        exit(1);
    }

    line_encoded = encode(line);
    dump_line(line_encoded, output);

    input.close();
    output.close();
}

void tANS::dump_line(std::vector<bool> &line, std::ofstream &output) {
    std::string message_str = "";
    size_t n_padding = 0;
    int message_len = line.size();

    while (message_len % CHAR_BIT) {
        message_str.push_back('0');
        n_padding++;
        message_len += 1;
    }

    std::bitset<CHAR_BIT> padding_bitset{n_padding};
    for (int i = 0; i < line.size(); i++)
        message_str += (line.at(i)) ? "1" : "0";
    message_str += padding_bitset.to_string();

    for (int i = 0; i != message_len; i += (CHAR_BIT)) {
        std::bitset<CHAR_BIT> byte{message_str.substr(i, i + CHAR_BIT)};
        unsigned long byte_l = byte.to_ulong();
        unsigned char byte_ch = static_cast<unsigned char>(byte_l);
        output << byte_ch;
    }

    unsigned long padding_l = padding_bitset.to_ulong();
    unsigned char padding_ch = static_cast<unsigned char>(padding_l);
    output << padding_ch;
}

void tANS::decode_file(std::string filename_in, std::string filename_out) {
    std::ifstream input;
    std::string line, line_decoded;
    std::vector<bool> line_bits;
    bool output_newline;

    std::ofstream output{filename_out};
    input.open(filename_in, std::ios::binary);
    

    if (!output.is_open()) {
        std::cerr << "Error while opening output encode file!" << std::endl;
        exit(1);
    }
    
    if (input.fail()) {
        std::cerr << "Error while opening input encode file!" << std::endl;
        exit(1);
    }

    std::vector<unsigned char> bytes(std::istreambuf_iterator<char>(input), {});
    int n_bytes = bytes.size();
    int last_idx = n_bytes - 1;
    for (int i = 0; i < n_bytes; i++) {
        unsigned char h = bytes.at(i);
        std::bitset<CHAR_BIT> bits{h};
    }

    unsigned char last_byte = bytes.at(last_idx);
    std::bitset<CHAR_BIT> bitset_last{last_byte};
    size_t n_to_skip = bitset_last.to_ulong();
    
    std::bitset<CHAR_BIT> bits_with_padding{bytes.at(0)};
    for (int i = CHAR_BIT - n_to_skip - 1; i >= 0; i--)
        line_bits.push_back(bits_with_padding[i]);

    for (int i = 1; i < last_idx; i ++) {
        std::bitset<CHAR_BIT> bits{bytes.at(i)};
        for (int j = CHAR_BIT - 1; j >= 0; j--)
            line_bits.push_back(bits[j]);
    }

    line_decoded = decode(line_bits);
    output << line_decoded;

    input.close();
    output.close();
}

int tANS::bits_to_int(std::vector<bool> &bits) {
    return std::accumulate(bits.begin(), bits.end(), 0,
                [](int p, int q)
                { return (p << 1) + q; }
            );
}
