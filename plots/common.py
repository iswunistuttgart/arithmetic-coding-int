# @copyright: (c) 2022, Institute for Control Engineering of Machine Tools and Manufacturing Units,
#             University of Stuttgart
#             All rights reserved. Licensed under the Apache License, Version 2.0 (the "License");
#             you may not use this file except in compliance with the License.
#             You may obtain a copy of the License at
#                  http://www.apache.org/licenses/LICENSE-2.0
#             Unless required by applicable law or agreed to in writing, software
#             distributed under the License is distributed on an "AS IS" BASIS,
#             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#             See the License for the specific language governing permissions and
#             limitations under the License.
# @author: Marc Fischer <marc.fischer@isw.uni-stuttgart.de>
# @description: Common functions for plots


import pathlib
import matplotlib
import matplotlib.font_manager as font_manager
from cycler import cycler


def cm_to_inch(value):
    return value/2.54

def setup_matplotlib():
    localPath = pathlib.Path(__file__).parent.resolve()
    custom_cycler = (cycler(color=[(0, 0.4470, 0.7410), (0.8500, 0.3250, 0.0980), (0.9290, 0.6940, 0.1250), (0.4940, 0.1840, 0.5560),(0.4660, 0.6740, 0.1880)]))
    font_dirs = [str(localPath)]
    font_files = font_manager.findSystemFonts(fontpaths=font_dirs)
    for font_file in font_files:
        font_manager.fontManager.addfont(font_file)
    matplotlib.rcParams['axes.prop_cycle'] = custom_cycler
    font = {'family': 'Times New Roman',
            'style': 'normal',
            'size': 8}
    matplotlib.rc('font', **font)