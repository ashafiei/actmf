/*
 * Actor Multimedia Framework (actmf)
 * Copyright (C) 2016  Arash Shafiei
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include "image_writer.h"

using namespace actmf;

image_writer_factory Factory;

caf::result< int > image_writer_bhvr::operator()(caf::param< std::string > app, caf::param< opencv_mat > mat)
{
  opencv_mat m = mat.get();
  std::cout << "writing frame number:" << m.number << "\n";       
  std::vector<uchar> data = m.get_data();
            
  cv::Mat * frame = m.get_mat();
      
  std::string name = "/home/sh/Videos/frame" + 
  std::to_string(m.number) + ".png";
      
  cv::imwrite(name, *frame);
  return 0;
}

caf::actor image_writer_factory::spawn()
{
  auto act = system->spawn<image_writer_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}