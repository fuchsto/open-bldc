#ifndef ABSTRACT_CONFIG_BUILDER_HPP__
#define ABSTRACT_CONFIG_BUILDER_HPP__

#include <yamlgen/interpreter.hpp>
#include <yamlgen/abstract_config_runner.hpp>
#include <yamlgen/exception/builder_exception.hpp>
#include <yamlgen/exception/runner_exception.hpp>


namespace YAMLGen { 

class AbstractConfigBuilder
{ 

public: 
	virtual ~AbstractConfigBuilder() { } 

public: 

	virtual void parse(ConfigNode const & config) = 0;
	virtual void parse_partial(ConfigNode const & config_node) = 0;
	virtual void run(AbstractConfigRunner & runner) { } 
};

} /* namespace YAMLGen */

#endif /* ABSTRACT_CONFIG_BUILDER_HPP__ */
