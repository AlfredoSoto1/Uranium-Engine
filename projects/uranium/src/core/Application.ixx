module;
#include "URAPI.h"

export module uranium.core.Application;

export namespace uranium::core {

	URANIUM_API UR_ABSTRACT_CLASS Application {
	public:
		virtual void init()     noexcept = 0;
		virtual void shutdown() noexcept = 0;

		virtual void loadConfig() noexcept = 0;
		virtual void saveConfig() noexcept = 0;
	};
}