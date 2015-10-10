/*
(c) LPM/UFRGS 2015, Péricles Lopes Machado

Python Sgems plugin.
*/

#ifndef __PYTHON_SGEMS_PLUGIN_H__
#define __PYTHON_SGEMS_PLUGIN_H__

#include <vector>
#include <string>

#include <Python.h>

namespace python_sgems_plugins {

class Notifier;

class PythonPlugin {
	public:
		PythonPlugin(PyObject* _instance = NULL);
		~PythonPlugin();

		bool initialize(const std::string& _params, Notifier* _notifier = nullptr);
		bool execute(Notifier* _notifier = nullptr);
		bool finalize(Notifier* _notifier = nullptr);
		std::string name();

	private:
		PyObject* instance_;
};

class PythonPluginFactory {
	public:
		PythonPluginFactory(PyObject* _module = NULL, PyObject* _class = NULL);
		~PythonPluginFactory();

		PythonPlugin* new_instance();

	private:
		PyObject* module_;
		PyObject* class_;
		
}; // class PythonPlugin

using PluginNamesList = std::vector<std::string>;
using PluginFactoryList = std::vector<PythonPluginFactory*>;

//Load python plugin names from PYTHONPATH
PluginNamesList get_plugin_names(const char* module) throw (const char*);

PythonPluginFactory* get_plugin_factory(const char* module, const char* plugin_name) throw (const char*);

void clear_factory_list(PluginFactoryList& factories);

} // namespace python_sgems_plugins

#endif // __PYTHON_SGEMS_PLUGIN_H__

