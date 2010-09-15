#ifndef FLAG_CONFIG_BUILDER_HPP__
#define FLAG_CONFIG_BUILDER_HPP__

#include <olconf/register_group_config.hpp>
#include <olconf/flag_config.hpp>

#include <yamlgen/abstract_config_builder.hpp>

#include <vector>


namespace YAMLGen { 
namespace OBLDC { 

template <class RunnerT>
class FlagConfigBuilder : public AbstractConfigBuilder
{

private: 

	::std::string m_module; 
	::std::vector<FlagConfig> m_flags; 

public: 

	FlagConfigBuilder() { } 

	virtual ~FlagConfigBuilder() { } 

	::std::vector<FlagConfig> const & flags() const { 
		return m_flags; 
	}

public: 

	virtual void parse(ConfigNode const & config);
	virtual void parse_partial(ConfigNode const & config_node);
	virtual void run(RunnerT & runner);

};

} /* namespace OBLDC */
} /* namespace YAMLGen */

#endif /* FLAG_CONFIG_BUILDER_HPP__ */
