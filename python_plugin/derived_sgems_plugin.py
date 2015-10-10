#!/bin/python

from base_sgems_plugin import BaseSgemsPlugin

"""
A derived python sgems plugin.
"""
class DerivedSgemsPlugin(BaseSgemsPlugin):
	def __init__(self):
		BaseSgemsPlugin.__init__(self)

	def initialize(self, params):		
		print "initialize DerivedSgemsPlugin"
		print params
		return True

	def execute(self):		
		print "execute DerivedSgemsPlugin"
		return True

	def finalize(self):
		print "finalize DerivedSgemsPlugin"
		return True

	def name(self):
		return "derived_sgems_plugin"

###############################################################
def get_plugins():
	return ["DerivedSgemsPlugin"]

