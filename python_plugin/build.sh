#!/bin/bash

g++ -std=c++11 -O2 -c python_sgems_plugin.cpp -I/usr/include/python2.7
g++ -std=c++11 -O2 -c python_sgems_plugin_test.cpp -I/usr/include/python2.7

g++ -std=c++11 -O2 -o python_test python_sgems_plugin_test.o python_sgems_plugin.o -lpython2.7


