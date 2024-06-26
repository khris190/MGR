#include "ArtGeneration.hpp"
#include "common/Config.hpp"
#include "fitness.h"
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cairo/cairo.h>
#include <filesystem>
#include <string>

void prepareConfig(int argc, const char* argv[])
{
    Config::parse(argc, argv);
    logger.setLevel((Level)Config::get<Config::Argument::VERBOSE>());
    if (Config::isUsed(Config::Argument::VERBOSE)) {
        logger.orTarget(Target::STDOUT);
    }
    if (Config::isUsed(Config::Argument::LOG)) {
        logger.setFile("./" + Config::get<Config::Argument::LOG>(), true);
        logger.xorTarget(Target::LOG_FILE);
    }
}

int main(int argc, const char* argv[])
{
    {
        prepareConfig(argc, argv);
        // file Exists

        if (!std::filesystem::exists(Config::get<Config::Argument::INPUT>())) {
            logger.logErr("no input file: " + std::filesystem::absolute(Config::get<Config::Argument::INPUT>()).string());
            return 2;
        }
        logger.logInfo("Starting");
        ArtGeneration gen(Config::get<Config::Argument::POPULATION>(), Config::get<Config::Argument::SHAPE_AMOUNT>());
        logger.logInfo("cairo_image_surface_create_from_png");
        cairo_surface_t* image = cairo_image_surface_create_from_png(Config::get<Config::Argument::INPUT>().c_str());

        int width = cairo_image_surface_get_width(image);
        int height = cairo_image_surface_get_height(image);
        unsigned char const* imgData = cairo_image_surface_get_data(image);

        std::vector<unsigned char> flippedPixels(width * height * 4);
        for (int y = 0; y < height; y++) {
            memcpy(flippedPixels.data() + (y * width * 4),
                imgData + ((height - y - 1) * width * 4),
                width * 4);
        }
        int stride = cairo_image_surface_get_stride(image);
        cairo_surface_destroy(image);
        image = cairo_image_surface_create_for_data(flippedPixels.data(), CAIRO_FORMAT_ARGB32, width, height, stride);

        logger.logInfo("StartEvolution");
        gen.startEvolution(image);
        cairo_surface_destroy(image);
        logger.logDeb(Profiler::getInstance()->getTimingsAsString().c_str());
    }
    return 0;
}
