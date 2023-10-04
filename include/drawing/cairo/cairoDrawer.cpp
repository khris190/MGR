// #include "cairoDrawer.hpp"
// // TODO use opengl
// void CarioDrawer::Draw(cairo_surface_t* img, float Scale)
// {
//     cairo_t* cr;
//     for (size_t i = 0; i < size; i++) {
//         int _width, _height;

//         _width = cairo_image_surface_get_width(img);
//         _height = cairo_image_surface_get_height(img);

//         float color[4] = { gene_arr[i].color.r, gene_arr[i].color.g, gene_arr[i].color.b, gene_arr[i].color.a };

//         int x = gene_arr[i].position.x * _width;
//         int y = gene_arr[i].position.y * _height;

//         float scaleX = gene_arr[i].scale.x * _width * Scale * 0.5;
//         float scaleY = gene_arr[i].scale.y * _height * Scale * 0.5;
//         float rotation = gene_arr[i].rotation * 3.14;

//         // kwadrat
//         if (gene_arr[i].type_of_shape == myData::ShapeType::rectangle) {
//             cr = cairo_create(img);
//             cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
//             myData::position_2D p1, p2, p3, p4;
//             if (rotation != 0) {
//                 p1 = rotate(scaleX, scaleY, rotation);
//                 p2 = rotate(-scaleX, scaleY, rotation);
//                 p3 = rotate(scaleX, -scaleY, rotation);
//                 p4 = rotate(-scaleX, -scaleY, rotation);
//             }
//             p1.move(x, y);
//             p2.move(x, y);
//             p3.move(x, y);
//             p4.move(x, y);

//             cairo_move_to(cr, p1.x, p1.y);
//             cairo_line_to(cr, p2.x, p2.y);
//             cairo_line_to(cr, p4.x, p4.y);
//             cairo_line_to(cr, p3.x, p3.y);
//             cairo_close_path(cr);
//             cairo_fill(cr);
//         } else if (gene_arr[i].type_of_shape == myData::ShapeType::ellipse) {
//             cr = cairo_create(img);
//             cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
//             cairo_translate(cr, x, y);
//             cairo_rotate(cr, rotation * 3.14);
//             cairo_scale(cr, scaleX, scaleY);
//             cairo_arc(cr, 0, 0, 1, 0, 2 * 3.14);
//             cairo_fill(cr);
//         } else if (gene_arr[i].type_of_shape == myData::ShapeType::triangle) {
//             cr = cairo_create(img);
//             cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
//             myData::position_2D p1, p2;
//             if (rotation != 0) {
//                 p1 = rotate(scaleX, scaleY, rotation * 2);
//                 p2 = rotate(-scaleX, scaleY, rotation * 2);
//             }
//             p1.move(x, y);
//             p2.move(x, y);

//             cairo_move_to(cr, x, y);
//             cairo_line_to(cr, p1.x, p1.y);
//             cairo_line_to(cr, p2.x, p2.y);
//             cairo_close_path(cr);
//             cairo_fill(cr);
//         }

//         cairo_destroy(cr);
//     }
// }