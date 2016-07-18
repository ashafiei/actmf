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

#ifndef ABSTRACT_SERVICE_H
#define ABSTRACT_SERVICE_H

#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "tmmp/all.h"

namespace actmf {  
  
  typedef struct VideoData {
    uint8_t * buffer[8];
    int width;
    int height;
  } VideoData;

  template <class Inspector>
  typename Inspector::result_type inspect(Inspector& f, AVRational& x) {
    return f(caf::meta::type_name("AVRational"), x.num, x.den
    );
  }
  
  /*
  template <class Inspector>
  typename Inspector::result_type inspect(Inspector& f, VideoData& x) {
    return f(caf::meta::type_name("VideoData"));
  }
  
    template <class Inspector>
  typename Inspector::result_type inspect(Inspector& f, AVFrameSideData& x) {
    return f(caf::meta::type_name("AVFrameSideData")
    );
  }
  
  template <class Inspector>
  typename Inspector::result_type inspect(Inspector& f, AVBufferRef& x) {
    return f(caf::meta::type_name("AVBufferRef")
    );
  }
  
  //template <class Inspector>
  //typename Inspector::result_type inspect(Inspector& f, AVRational& x) {
  //  return f(caf::meta::type_name("AVRational"), x.num, x.den
  //  );
  //}
  
  template <class Inspector>
  typename Inspector::result_type inspect(Inspector& f, AVFrame& x) {
    return f(caf::meta::type_name("AVFrame"));
  }

  template <class Inspector>
  typename std::enable_if<Inspector::is_loading::value,
                        typename Inspector::result_type>::type
  inspect(Inspector& f, RawFrame& x) {
    AVFrame data;
    uint8_t buffer;
    // write back to x at scope exit
    auto g = caf::detail::make_scope_guard([&] {
      x.setBuffer(&buffer);
      x.setFrame(&data);
    });
    return f(caf::meta::type_name("RawFrame"), data, buffer);
  }*/
  
  using direct_atom = caf::atom_constant<caf::atom("direct")>;
  
  using generate_atom = caf::atom_constant<caf::atom("generate")>;  
  using add_atom = caf::atom_constant<caf::atom("add")>;
  using disp_num_atom = caf::atom_constant<caf::atom("dis_num")>;
  using gen_disp_atom = caf::atom_constant<caf::atom("gen_disp")>;
  
  using register_atom = caf::atom_constant<caf::atom("register")>;
  using create_app_atom = caf::atom_constant<caf::atom("create_app")>;
  
  class abstract_service : public caf::event_based_actor
  {
  protected:
    virtual caf::behavior awaiting_task() = 0;
    caf::behavior awaiting_direction();
    std::map<std::string, std::vector<caf::actor>> next_service;
  public:
    abstract_service(caf::actor_config& cfg);
    caf::behavior make_behavior() override; 
    ~abstract_service();
    
  };
  
  class abstract_service_factory {
  public:
    virtual caf::actor spawn(caf::actor_system * system) = 0;
  };

}

#endif // ABSTRACT_SERVICE_H