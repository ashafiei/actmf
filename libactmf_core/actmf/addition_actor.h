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

#ifndef ACTMF_ADDITION_ACTOR_H
#define ACTMF_ADDITION_ACTOR_H

#include "caf/all.hpp"

namespace actmf {
  
  class addition : public caf::event_based_actor
  {
  private:
    int x;
  public:
    addition();
    addition(const addition& other);
    ~addition();
    addition& operator=(const addition& other);
    bool operator==(const addition& other) const;
  };
 
}

#endif // ACTMF_ADDITION_ACTOR_H
