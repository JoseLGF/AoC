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
        parse();
    }

    void parse () {
        version = stream.consume_int(3);
        length += 3;
        type_ID = stream.consume_int(3);
        length += 3;

        if (type_ID == 4) {
            parse_literal_value();
        }
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

        decode_operation_value();
    }

    void decode_operation_value() {
        switch (type_ID) {
            case 0: decode_sum();          break;
            case 1: decode_product();      break;
            case 2: decode_min();          break;
            case 3: decode_max();          break;
            case 5: decode_greater_than(); break;
            case 6: decode_less_than();    break;
            case 7: decode_equal_to();     break;
        }
    }

    void decode_sum() {
        uint64_t sum = 0;
        for (auto sub : sub_packets) {
            sum += sub->value;
        }
        this->value = sum;
    }

    void decode_product() {
        uint64_t prod = 1;
        for (auto sub : sub_packets) {
            prod *= sub->value;
        }
        this->value = prod;
    }

    void decode_min() {
        uint64_t min = 0xFFFFFFFFFFFFFFFF;
        for (auto sub : sub_packets) {
            if (sub->value < min) {
                min = sub->value;
            }
        }
        this->value = min;
    }

    void decode_max() {
        uint64_t max = 0;
        for (auto sub : sub_packets) {
            if (sub->value > max) {
                max = sub->value;
            }
        }
        this->value = max;
    }

    void decode_greater_than() {
        uint64_t first = sub_packets[0]->value;
        uint64_t second = sub_packets[1]->value;
        if (first > second) {
            this->value = 1;
        }
        else {
            this->value = 0;
        }
    }

    void decode_less_than() {
        uint64_t first = sub_packets[0]->value;
        uint64_t second = sub_packets[1]->value;
        if (first < second) {
            this->value = 1;
        }
        else {
            this->value = 0;
        }
    }

    void decode_equal_to() {
        uint64_t first = sub_packets[0]->value;
        uint64_t second = sub_packets[1]->value;
        if (first == second) {
            this->value = 1;
        }
        else {
            this->value = 0;
        }
    }

    void parse_subpackets_in_n_bits(uint64_t nbits) {
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
            value_nibbles.push_back(nibble_packet);
        }

        for (uint64_t nibble: value_nibbles) {
            value = (value << 4);
            value |= (nibble & 0xF);
        }

        int consumed_bits = value_nibbles.size() * 5;
        int remainder = consumed_bits % 4;
        if (remainder != 0) {
            int padding = 4 - remainder;
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

    uint64_t get_value() {
        return value;
    }
};

void day16(std::string& input_path)
{
    int part_1_solution = -1;
    uint64_t part_2_solution = -1;
    std::ifstream infile(input_path);

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    auto bits = make_bit_sequence(lines[0]);
    auto bitstream = BitStream(&bits);
    Packet packet(bitstream);

    // Part 1
    part_1_solution = packet.get_version_sum();

    // Part 2
    part_2_solution = packet.get_value();

    // Display final results
    std::cout << "Day 16:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << (uint64_t)part_2_solution << std::endl;
}
