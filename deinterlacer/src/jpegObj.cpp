#include "jpegObj.h"

#include <iostream>

namespace {

JpegObj::Params loadImage(const std::string& filename)
{
    // Open the JPEG file
    FILE* file = fopen(filename.c_str(), "rb");
    if (!file) {
        return { nullptr };
    }

    // Initialize the JPEG decompression structure
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Set the source file
    jpeg_stdio_src(&cinfo, file);

    // Read the JPEG header
    jpeg_read_header(&cinfo, TRUE);

    // Set color space to YCbCr
    cinfo.out_color_space = JCS_YCbCr;

    // Start decompression
    jpeg_start_decompress(&cinfo);

    // Allocate memory for the image buffer
    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int num_components = cinfo.num_components; // Usually 3 for YCbCr (Y, Cb, Cr)

    JSAMPARRAY buffer = (JSAMPARRAY)malloc(sizeof(JSAMPROW) * height);
    for (int i = 0; i < height; i++) {
        buffer[i] = (JSAMPROW)malloc(sizeof(JSAMPLE) * width * num_components);
    }

    // Read the image
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer + cinfo.output_scanline, 1);
    }

    // Clean up and close the file
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    return {
        buffer,
        width,
        height,
        num_components
        };
}
} // namespace

JpegObj::JpegObj(const std::string& filepath) : params(loadImage(filepath))
{
}

bool JpegObj::isValid()
{
    return params.data != nullptr;
}

JpegObj::~JpegObj()
{
    // Free allocated memory
    for (int i = 0; i < params.height; i++) {
        free(params.data[i]);
    }
    free(params.data);
}

bool JpegObj::save(const std::string& filepath, const int quality)
{
    // Open the JPEG file for writing
    FILE* file = fopen(filepath.c_str(), "wb");
    if (!file) {
        return false;
    }

    // Initialize the JPEG compression structure
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // Set the destination file
    jpeg_stdio_dest(&cinfo, file);

    // Set image parameters
    cinfo.image_width = params.width;
    cinfo.image_height = params.height;
    cinfo.input_components = params.num_components;
    cinfo.in_color_space = JCS_YCbCr;

    // Set default compression parameters
    jpeg_set_defaults(&cinfo);
    
    // Set the quality level
    jpeg_set_quality(&cinfo, quality, TRUE);

    // Start compression
    jpeg_start_compress(&cinfo, TRUE);

    // Write scanlines
    while (cinfo.next_scanline < cinfo.image_height) {
        jpeg_write_scanlines(&cinfo, params.data + cinfo.next_scanline, 1);
    }

    // Finish compression
    jpeg_finish_compress(&cinfo);

    // Clean up and close the file
    fclose(file);
    jpeg_destroy_compress(&cinfo); 

    return true;
}