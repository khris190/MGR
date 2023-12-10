#ifndef GENE_HPP
#define GENE_HPP

#include "common/DataStructures.hpp"
#include "genetic/gene/AbstractGene.hpp"
#include "mutators/AbstractMutator.hpp"
#include <memory>
class Gene : public AbstractGene {
public:
    Gene() = default;
    ~Gene() override = default;
    myData::float2 position;
    float rotation;
    myData::float2 scale;
    myData::color_RGBA color;
    void randomize();
    void mutate(float mutationRate = 0.001f) override;

protected:
    static std::unique_ptr<AbstactMutator> mutator;

private:
    void mutateType(float mutationRate = 0.001f);
    void mutateColor(float mutationRate = 0.001f);
    void mutatePos(float mutationRate = 0.001f);
    void mutateRot(float mutationRate = 0.001f);
    void mutateSize(float mutationRate = 0.001f);

    myData::ShapeType RandomiezeType();
};

#endif // GENE_HPP
