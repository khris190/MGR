#include "external_utils/argparse.hpp"
#include "my_utils/Logger.hpp"
#include <stdexcept>
#include <string>

#ifndef VERSION
#define VERSION "0.0.1"
#endif // !VERSION

namespace Config {
static argparse::ArgumentParser parser("main", VERSION,
                                       argparse::default_arguments::help);

bool parse(int argc, char const* argv[])
{
    parser.add_argument("-v", "--verbose")
        .nargs(argparse::nargs_pattern::optional)
        .scan<'i', int>()
        .default_value(0);

    parser.add_argument("-P", "--printvals")
        .help(std::string { "Print configurated values" })
        .default_value(false)
        .implicit_value(true);

    parser.add_argument("-i", "--input")
        .nargs(1)
        .default_value(std::string { "input.png" })
        .help("Input image fileName");

    parser.add_argument("-o", "--output")
        .nargs(1)
        .default_value(std::string { "output.png" })
        .help("Output image fileName");

    parser.add_argument("-t", "--threads")
        .nargs(1)
        .default_value(4)
        .help("Number of threads that the program will use for calculations.")
        .scan<'i', int>();

    parser.add_argument("-p", "--population")
        .nargs(1)
        .default_value(4)
        .help("Number of threads that the program will use for calculations.")
        .scan<'i', int>();

    parser.add_argument("-s", "--shapes-amount")
        .nargs(1)
        .default_value(4)
        .help("Amount of generated shapes per speciman.")
        .scan<'i', int>();

    parser.add_argument("-S", "--shapes-types")
        .nargs(1)
        .default_value(0b100)
        .help("Types of generated types in binary 100 - triangles 10 - ellipses 1 - squares.")
        .scan<'b', unsigned int>();

    parser.parse_args(argc, argv);
    if (parser.is_used("-v")) {
        auto test = parser.at("-v");
    }
    std::cout << std::to_string(parser.get<int>("-v")) << std::endl;
    if (auto test = parser.is_used(std::string { "-v" })) {
        std::cout << "/* message */" << std::endl;
    }
    std::cout << "/* message */" << std::endl;

    throw std::runtime_error("not implemented parse");
    return false;
}
} // namespace Config

// std::cout << " -h --help            Print help" << std::endl
//           << " -P --print-vals      Print configurated values" << std::endl >
//           << " -i --input           <file.png> Input image fileName" <<
//           std::endl
//           << " -o --output          <file.png> Output image fileName" <<
//           std::endl
//           << " -t --threads         <int> Number of threads that the program
//           will use for calculations " << std::endl
//           << " -p --population      <int> Size of population  " << std::endl
//           << " -s --shapes-amount   <int> Amount of generated shapes  " <<
//           std::endl
//           << " -S --shape-types     <int> Types of generated types in binary
//           10 - ellipses 1 - squares   " << std::endl
//           << " -r --resemblance     <float> % resemblance of source image at
//           which the program will exit" << std::endl
//           << " --hours              <float> hours after which the program
//           will call it a day" << std::endl
//           << " --scale              <float> % scale of shapes 1 means a
//           shape can take the whole canvas" << std::endl
//           << " -m --mutation        <float> % chance of mutation" <<
//           std::endl
//           << " -v --verbose         <int>(optional) print info during
//           program runtime" << std::endl
//           << " -L --log-to-file     <file>(optional) log to file and a name
//           of file Log will be saved to" << std::endl;