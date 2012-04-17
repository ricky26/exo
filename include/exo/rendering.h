#include "system.h"

#pragma once

namespace exo
{
	class EXO_API rendering_subsystem: public subsystem
	{
	public:
		typedef std::function<void()> job_fn_t;
		typedef std::pair<job_fn_t, size_t> job_t;
		typedef std::list<job_t> list_t;

		virtual void render(list_t&) = 0;
	};

	/**
	 * This class coordinates all rendering_subsystems.
	 */
	class EXO_API rendering_manager: public netlib::ref_counted
	{
	public:
		typedef std::vector<netlib::handle<rendering_subsystem>> list_t;

		void add(netlib::handle<rendering_subsystem> const& _ss);
		void remove(rendering_subsystem *_ss);

		void render();

	private:
		list_t mList;
	};
}