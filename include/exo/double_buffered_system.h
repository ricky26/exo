#include "system.h"

#pragma once

namespace exo
{
	class double_buffered_system;
	class EXO_API double_buffered_component_proxy: public component_proxy
	{
	public:
		double_buffered_component_proxy(
			double_buffered_system *_s, entity *_e,
			netlib::handle<component> const& _a,
			netlib::handle<component> const& _b);

	private:
		netlib::handle<component> mA, mB;
	};

	class EXO_API double_buffered_entity: public entity
	{
	public:
		double_buffered_entity(double_buffered_system *_s);
	};

	class EXO_API double_buffered_system: public system
	{
	};
}