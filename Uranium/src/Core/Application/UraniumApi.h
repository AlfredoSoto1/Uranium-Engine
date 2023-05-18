#pragma once

#ifdef _DEBUG // debug

#include <iostream>

// 
// throw_error(condition, message)
// 
// prints to the console the error message given
// and marks a breakpoint if and only if its on debug
// configuration.
// 
#define throw_error(condition, message) \
	if(condition) {\
		std::cerr << "Error at File: " << __FILE__ << "\nin line: "<< __LINE__  << "\n" << message << std::endl; __debugbreak();\
	}

// 
// compile_error(message)
// 
// tells the compiler there is a compilation error
// and sends a message to the user telling him what
// error is causing the problem (message should be provided as parameter)
// 
#define compile_error(message) static_assert(false, message)

// 
// print_status(status)
// 
// it prints what ever status is given
// this works exactly as std::cout from STD
// 
#define print_status(status) std::cout << status << std::endl

// 
// print_warning(condition, message)
// 
// prints a warning message if condition provided is
// a true statement
// 
#define print_warning(condition, message) if(condition) print_status(message)

#else // release

// 
// all these functions are empty when active
// configuration is set to realase. To see what
// they do, check the _DEBUG condition in this file
// 
#define throw_error(condition, message)

#define compile_error(message)

#define print_status(status)

#define print_warning(condition, message)

#endif