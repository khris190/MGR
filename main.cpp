#include "ArtGeneration.hpp"
#include "common/Config.hpp"
#include "drawing/openGL/openGLDrawer.hpp"
#include "fitness.h"
#include "genetic/Genotype.hpp"
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cairo/cairo.h>
#include <cstdlib>

int main(int argc, char const* argv[])
{

    Config::parse(argc, argv);
    // OpenGLDrawer::Draw();
    logger.setTarget(Target::DISABLED);
    logger.setLevel((Level)Config::get<Config::Argument::VERBOSE>());

    if (Config::is_used(Config::Argument::VERBOSE)) {
        logger.xorTarget(Target::STDOUT);
    }
    if (Config::is_used(Config::Argument::LOG)) {
        logger.setFile("./" + Config::get<Config::Argument::LOG>(), true);
        logger.xorTarget(Target::LOG_FILE);
    }

    // file Exists
    {
        newTimer("main");
        struct stat buffer;
        if ((stat(Config::get<Config::Argument::INPUT>().c_str(), &buffer) != 0)) {
            logger.LogErr("no input file: " + Config::get<Config::Argument::INPUT>());
            return 2;
        }
    }
    logger.LogInfo("Starting");
    ArtGeneration gen(Config::get<Config::Argument::POPULATION>(), Config::get<Config::Argument::SHAPE_AMOUNT>());
    logger.LogInfo("cairo_image_surface_create_from_png");
    cairo_surface_t* image = cairo_image_surface_create_from_png(Config::get<Config::Argument::INPUT>().c_str());
    logger.LogInfo("StartEvolution");
    gen.StartEvolution(image);
    cairo_surface_destroy(image);
    logger.LogDeb(profiler.getTimingsAsString().c_str());

    return 0;
}
// TODO go back to extern singleton