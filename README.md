Actor Multimedia Framework (actmf)
===============================

Actor Multimedia Framework (actmf) is an actor-based multimedia applications. An application consists of a number of components which together form a graph. Each component run as an actor. There is an actor called environment which is responsible of creating components of an application as actors.


Folder structure
===================

Here is how the project is organized.

	build
	libactmf_core (core package)
	examples
	CMakeLists.txt
	LICENCE
	README.md
	actmf.kdev4

Installation
===============
```bash
  #!/bin/bash
  cd build
  ../cmake
  ./configure
  make
```
Before compilation make sure that actor_framework library is installed:

```
  https://github.com/actor-framework/actor-framework
```

Development envirement
======================
Actor Multimedia Framework is configured to be developed under KDevelop IDE.
	
	kdevelop -p actmf.kdev4

Application development manual
===========

To create an application we need to create an application as well as the filters, connect filters to each other and run the pipeline. TMF provides APIs to do it.

Here is a producer/consumer example with one producer and three consumer:
```c++
  caf::actor env = caf::io::remote_actor("localhost", 5000);
  
  actmf::application app;
  actmf::component gen_num(std::string("gen_num"), actmf::gen_num::value);
  actmf::component addition(std::string("addition"), actmf::addition::value);
  actmf::component disp_num(std::string("disp_num"), actmf::disp_num::value);
  
  app.add_component(gen_num);
  app.add_component(addition);
  app.add_component(disp_num);
  
  app.add_link("gen_num", "addition");
  app.add_link("addition", "disp_num");
  
  caf::anon_send(env, actmf::create_app_atom::value, app);
  caf::await_all_actors_done();
  caf::shutdown();
```	

Actor development manual
=======================

Plug-in developers must implement new actors (components of application) in libactmf_core folder. An actor inherits from the actmf::abstract_actor class. Each actor must define ```addition_actor::awaiting_task``` as the initial behaviour of the actor.

Here is an example of a filter implementation:
```c++

namespace actmf {
  
  class addition_actor : public actmf::abstract_actor
  {
  private:
  protected:
    virtual caf::behavior awaiting_task();
  public:
    addition_actor(const std::__cxx11::string& host, int16_t port) : abstract_actor(host, port) {};
    ~addition_actor() {}
  };
 
}

using namespace actmf;

caf::behavior addition_actor::awaiting_task()
{
    return {
      [=](add_atom add, int x, int y) {
	int res = x + y;
	for(remote_actor ract : next_actors)
	  this->send(ract.act, disp_num_atom::value, res);
      }
    };
}

```
