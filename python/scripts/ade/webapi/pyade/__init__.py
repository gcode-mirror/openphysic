#!/usr/bin/python
# -*- coding: utf8 -*-

"""
    ADE API Test

    Copyright (C) 2011-2015 "Sébastien Celles" <s.celles@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
"""

import requests
import urllib
import xml.dom.minidom
import time

class ADEWebAPI():
    def __init__(self, url, login, password):
        self.url = url
        self.login = login
        self.password = password
        
        self.sessionId = None
        
        self.debug = True

    def xml_debug(self, xmlrep):
        if self.debug:
            print(xmlrep)
            time.sleep(1)

    def connect(self):
        params = {
            'function': 'connect',
            'login': self.login,
            'password': self.password
        }
        response = requests.get(self.url, params=params)
        print(response)
        print(response.text)

        #xmlrep = f.read()
        #self.xml_debug(xmlrep)
        
        #dom = xml.dom.minidom.parseString(xmlrep)
                
        #try:
        #    elt = dom.getElementsByTagName('session')[0]
        #    self.sessionId = elt.getAttribute('id')
        #except:
        #    #elt = dom.getElementsByTagName('error')
        #    raise Exception("Connect error")

    def disconnect(self):
        params = {
            'function': 'disconnect',
            'sessionId': self.sessionId
        }
        response = requests.get(self.url, params=params)
        print(response)
        print(response.text)

        #xmlrep = f.read()
        #self.xml_debug(xmlrep)
        
    def getProjectsById(self, id):
        params = {
            'function': 'getProjects',
            'sessionId': self.sessionId,
            'id': id
        }
        response = requests.get(self.url, params=params)
        print(response)
        print(response.text)

        #f = urllib.urlopen(self.url + "function={0}&sessionId={1}&id={2}".format('getProjects', self.sessionId, id))
        #xmlrep = f.read()
        #self.xml_debug(xmlrep)

    def getProjects(self, detail):
        params = {
            'function': 'getProjects',
            'sessionId': self.sessionId,
            'detail': detail
        }
        response = requests.get(self.url, params=params)
        print(response)
        print(response.text)

        #f = urllib.urlopen(self.url + "function={0}&sessionId={1}&detail={2}".format('getProjects', self.sessionId, detail))
        #xmlrep = f.read()
        #self.xml_debug(xmlrep)
        
    def setProject(self, projectId):
        params = {
            'function': 'setProject',
            'sessionId': self.sessionId,
            'projectId': projectId
        }
        response = requests.get(self.url, params=params)
        print(response)
        print(response.text)
            
    def getResources(self, category): # ToFix
        params = {
            'function': 'getResources',
            'sessionId': self.sessionId,
            'projectId': projectId,
            'category': category # classroom, trainee, instructor
        }
        response = requests.get(self.url, params=params)
        print(response)
        print(response.text)

        #f = urllib.urlopen(self.url + "function={0}&sessionId={1}&tree=true&name=Amphi&category=classroom".format('getResources', self.sessionId))
        #xmlrep = f.read()
        #self.xml_debug(xmlrep)

"""
    def getTraineeByCode(self, code): # ToFix
        f = urllib.urlopen(self.url + "function={0}&sessionId={1}&tree=false&code={2}&category=trainee&leaves=true".format('getResources', self.sessionId, code))
        xmlrep = f.read()
        self.xml_debug(xmlrep)


    def getClassrom(self, name):
        f = urllib.urlopen(self.url + "function={0}&sessionId={1}&tree=true&name={2}&category=classroom".format('getResources', self.sessionId, name))
        xmlrep = f.read()
        self.xml_debug(xmlrep)

    def getInstructorByName(self, name):
        f = urllib.urlopen(self.url + "function={0}&sessionId={1}&tree=true&name={2}&category=instructor".format('getResources', self.sessionId, name))
        xmlrep = f.read()
        self.xml_debug(xmlrep)

    def getInstructorByCode(self, code):
        f = urllib.urlopen(self.url + "function={0}&sessionId={1}&tree=true&code={2}&category=instructor".format('getResources', self.sessionId, code))
        xmlrep = f.read()
        self.xml_debug(xmlrep)

    def getActivities(self):
        f = urllib.urlopen(self.url + "function={0}&sessionId={1}&tree=true".format('getActivities', self.sessionId))
        xmlrep = f.read()
        self.xml_debug(xmlrep)
        
    def getEvents(self):
        pass
        
    def getCosts(self):
        pass

    def getCaracteristics(self):
        pass
        
    def getDate(self, week, day, slot):
        pass
"""


