/*
 * actor multimedia framework (actmf)
 * copyright (c) 2016  arash shafiei
 * 
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation, either version 3 of the license, or
 * (at your option) any later version.
 * 
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 * 
 * you should have received a copy of the gnu general public license
 * along with this program.  if not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef ACTMF_ENVIRONMENT_H
#define ACTMF_ENVIRONMENT_H

#include "caf/all.hpp"

namespace actmf {
  
  class environment : public caf::event_based_actor 
  {
  public:
    environment();
    environment(const environment& other);
    ~environment();
    environment& operator=(const environment& other);
    bool operator==(const environment& other) const;
  };
}

#endif // ACTMF_ENVIRONMENT_H
