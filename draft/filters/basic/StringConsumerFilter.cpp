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

#include "filters/basic/StringConsumerFilter.h"

using namespace actmf;
using namespace std;

FilterRegister<StringConsumerFilter> StringConsumerFilter::reg("string_consumer");

StringConsumerFilter::StringConsumerFilter(const string & name) : Filter(name) {
  input = createInputPort<string>("input");
}

void StringConsumerFilter::run() {
  
  input->lock();
  
  string * inputData = input->get();
  
  log("consuming "+*inputData);
  sleep(500);
  
  if (input->getStatus() == SampleStatus::EOS)
    status = FilterStatus::EOS; 
  
  input->unlock();
  
}

StringConsumerFilter::~StringConsumerFilter() {
  destroyPort(input);
}