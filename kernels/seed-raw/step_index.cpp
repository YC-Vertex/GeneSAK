#include "seed.h"

int main() {
    IndexTable *t = new IndexTable("ACCAACTGTACGTCGTACGATCGTACTGAT");
    t->saveFile("table.dump");

    IndexTable *copy = new IndexTable();
    copy->loadFile("table.dump");

    return 0;
}