#include <string>

#include "gact.h"

inline int64_t max(int64_t a, int64_t b) {
    return a > b ? a : b;
}

inline void setDefaultParams(AlignTask *task) {
    task->params["TILE_SIZE"] = 128;
    task->params["OVERLAP_SIZE"] = 32;
}

AlignTileRet alignTile(std::string ref, std::string qry, bool first, int maxTBLen) {
    int dp[ref.length()][qry.length()];
    int tb[ref.length()][qry.length()];

    int maxval = 0;
    MatchPos maxpos = {0, 0};

    AlignTileRet ret;
    ret.refTBStr = "";
    ret.qryTBStr = "";

    for (int i = 0; i < ref.length(); ++i) {
        for (int j = 0; j < qry.length(); ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
                tb[i][j] = 0;
                tb[i][j] |= (i > 0) ? 0b10 : 0;
                tb[i][j] |= (j > 0) ? 0b01 : 0;
                continue;
            }
            
            int u = dp[i][j-1] - 1; // insertion
            int l = dp[i-1][j] - 1; // deletion
            int ul = dp[i-1][j-1] + (ref[i] == qry[j] ? 1 : -1); // match / subst

            if (ul >= u && ul >= l) {
                dp[i][j] = ul;
                tb[i][j] = 0b11;
            }
            else if (l >= ul && l >= u) {
                dp[i][j] = l;
                tb[i][j] = 0b10;
            }
            else {
                dp[i][j] = u;
                tb[i][j] = 0b01;
            }

            if (dp[i][j] > maxval) {
                maxval = dp[i][j];
                maxpos = {uint64_t(i), uint64_t(j)};
            }
        }
    }

    if (first) {
        return {maxpos, "", ""};
    }

    int i = ref.length() - 1;
    int j = qry.length() - 1;

    while (maxTBLen != 0 && i >= 0 && j >= 0 && !(i == 0 && j == 0)) {
        bool im1 = false;
        bool jm1 = false;

        if (tb[i][j] & 0b10) {
            ret.refTBStr = ref[i] + ret.refTBStr;
            im1 = true;
        }
        else {
            ret.refTBStr = '-' + ret.refTBStr;
        }

        if (tb[i][j] & 0b01) {
            ret.qryTBStr = qry[j] + ret.qryTBStr;
            jm1 = true;
        }
        else {
            ret.qryTBStr = '-' + ret.qryTBStr;
        }

        if (im1) --i;
        if (jm1) --j;
        --maxTBLen;
    }

    ret.offset = {(uint64_t)i, (uint64_t) j};

    return ret;
}

GACTRet gact(AlignTask *task, std::string ref, std::string qry, MatchPos initPos) {
    if (task->params.find("TILE_SIZE") == task->params.end()) {
        setDefaultParams(task);
    }
    int T = task->params["TILE_SIZE"];
    int O = task->params["OVERLAP_SIZE"];

    int icurr = initPos.refPos + (qry.length() - 1 - initPos.qryPos);
    int jcurr = qry.length() - 1;
    bool first = true;

    MatchPos optPos;

    while (icurr > 0 && jcurr > 0) {
        int istart = max(0, icurr - T);
        int jstart = max(0, jcurr - T);

        std::string refSubStr = ref.substr(istart, icurr - istart + 1);
        std::string qrySubStr = qry.substr(jstart, jcurr - jstart + 1);

        AlignTileRet ret = alignTile(refSubStr, qrySubStr, first, T - O);

#ifdef __DEBUG__
        if (first) {
            std::cout << "optPos = (" 
                      << ret.offset.refPos << ", " 
                      << ret.offset.qryPos << ")" 
                      << std::endl << std::endl;
        }
        else {
            std::cout << "Ref[" << istart << ":" << icurr << "] <-> "
                      << "Qry[" << jstart << ":" << jcurr << "]:"
                      << std::endl;
            std::cout << ret.refTBStr << std::endl
                      << ret.qryTBStr << std::endl << std::endl;
        }
#endif // __DEBUG__

        icurr = istart + ret.offset.refPos;
        jcurr = jstart + ret.offset.qryPos;

        if (first) {
            optPos = {(uint64_t)icurr, (uint64_t)jcurr};
            first = false;
            continue;
        }

        if (icurr == 0 || jcurr == 0)
            break;
    }

    return optPos;
}