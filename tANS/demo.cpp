#include "tANS.hpp"

int main()
{
    // initialization
    tANS t_ans = tANS();
    // loading the alphabet
    t_ans.read_data("alphabet.txt");
    // encoding / decoding strings
    std::string to_encode = "somesamplemessage";
    std::vector<bool> encoded = t_ans.encode(to_encode);
    // encoded message as a vector
    std::cout << "Encoded message: ";
    for (size_t i = 0; i < encoded.size(); i++)
        std::cout << encoded.at(i);
    // decoding a message
    std::string decoded = t_ans.decode(encoded);
    std::cout << "\nDecoded message: " << decoded << '\n';
    // file encoding
    std::string message_fname = "message.txt";
    std::string encoded_fname = "encoded.bin";
    t_ans.encode_file(message_fname, encoded_fname);
    std::cout << "File encoding completed!\n";
    // file decoding
    std::string decoded_fname = "decoded.txt";
    t_ans.decode_file(encoded_fname, decoded_fname);
    std::cout << "File decoding completed!\n";
    // feel free to modify the alphabet files and messages!
    
    return 0;
}
