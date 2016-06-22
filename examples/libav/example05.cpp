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

using namespace actmf;
using namespace std;

int main(int argc, char** argv) {
  
  
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " <input video> <output path>" << endl;
    return -1;
  }
  
  Pipeline* pipe = Factory::createPipeline("Decoder/Writer Pipeline");
  
  string inputVideo = string(argv[1]);
  string outputPath = string(argv[2]);
  
  Filter* reader = Factory::createFilter("video_reader", "reader");
  Filter* writer = Factory::createFilter("image_writer", "writer");
  
  pipe->addFilters(reader, writer, nullptr);
  
  pipe->connectFilters(reader, writer);
  
  reader->setProp("input_video", inputVideo);
  writer->setProp("output_path", outputPath);
  
  pipe->init();
  
  pipe->run();
  
  Factory::destroyPipeline(pipe);
  
  return 0;
}
