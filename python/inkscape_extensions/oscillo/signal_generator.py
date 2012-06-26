#!/usr/bin/env python

'''
Copyright 2012 Sebastien Celles <s.celles@gmail.com>

This file is part of Oscillo Extension for Inkscape.

Oscillo Extension for Inkscape is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Oscillo Extension for Inkscape is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Oscillo Extension for Inkscape. If not, see http://www.gnu.org/licenses/.
'''

from pylab import *

class CSignalGenerator:
	"""
	Classe simulant un GBF
	"""
	def __init__(self):
		"""
		Constructeur
		"""
		
		self.mode = 'sin'
		self.frequency = 1000.0 # Hz
		self.offset = 0.1 # V
		self.amplitude = 1.0 # V
		self.phase = 0.0 # deg
		
		pass

	def display(self):
		for attr in dir(self):
			print("obj.%s = %s" % (attr, getattr(self, attr)))

	def getSignal(self, t):
		if self.mode=='sin':
			return(self.offset)
	
	def getPeriod(self):
		return(1/self.frequency)