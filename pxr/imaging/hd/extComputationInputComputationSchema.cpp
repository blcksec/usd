//
// Copyright 2021 Pixar
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
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// schema.template.cpp file to make changes.

#include "pxr/imaging/hd/extComputationInputComputationSchema.h"
#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdExtComputationInputComputationSchemaTokens,
    HDEXTCOMPUTATIONINPUTCOMPUTATION_SCHEMA_TOKENS);



HdTokenDataSourceHandle
HdExtComputationInputComputationSchema::GetName()
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdExtComputationInputComputationSchemaTokens->name);
}

HdPathDataSourceHandle
HdExtComputationInputComputationSchema::GetSourceComputation()
{
    return _GetTypedDataSource<HdPathDataSource>(
        HdExtComputationInputComputationSchemaTokens->sourceComputation);
}

HdTokenDataSourceHandle
HdExtComputationInputComputationSchema::GetSourceComputationOutputName()
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdExtComputationInputComputationSchemaTokens->sourceComputationOutputName);
}

/*static*/
HdContainerDataSourceHandle
HdExtComputationInputComputationSchema::BuildRetained(
        const HdTokenDataSourceHandle &name,
        const HdPathDataSourceHandle &sourceComputation,
        const HdTokenDataSourceHandle &sourceComputationOutputName
)
{
    TfToken names[3];
    HdDataSourceBaseHandle values[3];

    size_t count = 0;
    if (name) {
        names[count] = HdExtComputationInputComputationSchemaTokens->name;
        values[count++] = name;
    }

    if (sourceComputation) {
        names[count] = HdExtComputationInputComputationSchemaTokens->sourceComputation;
        values[count++] = sourceComputation;
    }

    if (sourceComputationOutputName) {
        names[count] = HdExtComputationInputComputationSchemaTokens->sourceComputationOutputName;
        values[count++] = sourceComputationOutputName;
    }

    return HdRetainedContainerDataSource::New(count, names, values);
}


HdExtComputationInputComputationSchema::Builder &
HdExtComputationInputComputationSchema::Builder::SetName(
    const HdTokenDataSourceHandle &name)
{
    _name = name;
    return *this;
}

HdExtComputationInputComputationSchema::Builder &
HdExtComputationInputComputationSchema::Builder::SetSourceComputation(
    const HdPathDataSourceHandle &sourceComputation)
{
    _sourceComputation = sourceComputation;
    return *this;
}

HdExtComputationInputComputationSchema::Builder &
HdExtComputationInputComputationSchema::Builder::SetSourceComputationOutputName(
    const HdTokenDataSourceHandle &sourceComputationOutputName)
{
    _sourceComputationOutputName = sourceComputationOutputName;
    return *this;
}

HdContainerDataSourceHandle
HdExtComputationInputComputationSchema::Builder::Build()
{
    return HdExtComputationInputComputationSchema::BuildRetained(
        _name,
        _sourceComputation,
        _sourceComputationOutputName
    );
}


PXR_NAMESPACE_CLOSE_SCOPE