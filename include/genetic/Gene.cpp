#include "Gene.hpp"

myData::ShapeType RandomieType()
{
    unsigned char out;
    // reroll while we get stuff that is not turned on
    do {
        out = (1 << rand() % Config::get<Config::Argument::SHAPE_AMOUNT>());
    } while ((out & Config::get<Config::Argument::SHAPE_TYPES>()) == 0);

    return (myData::ShapeType)out;
}

void Gene::Randomize()
{
    type_of_shape = RandomieType();
    position = myData::float2(fRand(), fRand());
    rotation = fRand();
    scale = myData::float2(fRand(), fRand());
    color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
}

void Gene::RandomizeCenter()
{
    type_of_shape = RandomieType();
    position = myData::float2(0.5f, 0.5f);
    rotation = fRand();
    scale = myData::float2(fRand(), fRand());
    color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
}

void Gene::Mutate(float mutation_rate)
{
    // if (Config::enabled_shape_types_amount > 1) {
    //     MutateType(mutation_rate);
    // }

    MutateColor(mutation_rate);
    MutatePos(mutation_rate);
    MutateRot(mutation_rate);
    MutateSize(mutation_rate);
}
void Gene::MutateType(float mutation_rate)
{

    if (fRand() <= mutation_rate / 2) {
        type_of_shape = RandomieType();
    }
}
void Gene::MutateColor(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        color = myData::color_RGBA(fRand(), fRand(), fRand(), fRand());
    }
}
void Gene::MutatePos(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        position = myData::float2(fRand(), fRand());
    }
}
void Gene::MutateRot(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        rotation = fRand();
    }
}
void Gene::MutateSize(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        scale = myData::float2(fRand(), fRand());
    }
}

void Gene::Wiggle(float mutation_rate)
{
    WiggleColor(mutation_rate);
    WigglePos(mutation_rate);
    WiggleRot(mutation_rate);
    WiggleSize(mutation_rate);
}

void Gene::WiggleColor(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        color.r += (fRand() - color.r) / 50;
        color.g += (fRand() - color.g) / 50;
        color.b += (fRand() - color.b) / 50;
        color.a += (fRand() - color.a) / 50;
    }
}
void Gene::WigglePos(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        position.x += (fRand() - position.x) / 100;
        position.y += (fRand() - position.y) / 100;
    }
}
void Gene::WiggleRot(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        rotation += (fRand() - rotation) / 50;
    }
}
void Gene::WiggleSize(float mutation_rate)
{
    if (fRand() <= mutation_rate) {
        scale.x += (fRand() - scale.x) / 50;
        scale.y += (fRand() - scale.y) / 50;
    }
}