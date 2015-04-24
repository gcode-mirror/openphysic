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

import pandas as pd

import logging
import logging.config
import traceback
import click
import os

import time

from pyade import ADEWebAPI, hide_string


ENV_VAR_ROOT = 'ADE_WEB_API'


def get_info(key, default_value):
    ENV_VAR_KEY = ENV_VAR_ROOT + "_" + key.upper()
    if default_value=='' or default_value is None:
        try:
            return(os.environ[ENV_VAR_KEY])
        except:
            logging.warning("You should pass %s using --%s or using environment variable %r" % (key, key, ENV_VAR_KEY))
            return(default_value)
    else:
        return(default_value)

@click.command()
@click.option("--url", default="", help="Server URL")
@click.option("--login", default="", help="User login")
@click.option("--password", default="", help="User password")
def main(url, login, password):
    logger = logging.getLogger('ADEWebAPI')
    #logger = logging.getLogger()

    url = get_info('url', url)
    login = get_info('login', login)
    password = get_info('password', password)

    #logger.debug("%s %s %s" % (url, login, hide_string(password)))
    print("%s %s %s" % (url, login, hide_string(password)))

    myade = ADEWebAPI(url, login, password)
    connected = myade.connect()
    print("connected: %s" % connected)

    try:

        projects = myade.getProjects(detail=5) # detail=..., id=...
        print("projects:\n%s" % pd.DataFrame(projects))

        project_set = myade.setProject(5) # 2014-2015=>5
        print("project_set: %s" % project_set)

        #resources = myade.getResources(category='trainee')
        resources = myade.getResources(category='trainee', id=4496)
        print("resources: %s" % resources)

        resources = myade.getResources(name='BC-138')
        #resources = myade.getResources(name='BC-138', not_allowed_parameter='test')
        print("resources: %s" % resources)

        resources = myade.getResources(category='room', name='BC-138')
        print("resources: %s" % resources)

        resources = myade.getResources(category='instructor', name='CELLES SEBASTIEN')
        print("resources: %s" % resources)

        #myade.getTraineeByCode('Z1PT11')
        #myade.getInstructorByName('CELLES SEBASTIEN')
        #myade.getInstructorByCode('4496')
        #myade.getClassrom('Amphi')
        #myade.getActivities()

    except:
        print(traceback.format_exc())

    delay = 5
    print("Wait %d seconds" % delay)
    time.sleep(delay)

    disconnected = myade.disconnect()
    print("disconnected: %s" % disconnected)

if __name__ == "__main__":
    basepath = os.path.dirname(__file__)
    logging.config.fileConfig(os.path.join(basepath, "logging.conf"))
    #logger = logging.getLogger("simpleExample")
    main()
