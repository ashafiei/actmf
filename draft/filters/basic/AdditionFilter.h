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

#ifndef ADDITIONFILTER_H_
#define ADDITIONFILTER_H_

#include "core/Factory.h"
#include "core/Filter.h"
#include "core/Port.h"

#include <iostream>

using namespace actmf;

struct AdditionFilter: public actmf::Filter {
 
private:
  actmf::InputPort<int> * input1;
  actmf::InputPort<int>* input2;
  
  static  FilterRegister<AdditionFilter> reg;
public:
  
  AdditionFilter(const std::string & name);
  
  virtual void run();
  
  virtual ~AdditionFilter();
  
};

#endif /* ADDITIONFILTER_H_ */
