#include "deinterlace.h"

template <>
void deinterlace<EDeinterlaceMethod::SimpleBlending>(JpegObj& jpegObj)
{
    // iterate backwards, so we can make changes inplace
    for (int h = jpegObj.params.height - 1; h > 1 ; h--)
    {
        JSAMPROW prevRow = jpegObj.params.data[h - 1];
        JSAMPROW currRow = jpegObj.params.data[h];
        
        for (int w = 0; w < jpegObj.params.width * jpegObj.params.num_components; w++)
        {
            currRow[w] = (prevRow[w] + currRow[w]) / 2;
        }
    }
}