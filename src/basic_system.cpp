#include "exo/basic_system.h"
#include <algorithm>

using namespace netlib;

namespace exo
{
	//
	// basic_component_proxy
	//

	basic_component_proxy::basic_component_proxy(entity *_e,
		netlib::handle<component> const& _c)
		: mEntity(_e), mComponent(_c)
	{
	}

	component *basic_component_proxy::read()
	{
		return mComponent.get();
	}

	component *basic_component_proxy::write()
	{
		return mComponent.get();
	}

	//
	// basic_entity
	//

	basic_entity::basic_entity(basic_system *_sys)
		: mSystem(_sys)
	{
	}

	component_proxy *basic_entity::component(component_type _ty)
	{
		auto it = mMap.find(_ty);
		if(it == mMap.end())
			return nullptr;

		return it->second.get();
	}

	component_proxy *basic_entity::create(component_type _ty, component_factory_t const& _f)
	{
		if(component_proxy *cp = component(_ty))
			return cp;

		handle<exo::component> c = _f();
		if(!c.get())
			return nullptr;

		handle<basic_component_proxy> ret = new basic_component_proxy(this, c);
		mMap.insert(map_t::value_type(_ty, ret));
		mSystem->notify_add(this, _ty, ret.get());
		return ret.get();
	}
	
	void basic_entity::remove(component_type _ty)
	{
		auto it = mMap.find(_ty);
		if(it == mMap.end())
			return;

		mSystem->notify_remove(this, _ty, it->second.get());
		mMap.erase(it);
	}

	//
	// basic_system
	//

	basic_system::basic_system()
	{
	}

	entity *basic_system::create()
	{
		handle<basic_entity> ent = new basic_entity(this);
		mEntities.insert(ent);
		return ent.get();
	}

	void basic_system::remove(entity *_e)
	{
		mEntities.erase(handle<entity>(_e)
			.cast_static<basic_entity>());
	}

	void basic_system::add(netlib::handle<subsystem> const& _s)
	{
		mSubsystems.insert(_s);
	}

	void basic_system::remove(subsystem *_s)
	{
		mSubsystems.erase(handle<subsystem>(_s));
	}

	void basic_system::notify_add(basic_entity *_e, component_type _ty,
		component_proxy *_c)
	{
		std::for_each(mSubsystems.begin(), mSubsystems.end(),
			[=](handle<subsystem> const& _s) {
				_s->add(_e, _ty, _c);
		});
	}

	void basic_system::notify_remove(basic_entity *_e, component_type _ty,
		component_proxy *_c)
	{
		std::for_each(mSubsystems.begin(), mSubsystems.end(),
			[=](handle<subsystem> const& _s) {
				_s->remove(_e, _ty, _c);
		});
	}
}