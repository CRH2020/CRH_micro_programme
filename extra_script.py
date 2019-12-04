from os import path
import sys
from os import environ

import mbedignore

Import("env")

ROOT_DIR = env['PROJECT_DIR']

mbedignore_path = path.join(ROOT_DIR, '.mbedignore')
mbed_os_dir = 'C:/Users/Nathan/.platformio/packages/framework-mbed'

# Does the job related to ignoring the paths. 
mbedignore.apply(mbedignore_path, mbed_os_dir)