set(PXR_PREFIX pxr/usdImaging)
set(PXR_PACKAGE usdVolImaging)

pxr_library(usdVolImaging
    LIBRARIES
        usdImaging

    PUBLIC_CLASSES
        dataSourceFieldAsset
        openvdbAssetAdapter
        field3dAssetAdapter
        tokens

    PUBLIC_HEADERS
        api.h

    RESOURCE_FILES
        plugInfo.json
)
