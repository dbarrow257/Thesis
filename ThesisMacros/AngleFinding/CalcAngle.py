import math

def CalcAngle(LayerName,RadiusToFind):
    RadiusEarth = 6371.0
    Angle = round(math.atan((RadiusToFind/RadiusEarth)),4)
    print(LayerName+": "+str(Angle))

CalcAngle("Inner Core",1220.0)
CalcAngle("Outer Core",3480.0)
CalcAngle("Lower Mantle",5701.0)
CalcAngle("Transition Zone",6371.0)
    
