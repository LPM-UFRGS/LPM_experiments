/*
(c) LPM/UFRGS 2015, Péricles Lopes Machado

Python Sgems plugin.
*/

#include "python_sgems_plugin.h"

#include <cstdlib>
#include <cstdio>

namespace python_sgems_plugins {

// Python Plugin
PythonPlugin::PythonPlugin(PyObject* _instance)
	: instance_(_instance)
{
}

PythonPlugin::~PythonPlugin()
{
	Py_DECREF(instance_);
}

bool PythonPlugin::initialize(const std::string& _params, Notifier* _notifier)
{
	bool ok = true;

	if (_notifier == nullptr) {
		PyObject* result = PyObject_CallMethod(instance_, "initialize", "(s)", const_cast<char*>(_params.c_str()));

		if (result == NULL) return false;

		if (PyBool_Check(result)) {
			ok = result == Py_True;
		} else {
			Py_DECREF(result);
		}
	}

	return ok;
}

bool PythonPlugin::execute(Notifier* _notifier)
{
	bool ok = true;

	PyObject* result = PyObject_CallMethod(instance_, "execute", NULL, NULL);
	
	if (result == NULL) return false;

	if (PyBool_Check(result)) {
		ok = result == Py_True;
	} else {
		Py_DECREF(result);
	}

	return ok;
}

bool PythonPlugin::finalize(Notifier* _notifier)
{
	bool ok = true;

	PyObject* result = PyObject_CallMethod(instance_, "finalize", NULL, NULL);

	if (result == NULL) return false;

	if (PyBool_Check(result)) {
		ok = result == Py_True;
	} else {
		Py_DECREF(result);
	}
	
	return ok;
}

std::string PythonPlugin::name()
{
	PyObject* result = PyObject_CallMethod(instance_, "name", NULL, NULL);

	if (result == NULL) return "";

	if (PyString_Check(result)) {
		return	PyString_AsString(result);
	}

	return "";
}

// Python Plugin Factory
PythonPluginFactory::PythonPluginFactory(PyObject* _module, PyObject* _class)
	: module_(_module), class_(_class)
{
}

PythonPluginFactory::~PythonPluginFactory()
{
	Py_DECREF(class_);
	Py_DECREF(module_);
}

PythonPlugin* PythonPluginFactory::new_instance()
{
	PyObject* pInstance = PyInstance_New(class_, NULL, NULL);
	if (pInstance == NULL) {
		return nullptr;
	}
	return new PythonPlugin(pInstance);
}

// Utilities functions
PluginNamesList get_plugin_names(const char* module) throw (const char*)
{
	fprintf(stderr, "Loading module %s...\n", module);	

	PyObject* pModule = PyImport_ImportModule(module);
	if (pModule == NULL) {
		throw "Error during module loading.";
	}

	PyObject* pFunc = PyObject_GetAttrString(pModule, "get_plugins");
	if (pFunc == NULL) {
		Py_DECREF(pModule);
		throw "Function 'get_plugins()' isn't defined.";
	}

	fprintf(stderr, "Loading plugin names from %s...\n", module);

	PyObject* pPluginList = PyObject_CallObject(pFunc, NULL);
	if (PyList_Check(pPluginList) == 0) {
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
		throw "'get_plugins()' must to return a list.";
	}

	Py_ssize_t pPluginListSize = PyList_Size(pPluginList);

	PluginNamesList plugins;

	for (Py_ssize_t i = 0; i < pPluginListSize; ++i) {
		PyObject* pPlugin = PyList_GetItem(pPluginList, i);

		if (PyString_Check(pPlugin) == 1) {
			const char* plugin_name = PyString_AsString(pPlugin);
			plugins.push_back(plugin_name);
		}
	}

	//BEGIN Unload python objects
	Py_DECREF(pPluginList);
	Py_XDECREF(pFunc);
	Py_DECREF(pModule);
	//END Unload python objects
	
	return plugins;
} 

PythonPluginFactory* get_plugin_factory(const char* module, const char* plugin_name) throw (const char*)
{
	fprintf(stderr, "Loading module %s...\n", module);	

	PyObject* pModule = PyImport_ImportModule(module);
	if (pModule == NULL) {
		throw "Error during module loading.";
	}

	PyObject* pClass = PyObject_GetAttrString(pModule, plugin_name);
	if (pClass == NULL) {
		Py_DECREF(pModule);
		throw "Error during class loading.";
	}

	PyObject* pInstance = PyInstance_New(pClass, NULL, NULL);
	if (pInstance == NULL) {
		Py_DECREF(pClass);
		Py_DECREF(pModule);		
		throw "Error during instance creation.";
	}

	if (PyObject_HasAttrString(pInstance, "initialize") == 0) {
		Py_DECREF(pInstance);		
		Py_DECREF(pClass);
		Py_DECREF(pModule);
		throw "'initialize()' method isn't defined.";
	}

	if (PyObject_HasAttrString(pInstance, "execute") == 0) {
		Py_DECREF(pInstance);		
		Py_DECREF(pClass);
		Py_DECREF(pModule);		
		throw "'execute()' method isn't defined.";
	}

	if (PyObject_HasAttrString(pInstance, "finalize") == 0) {
		Py_DECREF(pInstance);		
		Py_DECREF(pClass);
		Py_DECREF(pModule);
		throw "'finalize()' method isn't defined.";
	}

	if (PyObject_HasAttrString(pInstance, "name") == 0) {
		Py_DECREF(pInstance);		
		Py_DECREF(pClass);
		Py_DECREF(pModule);
		throw "'name()' method isn't defined.";
	}

	//BEGIN Unload python objects
	Py_DECREF(pInstance);
	//END Unload python objects

	return new PythonPluginFactory(pModule, pClass);
}

void clear_factory_list(PluginFactoryList& factories) 
{
	for (auto& factory: factories) {
		if (factory != nullptr) {
			delete factory;
		}
	}
}

} // namespace python_sgems_plugins

