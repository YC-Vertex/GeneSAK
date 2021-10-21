#include "dsoft.h"
#include "gact.h"
#include "seed.h"

int main() {
    std::string ref = "GATCACAGGTCTATCACCCTATTAACCACTCACGAGCTCTCCATGCATTTGGTATTACTCTATTAACCACTCTTAAAAAAAA";
    std::string qry = "ACTCTATTAACCACTC";

    IndexTable *t = new IndexTable(ref);
    std::vector<MatchPos> pos = dsoft(t, qry);

    for (auto &it : pos) {
        gact(t, ref, qry, it);
    }

    return 0;
}