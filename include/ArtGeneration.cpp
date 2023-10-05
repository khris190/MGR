#include "ArtGeneration.hpp"
#include "common/Config.hpp"
#include "drawing/openGL/openGLDrawer.hpp"
#include "genetic/Population.hpp"
#include "my_utils/Profiler.hpp"
#include <cstdio>
#include <exception>
#include "fitness.hpp"

void ArtGeneration::Draw(cairo_surface_t* img, size_t index)
{
    // throw new std::runtime_error("notimplemented");
    this->_population.children[index].Draw(img, Config::get<Config::Argument::SCALE>());
}

void ArtGeneration::AsyncFitness(cairo_surface_t* img, Population population, volatile int* best_indexes,
  volatile float* best_scores, int start, int stop, int _width, int _height)
{
    newTimer("fitness");
    best_indexes[0] = -1;
    best_indexes[1] = -1;
    volatile float bestScore = 0;
    volatile float bestScore2 = 0;
    best_scores[0] = 0;
    best_scores[1] = 0;
    for (size_t i = start; i < stop; i++) {
        cairo_surface_t* temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
        {
            newTimer("drawing");
            population.children[i].Draw(temp_surface);
        }
        float score = fitness(img, temp_surface);
        if (bestScore < score) {
            bestScore2 = bestScore;
            bestScore = score;
            best_scores[1] = best_scores[0];
            best_scores[0] = bestScore;
            best_indexes[1] = best_indexes[0];
            best_indexes[0] = i;
        } else if (bestScore2 < score) {
            bestScore2 = score;
            best_scores[1] = bestScore2;
            best_indexes[1] = i;
        }

        cairo_surface_destroy(temp_surface);
    }
}

void ArtGeneration::StartEvolution(cairo_surface_t* img)
{
    const int coreCount = Config::get<Config::Argument::THREADS>();
    float bestScore = 0;
    float bestScore2 = 0;
    int noChangesCounter = 0;
    long MutationsCounter = 0;
    float lastScore = bestScore;
    float savedBestScore = bestScore;

    int _width = cairo_image_surface_get_width(img);
    int _height = cairo_image_surface_get_height(img);

    OpenGLDrawer::Initialize(_width, _height);
    long wiggleCounter = 0;
    BS::thread_pool_light pool(coreCount);
    do {
        newTimer("Evolution: ");
#pragma region calculate best
        {
            newTimer("whole new generation");
            this->_population.DrawNFitness(img);
        }

        if (false) {
            // newTimer("whole old generation");
            // volatile int best[coreCount * 2];
            // volatile float bestScores[coreCount * 2];
            // {
            //     std::vector<std::future<void>> workers;
            //     int offset = this->_population.children.size() / coreCount;
            //     for (size_t i = 0; i < coreCount; i++) {

            //         workers.push_back(pool.submit(ArtGeneration::AsyncFitness, img, this->_population, best + (i *
            //         2),
            //           bestScores + (i * 2), offset * i, offset * (i + 1), _width, _height));
            //     }
            //     for (std::future<void>& t : workers) {
            //         try {
            //             t.get();
            //         } catch (const std::exception& e) {
            //             logger.LogErr(e.what());
            //         }
            //     }
            // }

            // this->parent1_ = -1;
            // this->parent2_ = -1;
            // bestScore = 0;
            // bestScore2 = 0;
            // for (size_t i = 0; i < coreCount * 2; i++) {
            //     if (bestScores[i] > bestScore) {
            //         bestScore2 = bestScore;
            //         bestScore = bestScores[i];
            //         this->parent2_ = this->parent1_;
            //         this->parent1_ = best[i];
            //     } else if (bestScores[i] > bestScore2) {
            //         bestScore2 = bestScores[i];
            //         this->parent2_ = best[i];
            //     }
            // }

            // if (this->parent2_ < 0) {
            //     bestScore = 0;
            //     for (size_t i = 1; i < coreCount * 2; i++) {
            //         if (bestScores[i] > bestScore) {
            //             bestScore = bestScores[i];
            //             this->parent2_ = best[i];
            //         }
            //     }
            // }
        }

        logger.LogDeb(Profiler::getInstance()->getTimingsAsString().c_str());
        if (0 > this->_population.bests[1].first || 0 > this->_population.bests[0].first) {
            logger.LogEmerg("wtf, parent1_ or parent2_ wasnt selected");
            exit(2);
        }
        this->_population.CreateNextGeneration(Config::get<Config::Argument::MUTATION>());
        bestScore = this->_population.bests[1].second;
        // OpenGLDrawer::Draw(this->_population.children[this->_population.bests[1].first]);
        // OpenGLDrawer::SaveToPNG(Config::GetOutputFilePathAndFileName(bestScore).c_str());
        if (lastScore == bestScore) {
            noChangesCounter++;
        } else {
            noChangesCounter = 0;
        }
        if (noChangesCounter >= 10) {
            logger.LogInfo("using increased mutation rate");
            // this->_population.CreateNextGeneration(Config::get<Config::Argument::MUTATION>() * 2);
        }

        lastScore = bestScore;
        logger.LogInfo(
          ("Score: " + std::to_string(bestScore) + "\nDifference: " + std::to_string(bestScore - savedBestScore))
            .c_str());
        // logger.LogDeb(profiler.getTimingsAsString().c_str());

        if (bestScore >= savedBestScore) {
            savedBestScore = bestScore;
            if (MutationsCounter % 50 == 0) {
                {
                    OpenGLDrawer::Draw(this->_population.children[this->_population.bests[1].first],
                      Config::get<Config::Argument::SCALE>());
                    OpenGLDrawer::SaveToPNG(Config::GetOutputFilePathAndFileName(savedBestScore).c_str());
                }
                logger.LogDeb(Profiler::getInstance()->getTimingsAsString().c_str());
            }
            MutationsCounter++;
        }
    } while (bestScore < Config::get<Config::Argument::RESEMBLENCE>() && !Config::doStop());

    OpenGLDrawer::Draw(
      this->_population.children[this->_population.bests[1].first], Config::get<Config::Argument::SCALE>());
    OpenGLDrawer::SaveToPNG(Config::GetOutputFilePathAndFileName(savedBestScore).c_str());
    OpenGLDrawer::clean();
}

ArtGeneration::ArtGeneration(int children_size, int genotype_size)
    : _population(children_size, genotype_size)
{
    srand(time(NULL));
}

ArtGeneration::~ArtGeneration() { }