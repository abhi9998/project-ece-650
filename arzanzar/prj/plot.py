import sys
import statistics
import matplotlib.pyplot as plt
import numpy as np;
ver =[];
avgcnf =[];
devcnf =[];
avgappv1 =[];
devappv1 =[];
avgappv2 =[];
devappv2 =[];
avgratiov1 =[];
devratiov1 =[];
avgratiov2=[];
devratiov2 =[];

while True:
    line = sys.stdin.readline();
    

    if line=='':
        break;
    a = line.split(',');
    ver.append(float(a[0]))
    avgcnf.append(float(a[1]));
    avgappv1.append(float(a[2]));
    avgappv2.append(float(a[3]));
    devcnf.append(float(a[4]));
    devappv1.append(float(a[5]));
    devappv2.append(float(a[6]));
    avgratiov1.append(float(a[7]));
    avgratiov2.append(float(a[8]));
    devratiov1.append(float(a[9]));
    devratiov2.append(float(a[10]));

print(ver)
print(avgcnf);
print(avgappv1);
print(avgappv2);
print(devcnf);
print(devappv1);
print(devappv2);

fig, ax = plt.subplots()
plt.xticks(ver)
ax.errorbar(ver, avgappv1, devappv1,label="Approx-VC-1")
ax.errorbar(ver, avgappv2, devappv2,label="Approx-VC-2")

plt.legend();
fig.autofmt_xdate()
plt.xticks(fontsize=13)
plt.yticks(fontsize=13)
plt.xlabel('No of vertices in input (V)',fontsize=15)
plt.ylabel('Running time (us)',fontsize=15)
plt.title('Mean running time of Approx-VC-1 and Approx-VC-2',fontsize=15)




fig, ax = plt.subplots()
plt.xticks(ver)
ax.errorbar(ver, avgcnf, devcnf,label="CNF-SAT-VC")
ax.ticklabel_format(useOffset=False, style='plain')
# ax.errorbar(ver, np.log10(avgappv1), np.log10(devappv1),label="Approx-VC1")
# ax.errorbar(ver, np.log10(avgappv2), np.log10(devappv2),label="Approx-VC2")
plt.legend();
fig.autofmt_xdate()
fig.set_size_inches(10.5, 6.5, forward=True)
# ax.set_yscale('log')
plt.xticks(fontsize=13)
plt.yticks(fontsize=13)
plt.xlabel('No of vertices in input (V)',fontsize=15)
plt.ylabel('Running time (us)',fontsize=15)
plt.title('Mean running time of CNF-SAT-VC',fontsize=15)





fig, ax = plt.subplots()
plt.xticks(ver[:13])
ax.errorbar(ver[:13], avgcnf[:13], devcnf[:13],label="CNF-SAT-VC")
ax.ticklabel_format(useOffset=False, style='plain')
plt.legend();
fig.autofmt_xdate()
plt.xticks(fontsize=13)
plt.yticks(fontsize=13)
plt.xlabel('No of vertices in input (V)',fontsize=15)
plt.ylabel('Running time (us)',fontsize=15)
plt.title('Mean running time of CNF-SAT for V in [2,14]',fontsize=15)




fig, ax = plt.subplots()
plt.ylim([0, 2.5])
ax.xaxis.set_ticks(ver[:13])
# ax.yaxis.set_ticks(np.arange(-1,3,0.25));
ax.errorbar(ver[:13], avgratiov1[:13], devratiov1[:13],label="Approx-VC-1 ratio")
ax.errorbar(ver[:13], avgratiov2[:13], devratiov2[:13],label="Approx-VC-2 ratio")
plt.legend();
fig.autofmt_xdate()
plt.xticks(fontsize=13)
plt.yticks(fontsize=13)
plt.xlabel('No of vertices in input (V)',fontsize=15)
plt.ylabel('Approximate Ratio (MAR)',fontsize=15)
plt.title('Mean Approximate ratio of  Approx-VC-1 and Approx-VC-2',fontsize=15)

plt.show()

