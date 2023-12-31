#pragma once

namespace Uranium::Core {

	class Log {
	public:
		static void log();
	};
#ifdef UR_DEBUG
	
#define ur_log(x)

#endif // UR_DEBUG

}