
#include <olconf/module_config_builder.hpp>
#include <olconf/module_config.hpp>

#include <yamlgen/config_node.hpp>
#include <yamlgen/logging.hpp>


namespace YAMLGen { 
namespace OBLDC { 

template <class RunnerT>
void
ModuleConfigBuilder<RunnerT>::parse(ConfigNode const & config) 
{
	ConfigNode root;
	ConfigNode::const_iterator root_it = config.find("config_root");
	if(root_it != config.end()) { 
		root = (*root_it).second;
	}
	else { 
		throw BuilderException("Could not find config_root in ModuleConfigBuilder");
	}
	parse_partial(root);
}

template <class RunnerT>
void
ModuleConfigBuilder<RunnerT>::parse_partial(ConfigNode const & config_node) 
{
	ConfigNode::const_iterator it_modules;
	ConfigNode::const_iterator end_modules = config_node.end(); 
	for(it_modules = config_node.begin(); it_modules != end_modules; ++it_modules) 
	{ 
		::std::string module_name     = (*it_modules).first; 
		ConfigNode module_config_node = (*it_modules).second; 
		ModuleConfig<RunnerT> module_config(module_name, module_config_node);

		ConfigNode::const_iterator modes_it; 
		ConfigNode::const_iterator modes_end = module_config_node.end(); 
		for(modes_it = module_config_node.begin(); modes_it != modes_end; ++modes_it) { 
			::std::string mode_name = (*modes_it).first;
			ConfigNode mode_config  = (*modes_it).second; 

/* TODO: Refactor to abstract factory pattern: 
 
			AbstractConfigBuilder * builder = ConfigBuilderFactory.get(module_name, mode_name); 
			builder->parse_partial(mode_config);
			module_config.add(*builder);
*/
			LOG_DEBUG_PRINT("Building mode %s in module %s", 
											mode_name.c_str(), module_name.c_str());

			if(mode_name == "register_groups") { 
				RegisterConfigBuilder<RunnerT> builder;
				builder.parse_partial(mode_config);
				module_config.add(builder);
			}
			if(mode_name == "flags") { 
				FlagConfigBuilder<RunnerT> builder;  
				builder.parse_partial(mode_config);
				module_config.add(builder);
			}
			if(mode_name == "defines") { 
				DefineConfigBuilder<RunnerT> builder; 
				builder.parse_partial(mode_config);
				module_config.add(builder);
			}
		}
		m_modules.push_back(module_config);
		
		LOG_DEBUG_PRINT("-----------------------------------");
		LOG_DEBUG_PRINT("Building module %s", module_name.c_str());
		LOG_DEBUG_PRINT("Module section:\n");
#if defined(LOG) && LOG == DEBUG
		module_config_node.log(); 
#endif
		LOG_DEBUG_PRINT("\n");
		LOG_DEBUG_PRINT("End Module section");
	}
}

template <class RunnerT>
void 
ModuleConfigBuilder<RunnerT>::run(RunnerT & runner) 
{ 
	runner.run(this); 
}

} /* namespace OBLDC */
} /* namespace YAMLGen */
