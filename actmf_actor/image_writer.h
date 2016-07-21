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

#ifndef ACTMF_IMAGE_WRITER_H
#define ACTMF_IMAGE_WRITER_H

#include "actmf_interface/abstract_service.h"
#include "tmmp/all.h"

namespace actmf {
  
  using image_writer_actor = 
  caf::typed_actor<caf::replies_to<string, RawFrame>::with<int>>;
  
  class image_writer_bhvr : public
  caf::composed_behavior<caf::composable_behavior<image_writer_actor>, abstract_service_bhvr> {
  private:
    ImageWriter * iwriter;
  public:
    image_writer_bhvr();
    caf::result<int> operator()(caf::param<string>, caf::param<RawFrame>) override; 
  };
  
  class image_writer_factory : abstract_service_factory
  {
  public:
   virtual void spawn(caf::actor_system * sys, int port);
  };
 
}

#endif // ACTMF_IMAGE_WRITER_H
