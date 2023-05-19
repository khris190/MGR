#ifndef OPENGLDRAWER_HPP
#define OPENGLDRAWER_HPP

#include "genetic/Genotype.hpp"
#include "handler.hpp"
#include "objects/mesh.hpp"
#include "my_utils/Logger.hpp"

namespace OpenGLDrawer
{
    void Initialize(int width, int height);

    void Draw(Genotype& populus);

    void AddTriangles(Genotype& populus, float Scale = 0.2f);

    std::vector<float> prepareTriangles(Genotype& genes, float Scale);
} // namespace OpenGLDrawer

#endif // OPENGLDRAWER_HPP
