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

#ifndef ACTMF_VIDEO_READER_H
#define ACTMF_VIDEO_READER_H

#include "actmf_interface/abstract_service.h"
#include "opencv2/opencv.hpp"

namespace actmf {
  
  using video_reader_actor = 
  caf::typed_actor<caf::replies_to<bool>::with<int>>;
  
  class video_reader_bhvr : public
  caf::composed_behavior<caf::composable_behavior<video_reader_actor>, abstract_service_bhvr> {
  private:
    cv::Mat frame;
    opencv_mat image;
    cv::VideoCapture * cap;
  public:
    video_reader_bhvr();
    caf::result<int> operator()(bool) override; 
  };
  
  class video_reader_factory : abstract_service_factory
  {
  protected:
    virtual void init(caf::actor);
    virtual caf::actor spawn();
  };
 
}

#endif // ACTMF_VIDEO_READER_H
