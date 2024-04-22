#pragma once
#include <iostream>

#define FQINFO FQInfo

struct FQInfo{
    int nKey;
    int *p;

    FQInfo(int key) : nKey(key), p(new(std::nothrow) int[2]) {}
    virtual ~FQInfo() { delete[] p; }

    friend std::ostream& operator << (std::ostream& out, const FQInfo& inf);
};

inline std::ostream& operator << (std::ostream& out, const FQInfo& inf){
    out << "Key: " << inf.nKey << ", p[0]: " << inf.p[0] << ", p[1]: " << inf.p[1];
    return out;
}

