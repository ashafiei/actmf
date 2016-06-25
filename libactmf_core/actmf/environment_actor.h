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

#include "actmf/abstract_actor.h"


namespace actmf {
  
  class environment_actor : public actmf::abstract_actor
  {
  private:

  protected:
    virtual caf::behavior awaiting_task();
  public:
    environment_actor(const std::__cxx11::string& host, int16_t port) : abstract_actor(host, port) {};
    ~environment_actor() {}
  };
}

#endif // ACTMF_ENVIRONMENT_H
