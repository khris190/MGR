#include "Config.hpp"
#include "fitness.h"
#include <optional>

int main(int argc, char const* argv[])
{
    Config::parse(argc, argv);
    calculateFitness(nullptr, nullptr, 10, 100);
    std::optional<int> test;
    auto test1 = Config::get<Config::Argument::HOURS>();
    auto test2 = typeid(test1).name();
    // ArgsParser parser(argc, argv);
    // Log.setTarget(Target::DISABLED);
    // Log.setLevel((Level)Config::verbose_level.value);
    // std::cout << Config::resemblance.value << std::endl;

    // if (Config::verbose.value)
    // {
    //     Log.setTarget(Target::STDOUT);
    //     Log.setLevel((Level)Config::verbose_level.value);
    // }
    // if (Config::log_to_file.value)
    // {
    //     Log.setFile(Config::out_folder_name + Config::log_to_file_name.value, true);
    //     Log.setTarget(Target::LOG_FILE);
    // }
    // Log.LogInfo("Starting");
    // if (parser.is_parsed)
    // {
    //     newTimer("mainTestTimer");
    //     Log.LogInfo("artGeneration");
    //     ArtGeneration gen(Config::population_size.value, Config::shape_amount.value);
    //     Log.LogInfo("cairo_image_surface_create_from_png");
    //     cairo_surface_t *image = cairo_image_surface_create_from_png(Config::input_name.value.c_str());
    //     Log.LogInfo("StartEvolution");
    //     gen.StartEvolution(image);
    //     cairo_surface_destroy(image);
    // }
    // Log.LogDeb(Profiler::getInstance()->getTimingsAsString());
    return 0;
}
