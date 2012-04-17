#include "exo.h"
#include <netlib/ref_counted.h>
#include <unordered_map>
#include <typeindex>

#pragma once

namespace exo
{
	typedef std::type_index component_type;

	class EXO_API component: public netlib::ref_counted
	{
	};

	class EXO_API component_proxy: public netlib::ref_counted
	{
	public:
		virtual component *read() = 0;
		virtual component *write() = 0;
	};

	class EXO_API entity: public netlib::ref_counted
	{
	public:
		typedef std::function<netlib::handle<component>()> component_factory_t;

		virtual component_proxy *component(component_type _ty) = 0;

		virtual component_proxy *create(component_type _ty,
			component_factory_t const&) = 0;

		template<typename T>
		inline component_proxy *create(component_type _ty)
		{
			return create(_ty, []() { return new T(); });
		}

		virtual void remove(component_type _ty) = 0;
	};

	class EXO_API subsystem: public netlib::ref_counted
	{
	public:
		virtual void add(entity *_e,
			component_type _ty, component_proxy *_c) = 0;
		virtual void remove(entity *_e,
			component_type _ty, component_proxy *_c) = 0;
	};

	class EXO_API system: public netlib::ref_counted
	{
	public:
		virtual entity *create() = 0;
		virtual void remove(entity *_e) = 0;

		virtual void add(netlib::handle<subsystem> const& _s) = 0;
		virtual void remove(subsystem *_s) = 0;
	};
}