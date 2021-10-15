#ifndef __SEED_H__
#define __SEED_H__

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using Seed = uint32_t;
using PtrTable = std::vector<uint64_t>;
using PosTable = std::vector<uint64_t>;

class IndexTable {
private:
    PtrTable tptr;
    PosTable tpos;
    std::unordered_map<std::string, int> params;

public:
    IndexTable();
    IndexTable(const std::string &genome);

    uint64_t lookup(Seed seed);

    void setParam(const std::string &key, int value) { params[key] = value; }

    void saveFile(const std::string &f);
    void loadFile(const std::string &f);

    void DEBUG_OUTPUT();
};

#endif // __SEED_H__