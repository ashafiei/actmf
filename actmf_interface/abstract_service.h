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
#include "opencv2/opencv.hpp"

namespace actmf {
  
  using direct_atom = caf::atom_constant<caf::atom("direct")>;
  
  using generate_atom = caf::atom_constant<caf::atom("generate")>;  
  using add_atom = caf::atom_constant<caf::atom("add")>;
  using disp_num_atom = caf::atom_constant<caf::atom("dis_num")>;
  using gen_disp_atom = caf::atom_constant<caf::atom("gen_disp")>;
  
  using register_atom = caf::atom_constant<caf::atom("register")>;
  using create_app_atom = caf::atom_constant<caf::atom("create_app")>;
  
  class opencv_mat {
private:
  int number;
  std::vector<uchar> data;
  cv::Mat * mat;
public:
  
  cv::Mat* operator->();
  cv::Mat* get_mat();
  
  opencv_mat();
  opencv_mat(const opencv_mat& x);

  void set_mat(cv::Mat * x);
  
  std::vector<uchar> & get_data();
  void set_data(std::vector<uchar> data, int rows, int cols, int type, int number);
  
  int get_number();
  void set_number(int number);
  
  explicit operator bool() const {
    return mat != nullptr;
  }
   
  ~opencv_mat();

};

template <class Inspector>
typename std::enable_if<Inspector::is_saving::value,
                        typename Inspector::result_type>::type
inspect(Inspector& f, opencv_mat& x) {
  return f(caf::meta::type_name("opencv_mat"), x->rows,
	   x->cols, x->type(),
	   x.get_number(), x.get_data()
  );
}

template <class Inspector>
typename std::enable_if<Inspector::is_loading::value,
                        typename Inspector::result_type>::type
inspect(Inspector& f, opencv_mat& x) {
  int rows, cols, type, number;
  std::vector<uchar> data;
  // write back to x at scope exit
  auto g = caf::detail::make_scope_guard([&] {
    x.set_data(data, rows, cols, type, number);
  });
  return f(caf::meta::type_name("opencv_mat"), rows, cols, type,
    number, data
  );
}
  
  class service {
  private:
    caf::actor * act;
    std::string addr;
    int16_t port;
  public:
    void set_actor(const caf::actor& act) {
      this->act = new caf::actor(act);
    }
    void set_address(std::string addr) {
      this->addr = addr;
    }
    void set_port(int16_t port) {
      this->port = port;
    }
    bool has_actor() { return act != nullptr; }
    caf::actor get_actor() { return *act; }
    std::string get_address() { return addr; }
    int16_t get_port() { return port; }
  };
  
  class abstract_service : public caf::event_based_actor
  {
  protected:
    virtual caf::behavior awaiting_task() = 0;
    caf::behavior awaiting_direction();
    void insert_service(std::string app, std::string host, int16_t port);
    std::map<std::string, std::vector<service *>> next_service;
  public:
    abstract_service(caf::actor_config& cfg);
    caf::behavior make_behavior() override; 
    ~abstract_service();
    
  };
  
  class abstract_service_factory {
  protected:
    caf::actor_system_config cfg;
    caf::actor_system * system;
    virtual caf::actor spawn() = 0;
  public:
    abstract_service_factory() {
        cfg.load<caf::io::middleman>();
	cfg.add_message_type<opencv_mat>("opencv_mat");
	system = new caf::actor_system(this->cfg);
    }
    void spawn_publish(int port) { 
      auto act = spawn(); 
      system->middleman().publish(act, port); }
  };

}

#endif // ABSTRACT_SERVICE_H