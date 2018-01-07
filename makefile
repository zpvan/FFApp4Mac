##########################################
#
#
#
##########################################

LIBDIR := ffmpeg-3.4.1-macos64-shared/bin/
LIBS := avutil.55 avformat.57 avcodec.57
INCLUDES := ffmpeg-3.4.1-macos64-dev/include/
TARGET := main
TARGETDIR := $(LIBDIR)

##########################################

CC := g++
RM-F := rm -f

##########################################



##########################################

all: $(TARGET)

main: Main.cpp
	$(CC) Main.cpp KEncoder.cpp KDemuxer.cpp -o $(addprefix $(TARGETDIR), $(TARGET)) $(addprefix -L, $(LIBDIR)) $(addprefix -l, $(LIBS)) -I$(INCLUDES) 

clean:
	$(RM-F) *.o
	$(RM-F) *.d

veryclean: clean
	$(RM-F) $(addprefix $(TARGETDIR), $(TARGET))

