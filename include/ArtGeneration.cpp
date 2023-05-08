// #include "ArtGeneration.hpp"

// void ArtGeneration::CreateChildren(float mutation_rate)
// {
//     for (size_t i = 0; i < children_size_; i++) {
//         if (i != this->parent1_ && i != this->parent2_) {
//             this->children_[i]->Cross(this->children_[parent1_], this->children_[parent2_]);
//             this->children_[i]->Mutate(mutation_rate);
//         }
//     }
// }

// void ArtGeneration::Draw(cairo_surface_t* img, size_t index) { this->children_[index]->Draw(img,
// Config::scale.value); }

// void ArtGeneration::AsyncFitness(cairo_surface_t* img, Genotype** children, volatile int* best_indexes,
//                                  volatile float* best_scores, int start, int stop, int _width, int _height)
// {
//     newTimer("fitness");
//     best_indexes[0] = -1;
//     best_indexes[1] = -1;
//     volatile float bestScore = 0;
//     volatile float bestScore2 = 0;
//     best_scores[0] = 0;
//     best_scores[1] = 0;
//     for (size_t i = start; i < stop; i++) {
//         cairo_surface_t* temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
//         {
//             newTimer("drawing");
//             children[i]->Draw(temp_surface);
//         }
//         float score = fitness(img, temp_surface);
//         if (bestScore < score) {
//             bestScore2 = bestScore;
//             bestScore = score;
//             best_scores[1] = best_scores[0];
//             best_scores[0] = bestScore;
//             best_indexes[1] = best_indexes[0];
//             best_indexes[0] = i;
//         } else if (bestScore2 < score) {
//             bestScore2 = score;
//             best_scores[1] = bestScore2;
//             best_indexes[1] = i;
//         }

//         cairo_surface_destroy(temp_surface);
//     }
// }

// void ArtGeneration::StartEvolution(cairo_surface_t* img)
// {
//     const int coreCount = Config::thread_count.value;
//     float bestScore = 0;
//     float bestScore2 = 0;
//     int noChangesCounter = 0;
//     long MutationsCounter = 0;
//     float lastScore = bestScore;
//     float savedBestScore = bestScore;

//     int _width, _height;

//     _width = cairo_image_surface_get_width(img);
//     _height = cairo_image_surface_get_height(img);

//     long wiggleCounter = 0;
//     BS::thread_pool_light pool(coreCount);
//     do {
//         newTimer("Evolution: ");
// #pragma region calculate best
//         volatile int best[coreCount * 2];
//         volatile float bestScores[coreCount * 2];
//         {
//             std::vector<std::future<void>> workers;
//             int offset = this->children_size_ / coreCount;
//             for (size_t i = 0; i < coreCount; i++) {
//                 workers.push_back(pool.submit(ArtGeneration::AsyncFitness, img, this->children_, best + (i * 2),
//                                               bestScores + (i * 2), offset * i, offset * (i + 1), _width, _height));
//             }
//             for (std::future<void>& t : workers) {
//                 t.get();
//             }
//         }

//         this->parent1_ = -1;
//         this->parent2_ = -1;
//         bestScore = 0;
//         bestScore2 = 0;
//         for (size_t i = 0; i < coreCount * 2; i++) {
//             if (bestScores[i] > bestScore) {
//                 bestScore2 = bestScore;
//                 bestScore = bestScores[i];
//                 this->parent2_ = this->parent1_;
//                 this->parent1_ = best[i];
//             } else if (bestScores[i] > bestScore2) {
//                 bestScore2 = bestScores[i];
//                 this->parent2_ = best[i];
//             }
//         }

//         if (this->parent2_ < 0) {
//             bestScore = 0;
//             for (size_t i = 1; i < coreCount * 2; i++) {
//                 if (bestScores[i] > bestScore) {
//                     bestScore = bestScores[i];
//                     this->parent2_ = best[i];
//                 }
//             }
//         }
//         if (0 > parent1_ || 0 > parent2_) {
//             Log.LogEmerg("wtf, parent1_ or parent2_ wasnt selected");
//         }

//         if (wiggleCounter % 4 == 3) {
//             // Wiggle
//             for (size_t i = 0; i < children_size_; i++) {
//                 if (i != parent1_ && i != parent2_) {
//                     this->children_[i]->Wiggle(Config::mutation.value * 2);
//                 }
//             }
//         } else if (wiggleCounter % 4 == 0) {
//             Log.LogInfo("WIGGLE");
//             this->CreateChildren(Config::mutation.value);
//         } else {
//             this->CreateChildren(Config::mutation.value);
//         }
//         wiggleCounter++;

//         if (lastScore == bestScore) {
//             noChangesCounter++;
//         } else {
//             noChangesCounter = 0;
//         }
//         if (noChangesCounter >= 10) {
//             Log.LogInfo("using increased mutation rate");
//             this->CreateChildren(Config::mutation.value * 2);
//         }

//         lastScore = bestScore;
//         Log.LogInfo("Score: " + std::to_string(bestScore)
//                     + "\nDifference: " + std::to_string(bestScore - savedBestScore));
//         Log.LogDeb(Profiler::getInstance()->getTimingsAsString());

//         if (bestScore >= savedBestScore) {
//             savedBestScore = bestScore;
//             if (MutationsCounter % 10 == 0) {
//                 cairo_surface_t* temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
//                 this->Draw(temp_surface, this->parent1_);
//                 cairo_surface_write_to_png(temp_surface,
//                 Config::GetOutputFilePathAndFileName(savedBestScore).c_str());

//                 cairo_surface_destroy(temp_surface);
//             }
//             MutationsCounter++;
//         }
//     } while (bestScore < Config::resemblance.value && !Config::doStop());
//     cairo_surface_t* temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
//     this->Draw(temp_surface, this->parent1_);
//     cairo_surface_write_to_png(temp_surface, Config::GetOutputFilePathAndFileName(savedBestScore).c_str());

//     if (temp_surface) {
//         cairo_surface_destroy(temp_surface);
//     }
// }

// void ArtGeneration::GenerateFirstPopulation(int children_size, int genotype_size)
// {
//     children_ = (Genotype**)malloc(sizeof(Genotype) * children_size);
//     for (size_t i = 0; i < children_size; i++) {
//         children_[i] = new Genotype(genotype_size);
//     }
// }

// ArtGeneration::ArtGeneration(int children_size, int genotype_size)
// {
//     srand(time(NULL));
//     this->children_size_ = children_size;
//     GenerateFirstPopulation(children_size, genotype_size);
// }

// ArtGeneration::~ArtGeneration()
// {
//     for (size_t i = 0; i < children_size_; i++) {
//         delete children_[i];
//     }

//     free(children_);
// }