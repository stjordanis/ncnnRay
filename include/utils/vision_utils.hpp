#define NOGDICAPMASKS // CC_, LC_, PC_, CP_, TC_, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES // WM_, EM_, LB_, CB_
#define NOWINSTYLES // WS_, CS_, ES_, LBS_, SBS_, CBS_
#define NOSYSMETRICS // SM_*
#define NOMENUS // MF_*
#define NOICONS // IDI_*
#define NOKEYSTATES // MK_*
#define NOSYSCOMMANDS // SC_*
#define NORASTEROPS // Binary and Tertiary raster ops
#define NOSHOWWINDOW // SW_*
#define OEMRESOURCE // OEM Resource values
#define NOATOM // Atom Manager routines
#define NOCLIPBOARD // Clipboard routines
#define NOCOLOR // Screen colors
#define NOCTLMGR // Control and Dialog routines
#define NODRAWTEXT // DrawText() and DT_*
#define NOGDI // All GDI defines and routines
#define NOKERNEL // All KERNEL defines and routines
#define NOUSER // All USER defines and routines
#define NONLS // All NLS defines and routines/
#define NOMB // MB_* and MessageBox()
#define NOMEMMGR // GMEM_, LMEM_, GHND, LHND, associated routines
#define NOMETAFILE // typedef METAFILEPICT
#define NOMINMAX // Macros min(a,b) and max(a,b)
#define NOMSG // typedef MSG and associated routines
#define NOOPENFILE // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL // SB_* and scrolling routines
#define NOSERVICE // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND // Sound driver routines
#define NOTEXTMETRIC // typedef TEXTMETRIC and associated routines
#define NOWH // SetWindowsHook and WH_*
#define NOWINOFFSETS // GWL_, GCL_, associated routines
#define NOCOMM // COMM driver routines
#define NOKANJI // Kanji support stuff.
#define NOHELP // Help engine interface.
#define NOPROFILER // Profiler interface.
#define NODEFERWINDOWPOS // DeferWindowPos routines
#define NOMCX // Modem Configuration Extensions

#pragma warning( push, 0 )
#pragma warning( disable : 4576 )
#include "raylib.h"
//#define NOUSER //Resolve ray error  error C2660: 'LoadImageA': function does not take 1 arguments
//#include <intrin.h> //Resolve ray error  ppltasks.h(2712): error C3861: '_ReturnAddress': identifier not found
#include <iostream>
#include <iostream>
#include <chrono>
#include <iostream>
#include <typeinfo>
#include <thread>
#include <future>

//############################################ ncnn ##########################################
#include "models/LFFD.h"
#include "net.h"

using namespace std;
using namespace std::chrono;

class VisionUtils {
public:
    VisionUtils();

   int tensorDIMS(const ncnn::Mat &tensor);
    ncnn::Mat rayImageToNcnn(const Image &image);
    Image ncnnToRayImage(ncnn::Mat  &tensor);
};

VisionUtils::VisionUtils() {}

int VisionUtils::tensorDIMS(const ncnn::Mat &tensor){
    return tensor.dims;
}

ncnn::Mat VisionUtils::rayImageToNcnn(const Image &image) {
    size_t width = image.width;
    size_t height = image.height;
    int dataSize = GetPixelDataSize(width, height, image.format);
    TraceLog(LOG_INFO, "ncnnRay: total pixels:%i", dataSize);

    int bytesPerPixel = dataSize / (width * height);
    TraceLog(LOG_INFO, "ncnnRay: bytesPerPixel:%i", bytesPerPixel);
//    if (bytesPerPixel==4) bytesPerPixel=3;

    auto pointer = new unsigned char[dataSize];
    const unsigned char *imagePointer = (unsigned char *) image.data;
    std::memcpy(pointer, imagePointer, dataSize);
//    error C2664: 'ncnn::Mat ncnn::Mat::from_pixels(const unsigned char *,int,int,int,ncnn::Allocator *)': cannot convert argument 1 from 'void *const ' to 'const unsigned char *'
//    ncnn::Mat tensor = ncnn::Mat::from_pixels(static_cast<const unsigned char *>(image.data), ncnn::Mat::PIXEL_BGR2RGB, width, height);
    int type=ncnn::Mat::PIXEL_RGB;
    if  (bytesPerPixel ==4){
         type=ncnn::Mat::PIXEL_RGBA;
    }
    ncnn::Mat tensor = ncnn::Mat::from_pixels(static_cast<const unsigned char *>(image.data), type, width, height);
    delete[] pointer;
    return tensor;
}

Image VisionUtils::ncnnToRayImage(ncnn::Mat  &tensor) {
    size_t width = tensor.w;
    size_t height = tensor.h;
    unsigned char* torchPointer = reinterpret_cast<unsigned char *>(RL_MALLOC(3 * height * width * sizeof(unsigned char)));
    tensor.to_pixels(torchPointer, ncnn::Mat::PIXEL_RGB);
//    return Image{0};
    return Image{
            torchPointer,
            (int) width,
            (int) height,
            1, //that line is mipmaps, keep as 1
            UNCOMPRESSED_R8G8B8}; //its an enum specifying formar, 8 bit R, 8 bit G, 8 bit B, no alpha UNCOMPRESSED_R8G8B8A8 UNCOMPRESSED_R8G8B8
}
