#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "common.h"

struct File
{
    std::string m_name;
    int m_size;
    int m_level;

public:
    File(std::string name, int size, int level)
    : m_name{name}
    , m_size{size}
    , m_level{level}
    {}

    void print() {
        for (int i=0;i<m_level;i++) { std::cout << "  "; }
        std::cout << "- " << m_name << "(file, size=" << m_size << ")\n";
    }
};

struct Directory
{
    Directory* m_parent;
    std::string m_name;
    std::vector<Directory*> m_subdirs;
    std::vector<File> m_files;
    int m_level;

    int m_size = -1;

public:
    Directory(std::string name)
        : m_name{name}
        , m_parent{nullptr}
        , m_level{0}
    {}

    Directory(std::string name, Directory* parent, int level)
        : m_name{name}
        , m_parent{parent}
        , m_level{level}
    {}

    Directory* FindChildByName(std::string dir_name) {
        Directory* out = nullptr;
        for (auto childPtr: m_subdirs) {
            if (childPtr->m_name == dir_name) {
                out = childPtr;
                break;
            }
        }
        return out;
    }

    void AddFile(std::string name, int size) {
        m_files.push_back(File(name, size, m_level+1));
    }

    void AddSubdirectory(Directory* dir_ptr) {
        m_subdirs.push_back(dir_ptr);
    }

    void print() {
        for (int i=0;i<m_level;i++) { std::cout << "  "; }
        std::cout << "- " << m_name << " (dir)\n";
        for (auto sd: m_subdirs) {
            sd->print();
        }
        for (auto f: m_files) {
            f.print();
        }
    }

    void calculate_size() {
        m_size = 0;
        for (auto& f: m_files) {
            m_size += f.m_size;
        }
        for (auto sd: m_subdirs) {
            sd->calculate_size();
            m_size += sd->m_size;
        }
    }
};

class FileSystem
{
    std::vector<Directory*> managed_dirs;
    Directory* m_current_dir;
    Directory* m_root;

public:
    FileSystem() {
        managed_dirs.push_back(new Directory("/"));
        m_root = managed_dirs[0];
        m_current_dir = m_root;
    }

    ~FileSystem() {
        for (auto p: managed_dirs) {
            delete p;
        }
    }

    void cd(std::string& dir_name) {
        if (dir_name == "/") {
            m_current_dir = m_root;
        } else if (dir_name == "..") {
            m_current_dir = m_current_dir->m_parent;
            // std::cout << "cd'ing into " << m_current_dir->m_name << std::endl;
        }
        else {
            Directory* ptr = m_current_dir->FindChildByName(dir_name);
            if (nullptr != ptr) {
                m_current_dir = ptr;
                // std::cout << "Found. Cd'ing into " << m_current_dir->m_name << std::endl;
            }
        }
    }

    void Command(std::vector<std::string>& tokens) {
        if ("cd" == tokens[1]) {
            cd(tokens[2]);
        }
        if ("ls" == tokens[1]) {
            ;
        }
    }

    void RegisterContent(std::vector<std::string>& tokens) {
        if ("dir" == tokens[0]) {
            std::string name = tokens[1];
            Directory* new_dir = new Directory(name, m_current_dir, m_current_dir->m_level+1);
            managed_dirs.push_back(new_dir);
            m_current_dir->AddSubdirectory(new_dir);
            // std::cout << "Register " << m_current_dir->m_name << "->" << name << std::endl;
        }
        else {
            int size = stoi(tokens[0]);
            std::string file_name = tokens[1];
            m_current_dir->AddFile(file_name, size);
        }
    }

    void print() {
        m_root->print();
    }

    void size_report() {
        int sum_atmost_100000 = 0;
        // std::cout << "Size report" << std::endl;
        m_root->calculate_size();
        for(auto md: managed_dirs) {
            if (md->m_size <= 100000) {
                sum_atmost_100000 += md->m_size;
            }
            // std::cout << md->m_name << ": " << md->m_size << std::endl;
        }
        // Part 1 solution
        std::cout << sum_atmost_100000 << std::endl;
    }

    std::vector<int> dirs_sizes() {
        std::vector<int> out;
        for (auto md: managed_dirs) {
            out.push_back(md->m_size);
        }
        return out;
    }
};

void day07(std::string& input_path) {
    std::cout << "Day 7:" << std::endl;

    auto lines = get_input(input_path);

    FileSystem fs;

    for (auto line: lines) {
        auto tokens = tokenize_string(line);
        if ("$" == tokens[0]) {
            fs.Command(tokens);
        }
        else {
            fs.RegisterContent(tokens);
        }
    }

    // fs.print();
    fs.size_report();

    // Part 2
    auto fs_sizes = fs.dirs_sizes();

    int total_disk_space = 70000000;
    int update_size = 30000000;
    int root_size = fs_sizes[0];
    int unused_space = total_disk_space - root_size;
    int min_dir_delete_size = update_size - unused_space;

    std::vector<int> candidates;
    for (int i=1; i<fs_sizes.size(); i++) {
        if (fs_sizes[i] >= min_dir_delete_size) {
            candidates.push_back(fs_sizes[i]);
        }
    }

    std::sort(candidates.begin(), candidates.end());
    std::cout << candidates[0] << std::endl;
}
