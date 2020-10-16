#include <stdio.h>

#if EMSCRIPTEN
#include <emscripten.h>
#endif // NCNN_VULKAN

int main() {
    printf("hello, world!\n");
    return 0;
}