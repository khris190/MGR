#include "Config.hpp"
#include "fitness.h"
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cstdlib>
void cleanup()
{
    shm_unlink("/profiler");
    shm_unlink("/logger");
}
int main(int argc, char const* argv[])
{
    Config::parse(argc, argv);
    std::optional<int> test;
    auto test1 = Config::get<Config::Argument::HOURS>();
    auto test2 = typeid(test1).name();
    logger.setTarget(Target::DISABLED);
    logger.setLevel((Level)Config::get<Config::Argument::VERBOSE>());

    if (Config::is_used(Config::Argument::VERBOSE)) {
        logger.xorTarget(Target::STDOUT);
    }
    if (Config::is_used(Config::Argument::LOG)) {
        logger.setFile("./" + Config::get<Config::Argument::LOG>(), true);
        logger.xorTarget(Target::LOG_FILE);
    }
    // Logger::getInstance()->LogInfo("Starting");
    {
        {
            newTimer("mainTestTimer");
            newTimer("mainTestTimer2");
        }
        for (size_t i = 0; i < 10000; i++) {
            logger.LogInfo("artGeneration");
        }
        // ArtGeneration gen(Config::population_size.value, Config::shape_amount.value);
        // Log.LogInfo("cairo_image_surface_create_from_png");
        // cairo_surface_t *image = cairo_image_surface_create_from_png(Config::input_name.value.c_str());
        // Log.LogInfo("StartEvolution");
        // gen.StartEvolution(image);
        // cairo_surface_destroy(image);
    }
    logger.LogDeb(profiler.getTimingsAsString());
    // Log.LogInfo(std::to_string(MAX_LEVEL_LENGTH));

    atexit(cleanup);
    return 0;
}
// TODO go back to extern singleton