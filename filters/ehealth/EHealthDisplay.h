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

#ifndef EHEALTHDISPLAY_H_
#define EHEALTHDISPLAY_H_

#include "core/actmf.h"
#include "core/Filter.h"
#include "core/Port.h"

#include <ehealthsensor/Sensor.h>

struct EHealthDisplay: public actmf::Filter {
private:

  actmf::InputPort<ehealthsensor::SensorData> * input;

  static actmf::FilterRegister<EHealthDisplay> reg;
    
public:
  
  EHealthDisplay(const std::string& name);
  
  virtual void init();
  
  virtual void run(); 
  
  virtual ~EHealthDisplay();
  
};

#endif /* EHEALTHDISPLAY_H_ */
