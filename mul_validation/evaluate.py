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
# @description: Calculates the slowdown of the encoded matrix multiplication
import pandas as pd
import pathlib
import os

if __name__ == '__main__':
    localPath = pathlib.Path(__file__).parent.resolve()

    df = pd.read_csv(os.path.join(
        localPath, 'mul100.csv'), delimiter=';')
    dfenc = pd.read_csv(os.path.join(
        localPath, 'mul100-enc.csv'), delimiter=';')

    print(df.head())
    print(dfenc.head())
    slowdown = dfenc['MEDIAN'] / df['MEDIAN']
    print(slowdown.head())

