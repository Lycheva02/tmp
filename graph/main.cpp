#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cstdint>
#include <sstream>

void serialize(const std::string& input_file, const std::string& bin_file) {
    size_t sz8 = sizeof(uint8_t);
    size_t sz32 = sizeof(uint32_t);
    
    std::ifstream tsv_f(input_file, std::ios::in);
    std::ofstream bin_f(bin_file, std::ios::binary);

    std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>> graph;
    uint32_t vertex1, vertex2, vertex, value, edgesCount;
    uint8_t weight;

    while (tsv_f >> vertex1 >> vertex2 >> value) {
        // Учитываем ребро только в одном направлении
        if (vertex1 < vertex2) {
            graph[vertex1].push_back(std::make_pair(vertex2, value));
        } else {
            graph[vertex2].push_back(std::make_pair(vertex1, value));
        }
    }

    for (auto& [v, prs] : graph) {
        vertex = v;
        edgesCount = prs.size();

        bin_f.write(reinterpret_cast<char*>(&vertex), sz32);
        bin_f.write(reinterpret_cast<char*>(&edgesCount), sz32);

        for (auto& [a, b] : prs) {
            bin_f.write(reinterpret_cast<char*>(&a), sz32);
            bin_f.write(reinterpret_cast<char*>(&b), sz8);
        }
    }

    tsv_f.close();
    bin_f.close();
}

void deserialize(const std::string& bin_file, const std::string& output_file) {
    std::ifstream bin_f(bin_file, std::ios::binary);
    std::ofstream tsv_f(output_file);

    uint32_t vertex, edgesCount, adjacentVertex, value;
    uint8_t weight;
    size_t sz8 = sizeof(uint8_t);
    size_t sz32 = sizeof(uint32_t);

    while (bin_f) {
        bin_f.read(reinterpret_cast<char*>(&vertex), sz32);
        bin_f.read(reinterpret_cast<char*>(&edgesCount), sz32);
        if (!bin_f)
            break;

        for (uint32_t i = 0; i < edgesCount; ++i) {
            bin_f.read(reinterpret_cast<char*>(&adjacentVertex), sz32);
            bin_f.read(reinterpret_cast<char*>(&weight), sz8);
            value = weight;

            tsv_f << vertex << "\t" << adjacentVertex << "\t" << value << std::endl;
        }
    }
    tsv_f.close();
    bin_f.close();
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