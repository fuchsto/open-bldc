#ifndef MODULE_CONFIG_GENERATOR_STRATEGY_HPP__
#define MODULE_CONFIG_GENERATOR_STRATEGY_HPP__

#include <olconf/module_config.hpp>

#include <yamlgen/abstract_config_builder.hpp>

#include <vector>


namespace YAMLGen { 
namespace OBLDC { 

template <class RunnerT>
class ModuleConfigBuilder : public AbstractConfigBuilder
{

private: 

	::std::vector<ModuleConfig<RunnerT> > m_modules; 

public: 

	ModuleConfigBuilder() { } 
	virtual ~ModuleConfigBuilder() { } 

public: 

	virtual void parse(ConfigNode const & config);
	virtual void parse_partial(ConfigNode const & config_node);
	virtual void run(RunnerT & runner);

public: 

	::std::vector<ModuleConfig<RunnerT> > const & modules(void) const { return m_modules; }

};

} /* namespace OBLDC */
} /* namespace YAMLGen */

#endif /* MODULE_CONFIG_GENERATOR_STRATEGY_HPP__ */
