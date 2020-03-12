#include <iostream>
using namespace std;

#define WIDTH 640
#define HEIGHT 320

void print_image(unsigned char* image, int width, int height)
{
    for (int i = 0; i < width * height; i++)
    {
        cout << (unsigned int)image[i] << "\t";
        if ((i + 1) % width == 0)

            cout << "\n";
    }
    cout << "\n";
}

void print_int_image(unsigned int* image, int width, int height)
{
    for (int i = 0; i < width * height; i++)
    {
        cout << (unsigned int)image[i] << "\t";
        if ((i + 1) % width == 0)

            cout << "\n";
    }
    cout << "\n";
}

void integral_image(unsigned char* image, int width, int height, unsigned int* ii_image)
{
    unsigned int* r_image = new unsigned int[WIDTH * HEIGHT];
    for (int i = 0; i < width * height; i++)
    {
        if (i / width == 0)
        {
            r_image[i] = image[i];
        }
        else
        {
            // cout << "//" << r_image[i-width] << " " << (unsigned int)image[i] << "//" << endl;
            r_image[i] = r_image[i - width] + image[i];
        }
    }
    for (int i = 0; i < width * height; i++)
    {
        if (i % width == 0)
        {
            ii_image[i] = r_image[i];
        }
        else
        {
            // cout << "##" << ii_image[i-width] << " " << r_image[i] << "##" << endl;
            ii_image[i] = ii_image[i - 1] + r_image[i];
        }
    }
    // print_int_image(ii_image, width, height);
}

int integral_image_sum_value(unsigned int* ii_image, int width, int height, int left, int top, int right, int bottom)
{
    unsigned int point1, point2, point3, point4;
    unsigned int result;
    point1 = ii_image[(left - 1) + ((top - 1) * width)];
    point2 = ii_image[right + ((top - 1) * width)];
    point3 = ii_image[(left - 1) + ((bottom)*width)];
    point4 = ii_image[right + ((bottom)*width)];
    // cout << "point " << point1 << " " << point2 << " " << point3 << " " << point4 <<endl;
    result = point1 - point2 - point3 + point4;
    return result;
}

int image_sum_value(unsigned char* image, int width, int height, int left, int top, int right, int bottom)
{
    unsigned int result, x, y;
    result = 0;
    for (int i = 0; i < ((right - left + 1) * (bottom - top + 1)); i++)
    {
        x = i / (right - left + 1) + top;
        y = i % (right - left + 1) + left;
        result += (unsigned int)image[x * width + y];
        // cout << "*" << (unsigned int)image[x*width+y];
    }
    return result;
}

int main()
{
    unsigned char* image = new unsigned char[WIDTH * HEIGHT];
    unsigned int* ii_image = new unsigned int[WIDTH * HEIGHT];
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        image[i] = rand() % 256;
    }
    // print_image(image, WIDTH, HEIGHT);
    integral_image(image, WIDTH, HEIGHT, ii_image);
    int sum1 = integral_image_sum_value(ii_image, WIDTH, HEIGHT, 10, 20, 50, 100);
    int sum2 = image_sum_value(image, WIDTH, HEIGHT, 10, 20, 50, 100);
    // int sum1 = integral_image_sum_value(ii_image, WIDTH, HEIGHT, 2, 2, 3, 3);
    // int sum2 = image_sum_value(image, WIDTH, HEIGHT, 2, 2, 3, 3);
    cout << "sum1 " << sum1 << endl;
    cout << "sum2 " << sum2 << endl;
    if (sum1 != sum2)
        cout << "error" << endl;
    delete[] image;
    delete[] ii_image;
}