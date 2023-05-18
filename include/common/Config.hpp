#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "external_utils/argparse.hpp"
#include "my_utils/Logger.hpp"
#include <any>
#include <bitset>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/stat.h>
#include <sys/types.h>
#include <type_traits>
#include <unordered_map>

// TODO https://www.youtube.com/watch?v=INn3xa4pMfg ??

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
        RESEMBLENCE = 9,
        HOURS = 10,
        SCALE = 11,
        MUTATION = 12,
        LOG = 13
    };

    template <Argument Condition> struct ArgumentType {
        using type = float;
    };
    template <> struct ArgumentType<Argument::VERBOSE> {
        using type = int;
    };
    template <> struct ArgumentType<Argument::PRINT_VALS> {
        using type = bool;
    };
    template <> struct ArgumentType<Argument::INPUT> {
        using type = std::string;
    };
    template <> struct ArgumentType<Argument::OUTPUT> {
        using type = std::string;
    };
    template <> struct ArgumentType<Argument::LOG> {
        using type = std::string;
    };
    template <> struct ArgumentType<Argument::THREADS> {
        using type = int;
    };
    template <> struct ArgumentType<Argument::POPULATION> {
        using type = int;
    };
    template <> struct ArgumentType<Argument::SHAPE_AMOUNT> {
        using type = int;
    };
    template <> struct ArgumentType<Argument::SHAPE_TYPES> {
        using type = unsigned int;
    };

    // template <Argument Arg> struct ArgumentType {
    //     template <Argument T> static constexpr auto getType()
    //     {
    //         if constexpr (T == Argument::VERBOSE)
    //             return std::__type_identity<int> {};
    //         else if constexpr (T == Argument::PRINT_VALS)
    //             return std::__type_identity<bool> {};
    //         else if constexpr (T == Argument::INPUT)
    //             return std::__type_identity<std::string> {};
    //         else if constexpr (T == Argument::OUTPUT)
    //             return std::__type_identity<std::string> {};
    //         else if constexpr (T == Argument::LOG)
    //             return std::__type_identity<std::string> {};
    //         else if constexpr (T == Argument::THREADS)
    //             return std::__type_identity<int> {};
    //         else if constexpr (T == Argument::POPULATION)
    //             return std::__type_identity<int> {};
    //         else if constexpr (T == Argument::SHAPE_AMOUNT)
    //             return std::__type_identity<int> {};
    //         else if constexpr (T == Argument::SHAPE_TYPES)
    //             return std::__type_identity<unsigned int> {};
    //         else
    //             return std::__type_identity<float> {};
    //     }

    //     using type = typename decltype(getType<Arg>())::type;
    // };

    static std::unordered_map<Argument, std::string_view> Arguments = { { Argument::VERBOSE, "-V" },
        { Argument::PRINT_VALS, "-p" }, { Argument::INPUT, "-i" }, { Argument::OUTPUT, "-o" },
        { Argument::THREADS, "-t" }, { Argument::POPULATION, "-p" }, { Argument::SHAPE_AMOUNT, "-s" },
        { Argument::SHAPE_TYPES, "-S" }, { Argument::RESEMBLENCE, "-r" }, { Argument::HOURS, "--hours" },
        { Argument::SCALE, "--scale" }, { Argument::MUTATION, "-m" }, { Argument::LOG, "-L" } };

    bool parse(int argc, char const* argv[]);

    bool is_used(Argument arg);

    template <typename name> auto testTemplate() -> name;

    template <Argument Condition> auto get() -> typename ArgumentType<Condition>::type
    {
        using type = typename ArgumentType<Condition>::type;
        return parser.get<type>(Arguments[Condition]);
    }

    extern std::time_t start_time;
    bool doStop(int SecondsAfterToStop = 3600);
    extern std::string out_folder_name;
    void CreateFolderForOutput();
    std::string GetOutputFilePathAndFileName(float Resemblance);

} // namespace Config

#endif // CONFIG_HPP
