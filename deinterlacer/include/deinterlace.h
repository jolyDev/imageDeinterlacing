#include "jpegObj.h"

enum EDeinterlaceMethod
{
    SimpleBlending = 1,
    Blending,
    Weaving,
    MotionCompensation,
    // ... 
};

template <unsigned int TDeinterlaceMethod>
void deinterlace(JpegObj& jpegObj);

template <>
void deinterlace<EDeinterlaceMethod::SimpleBlending>(JpegObj& jpegObj);