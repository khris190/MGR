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
    Log.setTarget(Target::DISABLED);
    Log.setLevel((Level)Config::get<Config::Argument::VERBOSE>());

    if (Config::is_used(Config::Argument::VERBOSE)) {
        Log.xorTarget(Target::STDOUT);
    }
    if (Config::is_used(Config::Argument::LOG)) {
        Log.setFile("./" + Config::get<Config::Argument::LOG>(), true);
        Log.xorTarget(Target::LOG_FILE);
    }
    // Log.LogInfo("Starting");
    {
        newTimer("mainTestTimer");
        for (size_t i = 0; i < 10000; i++) {
            Log.LogInfo("artGeneration");
        }
        // ArtGeneration gen(Config::population_size.value, Config::shape_amount.value);
        // Log.LogInfo("cairo_image_surface_create_from_png");
        // cairo_surface_t *image = cairo_image_surface_create_from_png(Config::input_name.value.c_str());
        // Log.LogInfo("StartEvolution");
        // gen.StartEvolution(image);
        // cairo_surface_destroy(image);
    }
    Log.LogDeb(Profiler::getInstance()->getTimingsAsString());
    return 0;
}
