#include "stdio.h"
#include "stdint.h"

extern "C"
{
    #include "libavutil/imgutils.h"
    #include "libavformat/avformat.h"
    #include "libavutil/samplefmt.h"
}

int main(int argc, char **argv)
{
    av_register_all();
}
