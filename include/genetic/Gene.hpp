#ifndef GENE_HPP
#define GENE_HPP

#include "common/Config.hpp"
#include "common/DataStructures.hpp"
#include "common/Randoms.hpp"
#include "my_utils/Logger.hpp"
#include <math.h>
class Gene {
public:
    myData::ShapeType type_of_shape;
    myData::float2 position;
    float rotation;
    myData::float2 scale;
    myData::color_RGBA color;
    void randomize();
    void mutate(float mutationRate = 0.001f);
    void wiggle(float mutationRate = 0.001f);

    void randomizeCenter();

private:
    void mutateType(float mutationRate = 0.001f);
    void mutateColor(float mutationRate = 0.001f);
    void mutatePos(float mutationRate = 0.001f);
    void mutateRot(float mutationRate = 0.001f);
    void mutateSize(float mutationRate = 0.001f);
    void wiggleColor(float mutationRate = 0.001f);
    void wigglePos(float mutationRate = 0.001f);
    void wiggleRot(float mutationRate = 0.001f);
    void wiggleSize(float mutationRate = 0.001f);

    myData::ShapeType RandomiezeType();
};

#endif // GENE_HPP
