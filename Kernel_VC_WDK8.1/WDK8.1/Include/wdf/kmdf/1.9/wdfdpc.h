/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

_WdfVersionBuild_

Module Name:

    wdfdpc.h

Abstract:

    This is the C header for driver frameworks DPC object

Revision History:


--*/

#ifndef _WDFDPC_1_9_H_
#define _WDFDPC_1_9_H_



#if (NTDDI_VERSION >= NTDDI_WIN2K)



//
// This is the function that gets called back into the driver
// when the DPC fires.
//
typedef
_Function_class_(EVT_WDF_DPC)
_IRQL_requires_same_
_IRQL_requires_(DISPATCH_LEVEL)
VOID
EVT_WDF_DPC(
    _In_
    WDFDPC Dpc
    );

typedef EVT_WDF_DPC *PFN_WDF_DPC;

typedef struct _WDF_DPC_CONFIG {
    ULONG       Size;
    PFN_WDF_DPC EvtDpcFunc;

    //
    // If this is TRUE, the DPC will automatically serialize
    // with the event callback handlers of its Parent Object.
    //
    // Parent Object's callback constraints should be compatible
    // with the DPC (DISPATCH_LEVEL), or the request will fail.
    //
    BOOLEAN     AutomaticSerialization;

} WDF_DPC_CONFIG, *PWDF_DPC_CONFIG;

VOID
FORCEINLINE
WDF_DPC_CONFIG_INIT(
    _Out_ PWDF_DPC_CONFIG Config,
    _In_  PFN_WDF_DPC     EvtDpcFunc
    )
{
    RtlZeroMemory(Config, sizeof(WDF_DPC_CONFIG));
    Config->Size = sizeof(WDF_DPC_CONFIG);
    Config->EvtDpcFunc = EvtDpcFunc;

    Config->AutomaticSerialization = TRUE;
}

//
// WDF Function: WdfDpcCreate
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFDPCCREATE)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDF_DPC_CONFIG Config,
    _In_
    PWDF_OBJECT_ATTRIBUTES Attributes,
    _Out_
    WDFDPC* Dpc
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
FORCEINLINE
WdfDpcCreate(
    _In_
    PWDF_DPC_CONFIG Config,
    _In_
    PWDF_OBJECT_ATTRIBUTES Attributes,
    _Out_
    WDFDPC* Dpc
    )
{
    return ((PFN_WDFDPCCREATE) WdfFunctions[WdfDpcCreateTableIndex])(WdfDriverGlobals, Config, Attributes, Dpc);
}

//
// WDF Function: WdfDpcEnqueue
//
typedef
_IRQL_requires_max_(HIGH_LEVEL)
WDFAPI
BOOLEAN
(*PFN_WDFDPCENQUEUE)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDPC Dpc
    );

_IRQL_requires_max_(HIGH_LEVEL)
BOOLEAN
FORCEINLINE
WdfDpcEnqueue(
    _In_
    WDFDPC Dpc
    )
{
    return ((PFN_WDFDPCENQUEUE) WdfFunctions[WdfDpcEnqueueTableIndex])(WdfDriverGlobals, Dpc);
}

//
// WDF Function: WdfDpcCancel
//
typedef
_When_(Wait == __true, _IRQL_requires_max_(PASSIVE_LEVEL))
_When_(Wait == __false, _IRQL_requires_max_(HIGH_LEVEL))
WDFAPI
BOOLEAN
(*PFN_WDFDPCCANCEL)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDPC Dpc,
    _In_
    BOOLEAN Wait
    );

_When_(Wait == __true, _IRQL_requires_max_(PASSIVE_LEVEL))
_When_(Wait == __false, _IRQL_requires_max_(HIGH_LEVEL))
BOOLEAN
FORCEINLINE
WdfDpcCancel(
    _In_
    WDFDPC Dpc,
    _In_
    BOOLEAN Wait
    )
{
    return ((PFN_WDFDPCCANCEL) WdfFunctions[WdfDpcCancelTableIndex])(WdfDriverGlobals, Dpc, Wait);
}

//
// WDF Function: WdfDpcGetParentObject
//
typedef
_IRQL_requires_max_(HIGH_LEVEL)
WDFAPI
WDFOBJECT
(*PFN_WDFDPCGETPARENTOBJECT)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDPC Dpc
    );

_IRQL_requires_max_(HIGH_LEVEL)
WDFOBJECT
FORCEINLINE
WdfDpcGetParentObject(
    _In_
    WDFDPC Dpc
    )
{
    return ((PFN_WDFDPCGETPARENTOBJECT) WdfFunctions[WdfDpcGetParentObjectTableIndex])(WdfDriverGlobals, Dpc);
}

//
// WDF Function: WdfDpcWdmGetDpc
//
typedef
_IRQL_requires_max_(HIGH_LEVEL)
WDFAPI
PKDPC
(*PFN_WDFDPCWDMGETDPC)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDPC Dpc
    );

_IRQL_requires_max_(HIGH_LEVEL)
PKDPC
FORCEINLINE
WdfDpcWdmGetDpc(
    _In_
    WDFDPC Dpc
    )
{
    return ((PFN_WDFDPCWDMGETDPC) WdfFunctions[WdfDpcWdmGetDpcTableIndex])(WdfDriverGlobals, Dpc);
}



#endif // (NTDDI_VERSION >= NTDDI_WIN2K)


#endif // _WDFDPC_1_9_H_
