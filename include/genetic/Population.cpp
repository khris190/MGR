#include "Population.hpp"
#include "external_utils/BS_thread_pool_light.hpp"
#include "my_utils/Profiler.hpp"

Population::Population(int populationSize, int genotypeSize)
    : pool(Config::get<Config::Argument::THREADS>())
{
    this->scores.reserve(populationSize);
    this->children.reserve(populationSize);
    for (size_t i = 0; i < populationSize; i++) {
        this->children.push_back(Genotype(genotypeSize));
        this->scores.push_back(0.f);
    }
    workers = std::vector<std::future<float>>(children.size());
}

void Population::CreateNextGeneration(int parent1_, int parent2_, float mutation_rate)
{
    for (size_t i = 0; i < this->children.size(); i++) {
        if (i != parent1_ && i != parent2_) {
            this->children[i].Cross(this->children[parent1_], this->children[parent2_]);
            this->children[i].Mutate(mutation_rate);
        }
    }
}
void Population::CreateNextGeneration(float mutation_rate)
{
    newTimer("CreateNextGeneration");
    for (size_t i = 0; i < this->children.size(); i++) {
        if (i != this->bests[0].first && i != this->bests[1].first) {
            this->children[i].Cross(this->children[this->bests[0].first], this->children[this->bests[1].first]);
            this->children[i].Mutate(mutation_rate);
        }
    }
}
float MyFitness(cairo_surface_t* img, unsigned char* surface) { return fitness(img, surface); }
void Population::DrawNFitness(cairo_surface_t* img)
{
    float scale = Config::get<Config::Argument::SCALE>();
    int width = cairo_image_surface_get_width(img);
    int height = cairo_image_surface_get_height(img);
    {

        std::vector<std::vector<unsigned char>> images(children.size());
        for (size_t i = 0; i < this->children.size(); i++) {
            OpenGLDrawer::Draw(this->children[i], scale);

            images[i] = OpenGLDrawer::getPixels();
            workers[i] = pool.submit(MyFitness, img, images[i].data());
            // u_char* cudaSurface = OpenGLDrawer::GetCUDAImgDataPointer(width, height);
            // this->scores[i] = fitnessGL(img, cudaSurface);
        }
        {
            for (size_t i = 0; i < this->children.size(); i++) {
                this->scores[i] = workers[i].get();
            }
        }
        this->bests = getBest();
    }
}

std::vector<std::pair<int, float>> Population::getBest()
{
    std::vector<std::pair<int, float>> result;
    result.push_back(
        std::pair<int, float>((this->scores[0] > this->scores[1]) ? 1 : 0, std::min(this->scores[0], this->scores[1])));
    result.push_back(
        std::pair<int, float>((this->scores[0] < this->scores[1]) ? 1 : 0, std::max(this->scores[0], this->scores[1])));

    // Iterate over the remaining elements of the vector
    for (int i = 2; i < this->scores.size(); i++) {
        if (this->scores[i] > result[1].second) {
            result[0].second = result[1].second;
            result[0].first = result[1].first;
            result[1].second = this->scores[i];
            result[1].first = i;
        } else if (this->scores[i] > result[0].second) {
            result[0].second = this->scores[i];
            result[0].first = i;
        }
    }

    return result;
}

Population::~Population() { }