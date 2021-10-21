#include <iostream>

#include "seed.h"

int main() {
    IndexTable *t = new IndexTable("GATCACAGGTCTATCACCCTATTAACCACTCACGGGAGCTCTCCATGCATTTGGTATTTT");
    t->saveFile("table.dump");

    IndexTable *copy = new IndexTable();
    copy->loadFile("table.dump");

    auto r = copy->lookup("CAC");
    std::cout << "CAC: ";
    for (auto it = r.begin; it != r.end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}