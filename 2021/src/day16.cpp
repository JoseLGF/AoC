#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <limits>
#include <unordered_set>
#include <utility>
#include <stack>
#include <set>
#include <queue>
#include <climits>

constexpr uint8_t TYPE_LITERAL_VALUE = 4;
constexpr uint8_t version_offset = 0;
constexpr uint8_t version_length = 3;
constexpr uint8_t type_ID_offset = 3;
constexpr uint8_t type_ID_length = 3;
constexpr uint8_t length_type_ID_offset = 6;
constexpr uint8_t length_type_ID_length = 1;
constexpr uint8_t num_subpackets_offset = 7;
constexpr uint8_t num_subpackets_length = 11;
constexpr uint8_t total_subpackets_length_offset = 7;
constexpr uint8_t total_subpackets_length_length = 15;

std::vector<bool> make_bit_sequence (std::string message)
{
    std::vector<bool> out;
    std::vector<bool> c_repr;
    for (auto c: message) {
        switch(c) {
            case '0': c_repr = {0,0,0,0}; break;
            case '1': c_repr = {0,0,0,1}; break;
            case '2': c_repr = {0,0,1,0}; break;
            case '3': c_repr = {0,0,1,1}; break;
            case '4': c_repr = {0,1,0,0}; break;
            case '5': c_repr = {0,1,0,1}; break;
            case '6': c_repr = {0,1,1,0}; break;
            case '7': c_repr = {0,1,1,1}; break;
            case '8': c_repr = {1,0,0,0}; break;
            case '9': c_repr = {1,0,0,1}; break;
            case 'A': c_repr = {1,0,1,0}; break;
            case 'B': c_repr = {1,0,1,1}; break;
            case 'C': c_repr = {1,1,0,0}; break;
            case 'D': c_repr = {1,1,0,1}; break;
            case 'E': c_repr = {1,1,1,0}; break;
            case 'F': c_repr = {1,1,1,1}; break;
            default: c_repr = {0,0,0,0};
        }
        out.insert(
                out.end(),
                c_repr.begin(),
                c_repr.end());
    }
    return out;
}

class BitStream
{
    std::vector<bool>* bits;
    uint64_t index;

    public:

    BitStream(std::vector<bool>* in_bits) {
        index = 0;
        bits = in_bits;
    }

    std::vector<bool> consume_bits(uint16_t num_bits) {
        std::vector<bool> out;
        if (index + num_bits > bits->size()) {
            std::cout << "Error, not enough bits left in stream."
                << std::endl;
            return out;
        }
        out.insert(
                out.end(),
                bits->begin()+index,
                bits->end()+index+num_bits);
        index += num_bits;
        return out;
    }
};

int get_int(std::vector<bool>& sequence, int length)
{
    std::vector<bool> bits;
    auto it = sequence.begin();

    for (int i=0; i<length; i++) {
        bits.push_back(
                *it);
        it++;
    }

    std::reverse(
        bits.begin(),
        bits.end());

    int out=0;
    for (int i=0; i<bits.size(); i++) {
        if (bits[i]) {
            out += (1 << i);
        }
    }
    return out;
}

class BITSPacket
{
    std::vector<bool> packet_bits;

    /*
     * Data for all packets
     */
    uint8_t version;
    uint8_t type_ID;
    uint64_t packet_length;

    /*
     * Data for Operator value types
     */
    uint8_t  length_type_ID;
    uint16_t num_subpackets;
    uint16_t total_subpackets_length_bits;
    uint64_t subpackets_offset;

    /*
     * Data for type_ID literal value
     */
    std::vector<uint8_t> value_nibbles;
    uint64_t value;

    /*
     * Data for operator types
     */
    std::vector<bool> sub_packets_bits;
    std::vector<BITSPacket*> sub_packets;

    public:
    BITSPacket(std::string message) {
        calculate_binary_repr(message);
        std::cout << "Creating packet with bits:" << std::endl;
        print_binary_repr();
        unpack();
    }

    // Create packet by only looking at the necessary number of bits
    BITSPacket(std::vector<bool> bits) {
        packet_bits = bits;
        std::cout << "Creating packet with bits:" << std::endl;
        print_binary_repr();
        unpack();
    }

    void calculate_total_subpackets_length_bits() {
        total_subpackets_length_bits = get_int(
                    total_subpackets_length_offset,
                    total_subpackets_length_length);
    }

    void calculate_num_subpackets() {
        num_subpackets = get_int(
                num_subpackets_offset,
                num_subpackets_length);
    }

    void parse_literal_value() {
        bool stop = false;
        int index = 6;
        while (not stop) {
            uint8_t nibble_packet = get_int(index, 5);
            value_nibbles.push_back(nibble_packet & 0b01111);
            stop = nibble_packet & 0b10000;
            index += 5;
        }
        std::cout << "Parsed " << value_nibbles.size() << " nibbles." << std::endl;
    }

    void unpack() {
        // Packet type identification
        calculate_version();
        calculate_type();

        // Literal value packet
        if (type_ID == TYPE_LITERAL_VALUE) {
            std::cout << "Parsing literal value: " << std::endl;
            parse_literal_value();
        }

        // Operator types
        else {
            calculate_length_type_ID();
            if (0 == length_type_ID) {
                calculate_total_subpackets_length_bits();
                subpackets_offset = 7 + 15;
                sub_packets = create_subpackets_by_bits(total_subpackets_length_bits);
            }
            else {
                calculate_num_subpackets();
                subpackets_offset = 7 + 11;
                sub_packets = create_subpackets_by_npackets(num_subpackets);
            }
        }
        calculate_packet_length();
    }

    std::vector<BITSPacket*>
    create_subpackets_by_bits(uint16_t num_bits)
    {
        std::cout << "Spawning subpackets from "
            << num_bits << " bits." << std::endl;
        std::vector<BITSPacket*> out;

        int consumed_bits = 0;
        while (consumed_bits < num_bits) {
            std::vector<bool> subpacket_bits;
            std::copy(
                    packet_bits.begin() + subpackets_offset,
                    packet_bits.begin() + subpackets_offset + num_bits,
                    std::back_inserter(subpacket_bits));

            BITSPacket* subpacket = new BITSPacket(subpacket_bits);
            int sub_length = subpacket->get_packet_length();
            consumed_bits += sub_length;
            out.push_back(subpacket);
        }
        return out;
    }

    std::vector<BITSPacket*>
    create_subpackets_by_npackets(uint16_t num_npackets)
    {
        std::vector<BITSPacket*> out;
        return out;
    }

    void calculate_packet_length(){
        if (type_ID == TYPE_LITERAL_VALUE) {
            packet_length = 6 + 5*value_nibbles.size();
        }
        else {
            if (length_type_ID == 0) {
                packet_length =
                      7
                    + 15
                    + total_subpackets_length_bits;
            }
            else {
                int all_subpackets_length = 0;
                for (auto subpacket: sub_packets) {
                    all_subpackets_length +=
                        subpacket->get_packet_length();
                }
            }
        }
    }

    uint64_t get_packet_length() {
        return packet_length;
    }

    std::vector<bool> get_segment (int offset, int length) {
        std::vector<bool> bits;
        auto it = packet_bits.begin()+offset;
        for (int i=0; i<length; i++) {
            bits.push_back(*it);
            it++;
        }
        return bits;
    }

    int get_int(int offset, int length) {
        std::vector<bool> bits;
        auto it = packet_bits.begin()+offset;

        for (int i=0; i<length; i++) {
            bits.push_back(
                    *it);
            it++;
        }

        std::reverse(
            bits.begin(),
            bits.end());

        int out=0;
        for (int i=0; i<bits.size(); i++) {
            if (bits[i]) {
                out += (1 << i);
            }
        }
        return out;
    }

    void calculate_version() {
        version = get_int(
                version_offset,
                version_length);
    }

    void calculate_type() {
        type_ID = get_int(
                type_ID_offset,
                type_ID_length);
    }

    void calculate_length_type_ID() {
        length_type_ID = get_int(
                length_type_ID_offset,
                length_type_ID_length);
    }

    void calculate_binary_repr(std::string message) {
        std::vector<bool> c_repr;
        for (auto c: message) {
            switch(c) {
                case '0': c_repr = {0,0,0,0}; break;
                case '1': c_repr = {0,0,0,1}; break;
                case '2': c_repr = {0,0,1,0}; break;
                case '3': c_repr = {0,0,1,1}; break;
                case '4': c_repr = {0,1,0,0}; break;
                case '5': c_repr = {0,1,0,1}; break;
                case '6': c_repr = {0,1,1,0}; break;
                case '7': c_repr = {0,1,1,1}; break;
                case '8': c_repr = {1,0,0,0}; break;
                case '9': c_repr = {1,0,0,1}; break;
                case 'A': c_repr = {1,0,1,0}; break;
                case 'B': c_repr = {1,0,1,1}; break;
                case 'C': c_repr = {1,1,0,0}; break;
                case 'D': c_repr = {1,1,0,1}; break;
                case 'E': c_repr = {1,1,1,0}; break;
                case 'F': c_repr = {1,1,1,1}; break;

                default: c_repr = {0,0,0,0};
            }
            packet_bits.insert(
                    packet_bits.end(),
                    c_repr.begin(),
                    c_repr.end());
        }
    }

    void print_binary_repr() {
        for (auto b: packet_bits) {
            std::cout << (b ? '1':'0');
        }
        std::cout << std::endl;
    }

    void recursive_print() {
        print();
        for (auto sub: sub_packets) {
            sub->recursive_print();
        }
    }

    void print() {
        std::cout << "Packet:" << std::endl;
        std::cout << "Version = " << (int)version << std::endl;
        std::cout << "Type ID = " << (int)type_ID << std::endl;
        if (type_ID == TYPE_LITERAL_VALUE) {
            // print value
            std::cout << "repr:";
            print_binary_repr();
        }
        else {
            std::cout << "Sub Packet Length ID = "
                      << (int)length_type_ID
                      << std::endl;
            if (length_type_ID == 0x00) {
                std::cout << "Sub Packet Bits ="
                          << (int)total_subpackets_length_bits
                          << std::endl;
            }
        }
    }
};

void day16()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("input/example16_2.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    auto bits = make_bit_sequence(lines[0]);
    auto bitstream = BitStream(&bits);
    BITSPacket packet(lines[0]);
    packet.recursive_print();

    // Part 1

    // Part 2

    // Display final results
    std::cout << "Day 16:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
