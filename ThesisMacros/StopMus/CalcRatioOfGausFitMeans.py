import math

SK4_CV = 2.272
SK4_Err = 0.003

SK5_CV = 2.267
SK5_Err = 0.006

CV = SK4_CV/SK5_CV
Err = CV * math.sqrt(pow(SK4_Err/SK4_CV,2)+pow(SK5_Err/SK5_CV,2))

print("SK4: "+str(SK4_CV)+" +/- "+str(SK4_Err))
print("SK5: "+str(SK5_CV)+" +/- "+str(SK5_Err))
print("Ratio: "+str(CV)+" +/- "+str(Err))
