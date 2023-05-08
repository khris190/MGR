#include "DataStructures.hpp"

namespace myData
{

    float2::float2(float x_, float y_)
        : x(x_)
        , y(y_)
    {
    }

    float3::float3(float x_, float y_, float z_)
        : x(x_)
        , y(y_)
        , z(z_)
    {
    }

    float4::float4(float x_, float y_, float z_, float a_)
        : x(x_)
        , y(y_)
        , z(z_)
        , a(a_)
    {
    }

    void position::move(float x_, float y_, float z_)
    {
        this->x += x_;
        this->y += y_;
        this->z += z_;
    }

    float2 position::get_2D() { return float2(this->x, this->y); }

    color_RGBA::color_RGBA(float r_, float g_, float b_, float a_)
        : r(r_)
        , g(g_)
        , b(b_)
        , a(a_)
    {
    }

    color_RGB::color_RGB(float r_, float g_, float b_)
        : r(r_)
        , g(g_)
        , b(b_)
    {
    }
}