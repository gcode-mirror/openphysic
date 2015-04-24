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

import logging
import traceback

import requests
import urllib
#import xml.dom.minidom
from xml.etree import ElementTree as ET
import time

def hide_string(s, char_replace='*'):
    return(char_replace*len(s))

class ADEWebAPI():
    def __init__(self, url, login, password):
        self.url = url
        self.login = login
        self.password = password
        
        self.sessionId = None
        
        self.debug = True

        self.logger = logging.getLogger('ADEWebAPI')

    def xml_debug(self, xmlrep):
        if self.debug:
            print(xmlrep)
            time.sleep(1)

    def hide_dict_values(self, d, hidden_keys=['password']):
        d_hidden = d.copy()
        for key in hidden_keys:
            if key in d_hidden.keys():
                d_hidden[key] = hide_string(d_hidden[key])
        return(d_hidden)

    def _send_request(self, func, params):
        params['function'] = func
        
        self.logger.debug("send %s" % self.hide_dict_values(params))
        response = requests.get(self.url, params=params)
        self.logger.debug(response)
        self.logger.debug(response.text)
        element = ET.fromstring(response.text)

        return(element)

    def connect(self):
        func = 'connect'

        params = {
            'login': self.login,
            'password': self.password
        }

        try:
            session = self._send_request(func, params)
            session_id = session.attrib["id"]
            self.sessionId = session_id
        except:
            raise(Exception(traceback.format_exc()))

    def disconnect(self):
        func = 'disconnect'

        params = {
            'sessionId': self.sessionId
        }

        try:
            disconnected = self._send_request(func, params)
            session_id = disconnected.attrib["sessionId"]
            assert(session_id == self.sessionId)
        except:
            raise(Exception(traceback.format_exc()))

        response = requests.get(self.url, params=params)

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


