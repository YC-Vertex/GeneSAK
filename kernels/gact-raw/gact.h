#ifndef __GACT_H__
#define __GACT_H__

#include "seed.h"
#include "dsoft.h"

#include <string>

typedef struct {
    MatchPos offset;
    std::string refTBStr;
    std::string qryTBStr;
} AlignTileRet;

typedef MatchPos GACTRet;

AlignTileRet alignTile(std::string ref, std::string qry, bool first, int maxTBLen);
GACTRet gact(AlignTask *task, std::string ref, std::string qry, MatchPos initPos);

#endif // __GACT_H__