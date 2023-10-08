#include "ArtGeneration.hpp"
#include "common/Config.hpp"
#include "drawing/openGL/openGLDrawer.hpp"
#include "fitness.h"
#include "genetic/Genotype.hpp"
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cairo/cairo.h>
#include <cstdlib>
#include <string>

void prepareConfig(int argc, const char* argv[])
{
    Config::parse(argc, argv);
    logger.setLevel((Level)Config::get<Config::Argument::VERBOSE>());
    if (Config::is_used(Config::Argument::VERBOSE)) {
        logger.orTarget(Target::STDOUT);
    }
    if (Config::is_used(Config::Argument::LOG)) {
        logger.setFile("./" + Config::get<Config::Argument::LOG>(), true);
        logger.xorTarget(Target::LOG_FILE);
    }
}

int main(int argc, const char* argv[])
{
    prepareConfig(argc, argv);
    // file Exists
    struct stat buffer;
    if ((stat(Config::get<Config::Argument::INPUT>().c_str(), &buffer) != 0)) {
        logger.LogErr("no input file: " + Config::get<Config::Argument::INPUT>());
        return 2;
    }
    logger.LogInfo("Starting");
    ArtGeneration gen(Config::get<Config::Argument::POPULATION>(), Config::get<Config::Argument::SHAPE_AMOUNT>());
    logger.LogInfo("cairo_image_surface_create_from_png");
    cairo_surface_t* image = cairo_image_surface_create_from_png(Config::get<Config::Argument::INPUT>().c_str());

    int _width = cairo_image_surface_get_width(image);
    int _height = cairo_image_surface_get_height(image);
    unsigned char* img_data = cairo_image_surface_get_data(image);

    std::vector<unsigned char> flippedPixels(_width * _height * 4);
    for (int y = 0; y < _height; y++) {
        memcpy(flippedPixels.data() + (y * _width * 4),
            img_data + ((_height - y - 1) * _width * 4),
            _width * 4);
    }
    int stride = cairo_image_surface_get_stride(image);
    image = cairo_image_surface_create_for_data(flippedPixels.data(), CAIRO_FORMAT_ARGB32, _width, _height, stride);

    logger.LogInfo("StartEvolution");
    gen.StartEvolution(image);
    cairo_surface_destroy(image);
    logger.LogDeb(Profiler::getInstance()->getTimingsAsString().c_str());

    return 0;
}