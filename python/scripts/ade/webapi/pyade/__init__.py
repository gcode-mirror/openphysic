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

class Resource(object):
    pass

class Room(Resource):
    pass

class Trainee(Resource):
    pass

class Instructor(Resource):
    pass

class ADEWebAPI():
    def __init__(self, url, login, password):
        self.url = url
        self.login = login
        self.password = password
        
        self.sessionId = None
        
        self.logger = logging.getLogger('ADEWebAPI')

    def hide_dict_values(self, d, hidden_keys=['password']):
        """Returns a dictionnary with some hidden values (such as password)
        when a dict is given"""
        d_hidden = d.copy()
        for key in hidden_keys:
            if key in d_hidden.keys():
                d_hidden[key] = hide_string(d_hidden[key])
        return(d_hidden)

    def _send_request(self, func, **params):
        """Send a request"""
        params['function'] = func

        if 'sessionId' not in params.keys():
            if self.sessionId is not None:
                params['sessionId'] = self.sessionId
        
        self.logger.debug("send %s" % self.hide_dict_values(params))
        response = requests.get(self.url, params=params)
        self.logger.debug(response)
        self.logger.debug(response.text)
        element = ET.fromstring(response.text)

        return(element)

    def connect(self):
        """Connect to server"""
        element = self._send_request('connect', login=self.login, password=self.password)
        returned_sessionId = element.attrib["id"]
        self.sessionId = returned_sessionId
        return(returned_sessionId is not None)

    def disconnect(self):
        """Disconnect from server"""
        element = self._send_request('disconnect')
        returned_sessionId = element.attrib["sessionId"]
        return(returned_sessionId == self.sessionId)

    def _list_with_attrib(self, lst):
        return(map(lambda elt: elt.attrib, lst))

    def getProjects(self, detail=None, id=None):
        """Returns (list of) projects"""
        element = self._send_request('getProjects', detail=detail, id=id)
        lst_projects = element.findall('project')
        lst_projects = self._list_with_attrib(lst_projects)
        return(lst_projects)
                
    def setProject(self, projectId):
        """Set current project"""
        element = self._send_request('setProject', projectId=projectId)
        returned_projectId = element.attrib["projectId"]        
        returned_sessionId = element.attrib["sessionId"] 
        return(returned_sessionId == self.sessionId \
            and returned_projectId==str(projectId))

    def getResources(self, **kwargs):
        opt_params = ['tree', 'folders', 'leaves', 'id', 'name', 'category', \
            'type', 'email', 'url', 'size', 'quantity', 'code', 'address1', \
            'address2', 'zipCode', 'state', 'city', 'country', 'telephone', \
            'fax', 'timezone', 'jobCategory', 'manager', 'codeX', 'codeY', \
            'codeZ', 'info', 'detail']
        element = self._send_request('getResources', **kwargs)
        if 'category' in kwargs.keys():
            lst_resources = element.findall(kwargs['category'])
            lst_resources = self._list_with_attrib(lst_resources)
            return(lst_resources)
        else:
            lst_resources = element.findall('resource')
            lst_resources = self._list_with_attrib(lst_resources)
            return(lst_resources)

"""
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


