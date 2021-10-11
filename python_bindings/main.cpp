

#include "slic3rClass.h"

int main()
{
    Slic3rClass s;
    s.loadConfig("config.ini");
    
    s.slice(s.addModel("Long_Trigger.stl"),"out.gcode",0.0,0.0);
    return 0;
} 
