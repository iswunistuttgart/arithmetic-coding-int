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
# @description: Make plots

import sys
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter
import pandas as pd
import os
import re
from common import *

def readData(path):
    fileList32 = ['perf_AN_32BIT.csv', 'perf_ONES_COMPLEMENT_32BIT.csv',
              'perf_TWOS_COMPLEMENT_32BIT.csv', 'perf_RESIDUE_32BIT.csv']
    fileList64 = ['perf_AN_64BIT.csv', 'perf_ONES_COMPLEMENT_64BIT.csv',
                'perf_TWOS_COMPLEMENT_64BIT.csv', 'perf_RESIDUE_64BIT.csv']
    dfnone32 = pd.read_csv(os.path.join(
        path, 'perf_NONE_32BIT.csv'), delimiter=';')
    dfnone64 = pd.read_csv(os.path.join(
        path, 'perf_NONE_64BIT.csv'), delimiter=';')
    data32 = pd.DataFrame()
    data64 = pd.DataFrame()
    for fl in fileList32:
        dfi = pd.read_csv(os.path.join(path, fl), delimiter=';')
        filename = os.path.basename(fl)
        titel = re.search(r'perf_([\w_\d]+).csv', filename).group(1)
        dfi = dfi.drop(labels=['MAX', 'MIN', 'COUNT','AVG'], axis=1)
        if fl=="perf_RESIDUE_32BIT":
            dfi[titel] = (dfi['MEDIAN']) / dfnone32['MEDIAN']
        else:
            dfi[titel] = (dfi['MEDIAN']+dfnone32['MEDIAN']) / dfnone32['MEDIAN']
        dfi = dfi.drop(labels=['MEDIAN'], axis=1)
        dfi = dfi.replace(
            to_replace=r'TAG_([\w_]+)_START-TAG_[\w_]+_END', value=r'\1', regex=True)
        dfi = dfi.set_index('TAGS')
        data32 = pd.concat([data32, dfi], axis=1)
    for fl in fileList64:
        dfi = pd.read_csv(os.path.join(path, fl), delimiter=';')
        filename = os.path.basename(fl)
        titel = re.search(r'perf_([\w_\d]+).csv', filename).group(1)
        dfi = dfi.drop(labels=['MAX', 'MIN', 'COUNT','AVG'], axis=1)
        if fl=="perf_RESIDUE_64BIT":
            dfi[titel] = (dfi['MEDIAN']) / dfnone64['MEDIAN']
        else:
            dfi[titel] = (dfi['MEDIAN']+dfnone64['MEDIAN']) / dfnone64['MEDIAN']
        dfi = dfi.drop(labels=['MEDIAN'], axis=1)
        dfi = dfi.replace(
            to_replace=r'TAG_([\w_]+)_START-TAG_[\w_]+_END', value=r'\1', regex=True)
        dfi = dfi.set_index('TAGS')
        data64 = pd.concat([data64, dfi], axis=1)
    data32 = data32.rename(columns={"AN_32BIT": "AN 32", "ONES_COMPLEMENT_32BIT": "1's comp. 32",
                        "TWOS_COMPLEMENT_32BIT": "2's comp 32", "RESIDUE_32BIT": "Res. 32"})
    data64 = data64.rename(columns={"AN_64BIT": "AN 64", "ONES_COMPLEMENT_64BIT": "1's comp. 64",
                        "TWOS_COMPLEMENT_64BIT": "2's comp 64", "RESIDUE_64BIT": "Res. 64"})
    print("Head of data ------------- ")
    print(data32.head())
    print(data64.head())
    print("Mean of data ------------- ")
    print(data32.mean().head())
    print(data64.mean().head())
    data32.to_csv(os.path.join(path, "out32.csv"))
    data64.to_csv(os.path.join(path, "out64.csv"))
    return (data32, data64)

def makePlot(data32,data64):
    linew = 0.6
    figure, axes = plt.subplots(2, 1)
    figure.subplots_adjust(wspace=0, hspace=0)
    ax1 = data32.plot.bar(ax=axes[0], width=0.9,edgecolor='k',linewidth=0.3)
    for axis in ['top','bottom','left','right']:
        ax1.spines[axis].set_linewidth(linew)
    leg = ax1.legend(bbox_to_anchor=(0, 1.02, 1, 0.2), loc="upper left",
            mode="expand", borderaxespad=0, ncol=4, prop={'size': 6})
    leg.get_frame().set_edgecolor('k')
    leg.get_frame().set_boxstyle('Round', pad=0, rounding_size=0)
    leg.get_frame().set_linewidth(linew)

    ax2 = data64.plot.bar(ax=axes[1], width=0.9,edgecolor='k',linewidth=0.3)
    for axis in ['top','bottom','left','right']:
        ax2.spines[axis].set_linewidth(linew)
    leg = ax2.legend(bbox_to_anchor=(0, 1.02, 1, 0.2), loc="upper left",
            mode="expand", borderaxespad=0, ncol=4, prop={'size': 6})
    leg.get_frame().set_edgecolor('k')
    leg.get_frame().set_boxstyle('Round', pad=0, rounding_size=0)
    leg.get_frame().set_linewidth(linew)

    
    ax1.set_yscale('log', base=2)
    ax1.yaxis.set_major_formatter(ScalarFormatter())
    ax1.axes.get_xaxis().set_ticks([])
    ax1.axes.set_xlabel(None)
    ax1.axes.set_ylabel("Slowdown")

    ax2.set_yscale('log', base=2)
    ax2.yaxis.set_major_formatter(ScalarFormatter())
    ax2.axes.set_xlabel("Operations")
    ax2.axes.set_ylabel("Slowdown")
    return figure


if __name__ == '__main__':
    
    path = os.path.join(os.getcwd(), sys.argv[1])
    (data32, data64) = readData(path)

    setup_matplotlib()
    figure = makePlot(data32,data64)
    figure.set_size_inches(cm_to_inch(12.5), cm_to_inch(8))
    plt.tight_layout()
    figure.savefig(os.path.join(path, 'perf.png'),
                bbox_inches="tight", dpi=500)
    figure.savefig(os.path.join(path, 'perf.pdf'),
                bbox_inches="tight", dpi=500)
    figure.savefig(os.path.join(path, 'perf.eps'),
               bbox_inches="tight", dpi=500,format='eps')





