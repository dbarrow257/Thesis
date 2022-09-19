import uproot
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams

from energy_bins import *
#from momentum_bins import *

def getMatrix(root_file, matrix_name) :
    return root_file[matrix_name].member("fElements").reshape((root_file[matrix_name].member("fNrows"), root_file[matrix_name].member("fNcols")))

def getCorrelation(covariance) :
    n = len(covariance)
    corr = covariance.copy()

    for i in range(n) :
        for j in range(n) :
            corr[i,j] /= covariance[i,i]**0.5*covariance[j,j]**0.5

    return corr

AX_TITLE_SIZE = 17
AX_LABEL_SIZE = 15

rcParams['font.family'] = 'serif'

fNew = uproot.open("SKJointErrorMatrix2020_Total_fitqun_v4_16042020.root")

bins_Erec = fNew[diag_name].axis().edges()
bins_Erec = bins_Erec[0:45]
hErec_New = np.concatenate([[fNew[diag_name].values()[0]],fNew[diag_name].values()])
hErec_New = hErec_New[0:45]

print(hErec_New)

fig, ax = plt.subplots()
fig.set_figwidth(16)
fig.set_figheight(9)
fig.subplots_adjust(bottom=0.4)
fig.subplots_adjust(top=0.7)
ax.plot(bins_Erec, hErec_New, drawstyle='steps-pre', label='2018 OA')
#ax.plot(bins_Erec, hErec_Old, drawstyle='steps-pre', label='2019/2020 OA', color = (0./255, 119/255., 187./255))
ax.set_xlim(0,len(hErec_New)-1)
ax.set_ylim(-0.05, 1.2)
#plt.yscale('log')
#ax.set_ylabel("Square root of diagonal covariance matrix elements", fontsize = 'large')
plt.yticks(fontsize=AX_LABEL_SIZE)
ax.set_ylabel("$\sqrt{\sigma_{ii}}$", fontsize = AX_TITLE_SIZE, horizontalalignment='right', y=1.0)

print( len(e_comp_tick), len(e_comp_ticklabel))

comp_ax = ax.twiny()
comp_ax.set_xlim(0,len(hErec_New)-1)
ax.set_xticks([i+0.5 for i in range(len(e_labels))] )
ax.set_xticklabels(e_labels, fontsize = AX_LABEL_SIZE)
for tick in ax.get_xticklabels():
        tick.set_rotation(90)
ax.set_xlabel(energy_label, x = 1, ha = 'right', fontsize = AX_TITLE_SIZE)

comp_ax.set_xticks(e_comp_tick)
comp_ax.set_xticklabels(e_comp_ticklabel, fontsize = AX_LABEL_SIZE)
comp_ax.set_xlabel("MC component", x = 1, ha = 'right', fontsize = AX_TITLE_SIZE)
for tick in comp_ax.get_xticklabels():
        tick.set_rotation(90)

sample_ax = ax.twiny()
sample_ax.set_xlim(0,len(hErec_New)-1)
sample_ax.xaxis.set_ticks_position('bottom')
sample_ax.xaxis.set_label_position('bottom')
sample_ax.spines['bottom'].set_position(('outward', 130))

sample_ax.set_xticks(e_sample_tick)
sample_ax.set_xticklabels(e_sample_ticklabel, fontsize = AX_LABEL_SIZE)
sample_ax.set_xlabel("Analysis sample", x = 1, ha = 'right', fontsize = AX_TITLE_SIZE)

sample_in_ax = ax.twiny()
sample_in_ax.set_xlim(0,len(hErec_New)-1)
sample_in_ax.xaxis.set_ticks_position('bottom')
sample_in_ax.xaxis.set_label_position('bottom')
sample_in_ax.spines['bottom'].set_position(('outward', 130))
sample_in_ax.set_xticks(e_sample_in_tick)
sample_in_ax.set_xticklabels(e_sample_in_ticklabel, fontsize = AX_LABEL_SIZE)
sample_in_ax.tick_params(direction = 'in')

for div in comp_divs :
        ax.axvline(x=div, c = '0.5', alpha = 1., ls = '--')

for div in sample_divs :
        ax.axvline(x=div, c = '0.25', alpha = 1., ls = '-')

#plt.tight_layout()
#ax.legend()
plt.savefig('SK_Error_2020_'+out_string+'.pdf', bbox_inches='tight')

plt.show()
