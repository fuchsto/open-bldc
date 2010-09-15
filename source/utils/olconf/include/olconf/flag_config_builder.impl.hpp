
#include <olconf/flag_config_builder.hpp>
#include <olconf/flag_config.hpp>

#include <yamlgen/config_node.hpp>
#include <yamlgen/abstract_config_runner.hpp>
#include <yamlgen/exception/builder_exception.hpp>


namespace YAMLGen {
namespace OBLDC { 

template <class RunnerT>
void
FlagConfigBuilder<RunnerT>::parse(ConfigNode const & config)
{
	ConfigNode root;
	ConfigNode::const_iterator root_it = config.find("config_root");
	if(root_it != config.end()) { 
		root = (*root_it).second;
	}
	else { 
		throw BuilderException("Could not find config_root", config);
	}
	parse_partial(root);
}

template <class RunnerT>
void 
FlagConfigBuilder<RunnerT>::parse_partial(ConfigNode const & config_node)
{
	ConfigNode::const_iterator it_flags;
	ConfigNode::const_iterator end_flags = config_node.end(); 
	for(it_flags = config_node.begin(); it_flags != end_flags; ++it_flags) 
	{ 
		::std::string flag_name = (*it_flags).first; 
		ConfigNode flag_config  = (*it_flags).second; 
		
		FlagConfig flag = FlagConfig(flag_name); 
		flag.set_properties(flag_config.values());
		
		m_flags.push_back(flag);
	}
}

template <class RunnerT>
void 
FlagConfigBuilder<RunnerT>::run(RunnerT & runner) 
{
	runner.run(this); 
}

} /* namespace OBLDC */
} /* namespace YAMLGen */
 
