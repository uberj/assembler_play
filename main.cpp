#include <string>
#include <iostream>
#include <fstream>

#include <sparsehash/sparse_hash_map>

#include "RawSeq.cpp"

using namespace std;

const int STOP_ITERATION = 1;

int main( int argc, const char* argv[] ) {
    RawSeq* rs = new RawSeq(argv[1]);
    RawSeqRead rsr = RawSeqRead(
        rs->line_width, // Max header size
        rs->line_width * rs->lines_per_read // Max read size
    );

    bool was_filled = true;
    while (was_filled) {
        was_filled = rs->fill(&rsr);
        if (was_filled)
            rsr.print();
    };
};
