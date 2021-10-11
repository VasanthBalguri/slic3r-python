#include "ConfigBase.hpp"
#include "Geometry.hpp"
#include "IO.hpp"
#include "Model.hpp"
#include "SLAPrint.hpp"
#include "Print.hpp"
#include "TriangleMesh.hpp"
#include "libslic3r.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <math.h>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/nowide/args.hpp>
#include <boost/nowide/iostream.hpp>

struct Slic3rModule{
    DynamicPrintConfig print_config;
    Model model;
    double estimatedMaterial = 0.0;
    double estimatedWeight = 0.0;
    double estimatedCost = 0.0;
    int addModel(std::string path);
    int loadConfig(std::string path);
    void info();
    int center(float x, float y);
    int translate(float x,float y,float z);
    int rotate(float rx,float ry,float rz);
    int scale(float scale);
    int scaleToFit(float x, float y,float z);
    int slice(std::string output_file, float centerX, float centerY);
   int export3MF(std::string path);
    int exportObj(std::string path);
    int exportSvg(std::string path);
    int exportPov(std::string path);
}; 
