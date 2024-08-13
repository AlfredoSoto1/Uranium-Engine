module;
#include "URAPI.h"

export module uranium.core.EntryPoint;

export import <vector>;
export import <memory>;

//import uranium.core.Application;

export namespace uranium::core {
	
	UR_DECLARE Application;

	/*
	* @brief
	* Starts the uranium core given application
	*/
	int start(int argc, char** argv, std::shared_ptr<Application> application);
}

module :private;

namespace uranium::core {
	int start(int argc, char** argv, std::shared_ptr<Application> application) {
		// Start application here		
		return 0;
	}
}
