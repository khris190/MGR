#include "Gene.hpp"

myData::ShapeType randomieType()
{
    unsigned char out;
    // reroll while we get stuff that is not turned on
    do {
        out = (1 << rand() % Config::get<Config::Argument::SHAPE_AMOUNT>());
    } while ((out & Config::get<Config::Argument::SHAPE_TYPES>()) == 0);

    return (myData::ShapeType)out;
}

void Gene::randomize()
{
    type_of_shape = randomieType();
    position = myData::float2(fRand(), fRand());
    rotation = fRand();
    scale = myData::float2(fRand(), fRand());
    color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
}

void Gene::randomizeCenter()
{
    type_of_shape = randomieType();
    position = myData::float2(0.5f, 0.5f);
    rotation = fRand();
    scale = myData::float2(fRand(), fRand());
    color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
}

void Gene::mutate(float mutationRate)
{
    // if (Config::enabled_shape_types_amount > 1) {
    //     MutateType( mutationRate);
    // }
    mutateColor(mutationRate);
    mutatePos(mutationRate);
    mutateRot(mutationRate);
    mutateSize(mutationRate);
}
void Gene::mutateType(float mutationRate)
{

    if (fRand() <= mutationRate / 2) {
        type_of_shape = randomieType();
    }
}
void Gene::mutateColor(float mutationRate)
{
    if (fRand() <= mutationRate) {
        color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
    }
}
void Gene::mutatePos(float mutationRate)
{
    if (fRand() <= mutationRate) {
        position = myData::float2(fRand(), fRand());
    }
}
void Gene::mutateRot(float mutationRate)
{
    if (fRand() <= mutationRate) {
        rotation = fRand();
    }
}
void Gene::mutateSize(float mutationRate)
{
    if (fRand() <= mutationRate) {
        scale = myData::float2(fRand(), fRand());
    }
}

void Gene::wiggle(float mutationRate)
{
    wiggleColor(mutationRate);
    wigglePos(mutationRate);
    wiggleRot(mutationRate);
    wiggleSize(mutationRate);
}

void Gene::wiggleColor(float mutationRate)
{
    if (fRand() <= mutationRate) {
        color.r += (fRand() - color.r) / 50;
        color.g += (fRand() - color.g) / 50;
        color.b += (fRand() - color.b) / 50;
        color.a += (fRand() - color.a) / 50;
    }
}
void Gene::wigglePos(float mutationRate)
{
    if (fRand() <= mutationRate) {
        position.x += (fRand() - position.x) / 100;
        position.y += (fRand() - position.y) / 100;
    }
}
void Gene::wiggleRot(float mutationRate)
{
    if (fRand() <= mutationRate) {
        rotation += (fRand() - rotation) / 50;
    }
}
void Gene::wiggleSize(float mutationRate)
{
    if (fRand() <= mutationRate) {
        scale.x += (fRand() - scale.x) / 50;
        scale.y += (fRand() - scale.y) / 50;
    }
}