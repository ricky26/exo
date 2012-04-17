#include "system.h"
#include <unordered_set>

#pragma once

namespace exo
{
	class basic_system;

	class EXO_API basic_component_proxy: public component_proxy
	{
	public:
		basic_component_proxy(entity *_e,
			netlib::handle<component> const& _c);

		component *read() override;
		component *write() override;

	private:
		entity *mEntity;
		netlib::handle<component> mComponent;
	};

	class EXO_API basic_entity: public entity
	{
	public:
		typedef std::unordered_map<component_type,
			netlib::handle<basic_component_proxy>> map_t;

		basic_entity(basic_system *_sys);

		component_proxy *component(component_type _ty) override;
		component_proxy *create(component_type _ty,
			component_factory_t const&) override;
		void remove(component_type _ty) override;

	private:
		map_t mMap;
		basic_system *mSystem;
	};

	class EXO_API basic_system: public system
	{
	public:
		friend class basic_entity;

		typedef std::unordered_set<netlib::handle<basic_entity>> entity_list_t;
		typedef std::unordered_set<netlib::handle<subsystem>> subsystem_list_t;

		basic_system();

		entity *create() override;
		void remove(entity *_e) override;

		void add(netlib::handle<subsystem> const& _s) override;
		void remove(subsystem *_s) override;

	protected:
		void notify_add(basic_entity *_e, component_type _ty,
			component_proxy *_c);
		void notify_remove(basic_entity *_e, component_type _ty,
			component_proxy *_c);

	private:
		entity_list_t mEntities;
		subsystem_list_t mSubsystems;
	};
}