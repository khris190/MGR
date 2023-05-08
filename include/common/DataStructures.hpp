
#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP

#pragma region floats

namespace myData
{

    enum ShapeType {
        rectangle = 1,
        ellipse = 2,
        triangle = 4,
    };
    union ShapesSwitches {
        struct ShapesBools {
            unsigned char rectangle : 1, ellipse : 1, triangle : 1;
        } bools;
        unsigned char shapes;
        ShapesSwitches(unsigned char x = 0) { shapes = x; }
    };
    struct float2 {
        float x, y;
        float2(float x_ = 0, float y_ = 0);
    };
    struct float3 {
        float x, y, z;
        float3(float x_ = 0, float y_ = 0, float z_ = 0);
    };
    struct float4 {
        float x, y, z, a;
        float4(float x_ = 0, float y_ = 0, float z_ = 0, float a_ = 0);
    };

    struct position : float3 {
        using float3::float3;
        void move(float x_ = 0, float y_ = 0, float z_ = 0);
        float2 get_2D();
        float3 get();
    };

    struct color_RGBA {
        float r, g, b, a;
        color_RGBA(float r_ = 0, float g_ = 0, float b_ = 0, float a_ = 0);
    };
    struct color_RGB {
        float r, g, b;
        color_RGB(float r_ = 0, float g_ = 0, float b_ = 0);
    };

} // namespace myData

#pragma endregion floats

#endif // DATASTRUCTURES_HPP
