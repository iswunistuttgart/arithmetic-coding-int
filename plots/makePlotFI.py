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
# @description: Make fault injection plots


import pandas as pd
import pathlib
import os
import glob
import matplotlib.pyplot as plt

from common import *


def getfromPath(name:str):
    localPath = pathlib.Path(__file__).parent.resolve()
    filter = os.path.join(localPath,"faultsim-res",name)+"/*.txt"
    files = glob.glob(filter)
    data = pd.DataFrame()
    for fl in files:
        dfi = pd.read_csv(fl, delimiter=',')
        dfi["Masked"] = dfi["TOTAL"] - dfi["ANSUC"] - dfi["ANFAIL"]
        dfi = dfi.rename(columns={"HANGED":"Hang","ANUNEXP":"SDC","ANCRASH":"AC-Detected","OSCRASH":"OS-Detected"})
        dfi = dfi.set_index('PROG')
        data = pd.concat([data, dfi], axis=0)
    print(data.head())
    data = data.groupby(['PROG']).sum().reset_index()
    print(data.head())
    data = data.drop(labels=["TOTAL","NONDIAG","ANFAIL","ANSUC"],axis=1)
    data = data[["PROG","Masked", "AC-Detected", "OS-Detected","Hang","SDC"]]
    data = data.set_index('PROG')
    data = data.rename(index={"val-mul":"Native","val-mul-enc":"AC"})
    data.to_csv(os.path.join(localPath, "fi-"+name+".csv"),index=False)
    return data

def makePlot(fi_perm,fi_trans):
    linew = 0.6
    figure, axes = plt.subplots(1, 2)
    figure.subplots_adjust(wspace=0, hspace=0)

    ax1 = fi_perm.plot.bar(ax=axes[0], width=0.9,edgecolor='k',linewidth=linew,stacked=True)
    ax1.set_title("Permanent fault inj.",fontweight="bold")
    ax1.axes.set_xticklabels(ax1.axes.get_xticklabels(), rotation = 0)
    ax1.axes.get_xaxis().set_label_text("")
    ax2 = fi_trans.plot.bar(ax=axes[1], width=0.9,edgecolor='k',linewidth=linew,stacked=True,legend=None)
    ax2.set_title("Transient fault inj.",fontweight="bold")


    ax2.axes.get_yaxis().set_ticks([])
    ax2.axes.get_xaxis().set_label_text("")
    ax2.axes.set_xticklabels(ax2.axes.get_xticklabels(), rotation = 0)

    
    for axis in ['top','bottom','left','right']:
        ax1.spines[axis].set_linewidth(linew)
        ax2.spines[axis].set_linewidth(linew)
    for axis in ['left','right']:
        ax1.spines[axis].set_linewidth(0)
        ax2.spines[axis].set_linewidth(0)
    ax1.spines['left'].set_linewidth(linew)
    leg = ax1.legend(bbox_to_anchor=(0.04, -0.015, 0.94, 1), loc="upper left",
            mode="expand", borderaxespad=0, ncol=5, prop={'size': 8},bbox_transform = plt.gcf().transFigure)
    leg.get_frame().set_edgecolor('k')
    leg.get_frame().set_boxstyle('Round', pad=0, rounding_size=0)
    leg.get_frame().set_linewidth(linew)
    return figure

if __name__ == '__main__':
   
    d1 = getfromPath("perm")
    d2 = getfromPath("trans")
    setup_matplotlib()
    figure = makePlot(d1,d2)
    figure.set_size_inches(cm_to_inch(12.5), cm_to_inch(8))
    plt.tight_layout()
    figure.savefig(os.path.join(os.getcwd(), 'fi.png'),
                bbox_inches="tight", dpi=500)
    figure.savefig(os.path.join(os.getcwd(), 'fi.pdf'),
                bbox_inches="tight", dpi=500)
    figure.savefig(os.path.join(os.getcwd(), 'fi.eps'),
                bbox_inches="tight", dpi=500,format='eps')
