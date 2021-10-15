#include "dsoft.h"

#include <assert.h>
#include <math.h>
#include <vector>

inline int max(int a, int b) {
    return a > b ? a : b;
}

std::vector<MatchPos> dsoft(IndexTable *table, const std::string &query) {
    assert(table->params["EMPTY_TABLE"] == 0);

    int B = table->params["BIN_SIZE"];
    int NB = ceil(table->params["REF_LEN"] / table->params["REF_LEN"]);
    int k = table->params["SEED_LEN"];
    int h = table->params["MATCH_THRES"];

    std::vector<MatchPos> candidate_pos(0);
    std::vector<uint64_t> last_hit_pos(NB, -k);
    std::vector<uint64_t> bp_count(NB, 0);

    for (int j = 0; j < query.length() - k + 1; ++j) {
        std::string seed = query.substr(j, k);
        LutRet hits = table->lookup(seed);

        for (auto it = hits.begin; it != hits.end; ++it) {
            if (*it - j < 0 || *it - j > B * NB)
                continue;

            int bin, overlap;
            bin = ceil((*it - j) / B);
            overlap = max(0, last_hit_pos[bin] + k - j);
            last_hit_pos[bin] = j;
            bp_count[bin] = bp_count[bin] + k - overlap;
            if (h + k - overlap > bp_count[bin] && bp_count[bin] >= h) {
                MatchPos pos = {*it, j};
                candidate_pos.push_back(pos);
            }
        }
    }

    return candidate_pos;
}