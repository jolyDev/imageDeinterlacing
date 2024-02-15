#include <iostream>

#include "deinterlace.h"

int main(int argc, char* argv[])
{
    const std::string input = argc >= 2 ? argv[1] : "No image path provided via argv";
    JpegObj image(input);
    if (!image.isValid())
    {
        std::cerr << "Error opening input file: " << input << std::endl;
    }

    deinterlace<EDeinterlaceMethod::SimpleBlending>(image);

    const std::string output = argc >= 3 ? argv[2] : "/app/data/out.jpg";
    if (!image.save(output))
    {
        std::cerr << "Error saving output file: " << output << std::endl;;
    };
}
