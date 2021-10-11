
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>

#include "slic3rmodule.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(Slic3rModule)
{
    class_<Slic3rModule>("Slic3rModule")
        .def_readonly("model", &Slic3rModule::model)
        .def_readonly("config", &Slic3rModule::print_config)
        .def_readonly("estimatedCost", &Slic3rModule::estimatedCost)
        .def_readonly("estimatedWeight", &Slic3rModule::estimatedWeight)
        .def_readonly("estimatedMaterial", &Slic3rModule::estimatedMaterial)
        .def("loadConfig", &Slic3rModule::loadConfig)
        .def("addModel", &Slic3rModule::addModel)
        .def("slice",&Slic3rModule::slice)
        .def("translate",&Slic3rModule::translate)
        .def("rotate",&Slic3rModule::rotate)
        .def("scale",&Slic3rModule::scale)
        .def("center",&Slic3rModule::center)
        .def("exportFile3MF",&Slic3rModule::export3MF)
        .def("exportFileSVG",&Slic3rModule::exportSvg)
        .def("exportFileObj",&Slic3rModule::exportObj)
        .def("exportFilePOV",&Slic3rModule::exportPov)
        .def("info",&Slic3rModule::info)
    ;
};
