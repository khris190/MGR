#include "Population.hpp"
#include "external_utils/BS_thread_pool_light.hpp"
#include "my_utils/Profiler.hpp"
float myFitness(cairo_surface_t *img, unsigned char *surface)
{
  return fitness(img, surface);
}

Population::Population(int populationSize, int genotypeSize)
    : pool(Config::get<Config::Argument::THREADS>())
{
  this->scores.reserve(populationSize);
  this->children.reserve(populationSize);
  for (size_t i = 0; i < populationSize; i++)
  {
    this->children.emplace_back(genotypeSize);
    this->scores.push_back(0.f);
  }
  workers = std::vector<std::future<float>>(children.size());
}

void Population::createNextGeneration(int parent1, int parent2,
                                      float mutationRate)
{
  for (size_t i = 0; i < this->children.size(); i++)
  {
    if (i != parent1 && i != parent2)
    {
      this->children[i].cross(this->children[parent1], this->children[parent2]);
      this->children[i].mutate(mutationRate);
    }
  }
}
void Population::createNextGeneration(float mutationRate)
{
  newTimer("createNextGeneration");
  for (size_t i = 0; i < this->children.size(); i++)
  {
    if (i != this->bests[0].first && i != this->bests[1].first)
    {
      this->children[i].cross(this->children[this->bests[0].first],
                              this->children[this->bests[1].first]);
      this->children[i].mutate(mutationRate);
    }
  }
}
void Population::drawNFitness(cairo_surface_t *img)
{
  newTimer("drawNFitness");
  float scale = Config::get<Config::Argument::SCALE>();
  int size = children.size();
  std::vector<std::vector<unsigned char>> images(children.size());
  for (size_t i = 0; i < this->children.size(); i++)
  {
    openGLDrawer::draw(this->children[i], scale);

    images[i] = openGLDrawer::getPixels();
    workers[i] = pool.submit(myFitness, img, images[i].data());
  }

  for (size_t i = 0; i < this->children.size(); i++)
  {
    this->scores[i] = workers[i].get();
    // this->scores[i] = myFitness(img, images[i].data());
  }
  this->bests = getBest();
}

std::vector<std::pair<int, float>> Population::getBest()
{
  std::vector<std::pair<int, float>> result;
  result.push_back(
      std::pair<int, float>((this->scores[0] > this->scores[1]) ? 1 : 0,
                            std::min(this->scores[0], this->scores[1])));
  result.push_back(
      std::pair<int, float>((this->scores[0] < this->scores[1]) ? 1 : 0,
                            std::max(this->scores[0], this->scores[1])));

  // Iterate over the remaining elements of the vector
  for (int i = 2; i < this->scores.size(); i++)
  {
    if (this->scores[i] > result[1].second)
    {
      result[0].second = result[1].second;
      result[0].first = result[1].first;
      result[1].second = this->scores[i];
      result[1].first = i;
    }
    else if (this->scores[i] > result[0].second)
    {
      result[0].second = this->scores[i];
      result[0].first = i;
    }
  }

  return result;
}