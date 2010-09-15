#ifndef ABSTRACT_CONFIG_RUNNER_HPP__
#define ABSTRACT_CONFIG_RUNNER_HPP__

#include <yamlgen/exception/builder_exception.hpp>

namespace YAMLGen { 

class AbstractConfigBuilder; 

class AbstractConfigRunner
{

public: 
	virtual ~AbstractConfigRunner() { } 

	virtual void run(AbstractConfigBuilder * const builder) { 
		throw BuilderException("No runner handler implemented for builder");
	}
};

} /* namespace YAMLGen */

#endif /* ABSTRACT_CONFIG_RUNNER_HPP__ */
