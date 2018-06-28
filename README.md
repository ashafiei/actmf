Actmf
=====

Actmf is an actor-based multimedia framework to build multimedia applications. An application consists of a number of components which together form a graph structure. Each component runs as an actor. There is an actor called environment which is responsible for creating components of an application as actors dynamically.

Pre-requirements
================

C++ Actor Framework:
```
https://github.com/actor-framework/actor-framework/releases/tag/0.15.0
```

OpenCV:
```
libopencv-dev
```

Build
===============
```bash
  #!/bin/bash
  cd build
  cmake ..
  make
```


Application development
===========

To create an application components need to be created and connected to each other.

Here is an example with three components, a number generator, an addition filter, and a number display component. The application graph is constructed in a configuration file.

```
application = 'addition'

g = 'num_gen'
a = 'addition'
d = 'num_disp'

connections = [(g, a), (a, d)]
```

Actor development
=======================

New actors (components of application) should be developed in ```actmf_actor``` folder. An actor inherits from the actmf::abstract_service_bhvr class. Each actor must define the operators according to the types it replies to. A factory is needed for spawning the actor.

```c++

namespace actmf {
  
  using addition_actor = 
  caf::typed_actor<caf::replies_to<std::string, int, int>::with<int>>;
  
  class addition_bhvr : public
  caf::composed_behavior<caf::composable_behavior<addition_actor>, abstract_service_bhvr> {
  
  public:
    caf::result<int> operator()(caf::param<std::string>, int, int) override;  
  };
  
  class addition_factory : abstract_service_factory
  {
  protected:
   virtual caf::actor spawn();
  };
}

using namespace actmf;

addition_factory Factory;

caf::result< int > addition_bhvr::operator()(caf::param< std::string > app, int x, int y)
{
  int res = x + y;
  for(service * serv : next_service[app.get()])
    caf::anon_send(serv->get_actor(), app.get(), res);
  return res;
}

caf::actor addition_factory::spawn()
{
  auto act = system->spawn<addition_bhvr>();
  return caf::actor_cast<caf::actor>(act);
}
```
