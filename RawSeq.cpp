#include "RawSeq.h"
#include <csignal> // for debuggin


RawSeq::RawSeq(const char* fname) {
    raw_fs.open(fname, std::fstream::in);

    RawSeqFileProperties conf = this->sniff_limits();

    // TODO, seek(0) when sniff_limits is actually implemented

    this->line_width = conf.max_line_width;
    this->lines_per_read = conf.max_lines_per_read;
};


RawSeqRead::RawSeqRead(unsigned int max_header_size, unsigned int max_read_size) {
    this->header = new char[max_header_size];
    this->read = new char[max_read_size];
};


bool RawSeq::fill(RawSeqRead* read) {
    // Assume the first char is a '>', so leave the fs at the next '>'
    // TODO handle comments
    int l_offset = 0;

    char peek = raw_fs.peek();
    if(peek == EOF) {
        return false; // TODO, figure out how iterators work in c++
    }

    raw_fs.getline(read->header, line_width); // Read in header (starswith('>'))

    peek = raw_fs.peek();
    while(1) {
        raw_fs.getline(read->read + l_offset, line_width); // fs read up to '\n'
        l_offset = l_offset + raw_fs.gcount() - 1; // -1 causes us to write over \n on the next read
        peek = raw_fs.peek();
        if (peek == '>' || peek == EOF)
            break;
    }

    return true;
};


void RawSeqRead::print() {
    cout << "Header: " << header << endl;
    cout << "Read: " << read << endl << endl;
}


// TODO
unsigned int MAX_LINE_WIDTH = 61; // Seq files seem to have fixed width. It would be nice to detect this
unsigned int MAX_LINES_PER_READ = 41; // Figure out how to sniff this from a seq file


RawSeqFileProperties RawSeq::sniff_limits() {
    return RawSeqFileProperties(MAX_LINE_WIDTH, MAX_LINES_PER_READ);
}
