/*
 * 
 *  Tiny Multimedia Framework (tmf)
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This file is part of tmf.
 *
 *  tmf is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  tmf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with tmf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef VIDEOREADER_H_
#define VIDEOREADER_H_

#include <iostream>
#include <string>

#include "filters/libav/types/RawFrame.h"

#ifdef __cplusplus
extern "C" {
  #endif
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
  #include <libavdevice/avdevice.h>
  #ifdef __cplusplus
}
#endif

using namespace std;

class VideoReader {
  
private:
  string name;
  AVFormatContext *pFormatCtx;
  AVCodecContext * pCodecCtx;
  AVInputFormat *video_fmt;
  AVDictionary *optionsDict;
  int vstream_idx;
  int frameNumber;
  string video_format;
  string input_format;
  string framerate;
  
public:
  
  VideoReader(string name);
  
  void setVideoFromat(string vformat);
  
  void setInputFormat(string iformat);
  
  void setFramerate(string framerate);
  
  int init();
  
  void dump();
  
  int getWidth();
  
  int getHeight();
  
  AVPixelFormat getPixFormat();
  
  AVCodecContext * getCodecContext();
  
  AVFormatContext * getFormatContext();
  
  int readFrame(RawFrame * frame);
  
  ~VideoReader();
  
};

#endif /* VIDEOREADER_H_ */
