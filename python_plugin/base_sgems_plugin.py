#!/bin/python

"""
The base python sgems plugin.
"""
class BaseSgemsPlugin:
	def __init__(self):
		pass

	def initialize(self, params):		
		print "initialize BaseSgemsPlugin"
		print params
		return True

	def execute(self):		
		print "execute BaseSgemsPlugin"
		return True

	def finalize(self):
		print "finalize BaseSgemsPlugin"
		return True

	#def name(self):
	#	return "base_sgems_plugin"

###############################################################
def get_plugins():
	return ["BaseSgemsPlugin"]
