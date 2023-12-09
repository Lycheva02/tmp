#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

void serialize(std::string input_file, std::string bin_file) {
    std::ifstream tsv_f(input_file, std::ios::in);
    std::ofstream bin_f(bin_file, std::ios::binary);
    uint32_t a, b, value, number;
    uint8_t weight;
    size_t sz8 = sizeof(uint8_t);
    size_t sz32 = sizeof(uint32_t);
    std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>> mp;

    while (tsv_f >> a >> b >> value) {  // не приводим к uint8_t тут, потому что в следующем цикле всё равно возникают проблемы с приведением типа val
        mp[value].push_back(std::make_pair(a, b));
    }
    tsv_f.close();

    for (auto &[val, prs]: mp) {
        weight = val;
        number = prs.size();
        bin_f.write(reinterpret_cast<char *>(&weight), sz8);
        bin_f.write(reinterpret_cast<char *>(&number), sz32);
        for (auto &[a, b]: prs) {
            bin_f.write(reinterpret_cast<char *>(&a), sz32);
            bin_f.write(reinterpret_cast<char *>(&b), sz32);
        }
    }

    bin_f.close();
}

void deserialize(std::string bin_file, std::string output_file) {
    std::ifstream bin_f(bin_file, std::ios::binary);
    std::ofstream tsv_f(output_file);
    uint32_t a, b, value, number;
    uint8_t weight;
    size_t sz8 = sizeof(uint8_t);
    size_t sz32 = sizeof(uint32_t);
    bool not_first_line = false;

    while (bin_f) {
        bin_f.read(reinterpret_cast<char *>(&weight), sz8);
        bin_f.read(reinterpret_cast<char *>(&number), sz32);
        value = weight;
        if (!bin_f)
            break;
        for (size_t i = 0; i < number; ++i) {
            bin_f.read(reinterpret_cast<char *>(&a), sz32);
            bin_f.read(reinterpret_cast<char *>(&b), sz32);
            if (not_first_line)
                tsv_f << std::endl;
            else
                not_first_line = true;
            tsv_f << a << '\t' << b << '\t' << value;
        }
    }

    bin_f.close();
    tsv_f.close();
}

int main(int argc, char **argv) {
    if (argc != 6) {
        std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
        exit(1);
    }
    if (strcmp(argv[1], "-s") == 0) {
        if (strcmp(argv[2], "-i") == 0) {
            if (strcmp(argv[4], "-o") == 0)
                serialize(argv[3], argv[5]);
            else {
                std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
                exit(1);
            }
        }
        else {
            if (strcmp(argv[2], "-o") == 0) {
                if (strcmp(argv[4], "-i") == 0)
                    serialize(argv[5], argv[3]);
                else {
                    std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
                    exit(1);
                }
            }
            else {
                std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
                exit(1);
            } 
        }
    } else if (strcmp(argv[1], "-d") == 0) {
        if (strcmp(argv[2], "-i") == 0) {
            if (strcmp(argv[4], "-o") == 0)
                deserialize(argv[3], argv[5]);
            else {
                std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
                exit(1);
            }
        }
        else {
            if (strcmp(argv[2], "-o") == 0) {
                if (strcmp(argv[4], "-i") == 0)
                    deserialize(argv[5], argv[3]);
                else {
                    std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
                    exit(1);
                }
            }
            else {
                std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
                exit(1);
            } 
        }
    } else {
        std::cout << "Неверный вызов команды. Доступен один из вариантов:\n./run -s -i input.tsv -o graph.bin\n./run -d -i graph.bin -o output.tsv";
    }
}