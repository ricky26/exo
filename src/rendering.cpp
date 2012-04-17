#include "exo/rendering.h"
#include <algorithm>

namespace exo
{
	//
	// rendering_manager
	//

	void rendering_manager::add(netlib::handle<rendering_subsystem> const& _ss)
	{
		mList.push_back(_ss);
	}

	void rendering_manager::remove(rendering_subsystem *_ss)
	{
		std::remove(mList.begin(), mList.end(), _ss);
	}

	void rendering_manager::render()
	{
		rendering_subsystem::list_t list;

		for(auto it = mList.begin();
			it != mList.end(); it++)
		{
			(*it)->render(list);
		}

		list.sort([](rendering_subsystem::job_t const& _a,
			rendering_subsystem::job_t const& _b) {
			return _a.second-_b.second;
		});

		for(auto it = list.begin();
			it != list.end(); it++)
		{
			it->first();
		}
	}
}