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

image_writer::image_writer(caf::actor_config& cfg): abstract_service(cfg)
{

}

caf::behavior image_writer::awaiting_task()
{
   return {
     [=](std::string app_name, opencv_mat mat) {
       caf::aout(this) << "writing frame number:" << mat.get_number() << "\n";       
       std::vector<uchar> data = mat.get_data();
             
       cv::Mat * frame = mat.get_mat();
       
       std::string name = "/home/sh/Videos/frame" + 
       std::to_string(mat.get_number()) + ".png";
      
       cv::imwrite(name, *frame);
     }
  };
}

image_writer::~image_writer()
{

}

caf::actor image_writer_factory::spawn()
{
  return system->spawn<image_writer>();
}