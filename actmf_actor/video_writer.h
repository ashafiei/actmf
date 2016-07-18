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

#ifndef ACTMF_VIDEO_WRITER_H
#define ACTMF_VIDEO_WRITER_H

#include "actmf_interface/abstract_service.h"
#include "tmmp/all.h"

namespace actmf {
  
  class video_writer : public abstract_service
  {
  private:
    VideoWriter * vwriter;
  protected:
    virtual caf::behavior awaiting_task();
  public:
    video_writer(caf::actor_config& cfg);
    ~video_writer();
  };
  
  class video_writer_factory : abstract_service_factory
  {
  public:
   virtual caf::actor spawn(caf::actor_system * system);
  };
 
}

#endif // ACTMF_VIDEO_WRITER_H
