#include "dsoft.h"

#include <assert.h>
#include <vector>

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline void setDefaultParams(IndexTable *table) {
    /* set default params */
    table->params["BIN_SIZE"] = 10;
    table->params["MATCH_THRES"] = 8;
}

std::vector<MatchPos> dsoft(IndexTable *table, const std::string &qry) {
    assert(table->params["EMPTY_TABLE"] == 0);

    if (table->params.find("BIN_SIZE") == table->params.end()) {
        setDefaultParams(table);
    }

    int B = table->params["BIN_SIZE"];
    int NB = table->params["REF_LEN"] / table->params["BIN_SIZE"];
    int k = table->params["SEED_LEN"];
    int h = table->params["MATCH_THRES"];

#ifdef __DEBUG__
    std::cout << "========== Parameters ==========" << std::endl
              << "Bin Size = " << B << std::endl
              << "# of Bins = " << NB << std::endl
              << "Match Threshold = " << h << std::endl
              << "================================" << std::endl << std::endl;
#endif // __DEBUG__

    std::vector<MatchPos> candidate_pos(0);
    std::vector<uint64_t> last_hit_pos(NB, -k);
    std::vector<uint64_t> bp_count(NB, 0);

    for (int j = 0; j < qry.length() - k + 1; ++j) {
        std::string seed = qry.substr(j, k);
        LutRet hits = table->lookup(seed);

        for (auto it = hits.begin; it != hits.end; ++it) {
            if (*it - j < 0 || *it - j > B * NB)
                continue;

            int bin, overlap;
            bin = (*it - j) / B;
            overlap = max(0, last_hit_pos[bin] + k - j);
            last_hit_pos[bin] = j;
            bp_count[bin] = bp_count[bin] + k - overlap;
            if (h + k - overlap > bp_count[bin] && bp_count[bin] >= h) {
                MatchPos pos = {*it, j};
                candidate_pos.push_back(pos);
            }
        }
    }

#ifdef __DEBUG__
    std::cout << "========== Results ==========" << std::endl;
    for (auto &it : candidate_pos) {
        std::cout << "Reference @ " << it.refPos
                  << " <-> Query @ " << it.qryPos << std::endl;
    }
    std::cout << "=============================" << std::endl << std::endl;
#endif // __DEBUG__

    return candidate_pos;
}