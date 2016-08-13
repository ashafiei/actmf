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

class frame {
public:
  int number;
  frame();
  frame(const frame &x);
};

class opencv_mat : public frame {
private:
  std::vector<uchar> data;
  cv::Mat * mat;
public:
  
  cv::Mat* operator->();
  cv::Mat* get_mat();
  
  opencv_mat();
  opencv_mat(const opencv_mat& x);

  void set_mat(cv::Mat * x);
  
  std::vector<uchar> & get_data();
  void set_data(std::vector<uchar> data, int rows, int cols, int type);
  
  explicit operator bool() const {
    return mat != nullptr;
  }
   
  ~opencv_mat();

};

class opencv_rect : public frame {

private:
  cv::Rect* rect;
public:
  cv::Rect* operator->();
  opencv_rect();
  opencv_rect(const opencv_rect& x);
  opencv_rect(const cv::Rect& r);
  void set_data(int x, int y, int width, int height);
};

template <class Inspector>
typename std::enable_if<Inspector::is_saving::value,
                        typename Inspector::result_type>::type
inspect(Inspector& f, opencv_mat& mat) {
  return f(caf::meta::type_name("opencv_mat"), mat->rows,
	   mat->cols, mat->type(),
	   mat.number, mat.get_data()
  );
}

template <class Inspector>
typename std::enable_if<Inspector::is_loading::value,
                        typename Inspector::result_type>::type
inspect(Inspector& f, opencv_mat& mat) {
  int rows, cols, type;
  std::vector<uchar> data;
  // write back to x at scope exit
  auto g = caf::detail::make_scope_guard([&] {
    mat.set_data(data, rows, cols, type);
  });
  return f(caf::meta::type_name("opencv_mat"), rows, cols, type,
    mat.number, data
  );
}

template <class Inspector>
typename std::enable_if<Inspector::is_saving::value,
                        typename Inspector::result_type>::type
inspect(Inspector& f, opencv_rect& rect) {
  return f(caf::meta::type_name("opencv_rect"), rect->x,
	   rect->y, rect->width, rect->height, rect.number);
}

template <class Inspector>
typename std::enable_if<Inspector::is_loading::value,
                        typename Inspector::result_type>::type
inspect(Inspector& f, opencv_rect& rect) {
  int x, y, width, height;
  // write back to x at scope exit
  auto g = caf::detail::make_scope_guard([&] {
    rect.set_data(x, y, width, height);
  });
  return f(caf::meta::type_name("opencv_rect"), x, y, width, height, rect.number);
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
  
  using abstract_service_actor = 
  caf::typed_actor<caf::replies_to<std::string, std::string, int16_t>::with<int>>;

  class abstract_service_bhvr : 
  public caf::composable_behavior<abstract_service_actor> {
  protected:
    std::map<std::string, std::vector<service *>> next_service;
  public:
    caf::result<int> operator()(caf::param<std::string>, caf::param<std::string>, int16_t) override; 
  };
  
  class abstract_service_factory {
  protected:
    caf::actor_system_config cfg;
    caf::actor_system * system;
    virtual caf::actor spawn() = 0;
    virtual void init(caf::actor act) {}
  public:
    abstract_service_factory() {
        cfg.load<caf::io::middleman>();
	cfg.add_message_type<opencv_mat>("opencv_mat");
	cfg.add_message_type<opencv_rect>("opencv_rect");
	cfg.add_message_type<std::vector<opencv_rect>>("vector<opencv_rect>");
	system = new caf::actor_system(this->cfg);
    }
    void spawn_publish(int port) { 
      auto act = spawn();
      system->middleman().publish(act, port);
      init(act);
    }
  };

}

#endif // ABSTRACT_SERVICE_H