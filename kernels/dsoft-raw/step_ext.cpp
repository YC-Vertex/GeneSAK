#include <iostream>

#include "dsoft.h"
#include "seed.h"

inline int min(int a, int b) {
    return a < b ? a : b;
}

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    std::string ref = "GATCACAGGTCTATCACCCTATTAACCACTCACGAGCTCTCCATGCATTTGGTATTACTCTATTAACCACTCTTAAAAAAAA";
    std::string qry = "ACTCTATTAACCACTC";

    IndexTable *t = new IndexTable(ref);
    std::vector<MatchPos> result = dsoft(t, qry);

    std::cout << "Query: " << std::endl
              << qry << std::endl << std::endl
              << "Results: " << std::endl;
    for (auto &it : result) {
        std::cout << ref.substr(max(0, it.refPos - t->params["BIN_SIZE"]), t->params["BIN_SIZE"] + t->params["SEED_LEN"]) << std::endl;
    }

    return 0;
}