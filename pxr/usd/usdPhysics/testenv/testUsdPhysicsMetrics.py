#!/pxrpythonsubst
#
# Copyright 2021 Pixar
#
# Licensed under the Apache License, Version 2.0 (the "Apache License")
# with the following modification; you may not use this file except in
# compliance with the Apache License and the following modification to it:
# Section 6. Trademarks. is deleted and replaced with:
#
# 6. Trademarks. This License does not grant permission to use the trade
#    names, trademarks, service marks, or product names of the Licensor
#    and its affiliates, except as required to comply with Section 4(c) of
#    the License and to reproduce the content of the NOTICE file.
#
# You may obtain a copy of the Apache License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the Apache License with the above modification is
# distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the Apache License for the specific
# language governing permissions and limitations under the Apache License.

import sys, os, unittest
from pxr import Tf, Usd, UsdPhysics

class TestUsdPhysicsMetrics(unittest.TestCase):

    def test_kilogramsPerUnit(self):
        stage = Usd.Stage.CreateInMemory()
        self.assertTrue(stage)

        self.assertEqual(UsdPhysics.GetStageKilogramsPerUnit(stage),
                         UsdPhysics.MassUnits.kilograms)
        self.assertFalse(UsdPhysics.StageHasAuthoredKilogramsPerUnit(stage))

        self.assertTrue(UsdPhysics.SetStageKilogramsPerUnit(stage,
                        UsdPhysics.MassUnits.grams))
        self.assertTrue(UsdPhysics.StageHasAuthoredKilogramsPerUnit(stage))
        authored = UsdPhysics.GetStageKilogramsPerUnit(stage)
        self.assertTrue(UsdPhysics.MassUnitsAre(authored, UsdPhysics.MassUnits.grams))


if __name__ == "__main__":
    unittest.main()
