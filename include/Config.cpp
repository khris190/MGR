#include "Config.hpp"
#include <string>

#ifndef VERSION
#define VERSION "0.0.1"
#endif // !VERSION

namespace Config
{
    argparse::ArgumentParser parser("main", VERSION, argparse ::default_arguments::all);
    bool is_used(Argument arg) { return parser.is_used(Arguments[arg]); }

    bool parse(int argc, char const* argv[])
    {
        parser.add_argument("-V", "--verbose")
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
            .default_value(128)
            .help("Number of threads that the program will use for calculations.")
            .scan<'i', int>();

        parser.add_argument("-s", "--shape-amount")
            .nargs(1)
            .default_value(64)
            .help("Amount of generated shapes per speciman.")
            .scan<'i', int>();

        parser.add_argument("-S", "--shape-types")
            .nargs(1)
            .default_value(0b100)
            .help("Types of generated types in binary 100 - triangles 10 - ellipses 1 - squares.")
            .scan<'b', unsigned int>();
        parser.add_argument("-r", "--resemblance")
            .nargs(1)
            .default_value(0.9)
            .help("resemblance of source image at which the program will exit.")
            .scan<'g', float>();
        parser.add_argument("--hours")
            .nargs(1)
            .default_value(4.f)
            .help("hours after which the program will call it a day.")
            .scan<'g', float>();
        parser.add_argument("--scale")
            .nargs(1)
            .default_value(0.4f)
            .help("scale of shapes 1 means a shape can take the whole canvas.")
            .scan<'g', float>();

        parser.add_argument("-m", "--mutation")
            .nargs(1)
            .default_value(0.005f)
            .help("scale of shapes 1 means a shape can take the whole canvas.")
            .scan<'g', float>();

        parser.add_argument("-L", "--log-to-file ")
            .nargs(argparse::nargs_pattern::optional)
            .default_value(std::string { "artGen.log" })
            .help("log to file and an optional name of file Log will be saved to");

        parser.parse_args(argc, argv);
        // if (parser.is_used("-v")) {
        //     auto test = parser.at("-v");
        // }
        // std::cout << parser.get<int>("-V") << std::endl;
        // if (auto test = parser.is_used(std::string { "-V" })) {
        //     std::cout << "/* message */" << std::endl;
        // }

        return true;
    }

} // namespace Config
