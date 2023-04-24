#include "external_utils/argparse.hpp"
#include <stdexcept>

#ifndef VERSION
#define VERSION "0.0.1" 
#endif // !VERSION

namespace Config
{
    static argparse::ArgumentParser parser("main", VERSION);

    bool parse(int argc, char const *argv[]) {
        parser.add_argument("-v", "--verbose").scan<'i', int>();



        throw  std::runtime_error("not implemented parse");
        return false;
    }
}