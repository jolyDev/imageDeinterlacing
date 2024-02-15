#include <cstddef>
#include <stdio.h>
#include <string>
#include <jpeglib.h>

class JpegObj {
public:

    JpegObj(const std::string& filepath);

    bool isValid();
    bool save(const std::string& name, const int quality = 100);

    ~JpegObj();

    struct Params
    {
        JSAMPARRAY data = nullptr;
        const int width = -1;
        const int height = -1;
        const int num_components = -1;
    };

    Params params;

private:
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr jerr;
};