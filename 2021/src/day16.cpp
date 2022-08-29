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

    BitStream() {
        index = 0;
        bits = nullptr;
    }

    void advance(uint16_t num_bits) {
        index += num_bits;
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

    uint64_t consume_int(uint64_t num_bits)
    {
        std::vector<bool> out_bits;
        auto it = bits->begin()+index;

        for (uint64_t i=0; i<num_bits; i++) {
            out_bits.push_back(*it);
            it++;
        }

        std::reverse(
            out_bits.begin(),
            out_bits.end());

        int out=0;
        for (uint64_t i=0; i<out_bits.size(); i++) {
            if (out_bits[i]) {
                out += (1 << i);
            }
        }
        index += num_bits;
        return out;
    }

    uint64_t get_index () {
        return index;
    }
};


class Packet
{
    BitStream stream;

    /*
     * Data for all packets
     */
    uint8_t version;
    uint8_t type_ID;
    uint64_t length;
    uint64_t value;

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

    /*
     * Data for operator types
     */
    std::vector<bool> sub_packets_bits;
    std::vector<Packet*> sub_packets;

    public:
    Packet(BitStream stream) {
        length = 0;
        value = 0;
        this->stream = stream;
        std::cout << "Creating packet from position:"
            << (uint64_t)stream.get_index() << std::endl;
        parse();

    }

    void parse () {
        version = stream.consume_int(3);
        length += 3;
        type_ID = stream.consume_int(3);
        length += 3;

        std::cout << " V:" << (int)version
                  << " T:" << (int)type_ID << std::endl;

        if (type_ID == 4) {
            parse_literal_value();
        }
        // Operator types
        else {
            parse_operator_type();
        }
    }

    void parse_operator_type() {
        length_type_ID = stream.consume_int(1);
        length += 1;
        if (0 == length_type_ID) {
            total_subpackets_length_bits = stream.consume_int(15);
            length += 15;
            parse_subpackets_in_n_bits(total_subpackets_length_bits);
        }
        else {
            num_subpackets = stream.consume_int(11);
            length += 11;
            parse_n_subpackets(num_subpackets);
        }

    }

    void parse_subpackets_in_n_bits(uint64_t nbits) {
        std::cout << "Creating packets from " <<
            (int)nbits << " bits." << std::endl;
        bool stop = false;
        uint64_t consumed_bits = 0;
        while (! stop) {
            Packet* sub = new Packet(stream);
            sub_packets.push_back(sub);

            consumed_bits += sub->get_length();
            stream.advance(sub->get_length());
            if (consumed_bits >= nbits) {
                stop = true;
            }
        }
        length += nbits;
    }

    void parse_n_subpackets(uint64_t npackets) {
        uint64_t consumed_bits {};
        std::cout << "Creating packets from " <<
            (int)npackets << " packets." << std::endl;
        for (uint64_t i=0; i<npackets; i++) {
            Packet* sub = new Packet(stream);
            stream.advance(sub->get_length());
            consumed_bits += sub->get_length();
            sub_packets.push_back(sub);
        }
        length += consumed_bits;
    }

    void parse_literal_value() {
        bool stop = false;
        while (not stop) {
            stop = !(stream.consume_int(1));
            length += 1;
            uint64_t nibble_packet = stream.consume_int(4);
            length += 4;
            std::cout << nibble_packet << std::endl;
            value_nibbles.push_back(nibble_packet);
        }
        std::cout << "Parsed " << value_nibbles.size() << " nibbles." << std::endl;
        value = 0;
        for (uint64_t nibble: value_nibbles) {
            value = (value << 4);
            value |= (nibble & 0xF);
        }
        std::cout << "value: " << (int)value << std::endl;
        // Advance the remaining padding
        int consumed_bits = value_nibbles.size() * 5;
        int remainder = consumed_bits % 4;
        if (remainder != 0) {
            int padding = 4 - remainder;
            std::cout << "Skipping padding " << (int)padding << std::endl;
            stream.advance(padding);
        }
    }

    uint64_t get_length() {
        return length;
    }

    uint64_t get_version_sum() {
        uint64_t sum {};
        for (auto ptr_child: sub_packets) {
            sum += ptr_child->get_version_sum();
        }
        return version + sum;
    }

};

void day16()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("input/day16.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    std::cout << lines[0].size()*8 << " Zeroes" << std::endl;

    // Init
    auto bits = make_bit_sequence(lines[0]);
    auto bitstream = BitStream(&bits);
        std::cout << line << std::endl;
    Packet packet(bitstream);

    // Part 1
    part_1_solution = packet.get_version_sum();

    // Part 2

    // Display final results
    std::cout << "Day 16:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
