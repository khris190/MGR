#ifndef CAIRODRAWER_HPP
#define CAIRODRAWER_HPP

#include "../drawingInterface.hpp"
#include <cairo/cairo.h>
#include <cstddef>

class CarioDrawer : public IDrawer
{
public:
    CarioDrawer() = default;
    CarioDrawer(CarioDrawer&&) = default;
    CarioDrawer(const CarioDrawer&) = default;
    CarioDrawer& operator=(CarioDrawer&&) = default;
    CarioDrawer& operator=(const CarioDrawer&) = default;
    ~CarioDrawer() = default;

    void drawImage(Genotype genotype);

private:
};

#endif // CAIRODRAWER_HPP
