//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/pxr.h"
#include "pxr/usd/usdPhysics/metrics.h"

#include "pxr/usd/usd/stage.h"

#include "pxr/base/tf/pyResultConversions.h"

#include <boost/python/class.hpp>
#include <boost/python/def.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapMetrics()
{
    def("GetStageKilogramsPerUnit", UsdPhysicsGetStageKilogramsPerUnit, 
            arg("stage"));
    def("StageHasAuthoredKilogramsPerUnit", 
            UsdPhysicsStageHasAuthoredKilogramsPerUnit, arg("stage"));
    def("SetStageKilogramsPerUnit", UsdPhysicsSetStageKilogramsPerUnit, 
        (arg("stage"), arg("metersPerUnit")));
    def("MassUnitsAre", UsdPhysicsMassUnitsAre, 
        (arg("authoredUnits"), arg("standardUnits"), arg("epsilon")=1e-5));

    boost::python::class_<UsdPhysicsMassUnits>
        cls("MassUnits", boost::python::no_init);
    cls
        .def_readonly("kilograms", UsdPhysicsMassUnits::kilograms)
        .def_readonly("grams", UsdPhysicsMassUnits::grams)
        .def_readonly("slugs", UsdPhysicsMassUnits::slugs);
}
