#include "stdio.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
}

int main(int argc, char **argv)
{
    printf("%s\n", avcodec_configuration());
    return 0;
}
