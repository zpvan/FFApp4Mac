#include "stdio.h"
#include "stdint.h"
#include "unistd.h"
#include "getopt.h"

#include "KEncoder.h"

extern "C"
{
    #include "libavutil/imgutils.h"
    #include "libavformat/avformat.h"
    #include "libavutil/samplefmt.h"
}

const int FUNCTION = 100;
const char* ENC = "enc";

struct option longopts[] = 
{
    {"func", required_argument, NULL, FUNCTION},
};

int main(int argc, char **argv)
{
    int oc;
    char ec;
    char *func = NULL;
    while((oc = getopt_long(argc, argv, "", longopts, NULL)) != -1)
    {
        switch(oc)
        {
            case FUNCTION:
                printf("function: %s\n", optarg);
                func = optarg;
                break;
        }
    }
    if (!strcmp(ENC, func))
    {
        printf("启动编码器\n");
        KEncoder *encoder = new KEncoder();
        encoder->init(argv);
    }
    av_register_all();
}
