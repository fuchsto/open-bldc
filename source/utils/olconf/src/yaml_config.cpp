
#include <olconf/yaml_config.hpp>
#include <olconf/module_config_builder.impl.hpp>
#include <olconf/register_config_builder.impl.hpp>
#include <olconf/flag_config_builder.impl.hpp>
#include <olconf/define_config_builder.impl.hpp>
#include <olconf/header_generation_runner.hpp>

#include <yamlgen/logging.hpp>
#include <yamlgen/config_generator.hpp>
#include <yamlgen/exception/interpreter_exception.hpp>
#include <yamlgen/exception/parser_exception.hpp>
#include <yamlgen/exception/builder_exception.hpp>
#include <yamlgen/exception/config_exception.hpp>


namespace YAMLGen { 
namespace OBLDC { 

void
YAMLConfig::read(char const * filename) 
{
	Interpreter interpreter; 
	interpreter.read(filename); 
	
	Postprocessor postproc(interpreter.config());
	postproc.run(); 

	ModuleConfigBuilder<HeaderGenerationRunner> builder;
	builder.parse(postproc.config());

	HeaderGenerationRunner runner; 
	builder.run(runner);

/* 
	Note that a ConfigGenerator can parse several 
	interpreters, and you can run several runners 
	on the same configurator: 

		config_generator.parse(first_interpreter); 
		config_generator.parse(second_interpreter); 

		config_generator.run(first_strategy); 
		config_generator.run(second_strategy); 
		config_generator.run(third_strategy); 
*/

}

} /* namespace OBLDC */
} /* namespace YAMLGen */
