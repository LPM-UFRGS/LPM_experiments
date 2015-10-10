/*
(c) LPM/UFRGS 2015, Péricles Lopes Machado

Python Sgems plugin test.
*/

#include "python_sgems_plugin.h"

#include <iostream>
#include <Python.h>

int main()
{

	std::vector<const char*> modules = {"base_sgems_plugin", "derived_sgems_plugin", "error_module"};

	setenv("PYTHONPATH", ".", 1);

 	Py_Initialize();
	
	python_sgems_plugins::PluginNamesList plugins;
	python_sgems_plugins::PluginFactoryList factories;

	for (const char* module : modules) {
		try {
			plugins = python_sgems_plugins::get_plugin_names(module);
			for (auto& plugin: plugins) {
				std::cout << plugin << "\n";
			
				try {
					factories.push_back(python_sgems_plugins::get_plugin_factory(module, plugin.c_str()));
				} catch (const char* e) {
					std::cerr << "Error: " << e << "\n";
				}
			}
		} catch (const char* e) {
			std::cerr << "Exception: " << e << "\n";
		}
	}

	for (auto factory: factories) {
		python_sgems_plugins::PythonPlugin* p = factory->new_instance();

		std::cout << "\n---- Python Plugin ----\n";
		std::cout << "name(): " << p->name() << "\n";
		std::cout << "initialize(): " << p->initialize("Ola python! :)") << "\n";			
		std::cout << "execute(): " << p->execute() << "\n";
		std::cout << "finalize(): " << p->finalize() << "\n";
		std::cout << "----------------------\n\n";

		delete p;
	}

	clear_factory_list(factories);
	Py_Finalize();

	return 0;
}


