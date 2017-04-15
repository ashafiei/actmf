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

#ifndef ACTMF_HAARDETECT_H
#define ACTMF_HAARDETECT_H

#include "actmf_interface/abstract_service.h"
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"

namespace actmf {
  
  using haardetect_actor = 
  caf::typed_actor<caf::replies_to<std::string, opencv_mat>::with<int>>;
  
  class haardetect_bhvr : public
  caf::composed_behavior<caf::composable_behavior<haardetect_actor>, abstract_service_bhvr> {
  private:
    cv::Mat gray;
    cv::CascadeClassifier cascade;
    std::vector<cv::Rect> objects;
  public:
    haardetect_bhvr();
    caf::result<int> operator()(caf::param<std::string>, caf::param<opencv_mat>) override;  
  };
  
  class haardetect_factory : abstract_service_factory
  {
  protected:
 virtual caf::actor remote_spawn(caf::expected<caf::node_id> node,
					  caf::message args, 
					  caf::duration tout);
  };
 
}

#endif // ACTMF_HAARDETECT_H