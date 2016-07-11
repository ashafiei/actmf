Actor Multimedia Framework (actmf)
===============================

Actor Multimedia Framework (actmf) is an actor-based multimedia framework to build multimedia applications. An application consists of a number of components which together form a graph structure. Each component runs as an actor. There is an actor called environment which is responsible for creating components of an application as actors dynamically.


Folder structure
===================

Here is how the project is organized.

	actmf_actor
	actmf_application
	actmf_interface
	actmf_system
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
  make
```
Before compilation make sure that actor_framework library is installed:

	https://github.com/actor-framework/actor-framework

Development envirement
======================
Actor Multimedia Framework is configured to be developed under KDevelop IDE.
	
	kdevelop -p actmf.kdev4

Application development manual
===========

To create an application we need to create components, connect them together and sent them to the environment actor. The application graph is constructed in a configuration file.

Here is an example with three components, a number generator, an addition filter, and a number display component:

	application = 'addition'

	g = 'num_gen'
	a = 'addition'
	d = 'num_disp'

	connections = [(g, a), (a, d)]
	
The configuration file is passed to the application.


Actor development manual
=======================

Actor developers must implement new actors (components of application) in ```actmf_actor``` folder. An actor inherits from the actmf::abstract_service class. Each actor must define ```addition_actor::awaiting_task``` as the initial behaviour of the actor. A factory is needed for spawning the actor.

Here is an example:

```c++

namespace actmf {
  
  class addition : public abstract_service
  {
  protected:
    virtual caf::behavior awaiting_task();
  public:
    addition(caf::actor_config& cfg);
    ~addition();
  };
  
  class addition_factory : abstract_service_factory
  {
  public:
   virtual caf::actor spawn(caf::actor_system* system);
  };
 
}

addition_factory Factory;

addition::addition(caf::actor_config& cfg): abstract_service(cfg)
{

}

caf::behavior addition::awaiting_task()
{
   return {
      [=](int app_id, int x, int y) {
        int res = x + y;
        for(auto act : next_service[app_id])
          this->send(act, app_id, res);
      }
  };
}

addition::~addition()
{

}

caf::actor addition_factory::spawn(caf::actor_system* system)
{
  return system->spawn<addition>();
}

```
