/*
 * 
 *  Act Multimedia Framework (actmf)
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This file is part of actmf.
 *
 *  actmf is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  actmf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with actmf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "core/actmf.h"

using namespace std;
using namespace actmf;

int main(int argc, char** argv) {
  
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <output video> " << endl;
    return -1;
  }
  
  string outputVideo = argv[1];
 
  Pipeline* pipe = Factory::createPipeline("DASH webcam stream");
  
  Filter* reader = Factory::createFilter("video_reader", "reader");
  Filter* scaler = Factory::createFilter("image_scaler", "scaler");
  Filter* encoder = Factory::createFilter("video_encoder", "encoder");
  Filter* muxer = Factory::createFilter("video_muxer", "muxer");
  
  pipe->addFilters(reader, scaler,encoder, muxer, nullptr);
  
  pipe->connectFilters(reader, scaler);
  pipe->connectFilters(scaler, encoder);
  pipe->connectFilters(encoder, muxer);
  
  reader->setProp("input_video", "/dev/video0");
  reader->setProp("video_format", "video4linux2");
  reader->setProp("input_format", "mjpeg");
  reader->setProp("framerate", "20");
  
  scaler->setProp<int>("width", 640);
  scaler->setProp<int>("height", 480);
  
  encoder->setProp("bitrate", 400000);
  encoder->setProp("framerate", 20);
  encoder->setProp("output_video", outputVideo);
  
  pipe->init();
  
  pipe->run();
  
  Factory::destroyPipeline(pipe);
  
  return 0;
}
