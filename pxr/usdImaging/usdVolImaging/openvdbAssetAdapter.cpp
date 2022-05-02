//
// Copyright 2018 Pixar
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
#include "pxr/usdImaging/usdVolImaging/openvdbAssetAdapter.h"

#include "pxr/usdImaging/usdVolImaging/dataSourceFieldAsset.h"
#include "pxr/usdImaging/usdVolImaging/tokens.h"

#include "pxr/usd/usdVol/tokens.h"

#include "pxr/base/tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    typedef UsdImagingOpenVDBAssetAdapter Adapter;
    TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter> >();
    t.SetFactory< UsdImagingPrimAdapterFactory<Adapter> >();
}

UsdImagingOpenVDBAssetAdapter::~UsdImagingOpenVDBAssetAdapter() = default;

TfTokenVector
UsdImagingOpenVDBAssetAdapter::GetImagingSubprims()
{
    return { TfToken() };
}

TfToken
UsdImagingOpenVDBAssetAdapter::GetImagingSubprimType(TfToken const& subprim)
{
    if (subprim.IsEmpty()) {
        return UsdVolImagingTokens->openvdbAsset;
    }
    return TfToken();
}

HdContainerDataSourceHandle
UsdImagingOpenVDBAssetAdapter::GetImagingSubprimData(
        TfToken const& subprim,
        UsdPrim const& prim,
        const UsdImagingDataSourceStageGlobals &stageGlobals)
{
    if (subprim.IsEmpty()) {
        return UsdImagingDataSourceFieldAssetPrim::New(
            prim.GetPath(),
            prim,
            stageGlobals);
    }
    return nullptr;
}

VtValue
UsdImagingOpenVDBAssetAdapter::Get(
    UsdPrim const& prim,
    SdfPath const& cachePath,
    TfToken const& key,
    UsdTimeCode time,
    VtIntArray *outIndices) const
{
    if ( key == UsdVolTokens->filePath ||
         key == UsdVolTokens->fieldName ||
         key == UsdVolTokens->fieldIndex ||
         key == UsdVolTokens->fieldDataType ||
         key == UsdVolTokens->vectorDataRoleHint ||
         key == UsdVolTokens->fieldClass) {
        
        if (UsdAttribute const &attr = prim.GetAttribute(key)) {
            VtValue value;
            if (attr.Get(&value, time)) {
                return value;
            }
        }

        if (key == UsdVolTokens->filePath) {
            return VtValue(SdfAssetPath());
        }
        if (key == UsdVolTokens->fieldIndex) {
            constexpr int def = 0;
            return VtValue(def);
        }

        return VtValue(TfToken());
    }
    
    return
        BaseAdapter::Get(
            prim,
            cachePath,
            key,
            time,
            outIndices);
}

TfToken
UsdImagingOpenVDBAssetAdapter::GetPrimTypeToken() const
{
    return UsdVolImagingTokens->openvdbAsset;
}

PXR_NAMESPACE_CLOSE_SCOPE
