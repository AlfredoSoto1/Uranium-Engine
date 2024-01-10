#include "GraphicContext.h"

namespace Uranium::Platform::Interface {

	GraphicContext::GraphicContext(
		const std::string& engineName      = "Engine",
		const std::string& applicationName = "Application",

		uint32_t appMajor = 1,
		uint32_t appMinor = 0,
		uint32_t appPatch = 0,

		uint32_t engineMajor = 1,
		uint32_t engineMinor = 0,
		uint32_t enginePatch = 0
	) noexcept :
		engineName(engineName),
		applicationName(applicationName),

		appMajor(appMajor),
		appMinor(appMinor),
		appPatch(appPatch),

		engineMajor(engineMajor),
		engineMinor(engineMinor),
		enginePatch(enginePatch)
	{
	}
}