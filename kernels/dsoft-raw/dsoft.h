#ifndef __DSOFT_H__
#define __DSOFT_H__

#include "seed.h"

typedef struct {
    uint64_t refPos;
    uint64_t qryPos;
} MatchPos;

std::vector<MatchPos> dsoft(IndexTable *table, const std::string &query);

#endif // __DSOFT_H__