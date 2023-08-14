#pragma once

#ifdef _DEBUG // debug

#include <iostream>

// 
// debug_code(code_injected)
// 
// runs the code that is injected as parameter for this macro
// build mode is on release, this code will be removed
// at compile time
//
#define debug_code(code_injected) code_injected

// 
// debug_break(condition, message)
// 
// prints to the console the error message given
// and marks a breakpoint if and only if its on debug
// configuration.
// 
#define debug_break(condition, message) \
	if(condition) {\
		std::cerr << "Error at File: " << __FILE__ << "\nin line: "<< __LINE__  << "\n" << message << std::endl; __debugbreak();\
	}

// 
// compile_error(condition, message)
// 
// tells the compiler there is a compilation error
// and sends a message to the user telling him what
// error is causing the problem (message should be provided as parameter)
// 
#define compile_error(condition, message) static_assert(condition, message)

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
#define debug_code(code_injected)

#define debug_break(condition, message)

#define compile_error(condition, message)

#define print_status(status)

#define print_warning(condition, message)

#endif