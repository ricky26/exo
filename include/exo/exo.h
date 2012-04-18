#include <prototype/prototype.h>

#pragma once

#ifdef EXO_STATIC
#define EXO_API
#else
#ifdef EXO_EXPORTS
#	define EXO_API NETLIB_API_EXPORT
#else
#	define EXO_API NETLIB_API_IMPORT
#endif
#endif

#define EXO_THREAD			NETLIB_THREAD
#define EXO_INLINE			NETLIB_INLINE

namespace exo
{
};