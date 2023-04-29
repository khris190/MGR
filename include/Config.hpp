#include "external_utils/argparse.hpp"
#include "my_utils/Logger.hpp"
#include <any>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string>

#define TYPE_FROM_ARGUMENT(enum_value)                                                                                 \
    std::conditional_t<                                                                                                \
        enum_value == Argument::VERBOSE, int,                                                                          \
        std::conditional_t<                                                                                            \
            enum_value == Argument::PRINT_VALS, bool,                                                                  \
            std::conditional_t<                                                                                        \
                enum_value == Argument::INPUT, std::string,                                                            \
                std::conditional_t<                                                                                    \
                    enum_value == Argument::OUTPUT, std::string,                                                       \
                    std::conditional_t<                                                                                \
                        enum_value == Argument::THREADS, int,                                                          \
                        std::conditional_t<                                                                            \
                            enum_value == Argument::POPULATION, int,                                                   \
                            std::conditional_t<enum_value == Argument::SHAPE_AMOUNT, int,                              \
                                               std::conditional_t<enum_value == Argument::LOG, std::string,            \
                                                                  /* default type */ float>>>>>>>>

namespace Config
{

    extern argparse::ArgumentParser parser;
    enum class Argument : short {
        VERBOSE = 1,
        PRINT_VALS = 2,
        INPUT = 3,
        OUTPUT = 4,
        THREADS = 5,
        POPULATION = 6,
        SHAPE_AMOUNT = 7,
        SHAPE_TYPES = 8,
        RESEMPLENCE = 9,
        HOURS = 10,
        SCALE = 11,
        MUTATION = 12,
        LOG = 13
    };

    static map<Argument, string> Arguments
        = { { Argument::VERBOSE, "-V" },      { Argument::PRINT_VALS, "-p" },  { Argument::INPUT, "-i" },
            { Argument::OUTPUT, "-o" },       { Argument::THREADS, "-t" },     { Argument::POPULATION, "-p" },
            { Argument::SHAPE_AMOUNT, "-s" }, { Argument::SHAPE_TYPES, "-S" }, { Argument::RESEMPLENCE, "-r" },
            { Argument::HOURS, "--hours" },   { Argument::SCALE, "--scale" },  { Argument::MUTATION, "-m" },
            { Argument::LOG, "-L" } };

    bool parse(int argc, char const* argv[]);

    bool is_used(Argument arg);

    template <typename name> auto testTemplate() -> name;

    template <Argument E> auto get() -> TYPE_FROM_ARGUMENT(E)
    {
        return parser.get<TYPE_FROM_ARGUMENT(E)>(Arguments[E]);
    }
}