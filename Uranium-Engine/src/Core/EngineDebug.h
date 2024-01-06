#pragma once

namespace Uranium::Core {

#ifdef UR_DEBUG
#define debug_var(variable_declaration) variable_declaration
#else
#define debug_var(variable_declaration)
#endif

#ifdef UR_DEBUG
#define debug_var(variable_declaration, debug_value, release_value) variable_declaration = debug_value
#else
#define debug_var(variable_declaration, debug_value, release_value) variable_declaration = release_value
#endif

#ifdef UR_DEBUG
#define debug_function(function_declaration) function_declaration
#else
#define debug_function(function_declaration)
#endif

}