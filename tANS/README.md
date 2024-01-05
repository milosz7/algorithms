# tANS

### Introduction
tANS is a variant of an asymmetric numeral systems algorithm created by Jarek Duda. [paper](https://arxiv.org/abs/1311.2540)

### Class methods
- `void read_data(std::string filename)` - reads alphabet with probabilities of occurences of each symbol from a text file.
- `std::vector<bool> encode(std::string message)` - encodes a string into bits stored in a bool vector acting as a dynamic bitset.
- `std::string decode(std::vector<bool> &message)` - decodes a bool vector into a string message.
- `void encode_file(std::string filename in, std::string filename_out)` - encodes contents of a text file. Works only for single line inputs. (multiline input throws an error!)
- `void decode_file(std::string filename in, std::string filename_out)` - decodes contents of a binary file that has been encoded using the `encode file` method.

### Creating an alphabet
The `read_data` method reads the contents of an alphabet text file line by line. Each entry should be in the following format:
```
alphabet_character,probability
```
Where `alphabet_character` is a single printable ASCII char, and probability is a string representation of a double following the regular expression: `\d{1,2}\.\d+`. Any invalid input is going to be detected and the program won't run. The sum of probabilities must sum up approximately to 1!

### demo.cpp
The `demo.cpp` file contains the presentation of all avaliable methods. In order to compile it use the following command:
```
make
```
Then run the program using:
```
./demo.x
```
