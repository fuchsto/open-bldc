#ifndef MODULE_CONFIG_HPP__
#define MODULE_CONFIG_HPP__

#include <olconf/register_config_builder.hpp>
#include <olconf/flag_config_builder.hpp>
#include <olconf/define_config_builder.hpp>

#include <yamlgen/config_node.hpp>


namespace YAMLGen { 
namespace OBLDC { 

template <class RunnerT>
class ModuleConfig
{

private: 

	::std::string m_name; 
	ConfigNode m_config_node; 

private: 

	::std::vector<RegisterConfigBuilder<RunnerT> > m_registers;
	::std::vector<FlagConfigBuilder<RunnerT> > m_flags; 
	::std::vector<DefineConfigBuilder<RunnerT> > m_defines; 

public: 

	::std::vector<RegisterConfigBuilder<RunnerT> > & registers() { 
		return m_registers;
	}
	::std::vector<FlagConfigBuilder<RunnerT> > & flags() { 
		return m_flags;
	}
	::std::vector<DefineConfigBuilder<RunnerT> > & defines() { 
		return m_defines;
	}

public: 

	ModuleConfig(::std::string const & name, 
							 ConfigNode const & config_node) 
	: m_name(name), m_config_node(config_node) 
	{ } 

public: 

	void add(RegisterConfigBuilder<RunnerT> const & builder) { 
		m_registers.push_back(builder); 
	}
	void add(DefineConfigBuilder<RunnerT> const & builder) { 
		m_defines.push_back(builder); 
	}
	void add(FlagConfigBuilder<RunnerT> const & builder) { 
		m_flags.push_back(builder); 
	}

public: 

	::std::string const & name(void) const { return m_name; }
	ConfigNode const & config(void) const  { return m_config_node; } 

};

} /* namespace OBLDC */
} /* namespace YAMLGen */

#endif
