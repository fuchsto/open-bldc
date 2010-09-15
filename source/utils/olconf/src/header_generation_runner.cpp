
#include <olconf/header_generation_runner.hpp>
#include <olconf/register_config_builder.hpp>
#include <olconf/flag_config_builder.hpp>
#include <olconf/define_config_builder.hpp>
#include <olconf/register_group_config.hpp>
#include <olconf/register_config.hpp>

#include <iostream>
#include <vector>

/*	TODO: 
 *	Can be refactored
 *
 *		GenericRunner<ConcreteRunnerT>
 *
 *	--> 
 *
 *		GenericRunner<HeaderGenerationRunner> runner; 
 *
 */

namespace YAMLGen { 
namespace OBLDC { 

void
HeaderGenerationRunner::run(ModuleConfigBuilder<HeaderGenerationRunner> const * builder) 
{ 
	::std::cout << "#ifndef MODULE_CONFIG_HPP__" << ::std::endl;
	::std::cout << "#define MODULE_CONFIG_HPP__" << ::std::endl;

	::std::vector<ModuleConfig<HeaderGenerationRunner> >::const_iterator mod_it;
	::std::vector<ModuleConfig<HeaderGenerationRunner> >::const_iterator mod_end;
	mod_end = builder->modules().end(); 
	for(mod_it = builder->modules().begin(); mod_it != mod_end; ++mod_it) { 
		ModuleConfig<HeaderGenerationRunner> module = (*mod_it); 
		HeaderGenerationRunner runner(module.name()); 

		::std::vector<RegisterConfigBuilder<HeaderGenerationRunner> >::iterator reg_it;
		::std::vector<RegisterConfigBuilder<HeaderGenerationRunner> >::const_iterator reg_end;
		reg_end = module.registers().end();
		for(reg_it = module.registers().begin(); reg_it != reg_end; ++reg_it) { 
			RegisterConfigBuilder<HeaderGenerationRunner> builder = (*reg_it); 
			builder.run(runner);
		}

		::std::vector<FlagConfigBuilder<HeaderGenerationRunner> >::iterator flag_it;
		::std::vector<FlagConfigBuilder<HeaderGenerationRunner> >::const_iterator flag_end;
		flag_end = module.flags().end();
		for(flag_it = module.flags().begin(); flag_it != flag_end; ++flag_it) { 
			FlagConfigBuilder<HeaderGenerationRunner> builder = (*flag_it); 
			builder.run(runner);
		}

		::std::vector<DefineConfigBuilder<HeaderGenerationRunner> >::iterator def_it;
		::std::vector<DefineConfigBuilder<HeaderGenerationRunner> >::const_iterator def_end;
		def_end = module.defines().end();
		for(def_it = module.defines().begin(); def_it != def_end; ++def_it) { 
			DefineConfigBuilder<HeaderGenerationRunner> builder = (*def_it); 
			builder.run(runner);
		}
	}

	::std::cout << ::std::endl; 
	::std::cout << "#endif /* MODULE_CONFIG_HPP__ */" << ::std::endl;
}

void
HeaderGenerationRunner::run(RegisterConfigBuilder<HeaderGenerationRunner> const * builder) 
{ 
	::std::vector<RegisterGroupConfig> const register_groups = builder->register_groups(); 

	::std::vector<RegisterGroupConfig>::const_iterator groups_it; 
	::std::vector<RegisterGroupConfig>::const_iterator groups_end = register_groups.end(); 

	for(groups_it = register_groups.begin(); groups_it != groups_end; ++groups_it) {
		RegisterGroupConfig group = (*groups_it);
		::std::vector<RegisterConfig> const registers = group.registers();

		::std::cout << ::std::endl; 
		::std::cout << "/* Module: " << m_module << " Register group: " << group.name() << " */" << ::std::endl;

		::std::vector<RegisterConfig>::const_iterator register_it; 
		::std::vector<RegisterConfig>::const_iterator register_end = registers.end();
		for(register_it = registers.begin(); register_it != register_end; ++register_it) { 
			::std::cout << "#define " << m_module << "__" << (*register_it).name();
			::std::cout << " " << (*register_it).register_nr() << ::std::endl;
		}
	}
	::std::cout << ::std::endl; 
}

void
HeaderGenerationRunner::run(FlagConfigBuilder<HeaderGenerationRunner> const * builder) 
{ 
	::std::vector<FlagConfig> const flags = builder->flags(); 

	::std::vector<FlagConfig>::const_iterator flags_it; 
	::std::vector<FlagConfig>::const_iterator flags_end = flags.end(); 

	for(flags_it = flags.begin(); flags_it != flags_end; ++flags_it) {
		FlagConfig flag = (*flags_it);

		::std::cout << ::std::endl; 
		::std::cout << "/* Module: " << m_module << " Flag: " << flag.name() << " */" << ::std::endl;
		::std::cout << "#define " << m_module << "__FLAG_" << flag.name();
		::std::cout << " " << flag.bit() << ::std::endl;
	}
	::std::cout << ::std::endl; 
}

void
HeaderGenerationRunner::run(DefineConfigBuilder<HeaderGenerationRunner> const * builder) 
{ 
	::std::map< ::std::string, ::std::string> const defines = builder->defines(); 

	::std::map< ::std::string, ::std::string>::const_iterator defines_it; 
	::std::map< ::std::string, ::std::string>::const_iterator defines_end = defines.end(); 

	for(defines_it = defines.begin(); defines_it != defines_end; ++defines_it) {
		::std::string name  = (*defines_it).first; 
		::std::string value = (*defines_it).second; 

		::std::cout << ::std::endl; 
		::std::cout << "/* Module: " << m_module << " Define: " << name << " */" << ::std::endl;
	
		if(value == "no") { 
			::std::cout << "// "; 
		} 
		::std::cout << "#define " << m_module << "__" << name;
			
		if(value != "yes" && value != "no") { 
			::std::cout << " " << value << ::std::endl;
		}
	}
	::std::cout << ::std::endl; 
}

} /* namespace OBLDC */
} /* namespace YAMLGen */
