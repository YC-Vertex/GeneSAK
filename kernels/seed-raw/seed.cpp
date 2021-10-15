#include <fstream>
#include <iostream>
#include <math.h>
#include <numeric>
#include <unordered_map>

#include "seed.h"


std::unordered_map<char, Seed> BPLUT = {
    {'G', 0}, {'A', 1}, {'C', 2}, {'T', 3}
};
std::unordered_map<Seed, char> BPLUT_INV = {
    {0, 'G'}, {1, 'A'}, {2, 'C'}, {3, 'T'}
};

inline int min(int a, int b) {
    return a < b ? a : b;
}

Seed str2seed(const std::string &sstr) {
    Seed sval = 0;
    for (int i = 0; i < sstr.length(); ++i) {
        sval *= 4;
        sval += BPLUT[sstr[i]];
    }
    return sval;
}

std::string seed2str(Seed sval, int len) {
    std::string sstr = "";
    for (int i = 0; i < len; ++i) {
        sstr = BPLUT_INV[sval % 4] + sstr;
        sval /= 4;
    }
    return sstr;
}


/* class IndexTable */

IndexTable::IndexTable() {
    /* set default params */
    params["MAX_REF_LEN"] = 20e6;
    params["REF_LEN"] = 20e6;
    params["SEED_LEN"] = 3;
    params["EMPTY_TABLE"] = 1;
}

IndexTable::IndexTable(const std::string &genome) {
    /* set default params */
    params["MAX_REF_LEN"] = 20e6;
    params["REF_LEN"] = min(genome.length(), params["MAX_REF_LEN"]);
    params["SEED_LEN"] = 3;
    params["EMPTY_TABLE"] = 0;

    /* calculate params */
    int glen = params["REF_LEN"];
    int slen = params["SEED_LEN"];
    uint64_t ptrcnt = pow(4, slen);
    uint64_t poscnt = glen - slen + 1;

#ifdef __DEBUG__
    std::cout << "========== Parameters ==========" << std::endl
              << "Genome Length = " << glen << std::endl
              << "Seed Length = " << slen << std::endl
              << "# of Entries in the Pointer Table = " << ptrcnt << std::endl
              << "# of Entries in the Position Table = " << poscnt << std::endl
              << "================================" << std::endl << std::endl;
#endif // __DEBUG__

    /* initialize table */
    tptr.insert(tptr.begin(), ptrcnt, 0);

    /* generate position table */
    for (uint64_t i = 0; i < poscnt; ++i) {
        Seed s = str2seed(genome.substr(i, slen));

        uint64_t index = std::accumulate(tptr.begin(), tptr.begin() + s + 1, 0);
        tptr[s] += 1;

        tpos.insert(tpos.begin() + index, i);
    }

    /* generate pointer table */
    uint64_t n = 0;
    for (auto it = tptr.begin(); it != tptr.end(); ++it) {
        n += *it;
        *it = n - *it;
    }

#ifdef __DEBUG__
    std::cout << "========== Results ==========" << std::endl;
    DEBUG_OUTPUT();
    std::cout << "=============================" << std::endl << std::endl;
#endif // __DEBUG__
}

LutRet IndexTable::lookup(Seed seed) {
    if (seed != tptr.size() - 1)
        return {tpos.begin() + tptr[seed], tpos.begin() + tptr[seed+1]};
    else
        return {tpos.begin() + tptr[seed], tpos.end()};
}

LutRet IndexTable::lookup(const std::string &sstr) {
    Seed sval = str2seed(sstr);
    return lookup(sval);
}

void IndexTable::DEBUG_OUTPUT() {
    for (Seed i = 0; i < tptr.size(); ++i) {
        bool flag = false;
        auto start = tpos.begin() + tptr[i];
        auto end = (i != tptr.size() - 1) ? tpos.begin() + tptr[i+1] : tpos.end();

        for (auto it = start; it != end; ++it) {
            if (!flag) {
                std::cout << "> " << seed2str(i, params["SEED_LEN"]) << ": ";
                flag = true;
            }
            std::cout << *it << " ";
        }

        if (flag) {
            std::cout << std::endl;
        }
    }
}

void IndexTable::saveFile(const std::string &f) {
    std::ofstream file(f);

    file << params.size() << " ";
    for (auto &it : params) {
        file << it.first << " " << it.second << " ";
    }
    file << std::endl;

    for (auto &it : tptr) {
        file << it << " ";
    }
    file << std::endl;

    for (auto &it : tpos) {
        file << it << " ";
    }
    file << std::endl;
}

void IndexTable::loadFile(const std::string &f) {
    std::ifstream file(f);

    int param_count;
    int ptrcnt, poscnt;

    file >> param_count;

    for (int i = 0; i < param_count; ++i) {
        std::string k;
        int v;
        file >> k >> v;
        params[k] = v;
    }

    ptrcnt = pow(4, params["SEED_LEN"]);
    poscnt = params["REF_LEN"] - params["SEED_LEN"] + 1;

    for (int i = 0; i < ptrcnt; ++i) {
        uint64_t n;
        file >> n;
        tptr.push_back(n);
    }

    for (int i = 0; i < poscnt; ++i) {
        uint64_t n;
        file >> n;
        tpos.push_back(n);
    }

#ifdef __DEBUG__
    std::cout << "========== Results ==========" << std::endl;
    DEBUG_OUTPUT();
    std::cout << "=============================" << std::endl << std::endl;
#endif // __DEBUG__
}