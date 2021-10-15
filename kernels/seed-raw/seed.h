#ifndef __SEED_H__
#define __SEED_H__

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using Seed = uint32_t;
using PtrTable = std::vector<uint64_t>;
using PosTable = std::vector<uint64_t>;

typedef struct {
    PosTable::iterator begin;
    PosTable::iterator end;
} LutRet;

class IndexTable {
private:
    PtrTable tptr;
    PosTable tpos;
    std::unordered_map<std::string, int> params;

public:
    IndexTable();
    IndexTable(const std::string &genome);

    LutRet lookup(Seed sval);
    LutRet lookup(const std::string &sstr);

    void setParam(const std::string &key, int value) { params[key] = value; }

    void saveFile(const std::string &f);
    void loadFile(const std::string &f);

    void DEBUG_OUTPUT();
};

#endif // __SEED_H__