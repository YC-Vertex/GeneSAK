#include <iostream>

#include "dsoft.h"
#include "seed.h"

int main() {
    IndexTable *table = new IndexTable();
    table->loadFile("table.dump");

    /* set default params */
    table->params["BIN_SIZE"] = 10;
    table->params["MATCH_THRES"] = 6;

    std::vector<MatchPos> result = dsoft(table, "ACTCTATTAACCACTC");

    std::cout << "========== Results ==========" << std::endl;
    for (auto &it : result) {
        std::cout << "Reference @ " << it.refPos << " <-> Query @ " << it.qryPos << std::endl;
    }
    std::cout << "=============================" << std::endl << std::endl;

    return 0;
}