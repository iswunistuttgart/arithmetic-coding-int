# Making Plots

The documentation asumes a debian based linux distro 

## Requirements
* python 3
  * `apt install python3`
* matplotlib
  * `pip install matplotlib`
* pandas
  * `pip install pandas`

## Make plots
 
 * Run the `execute-perf.sh` from the root dir to generate the performance measurments or use our results in `plots/perf-res`.
 * Than execute `python makePlots.py <path>` the generate the plot. `<path>` is the directory with the timing exports of `execute-perf.sh`
 * The script `makePlotFI.py` generates the plot of the fault simulation with BFI.