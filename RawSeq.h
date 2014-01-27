#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class RawSeqRead {
    public:
        RawSeqRead(unsigned int max_header_length, unsigned int max_read_length);

        void print();

        char* header;
        char* read;
};

class RawSeqFileProperties {
    public:
        RawSeqFileProperties(int max_line_width, int max_lines_per_read) :
            max_line_width(max_line_width), max_lines_per_read(max_lines_per_read) {};

        int max_line_width;
        int max_lines_per_read;
};

class RawSeq {
    public:
        RawSeq(const char* fname);
        ~RawSeq();

        RawSeqFileProperties sniff_limits();

        bool fill(RawSeqRead* read);

        unsigned int line_width;
        unsigned int lines_per_read;
    private:
        const char* fname;

        std::fstream raw_fs;
};
