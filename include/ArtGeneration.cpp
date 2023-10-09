#include "ArtGeneration.hpp"
#include "common/Config.hpp"
#include "drawing/openGL/openGLDrawer.hpp"
#include "fitness.hpp"
#include "genetic/Population.hpp"
#include "my_utils/Profiler.hpp"
#include <cstdio>
#include <exception>

void ArtGeneration::draw(cairo_surface_t* img, size_t index)
{
    this->population.children[index].draw(img, Config::get<Config::Argument::SCALE>());
}

void ArtGeneration::startEvolution(cairo_surface_t* img)
{
    const int coreCount = Config::get<Config::Argument::THREADS>();
    float bestScore = 0;
    int noChangesCounter = 0;
    long mutationsCounter = 0;
    float lastScore = bestScore;
    float savedBestScore = bestScore;

    int width = cairo_image_surface_get_width(img);
    int height = cairo_image_surface_get_height(img);

    openGLDrawer::initialize(width, height);
    BS::thread_pool_light pool(coreCount);
    do {
        newTimer("Evolution: ");
#pragma region calculate best
        this->population.drawNFitness(img);

        logger.LogDeb(Profiler::getInstance()->getTimingsAsString().c_str());
        if (0 > this->population.bests[1].first || 0 > this->population.bests[0].first) {
            logger.LogEmerg("wtf, parent1_ or parent2_ wasnt selected");
            exit(2);
        }
        this->population.createNextGeneration(Config::get<Config::Argument::MUTATION>());
        bestScore = this->population.bests[1].second;
        if (lastScore == bestScore) {
            noChangesCounter++;
        } else {
            noChangesCounter = 0;
        }

        lastScore = bestScore;
        logger.LogInfo(
            ("Score: " + std::to_string(bestScore) + "\nDifference: " + std::to_string(bestScore - savedBestScore))
                .c_str());

        if (bestScore >= savedBestScore) {
            savedBestScore = bestScore;
            if (mutationsCounter % 50 == 0) {
                {
                    openGLDrawer::draw(this->population.children[this->population.bests[1].first],
                        Config::get<Config::Argument::SCALE>());
                    openGLDrawer::saveToPNG(Config::getOutputFilePathAndFileName(savedBestScore).c_str());
                }
                logger.LogDeb(Profiler::getInstance()->getTimingsAsString().c_str());
            }
            mutationsCounter++;
        }
    } while (bestScore < Config::get<Config::Argument::RESEMBLENCE>() && !Config::doStop());

    openGLDrawer::draw(
        this->population.children[this->population.bests[1].first], Config::get<Config::Argument::SCALE>());
    openGLDrawer::saveToPNG(Config::getOutputFilePathAndFileName(savedBestScore).c_str());
    openGLDrawer::clean();
}

ArtGeneration::ArtGeneration(int childrenSize, int genotypeSize)
    : population(childrenSize, genotypeSize)
{
    srand(static_cast<unsigned int>(time(nullptr)));
}