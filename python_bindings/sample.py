import Slic3rModule
m = Slic3rModule.Slic3rModule()
m.addModel("sussane.stl")
m.slice("out.gcode",0,0)
