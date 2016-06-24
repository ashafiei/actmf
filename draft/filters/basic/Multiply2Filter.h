/*
 * 
 *  Act Multimedia Framework (actmf)
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This file is part of actmf.
 *
 *  actmf is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  actmf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with actmf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MULTIPLY2FILTER_H_
#define MULTIPLY2FILTER_H_

#include "core/Factory.h"
#include "core/Filter.h"


class Multiply2Filter: public actmf::Filter {
private:
  actmf::InputPort<int> * input;
  actmf::OutputPort<int> * output;
  
  static actmf::FilterRegister<Multiply2Filter> reg;
public:
  
  Multiply2Filter(const std::string & name);
  
  virtual void run();
  
  virtual ~Multiply2Filter();
  
};

#endif /* MULTIPLY2FILTER_H_ */