/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   backgroundimage2_jpg;
    const int            backgroundimage2_jpgSize = 1969712;

    extern const char*   fractal_Rainbow_jpeg;
    const int            fractal_Rainbow_jpegSize = 94587;

    extern const char*   fractalBlue_jpeg;
    const int            fractalBlue_jpegSize = 54320;

    extern const char*   fractalGreen_jpeg;
    const int            fractalGreen_jpegSize = 121390;

    extern const char*   Knob2_png;
    const int            Knob2_pngSize = 33608;

    extern const char*   LOGO_Capr_png;
    const int            LOGO_Capr_pngSize = 1712519;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
