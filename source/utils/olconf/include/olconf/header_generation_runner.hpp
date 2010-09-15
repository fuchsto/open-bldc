#ifndef HEADER_GENERATION_RUNNER_HPP__
#define HEADER_GENERATION_RUNNER_HPP__

#include <yamlgen/abstract_config_runner.hpp>

#include <olconf/module_config_builder.hpp>
#include <olconf/register_config_builder.hpp>
#include <olconf/flag_config_builder.hpp>
#include <olconf/define_config_builder.hpp>


namespace YAMLGen { 
namespace OBLDC { 

class HeaderGenerationRunner : public AbstractConfigRunner
{
private: 

	::std::string m_module; 

public: 

	HeaderGenerationRunner()
	: m_module("Unknown") { } 

	HeaderGenerationRunner(::std::string const & module) 
	: m_module(module) { } 

public: 

	virtual void run(ModuleConfigBuilder<HeaderGenerationRunner> const * builder); 
	virtual void run(RegisterConfigBuilder<HeaderGenerationRunner> const * builder); 
	virtual void run(FlagConfigBuilder<HeaderGenerationRunner> const * builder); 
	virtual void run(DefineConfigBuilder<HeaderGenerationRunner> const * builder); 

};

} /* namespace OBLDC */
} /* namespace YAMLGen */

#endif /* HEADER_GENERATION_RUNNER_HPP__ */
