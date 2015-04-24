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
from xml.etree import ElementTree as ET
import time

def hide_string(s, char_replace='*'):
    return(char_replace*len(s))

class Project(object):
    pass

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

    def _test_params(self, given_params, opt_params):
        """Test if kwargs parameters are in allowed optional parameters"""
        given_params = set(given_params.keys())
        msg = "One (or many) parameters of '%s' call are not allowed. %s is not in %s" \
            % ('getResources', given_params-opt_params, opt_params)
        assert given_params <= opt_params, msg

    def _list_with_attrib(self, lst):
        """Returns a list of dict (attributes of XML element)"""
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
        opt_params = set(['tree', 'folders', 'leaves', 'id', 'name', 'category', \
            'type', 'email', 'url', 'size', 'quantity', 'code', 'address1', \
            'address2', 'zipCode', 'state', 'city', 'country', 'telephone', \
            'fax', 'timezone', 'jobCategory', 'manager', 'codeX', 'codeY', \
            'codeZ', 'info', 'detail'])
        self._test_params(kwargs, opt_params)
        element = self._send_request('getResources', **kwargs)
        if 'category' in kwargs.keys():
            category = kwargs['category']
        else:
            category = 'resource'
        lst_resources = element.findall(category)
        lst_resources = self._list_with_attrib(lst_resources)
        return(lst_resources)

    def getActivities(self, **kwargs):
        opt_params = set(['tree', 'id', 'name', 'resources', 'type', 'url', \
            'capacity', 'duration', 'repetition', 'code', 'timezone', 'codeX', \
            'codeY', 'codeZ', 'maxSeats', 'seatseLeft', 'info'])
        self._test_params(kwargs, opt_params)
        
    def getEvents(self):
        pass
        
    def getCosts(self):
        pass

    def getCaracteristics(self):
        pass
        
    def getDate(self, week, day, slot):
        pass
