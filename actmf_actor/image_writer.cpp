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
  iwriter = new ImageWriter(1280, 720, AV_PIX_FMT_YUV420P);
  iwriter->setPath("/home/sh/Videos/");
}

caf::behavior image_writer::awaiting_task()
{
   return {
     [=](std::string app_name, RawFrame data) {
       caf::aout(this) << "writing frame number:" << data.getNumber() << "\n";       
       iwriter->writeImage(&data);
       //caf::aout(this) << "data is written\n";       
       //caf::aout(this) << *(data.data->data[0]) << data.data->width << std::endl;
       //caf::aout(this) << *(data.buffer[0]) << *(data.buffer[1])
       //<< *(data.buffer[2]) << *(data.buffer[3]) << *(data.buffer[4])
       //<< data.height << data.width << std::endl;
     }
  };
}

image_writer::~image_writer()
{

}

caf::actor image_writer_factory::spawn(caf::actor_system * system)
{
  return system->spawn<image_writer>();
}