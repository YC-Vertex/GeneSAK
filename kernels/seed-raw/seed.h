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

class AlignTask {
public:
    std::unordered_map<std::string, int> params;

public:
    void setParam(const std::string &key, int value) { params[key] = value; }
};

class IndexTable : public AlignTask{
private:
    PtrTable tptr;
    PosTable tpos;

public:
    IndexTable();
    IndexTable(const std::string &reference);

    LutRet lookup(Seed sval);
    LutRet lookup(const std::string &sstr);

    void saveFile(const std::string &f);
    void loadFile(const std::string &f);

    void DEBUG_OUTPUT();
};

#endif // __SEED_H__