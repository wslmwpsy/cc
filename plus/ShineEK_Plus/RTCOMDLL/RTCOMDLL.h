

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Tue Dec 11 18:32:46 2007
 */
/* Compiler settings for RTCOMDLL.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RTCOMDLL_h__
#define __RTCOMDLL_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPropSet_FWD_DEFINED__
#define __IPropSet_FWD_DEFINED__
typedef interface IPropSet IPropSet;
#endif 	/* __IPropSet_FWD_DEFINED__ */


#ifndef __IABIT_FWD_DEFINED__
#define __IABIT_FWD_DEFINED__
typedef interface IABIT IABIT;
#endif 	/* __IABIT_FWD_DEFINED__ */


#ifndef __ISONY_FWD_DEFINED__
#define __ISONY_FWD_DEFINED__
typedef interface ISONY ISONY;
#endif 	/* __ISONY_FWD_DEFINED__ */


#ifndef __IRTLCSSAPI_FWD_DEFINED__
#define __IRTLCSSAPI_FWD_DEFINED__
typedef interface IRTLCSSAPI IRTLCSSAPI;
#endif 	/* __IRTLCSSAPI_FWD_DEFINED__ */


#ifndef __IPropSet10059_FWD_DEFINED__
#define __IPropSet10059_FWD_DEFINED__
typedef interface IPropSet10059 IPropSet10059;
#endif 	/* __IPropSet10059_FWD_DEFINED__ */


#ifndef __IPropSet10060_FWD_DEFINED__
#define __IPropSet10060_FWD_DEFINED__
typedef interface IPropSet10060 IPropSet10060;
#endif 	/* __IPropSet10060_FWD_DEFINED__ */


#ifndef __IPropSet10061_FWD_DEFINED__
#define __IPropSet10061_FWD_DEFINED__
typedef interface IPropSet10061 IPropSet10061;
#endif 	/* __IPropSet10061_FWD_DEFINED__ */


#ifndef __IPropSet10063_FWD_DEFINED__
#define __IPropSet10063_FWD_DEFINED__
typedef interface IPropSet10063 IPropSet10063;
#endif 	/* __IPropSet10063_FWD_DEFINED__ */


#ifndef __IPropSet20065_FWD_DEFINED__
#define __IPropSet20065_FWD_DEFINED__
typedef interface IPropSet20065 IPropSet20065;
#endif 	/* __IPropSet20065_FWD_DEFINED__ */


#ifndef __IPropSet20066_FWD_DEFINED__
#define __IPropSet20066_FWD_DEFINED__
typedef interface IPropSet20066 IPropSet20066;
#endif 	/* __IPropSet20066_FWD_DEFINED__ */


#ifndef __IPropSet20068_FWD_DEFINED__
#define __IPropSet20068_FWD_DEFINED__
typedef interface IPropSet20068 IPropSet20068;
#endif 	/* __IPropSet20068_FWD_DEFINED__ */


#ifndef __IPropSet20069_FWD_DEFINED__
#define __IPropSet20069_FWD_DEFINED__
typedef interface IPropSet20069 IPropSet20069;
#endif 	/* __IPropSet20069_FWD_DEFINED__ */


#ifndef __IPropSet20070_FWD_DEFINED__
#define __IPropSet20070_FWD_DEFINED__
typedef interface IPropSet20070 IPropSet20070;
#endif 	/* __IPropSet20070_FWD_DEFINED__ */


#ifndef __IPropSet20072_FWD_DEFINED__
#define __IPropSet20072_FWD_DEFINED__
typedef interface IPropSet20072 IPropSet20072;
#endif 	/* __IPropSet20072_FWD_DEFINED__ */


#ifndef __IPropSet20080_FWD_DEFINED__
#define __IPropSet20080_FWD_DEFINED__
typedef interface IPropSet20080 IPropSet20080;
#endif 	/* __IPropSet20080_FWD_DEFINED__ */


#ifndef __IPropSet20082_FWD_DEFINED__
#define __IPropSet20082_FWD_DEFINED__
typedef interface IPropSet20082 IPropSet20082;
#endif 	/* __IPropSet20082_FWD_DEFINED__ */


#ifndef __IPropSet20083_FWD_DEFINED__
#define __IPropSet20083_FWD_DEFINED__
typedef interface IPropSet20083 IPropSet20083;
#endif 	/* __IPropSet20083_FWD_DEFINED__ */


#ifndef __IPropSet20086_FWD_DEFINED__
#define __IPropSet20086_FWD_DEFINED__
typedef interface IPropSet20086 IPropSet20086;
#endif 	/* __IPropSet20086_FWD_DEFINED__ */


#ifndef __PropSet_FWD_DEFINED__
#define __PropSet_FWD_DEFINED__

#ifdef __cplusplus
typedef class PropSet PropSet;
#else
typedef struct PropSet PropSet;
#endif /* __cplusplus */

#endif 	/* __PropSet_FWD_DEFINED__ */


#ifndef __ABIT_FWD_DEFINED__
#define __ABIT_FWD_DEFINED__

#ifdef __cplusplus
typedef class ABIT ABIT;
#else
typedef struct ABIT ABIT;
#endif /* __cplusplus */

#endif 	/* __ABIT_FWD_DEFINED__ */


#ifndef __SONY_FWD_DEFINED__
#define __SONY_FWD_DEFINED__

#ifdef __cplusplus
typedef class SONY SONY;
#else
typedef struct SONY SONY;
#endif /* __cplusplus */

#endif 	/* __SONY_FWD_DEFINED__ */


#ifndef __RTLCSSAPI_FWD_DEFINED__
#define __RTLCSSAPI_FWD_DEFINED__

#ifdef __cplusplus
typedef class RTLCSSAPI RTLCSSAPI;
#else
typedef struct RTLCSSAPI RTLCSSAPI;
#endif /* __cplusplus */

#endif 	/* __RTLCSSAPI_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_RTCOMDLL_0000 */
/* [local] */ 

typedef void *HANDLE;



extern RPC_IF_HANDLE __MIDL_itf_RTCOMDLL_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RTCOMDLL_0000_v0_0_s_ifspec;

#ifndef __IPropSet_INTERFACE_DEFINED__
#define __IPropSet_INTERFACE_DEFINED__

/* interface IPropSet */
/* [unique][helpstring][dual][uuid][object] */ 

typedef struct _HDAUDIOSUPPORTFORMAT
    {
    DWORD dwSampleRate;
    DWORD wSupportChannelMode;
    } 	HDAudioSupportFormat;

typedef struct _HDAUDIOSUPPORTFORMAT HDAudioFormatChannel;

typedef struct _SwDrcProperties
    {
    BOOL fEnable;
    LONG PeakDetectAttackTime;
    LONG PeakDetectReleaseTime;
    LONG LMGSAttackTime;
    LONG LMGSReleaseTime;
    LONG LookAheadTime;
    LONG LimiterThreshold;
    LONG OutputGain;
    LONG InputGain;
    } 	SWDRCPROPERTIES;


EXTERN_C const IID IID_IPropSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CF743829-4C33-457D-82CB-A00DE3308CD5")
    IPropSet : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetChannelNum( 
            /* [in] */ long Num) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMaxChannelNum( 
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelNum( 
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontHeadPhoneOuputMode( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontMicInOutputMode( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRearLineInOutputMode( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRearMicInOutputMode( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontHeadPhoneUAJOutputMode( 
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontMicInUAJOutputMode( 
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontMicInUAJDeviceMode( 
            /* [in] */ long DeviceType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontHeadPhoneUAJDeviceMode( 
            /* [in] */ long DeviceType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRearLineInOutputMode( 
            /* [in] */ BOOL InOutMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRearMicInOutputMode( 
            /* [in] */ BOOL InOutMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCenLfeSwapStatus( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCenLfeSwapStatus( 
            /* [in] */ BOOL bStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontHPTunOnRearSpeaker( 
            /* [in] */ BOOL Enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontHPTunOnRearSpeaker( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAC3SupportStatus( 
            /* [out] */ WORD *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisableUpMixing( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDisableUpMixing( 
            /* [in] */ BOOL Enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMaxDSBufferChannels( 
            /* [out] */ WORD *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get2DEngineStatus( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisableAudioWizard( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseAudioWizard( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set2DEngineStatus( 
            /* [in] */ BOOL Enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get3DBufferEnabled( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get3DEAXEnabled( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSVIDValue( 
            /* [out] */ DWORD *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSSIDValue( 
            /* [out] */ DWORD *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateSaveWaveFile( 
            /* [in] */ ULONG node,
            /* [in] */ LPSTR pszFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseSaveWaveFile( 
            /* [in] */ ULONG node) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableSaveWaveFile( 
            /* [in] */ ULONG node,
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCreatedSaveWaveFile( 
            /* [in] */ ULONG node,
            /* [in] */ LPSTR pszFileName,
            /* [in] */ DWORD dwBufSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSaveWaveStatus( 
            /* [in] */ ULONG node,
            /* [out] */ BOOL *pfEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSaveWaveOverflow( 
            /* [in] */ ULONG node,
            /* [out] */ BOOL *pfOverflow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyPL2Enable( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyPL2Enable( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyHPEnable( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyHPEnable( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyVSEnable( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyVSEnable( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyPL2Panorama( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyPL2Panorama( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyPL2Mode( 
            /* [out] */ ULONG *pMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyPL2Mode( 
            /* [in] */ ULONG Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyPL2Dimension( 
            /* [out] */ ULONG *pDim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyPL2Dimension( 
            /* [in] */ ULONG Dim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyPL2CenterWidth( 
            /* [out] */ ULONG *pCenterWidth) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyPL2CenterWidth( 
            /* [in] */ ULONG CenterWidth) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyHPRoom( 
            /* [out] */ ULONG *pRoom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyHPRoom( 
            /* [in] */ ULONG Room) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyVSRoom( 
            /* [out] */ ULONG *pRoom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyVSRoom( 
            /* [in] */ ULONG Room) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBassManagement( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBassManagement( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSubwooferEnable( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSubwooferEnable( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSendBass2Sub( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSendBass2Sub( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCenterDelay( 
            /* [out] */ LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCenterDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSubwooferDelay( 
            /* [out] */ LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSubwooferDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRearLeftDelay( 
            /* [out] */ LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRearLeftDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRearRightDelay( 
            /* [out] */ LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRearRightDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontLeftTrim( 
            /* [out] */ LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontLeftTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontRightTrim( 
            /* [out] */ LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontRightTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCenterTrim( 
            /* [out] */ LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCenterTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSubwooferTrim( 
            /* [out] */ LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSubwooferTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRearLeftTrim( 
            LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRearLeftTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRearRightTrim( 
            /* [out] */ LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRearRightTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFullRangeFrontSpeaker( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFullRangeFrontSpeaker( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyPL2XMode( 
            /* [out] */ BOOL *pfIsPL2XMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSideLeftDelay( 
            /* [out] */ LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSideLeftDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSideRightDelay( 
            LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSideRightDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSideLeftTrim( 
            /* [out] */ LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSideLeftTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSideRightTrim( 
            /* [out] */ LONG *pTrim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSideRightTrim( 
            /* [in] */ LONG Trim) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDriverModel( 
            /* [out] */ BOOL *bDModel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontMicDevType( 
            /* [out] */ ULONG *ulDeviceType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontMicDevType( 
            /* [in] */ ULONG ulDeviceType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontLineInDevType( 
            /* [out] */ ULONG *ulDeviceType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontLineInDevType( 
            /* [in] */ ULONG ulDeviceType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLineIn1MuteState( 
            /* [out] */ BOOL *bMuteState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLineIn1MuteState( 
            /* [in] */ BOOL bMuteState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLineIn2MuteState( 
            /* [out] */ BOOL *bMuteState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLineIn2MuteState( 
            /* [in] */ BOOL bMuteState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMultiStreamState( 
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDTSSupportStatus( 
            /* [out] */ WORD *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDtsNeoEnable( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDtsNeoEnable( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDtsNeoMode( 
            /* [out] */ ULONG *pMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDtsNeoMode( 
            /* [in] */ ULONG Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDtsNeoCenterGain( 
            /* [out] */ ULONG *pCenterGain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDtsNeoCenterGain( 
            /* [in] */ ULONG CenterGain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontLineInSupportDevType( 
            /* [out] */ ULONG *ulSuDevType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontMicSupportDevType( 
            /* [out] */ ULONG *ulSuDevType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEaxIndex( 
            /* [out] */ long *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEAXIndex( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBbeEnable( 
            /* [out] */ BOOL *pfEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBbeEnable( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBbeSpkMode( 
            /* [out] */ ULONG *pMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBbeSpkMode( 
            /* [in] */ ULONG Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLibVersionTableSize( 
            /* [out] */ ULONG *pSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLibVersionTable( 
            /* [out] */ ULONG *pTable,
            /* [in] */ ULONG Size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyEvent( 
            /* [in] */ ULONG hEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveDolbyEvent( 
            /* [in] */ ULONG hEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontLeftDelay( 
            /* [out] */ LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontLeftDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFrontRightDelay( 
            /* [out] */ LONG *pDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrontRightDelay( 
            /* [in] */ LONG Delay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyDownMix( 
            /* [out] */ BOOL *bIsDownMix) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyDownMix( 
            /* [in] */ BOOL bIsDownMix) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDolbyDLiveAutoOverride( 
            /* [out] */ BOOL *bIsAutoOverride) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDolbyDLiveAutoOverride( 
            /* [in] */ BOOL bIsAutoOverride) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBassManagementMode( 
            /* [out] */ ULONG *ulMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBassManagementMode( 
            /* [in] */ ULONG ulMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDBDelayScale( 
            /* [out] */ LONG *lScale) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDBDelayScale( 
            /* [in] */ LONG lScale) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDBDelayDistance( 
            /* [in] */ LONG lSpeaker,
            /* [out] */ float *fDistance) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDBDelayDistance( 
            /* [in] */ LONG lSpeaker,
            /* [in] */ float fDistance) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetASUSMicState( 
            /* [out] */ WORD *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetASUSMicState( 
            /* [in] */ WORD wValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQReset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQLevel( 
            /* [in] */ long Index,
            /* [in] */ long SetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEQLevel( 
            /* [in] */ long Index,
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEQIndex( 
            /* [out] */ long *RtnValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQIndex( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEQEnable( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQEnable( 
            /* [in] */ BOOL Enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVoiceCancelStatus( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVoiceCancelStatus( 
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetKaraokePitch( 
            /* [out] */ LONG *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetKaraokePitch( 
            /* [in] */ LONG lValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEQCenter( 
            /* [in] */ long Index,
            /* [out] */ long *lRetrunVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQCenter( 
            /* [in] */ long Index,
            /* [in] */ long lSetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEQBandwidth( 
            /* [in] */ long Index,
            /* [out] */ long *lReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQBandwidth( 
            /* [in] */ long Index,
            /* [in] */ long lSetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSWEQ( 
            /* [in] */ long lIndex,
            /* [out] */ long *lGain,
            /* [out] */ long *lFrequency,
            /* [out] */ long *lBandwidth,
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSWEQ( 
            /* [in] */ long lIndex,
            /* [in] */ long lGain,
            /* [in] */ long lFrequency,
            /* [in] */ long lBandwidth,
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetSWEQ( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartHDAudioAuthentication( 
            /* [size_is][in] */ BYTE *pR1,
            /* [size_is][out] */ BYTE *pClientAuthData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FinishHDAudioAuthentication( 
            /* [size_is][in] */ BYTE *pServerAuthData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHDAudioSupportedFormatNumber( 
            /* [out] */ DWORD *Count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHDAudioSupportedFormat( 
            /* [size_is][out] */ BYTE *pFormat,
            /* [in] */ DWORD Count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAcerPowerManagement( 
            /* [out] */ DWORD *dwData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAcerPowerManagement( 
            /* [in] */ DWORD dwData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSWEQLoudness( 
            /* [out] */ BOOL *bEnable,
            /* [out] */ long *ldB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSWEQLoudness( 
            /* [in] */ BOOL bEnable,
            /* [in] */ long ldB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAPHandleAndMessage( 
            /* [in] */ HWND hWnd,
            /* [in] */ DWORD dwMessage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPinPlugState( 
            /* [in] */ ULONG ulPinName,
            /* [out] */ BOOL *bPlugState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetHDAudioSupportedFormat( 
            /* [in] */ HDAudioSupportFormat SetFormat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSWDrc( 
            /* [out] */ SWDRCPROPERTIES *pSWDRC) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSWDrc( 
            /* [in] */ SWDRCPROPERTIES pSWDRC) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetHDAudioStop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetHDAudioDisable( 
            /* [in] */ BOOL bState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartCBLKHDAudioAuthentication( 
            /* [size_is][in] */ BYTE *pStartBlockKsKc,
            /* [size_is][out] */ BYTE *pStartBlockRsFc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FinishCBLKHDAudioAuthentication( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCBLKHDAudioSupportedFormat( 
            /* [size_is][out] */ BYTE *pFormat,
            /* [in] */ DWORD Count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCBLKHDAudioSupportedFormatNumber( 
            /* [out] */ DWORD *Count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCBLKHDAudioSupportedFormat( 
            /* [in] */ HDAudioSupportFormat SetFormat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCBLKHDAudioStop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDockOrUndock( 
            /* [in] */ ULONG bDock) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMicNoiseSuppressionSupported( 
            /* [out] */ BOOL *bSupported) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMicNoiseSuppression( 
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMicNoiseSuppression( 
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMicBeamFormingSupported( 
            /* [out] */ BOOL *bSupported) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMicBeamForming( 
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMicBeamForming( 
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMicAECSupported( 
            /* [out] */ BOOL *bSupported) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMicAEC( 
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMicAEC( 
            /* [in] */ BOOL bEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetChannelNum )( 
            IPropSet * This,
            /* [in] */ long Num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMaxChannelNum )( 
            IPropSet * This,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelNum )( 
            IPropSet * This,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontHeadPhoneOuputMode )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontMicInOutputMode )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRearLineInOutputMode )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRearMicInOutputMode )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontHeadPhoneUAJOutputMode )( 
            IPropSet * This,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontMicInUAJOutputMode )( 
            IPropSet * This,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontMicInUAJDeviceMode )( 
            IPropSet * This,
            /* [in] */ long DeviceType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontHeadPhoneUAJDeviceMode )( 
            IPropSet * This,
            /* [in] */ long DeviceType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRearLineInOutputMode )( 
            IPropSet * This,
            /* [in] */ BOOL InOutMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRearMicInOutputMode )( 
            IPropSet * This,
            /* [in] */ BOOL InOutMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCenLfeSwapStatus )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCenLfeSwapStatus )( 
            IPropSet * This,
            /* [in] */ BOOL bStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontHPTunOnRearSpeaker )( 
            IPropSet * This,
            /* [in] */ BOOL Enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontHPTunOnRearSpeaker )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAC3SupportStatus )( 
            IPropSet * This,
            /* [out] */ WORD *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisableUpMixing )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDisableUpMixing )( 
            IPropSet * This,
            /* [in] */ BOOL Enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMaxDSBufferChannels )( 
            IPropSet * This,
            /* [out] */ WORD *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get2DEngineStatus )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisableAudioWizard )( 
            IPropSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseAudioWizard )( 
            IPropSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Set2DEngineStatus )( 
            IPropSet * This,
            /* [in] */ BOOL Enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get3DBufferEnabled )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get3DEAXEnabled )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSVIDValue )( 
            IPropSet * This,
            /* [out] */ DWORD *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSSIDValue )( 
            IPropSet * This,
            /* [out] */ DWORD *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateSaveWaveFile )( 
            IPropSet * This,
            /* [in] */ ULONG node,
            /* [in] */ LPSTR pszFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseSaveWaveFile )( 
            IPropSet * This,
            /* [in] */ ULONG node);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableSaveWaveFile )( 
            IPropSet * This,
            /* [in] */ ULONG node,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCreatedSaveWaveFile )( 
            IPropSet * This,
            /* [in] */ ULONG node,
            /* [in] */ LPSTR pszFileName,
            /* [in] */ DWORD dwBufSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSaveWaveStatus )( 
            IPropSet * This,
            /* [in] */ ULONG node,
            /* [out] */ BOOL *pfEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSaveWaveOverflow )( 
            IPropSet * This,
            /* [in] */ ULONG node,
            /* [out] */ BOOL *pfOverflow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyPL2Enable )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyPL2Enable )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyHPEnable )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyHPEnable )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyVSEnable )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyVSEnable )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyPL2Panorama )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyPL2Panorama )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyPL2Mode )( 
            IPropSet * This,
            /* [out] */ ULONG *pMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyPL2Mode )( 
            IPropSet * This,
            /* [in] */ ULONG Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyPL2Dimension )( 
            IPropSet * This,
            /* [out] */ ULONG *pDim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyPL2Dimension )( 
            IPropSet * This,
            /* [in] */ ULONG Dim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyPL2CenterWidth )( 
            IPropSet * This,
            /* [out] */ ULONG *pCenterWidth);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyPL2CenterWidth )( 
            IPropSet * This,
            /* [in] */ ULONG CenterWidth);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyHPRoom )( 
            IPropSet * This,
            /* [out] */ ULONG *pRoom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyHPRoom )( 
            IPropSet * This,
            /* [in] */ ULONG Room);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyVSRoom )( 
            IPropSet * This,
            /* [out] */ ULONG *pRoom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyVSRoom )( 
            IPropSet * This,
            /* [in] */ ULONG Room);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBassManagement )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBassManagement )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSubwooferEnable )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSubwooferEnable )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSendBass2Sub )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSendBass2Sub )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCenterDelay )( 
            IPropSet * This,
            /* [out] */ LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCenterDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSubwooferDelay )( 
            IPropSet * This,
            /* [out] */ LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSubwooferDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRearLeftDelay )( 
            IPropSet * This,
            /* [out] */ LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRearLeftDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRearRightDelay )( 
            IPropSet * This,
            /* [out] */ LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRearRightDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontLeftTrim )( 
            IPropSet * This,
            /* [out] */ LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontLeftTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontRightTrim )( 
            IPropSet * This,
            /* [out] */ LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontRightTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCenterTrim )( 
            IPropSet * This,
            /* [out] */ LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCenterTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSubwooferTrim )( 
            IPropSet * This,
            /* [out] */ LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSubwooferTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRearLeftTrim )( 
            IPropSet * This,
            LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRearLeftTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRearRightTrim )( 
            IPropSet * This,
            /* [out] */ LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRearRightTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFullRangeFrontSpeaker )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFullRangeFrontSpeaker )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyPL2XMode )( 
            IPropSet * This,
            /* [out] */ BOOL *pfIsPL2XMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSideLeftDelay )( 
            IPropSet * This,
            /* [out] */ LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSideLeftDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSideRightDelay )( 
            IPropSet * This,
            LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSideRightDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSideLeftTrim )( 
            IPropSet * This,
            /* [out] */ LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSideLeftTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSideRightTrim )( 
            IPropSet * This,
            /* [out] */ LONG *pTrim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSideRightTrim )( 
            IPropSet * This,
            /* [in] */ LONG Trim);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDriverModel )( 
            IPropSet * This,
            /* [out] */ BOOL *bDModel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontMicDevType )( 
            IPropSet * This,
            /* [out] */ ULONG *ulDeviceType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontMicDevType )( 
            IPropSet * This,
            /* [in] */ ULONG ulDeviceType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontLineInDevType )( 
            IPropSet * This,
            /* [out] */ ULONG *ulDeviceType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontLineInDevType )( 
            IPropSet * This,
            /* [in] */ ULONG ulDeviceType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLineIn1MuteState )( 
            IPropSet * This,
            /* [out] */ BOOL *bMuteState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLineIn1MuteState )( 
            IPropSet * This,
            /* [in] */ BOOL bMuteState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLineIn2MuteState )( 
            IPropSet * This,
            /* [out] */ BOOL *bMuteState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLineIn2MuteState )( 
            IPropSet * This,
            /* [in] */ BOOL bMuteState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMultiStreamState )( 
            IPropSet * This,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDTSSupportStatus )( 
            IPropSet * This,
            /* [out] */ WORD *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDtsNeoEnable )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDtsNeoEnable )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDtsNeoMode )( 
            IPropSet * This,
            /* [out] */ ULONG *pMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDtsNeoMode )( 
            IPropSet * This,
            /* [in] */ ULONG Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDtsNeoCenterGain )( 
            IPropSet * This,
            /* [out] */ ULONG *pCenterGain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDtsNeoCenterGain )( 
            IPropSet * This,
            /* [in] */ ULONG CenterGain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontLineInSupportDevType )( 
            IPropSet * This,
            /* [out] */ ULONG *ulSuDevType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontMicSupportDevType )( 
            IPropSet * This,
            /* [out] */ ULONG *ulSuDevType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEaxIndex )( 
            IPropSet * This,
            /* [out] */ long *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEAXIndex )( 
            IPropSet * This,
            /* [in] */ long Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBbeEnable )( 
            IPropSet * This,
            /* [out] */ BOOL *pfEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBbeEnable )( 
            IPropSet * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBbeSpkMode )( 
            IPropSet * This,
            /* [out] */ ULONG *pMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBbeSpkMode )( 
            IPropSet * This,
            /* [in] */ ULONG Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLibVersionTableSize )( 
            IPropSet * This,
            /* [out] */ ULONG *pSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLibVersionTable )( 
            IPropSet * This,
            /* [out] */ ULONG *pTable,
            /* [in] */ ULONG Size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyEvent )( 
            IPropSet * This,
            /* [in] */ ULONG hEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveDolbyEvent )( 
            IPropSet * This,
            /* [in] */ ULONG hEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontLeftDelay )( 
            IPropSet * This,
            /* [out] */ LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontLeftDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFrontRightDelay )( 
            IPropSet * This,
            /* [out] */ LONG *pDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFrontRightDelay )( 
            IPropSet * This,
            /* [in] */ LONG Delay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyDownMix )( 
            IPropSet * This,
            /* [out] */ BOOL *bIsDownMix);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyDownMix )( 
            IPropSet * This,
            /* [in] */ BOOL bIsDownMix);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDolbyDLiveAutoOverride )( 
            IPropSet * This,
            /* [out] */ BOOL *bIsAutoOverride);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDolbyDLiveAutoOverride )( 
            IPropSet * This,
            /* [in] */ BOOL bIsAutoOverride);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBassManagementMode )( 
            IPropSet * This,
            /* [out] */ ULONG *ulMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBassManagementMode )( 
            IPropSet * This,
            /* [in] */ ULONG ulMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDBDelayScale )( 
            IPropSet * This,
            /* [out] */ LONG *lScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDBDelayScale )( 
            IPropSet * This,
            /* [in] */ LONG lScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDBDelayDistance )( 
            IPropSet * This,
            /* [in] */ LONG lSpeaker,
            /* [out] */ float *fDistance);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDBDelayDistance )( 
            IPropSet * This,
            /* [in] */ LONG lSpeaker,
            /* [in] */ float fDistance);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetASUSMicState )( 
            IPropSet * This,
            /* [out] */ WORD *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetASUSMicState )( 
            IPropSet * This,
            /* [in] */ WORD wValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQReset )( 
            IPropSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQLevel )( 
            IPropSet * This,
            /* [in] */ long Index,
            /* [in] */ long SetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEQLevel )( 
            IPropSet * This,
            /* [in] */ long Index,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEQIndex )( 
            IPropSet * This,
            /* [out] */ long *RtnValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQIndex )( 
            IPropSet * This,
            /* [in] */ long Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEQEnable )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQEnable )( 
            IPropSet * This,
            /* [in] */ BOOL Enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVoiceCancelStatus )( 
            IPropSet * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVoiceCancelStatus )( 
            IPropSet * This,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetKaraokePitch )( 
            IPropSet * This,
            /* [out] */ LONG *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetKaraokePitch )( 
            IPropSet * This,
            /* [in] */ LONG lValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEQCenter )( 
            IPropSet * This,
            /* [in] */ long Index,
            /* [out] */ long *lRetrunVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQCenter )( 
            IPropSet * This,
            /* [in] */ long Index,
            /* [in] */ long lSetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEQBandwidth )( 
            IPropSet * This,
            /* [in] */ long Index,
            /* [out] */ long *lReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQBandwidth )( 
            IPropSet * This,
            /* [in] */ long Index,
            /* [in] */ long lSetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSWEQ )( 
            IPropSet * This,
            /* [in] */ long lIndex,
            /* [out] */ long *lGain,
            /* [out] */ long *lFrequency,
            /* [out] */ long *lBandwidth,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSWEQ )( 
            IPropSet * This,
            /* [in] */ long lIndex,
            /* [in] */ long lGain,
            /* [in] */ long lFrequency,
            /* [in] */ long lBandwidth,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetSWEQ )( 
            IPropSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartHDAudioAuthentication )( 
            IPropSet * This,
            /* [size_is][in] */ BYTE *pR1,
            /* [size_is][out] */ BYTE *pClientAuthData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FinishHDAudioAuthentication )( 
            IPropSet * This,
            /* [size_is][in] */ BYTE *pServerAuthData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHDAudioSupportedFormatNumber )( 
            IPropSet * This,
            /* [out] */ DWORD *Count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHDAudioSupportedFormat )( 
            IPropSet * This,
            /* [size_is][out] */ BYTE *pFormat,
            /* [in] */ DWORD Count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAcerPowerManagement )( 
            IPropSet * This,
            /* [out] */ DWORD *dwData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAcerPowerManagement )( 
            IPropSet * This,
            /* [in] */ DWORD dwData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSWEQLoudness )( 
            IPropSet * This,
            /* [out] */ BOOL *bEnable,
            /* [out] */ long *ldB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSWEQLoudness )( 
            IPropSet * This,
            /* [in] */ BOOL bEnable,
            /* [in] */ long ldB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAPHandleAndMessage )( 
            IPropSet * This,
            /* [in] */ HWND hWnd,
            /* [in] */ DWORD dwMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPinPlugState )( 
            IPropSet * This,
            /* [in] */ ULONG ulPinName,
            /* [out] */ BOOL *bPlugState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetHDAudioSupportedFormat )( 
            IPropSet * This,
            /* [in] */ HDAudioSupportFormat SetFormat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSWDrc )( 
            IPropSet * This,
            /* [out] */ SWDRCPROPERTIES *pSWDRC);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSWDrc )( 
            IPropSet * This,
            /* [in] */ SWDRCPROPERTIES pSWDRC);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetHDAudioStop )( 
            IPropSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetHDAudioDisable )( 
            IPropSet * This,
            /* [in] */ BOOL bState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartCBLKHDAudioAuthentication )( 
            IPropSet * This,
            /* [size_is][in] */ BYTE *pStartBlockKsKc,
            /* [size_is][out] */ BYTE *pStartBlockRsFc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FinishCBLKHDAudioAuthentication )( 
            IPropSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCBLKHDAudioSupportedFormat )( 
            IPropSet * This,
            /* [size_is][out] */ BYTE *pFormat,
            /* [in] */ DWORD Count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCBLKHDAudioSupportedFormatNumber )( 
            IPropSet * This,
            /* [out] */ DWORD *Count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCBLKHDAudioSupportedFormat )( 
            IPropSet * This,
            /* [in] */ HDAudioSupportFormat SetFormat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCBLKHDAudioStop )( 
            IPropSet * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyDockOrUndock )( 
            IPropSet * This,
            /* [in] */ ULONG bDock);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMicNoiseSuppressionSupported )( 
            IPropSet * This,
            /* [out] */ BOOL *bSupported);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMicNoiseSuppression )( 
            IPropSet * This,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMicNoiseSuppression )( 
            IPropSet * This,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMicBeamFormingSupported )( 
            IPropSet * This,
            /* [out] */ BOOL *bSupported);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMicBeamForming )( 
            IPropSet * This,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMicBeamForming )( 
            IPropSet * This,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMicAECSupported )( 
            IPropSet * This,
            /* [out] */ BOOL *bSupported);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMicAEC )( 
            IPropSet * This,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMicAEC )( 
            IPropSet * This,
            /* [in] */ BOOL bEnable);
        
        END_INTERFACE
    } IPropSetVtbl;

    interface IPropSet
    {
        CONST_VTBL struct IPropSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet_SetChannelNum(This,Num)	\
    (This)->lpVtbl -> SetChannelNum(This,Num)

#define IPropSet_Init(This,ReturnVal)	\
    (This)->lpVtbl -> Init(This,ReturnVal)

#define IPropSet_GetMaxChannelNum(This,ReturnVal)	\
    (This)->lpVtbl -> GetMaxChannelNum(This,ReturnVal)

#define IPropSet_GetChannelNum(This,ReturnVal)	\
    (This)->lpVtbl -> GetChannelNum(This,ReturnVal)

#define IPropSet_GetFrontHeadPhoneOuputMode(This,ReturnVal)	\
    (This)->lpVtbl -> GetFrontHeadPhoneOuputMode(This,ReturnVal)

#define IPropSet_GetFrontMicInOutputMode(This,ReturnVal)	\
    (This)->lpVtbl -> GetFrontMicInOutputMode(This,ReturnVal)

#define IPropSet_GetRearLineInOutputMode(This,ReturnVal)	\
    (This)->lpVtbl -> GetRearLineInOutputMode(This,ReturnVal)

#define IPropSet_GetRearMicInOutputMode(This,ReturnVal)	\
    (This)->lpVtbl -> GetRearMicInOutputMode(This,ReturnVal)

#define IPropSet_GetFrontHeadPhoneUAJOutputMode(This,ReturnVal)	\
    (This)->lpVtbl -> GetFrontHeadPhoneUAJOutputMode(This,ReturnVal)

#define IPropSet_GetFrontMicInUAJOutputMode(This,ReturnVal)	\
    (This)->lpVtbl -> GetFrontMicInUAJOutputMode(This,ReturnVal)

#define IPropSet_SetFrontMicInUAJDeviceMode(This,DeviceType)	\
    (This)->lpVtbl -> SetFrontMicInUAJDeviceMode(This,DeviceType)

#define IPropSet_SetFrontHeadPhoneUAJDeviceMode(This,DeviceType)	\
    (This)->lpVtbl -> SetFrontHeadPhoneUAJDeviceMode(This,DeviceType)

#define IPropSet_SetRearLineInOutputMode(This,InOutMode)	\
    (This)->lpVtbl -> SetRearLineInOutputMode(This,InOutMode)

#define IPropSet_SetRearMicInOutputMode(This,InOutMode)	\
    (This)->lpVtbl -> SetRearMicInOutputMode(This,InOutMode)

#define IPropSet_GetCenLfeSwapStatus(This,ReturnVal)	\
    (This)->lpVtbl -> GetCenLfeSwapStatus(This,ReturnVal)

#define IPropSet_SetCenLfeSwapStatus(This,bStatus)	\
    (This)->lpVtbl -> SetCenLfeSwapStatus(This,bStatus)

#define IPropSet_SetFrontHPTunOnRearSpeaker(This,Enable)	\
    (This)->lpVtbl -> SetFrontHPTunOnRearSpeaker(This,Enable)

#define IPropSet_GetFrontHPTunOnRearSpeaker(This,ReturnVal)	\
    (This)->lpVtbl -> GetFrontHPTunOnRearSpeaker(This,ReturnVal)

#define IPropSet_GetAC3SupportStatus(This,ReturnVal)	\
    (This)->lpVtbl -> GetAC3SupportStatus(This,ReturnVal)

#define IPropSet_GetDisableUpMixing(This,ReturnVal)	\
    (This)->lpVtbl -> GetDisableUpMixing(This,ReturnVal)

#define IPropSet_SetDisableUpMixing(This,Enable)	\
    (This)->lpVtbl -> SetDisableUpMixing(This,Enable)

#define IPropSet_GetMaxDSBufferChannels(This,ReturnVal)	\
    (This)->lpVtbl -> GetMaxDSBufferChannels(This,ReturnVal)

#define IPropSet_Get2DEngineStatus(This,ReturnVal)	\
    (This)->lpVtbl -> Get2DEngineStatus(This,ReturnVal)

#define IPropSet_DisableAudioWizard(This)	\
    (This)->lpVtbl -> DisableAudioWizard(This)

#define IPropSet_CloseAudioWizard(This)	\
    (This)->lpVtbl -> CloseAudioWizard(This)

#define IPropSet_Set2DEngineStatus(This,Enable)	\
    (This)->lpVtbl -> Set2DEngineStatus(This,Enable)

#define IPropSet_Get3DBufferEnabled(This,ReturnVal)	\
    (This)->lpVtbl -> Get3DBufferEnabled(This,ReturnVal)

#define IPropSet_Get3DEAXEnabled(This,ReturnVal)	\
    (This)->lpVtbl -> Get3DEAXEnabled(This,ReturnVal)

#define IPropSet_GetSVIDValue(This,ReturnVal)	\
    (This)->lpVtbl -> GetSVIDValue(This,ReturnVal)

#define IPropSet_GetSSIDValue(This,ReturnVal)	\
    (This)->lpVtbl -> GetSSIDValue(This,ReturnVal)

#define IPropSet_CreateSaveWaveFile(This,node,pszFileName)	\
    (This)->lpVtbl -> CreateSaveWaveFile(This,node,pszFileName)

#define IPropSet_CloseSaveWaveFile(This,node)	\
    (This)->lpVtbl -> CloseSaveWaveFile(This,node)

#define IPropSet_EnableSaveWaveFile(This,node,fEnable)	\
    (This)->lpVtbl -> EnableSaveWaveFile(This,node,fEnable)

#define IPropSet_GetCreatedSaveWaveFile(This,node,pszFileName,dwBufSize)	\
    (This)->lpVtbl -> GetCreatedSaveWaveFile(This,node,pszFileName,dwBufSize)

#define IPropSet_GetSaveWaveStatus(This,node,pfEnabled)	\
    (This)->lpVtbl -> GetSaveWaveStatus(This,node,pfEnabled)

#define IPropSet_GetSaveWaveOverflow(This,node,pfOverflow)	\
    (This)->lpVtbl -> GetSaveWaveOverflow(This,node,pfOverflow)

#define IPropSet_GetDolbyPL2Enable(This,pfEnable)	\
    (This)->lpVtbl -> GetDolbyPL2Enable(This,pfEnable)

#define IPropSet_SetDolbyPL2Enable(This,fEnable)	\
    (This)->lpVtbl -> SetDolbyPL2Enable(This,fEnable)

#define IPropSet_GetDolbyHPEnable(This,pfEnable)	\
    (This)->lpVtbl -> GetDolbyHPEnable(This,pfEnable)

#define IPropSet_SetDolbyHPEnable(This,fEnable)	\
    (This)->lpVtbl -> SetDolbyHPEnable(This,fEnable)

#define IPropSet_GetDolbyVSEnable(This,pfEnable)	\
    (This)->lpVtbl -> GetDolbyVSEnable(This,pfEnable)

#define IPropSet_SetDolbyVSEnable(This,fEnable)	\
    (This)->lpVtbl -> SetDolbyVSEnable(This,fEnable)

#define IPropSet_GetDolbyPL2Panorama(This,pfEnable)	\
    (This)->lpVtbl -> GetDolbyPL2Panorama(This,pfEnable)

#define IPropSet_SetDolbyPL2Panorama(This,fEnable)	\
    (This)->lpVtbl -> SetDolbyPL2Panorama(This,fEnable)

#define IPropSet_GetDolbyPL2Mode(This,pMode)	\
    (This)->lpVtbl -> GetDolbyPL2Mode(This,pMode)

#define IPropSet_SetDolbyPL2Mode(This,Mode)	\
    (This)->lpVtbl -> SetDolbyPL2Mode(This,Mode)

#define IPropSet_GetDolbyPL2Dimension(This,pDim)	\
    (This)->lpVtbl -> GetDolbyPL2Dimension(This,pDim)

#define IPropSet_SetDolbyPL2Dimension(This,Dim)	\
    (This)->lpVtbl -> SetDolbyPL2Dimension(This,Dim)

#define IPropSet_GetDolbyPL2CenterWidth(This,pCenterWidth)	\
    (This)->lpVtbl -> GetDolbyPL2CenterWidth(This,pCenterWidth)

#define IPropSet_SetDolbyPL2CenterWidth(This,CenterWidth)	\
    (This)->lpVtbl -> SetDolbyPL2CenterWidth(This,CenterWidth)

#define IPropSet_GetDolbyHPRoom(This,pRoom)	\
    (This)->lpVtbl -> GetDolbyHPRoom(This,pRoom)

#define IPropSet_SetDolbyHPRoom(This,Room)	\
    (This)->lpVtbl -> SetDolbyHPRoom(This,Room)

#define IPropSet_GetDolbyVSRoom(This,pRoom)	\
    (This)->lpVtbl -> GetDolbyVSRoom(This,pRoom)

#define IPropSet_SetDolbyVSRoom(This,Room)	\
    (This)->lpVtbl -> SetDolbyVSRoom(This,Room)

#define IPropSet_GetBassManagement(This,pfEnable)	\
    (This)->lpVtbl -> GetBassManagement(This,pfEnable)

#define IPropSet_SetBassManagement(This,fEnable)	\
    (This)->lpVtbl -> SetBassManagement(This,fEnable)

#define IPropSet_GetSubwooferEnable(This,pfEnable)	\
    (This)->lpVtbl -> GetSubwooferEnable(This,pfEnable)

#define IPropSet_SetSubwooferEnable(This,fEnable)	\
    (This)->lpVtbl -> SetSubwooferEnable(This,fEnable)

#define IPropSet_GetSendBass2Sub(This,pfEnable)	\
    (This)->lpVtbl -> GetSendBass2Sub(This,pfEnable)

#define IPropSet_SetSendBass2Sub(This,fEnable)	\
    (This)->lpVtbl -> SetSendBass2Sub(This,fEnable)

#define IPropSet_GetCenterDelay(This,pDelay)	\
    (This)->lpVtbl -> GetCenterDelay(This,pDelay)

#define IPropSet_SetCenterDelay(This,Delay)	\
    (This)->lpVtbl -> SetCenterDelay(This,Delay)

#define IPropSet_GetSubwooferDelay(This,pDelay)	\
    (This)->lpVtbl -> GetSubwooferDelay(This,pDelay)

#define IPropSet_SetSubwooferDelay(This,Delay)	\
    (This)->lpVtbl -> SetSubwooferDelay(This,Delay)

#define IPropSet_GetRearLeftDelay(This,pDelay)	\
    (This)->lpVtbl -> GetRearLeftDelay(This,pDelay)

#define IPropSet_SetRearLeftDelay(This,Delay)	\
    (This)->lpVtbl -> SetRearLeftDelay(This,Delay)

#define IPropSet_GetRearRightDelay(This,pDelay)	\
    (This)->lpVtbl -> GetRearRightDelay(This,pDelay)

#define IPropSet_SetRearRightDelay(This,Delay)	\
    (This)->lpVtbl -> SetRearRightDelay(This,Delay)

#define IPropSet_GetFrontLeftTrim(This,pTrim)	\
    (This)->lpVtbl -> GetFrontLeftTrim(This,pTrim)

#define IPropSet_SetFrontLeftTrim(This,Trim)	\
    (This)->lpVtbl -> SetFrontLeftTrim(This,Trim)

#define IPropSet_GetFrontRightTrim(This,pTrim)	\
    (This)->lpVtbl -> GetFrontRightTrim(This,pTrim)

#define IPropSet_SetFrontRightTrim(This,Trim)	\
    (This)->lpVtbl -> SetFrontRightTrim(This,Trim)

#define IPropSet_GetCenterTrim(This,pTrim)	\
    (This)->lpVtbl -> GetCenterTrim(This,pTrim)

#define IPropSet_SetCenterTrim(This,Trim)	\
    (This)->lpVtbl -> SetCenterTrim(This,Trim)

#define IPropSet_GetSubwooferTrim(This,pTrim)	\
    (This)->lpVtbl -> GetSubwooferTrim(This,pTrim)

#define IPropSet_SetSubwooferTrim(This,Trim)	\
    (This)->lpVtbl -> SetSubwooferTrim(This,Trim)

#define IPropSet_GetRearLeftTrim(This,pTrim)	\
    (This)->lpVtbl -> GetRearLeftTrim(This,pTrim)

#define IPropSet_SetRearLeftTrim(This,Trim)	\
    (This)->lpVtbl -> SetRearLeftTrim(This,Trim)

#define IPropSet_GetRearRightTrim(This,pTrim)	\
    (This)->lpVtbl -> GetRearRightTrim(This,pTrim)

#define IPropSet_SetRearRightTrim(This,Trim)	\
    (This)->lpVtbl -> SetRearRightTrim(This,Trim)

#define IPropSet_GetFullRangeFrontSpeaker(This,pfEnable)	\
    (This)->lpVtbl -> GetFullRangeFrontSpeaker(This,pfEnable)

#define IPropSet_SetFullRangeFrontSpeaker(This,fEnable)	\
    (This)->lpVtbl -> SetFullRangeFrontSpeaker(This,fEnable)

#define IPropSet_GetDolbyPL2XMode(This,pfIsPL2XMode)	\
    (This)->lpVtbl -> GetDolbyPL2XMode(This,pfIsPL2XMode)

#define IPropSet_GetSideLeftDelay(This,pDelay)	\
    (This)->lpVtbl -> GetSideLeftDelay(This,pDelay)

#define IPropSet_SetSideLeftDelay(This,Delay)	\
    (This)->lpVtbl -> SetSideLeftDelay(This,Delay)

#define IPropSet_GetSideRightDelay(This,pDelay)	\
    (This)->lpVtbl -> GetSideRightDelay(This,pDelay)

#define IPropSet_SetSideRightDelay(This,Delay)	\
    (This)->lpVtbl -> SetSideRightDelay(This,Delay)

#define IPropSet_GetSideLeftTrim(This,pTrim)	\
    (This)->lpVtbl -> GetSideLeftTrim(This,pTrim)

#define IPropSet_SetSideLeftTrim(This,Trim)	\
    (This)->lpVtbl -> SetSideLeftTrim(This,Trim)

#define IPropSet_GetSideRightTrim(This,pTrim)	\
    (This)->lpVtbl -> GetSideRightTrim(This,pTrim)

#define IPropSet_SetSideRightTrim(This,Trim)	\
    (This)->lpVtbl -> SetSideRightTrim(This,Trim)

#define IPropSet_GetDriverModel(This,bDModel)	\
    (This)->lpVtbl -> GetDriverModel(This,bDModel)

#define IPropSet_GetFrontMicDevType(This,ulDeviceType)	\
    (This)->lpVtbl -> GetFrontMicDevType(This,ulDeviceType)

#define IPropSet_SetFrontMicDevType(This,ulDeviceType)	\
    (This)->lpVtbl -> SetFrontMicDevType(This,ulDeviceType)

#define IPropSet_GetFrontLineInDevType(This,ulDeviceType)	\
    (This)->lpVtbl -> GetFrontLineInDevType(This,ulDeviceType)

#define IPropSet_SetFrontLineInDevType(This,ulDeviceType)	\
    (This)->lpVtbl -> SetFrontLineInDevType(This,ulDeviceType)

#define IPropSet_GetLineIn1MuteState(This,bMuteState)	\
    (This)->lpVtbl -> GetLineIn1MuteState(This,bMuteState)

#define IPropSet_SetLineIn1MuteState(This,bMuteState)	\
    (This)->lpVtbl -> SetLineIn1MuteState(This,bMuteState)

#define IPropSet_GetLineIn2MuteState(This,bMuteState)	\
    (This)->lpVtbl -> GetLineIn2MuteState(This,bMuteState)

#define IPropSet_SetLineIn2MuteState(This,bMuteState)	\
    (This)->lpVtbl -> SetLineIn2MuteState(This,bMuteState)

#define IPropSet_GetMultiStreamState(This,bEnable)	\
    (This)->lpVtbl -> GetMultiStreamState(This,bEnable)

#define IPropSet_GetDTSSupportStatus(This,ReturnVal)	\
    (This)->lpVtbl -> GetDTSSupportStatus(This,ReturnVal)

#define IPropSet_GetDtsNeoEnable(This,pfEnable)	\
    (This)->lpVtbl -> GetDtsNeoEnable(This,pfEnable)

#define IPropSet_SetDtsNeoEnable(This,fEnable)	\
    (This)->lpVtbl -> SetDtsNeoEnable(This,fEnable)

#define IPropSet_GetDtsNeoMode(This,pMode)	\
    (This)->lpVtbl -> GetDtsNeoMode(This,pMode)

#define IPropSet_SetDtsNeoMode(This,Mode)	\
    (This)->lpVtbl -> SetDtsNeoMode(This,Mode)

#define IPropSet_GetDtsNeoCenterGain(This,pCenterGain)	\
    (This)->lpVtbl -> GetDtsNeoCenterGain(This,pCenterGain)

#define IPropSet_SetDtsNeoCenterGain(This,CenterGain)	\
    (This)->lpVtbl -> SetDtsNeoCenterGain(This,CenterGain)

#define IPropSet_GetFrontLineInSupportDevType(This,ulSuDevType)	\
    (This)->lpVtbl -> GetFrontLineInSupportDevType(This,ulSuDevType)

#define IPropSet_GetFrontMicSupportDevType(This,ulSuDevType)	\
    (This)->lpVtbl -> GetFrontMicSupportDevType(This,ulSuDevType)

#define IPropSet_GetEaxIndex(This,lRetVal)	\
    (This)->lpVtbl -> GetEaxIndex(This,lRetVal)

#define IPropSet_SetEAXIndex(This,Index)	\
    (This)->lpVtbl -> SetEAXIndex(This,Index)

#define IPropSet_GetBbeEnable(This,pfEnable)	\
    (This)->lpVtbl -> GetBbeEnable(This,pfEnable)

#define IPropSet_SetBbeEnable(This,fEnable)	\
    (This)->lpVtbl -> SetBbeEnable(This,fEnable)

#define IPropSet_GetBbeSpkMode(This,pMode)	\
    (This)->lpVtbl -> GetBbeSpkMode(This,pMode)

#define IPropSet_SetBbeSpkMode(This,Mode)	\
    (This)->lpVtbl -> SetBbeSpkMode(This,Mode)

#define IPropSet_GetLibVersionTableSize(This,pSize)	\
    (This)->lpVtbl -> GetLibVersionTableSize(This,pSize)

#define IPropSet_GetLibVersionTable(This,pTable,Size)	\
    (This)->lpVtbl -> GetLibVersionTable(This,pTable,Size)

#define IPropSet_SetDolbyEvent(This,hEvent)	\
    (This)->lpVtbl -> SetDolbyEvent(This,hEvent)

#define IPropSet_RemoveDolbyEvent(This,hEvent)	\
    (This)->lpVtbl -> RemoveDolbyEvent(This,hEvent)

#define IPropSet_GetFrontLeftDelay(This,pDelay)	\
    (This)->lpVtbl -> GetFrontLeftDelay(This,pDelay)

#define IPropSet_SetFrontLeftDelay(This,Delay)	\
    (This)->lpVtbl -> SetFrontLeftDelay(This,Delay)

#define IPropSet_GetFrontRightDelay(This,pDelay)	\
    (This)->lpVtbl -> GetFrontRightDelay(This,pDelay)

#define IPropSet_SetFrontRightDelay(This,Delay)	\
    (This)->lpVtbl -> SetFrontRightDelay(This,Delay)

#define IPropSet_GetDolbyDownMix(This,bIsDownMix)	\
    (This)->lpVtbl -> GetDolbyDownMix(This,bIsDownMix)

#define IPropSet_SetDolbyDownMix(This,bIsDownMix)	\
    (This)->lpVtbl -> SetDolbyDownMix(This,bIsDownMix)

#define IPropSet_GetDolbyDLiveAutoOverride(This,bIsAutoOverride)	\
    (This)->lpVtbl -> GetDolbyDLiveAutoOverride(This,bIsAutoOverride)

#define IPropSet_SetDolbyDLiveAutoOverride(This,bIsAutoOverride)	\
    (This)->lpVtbl -> SetDolbyDLiveAutoOverride(This,bIsAutoOverride)

#define IPropSet_GetBassManagementMode(This,ulMode)	\
    (This)->lpVtbl -> GetBassManagementMode(This,ulMode)

#define IPropSet_SetBassManagementMode(This,ulMode)	\
    (This)->lpVtbl -> SetBassManagementMode(This,ulMode)

#define IPropSet_GetDBDelayScale(This,lScale)	\
    (This)->lpVtbl -> GetDBDelayScale(This,lScale)

#define IPropSet_SetDBDelayScale(This,lScale)	\
    (This)->lpVtbl -> SetDBDelayScale(This,lScale)

#define IPropSet_GetDBDelayDistance(This,lSpeaker,fDistance)	\
    (This)->lpVtbl -> GetDBDelayDistance(This,lSpeaker,fDistance)

#define IPropSet_SetDBDelayDistance(This,lSpeaker,fDistance)	\
    (This)->lpVtbl -> SetDBDelayDistance(This,lSpeaker,fDistance)

#define IPropSet_GetASUSMicState(This,ReturnVal)	\
    (This)->lpVtbl -> GetASUSMicState(This,ReturnVal)

#define IPropSet_SetASUSMicState(This,wValue)	\
    (This)->lpVtbl -> SetASUSMicState(This,wValue)

#define IPropSet_SetEQReset(This)	\
    (This)->lpVtbl -> SetEQReset(This)

#define IPropSet_SetEQLevel(This,Index,SetVal)	\
    (This)->lpVtbl -> SetEQLevel(This,Index,SetVal)

#define IPropSet_GetEQLevel(This,Index,ReturnVal)	\
    (This)->lpVtbl -> GetEQLevel(This,Index,ReturnVal)

#define IPropSet_GetEQIndex(This,RtnValue)	\
    (This)->lpVtbl -> GetEQIndex(This,RtnValue)

#define IPropSet_SetEQIndex(This,Index)	\
    (This)->lpVtbl -> SetEQIndex(This,Index)

#define IPropSet_GetEQEnable(This,ReturnVal)	\
    (This)->lpVtbl -> GetEQEnable(This,ReturnVal)

#define IPropSet_SetEQEnable(This,Enable)	\
    (This)->lpVtbl -> SetEQEnable(This,Enable)

#define IPropSet_GetVoiceCancelStatus(This,ReturnVal)	\
    (This)->lpVtbl -> GetVoiceCancelStatus(This,ReturnVal)

#define IPropSet_SetVoiceCancelStatus(This,bEnable)	\
    (This)->lpVtbl -> SetVoiceCancelStatus(This,bEnable)

#define IPropSet_GetKaraokePitch(This,ReturnVal)	\
    (This)->lpVtbl -> GetKaraokePitch(This,ReturnVal)

#define IPropSet_SetKaraokePitch(This,lValue)	\
    (This)->lpVtbl -> SetKaraokePitch(This,lValue)

#define IPropSet_GetEQCenter(This,Index,lRetrunVal)	\
    (This)->lpVtbl -> GetEQCenter(This,Index,lRetrunVal)

#define IPropSet_SetEQCenter(This,Index,lSetVal)	\
    (This)->lpVtbl -> SetEQCenter(This,Index,lSetVal)

#define IPropSet_GetEQBandwidth(This,Index,lReturnVal)	\
    (This)->lpVtbl -> GetEQBandwidth(This,Index,lReturnVal)

#define IPropSet_SetEQBandwidth(This,Index,lSetVal)	\
    (This)->lpVtbl -> SetEQBandwidth(This,Index,lSetVal)

#define IPropSet_GetSWEQ(This,lIndex,lGain,lFrequency,lBandwidth,bEnable)	\
    (This)->lpVtbl -> GetSWEQ(This,lIndex,lGain,lFrequency,lBandwidth,bEnable)

#define IPropSet_SetSWEQ(This,lIndex,lGain,lFrequency,lBandwidth,bEnable)	\
    (This)->lpVtbl -> SetSWEQ(This,lIndex,lGain,lFrequency,lBandwidth,bEnable)

#define IPropSet_ResetSWEQ(This)	\
    (This)->lpVtbl -> ResetSWEQ(This)

#define IPropSet_StartHDAudioAuthentication(This,pR1,pClientAuthData)	\
    (This)->lpVtbl -> StartHDAudioAuthentication(This,pR1,pClientAuthData)

#define IPropSet_FinishHDAudioAuthentication(This,pServerAuthData)	\
    (This)->lpVtbl -> FinishHDAudioAuthentication(This,pServerAuthData)

#define IPropSet_GetHDAudioSupportedFormatNumber(This,Count)	\
    (This)->lpVtbl -> GetHDAudioSupportedFormatNumber(This,Count)

#define IPropSet_GetHDAudioSupportedFormat(This,pFormat,Count)	\
    (This)->lpVtbl -> GetHDAudioSupportedFormat(This,pFormat,Count)

#define IPropSet_GetAcerPowerManagement(This,dwData)	\
    (This)->lpVtbl -> GetAcerPowerManagement(This,dwData)

#define IPropSet_SetAcerPowerManagement(This,dwData)	\
    (This)->lpVtbl -> SetAcerPowerManagement(This,dwData)

#define IPropSet_GetSWEQLoudness(This,bEnable,ldB)	\
    (This)->lpVtbl -> GetSWEQLoudness(This,bEnable,ldB)

#define IPropSet_SetSWEQLoudness(This,bEnable,ldB)	\
    (This)->lpVtbl -> SetSWEQLoudness(This,bEnable,ldB)

#define IPropSet_SetAPHandleAndMessage(This,hWnd,dwMessage)	\
    (This)->lpVtbl -> SetAPHandleAndMessage(This,hWnd,dwMessage)

#define IPropSet_GetPinPlugState(This,ulPinName,bPlugState)	\
    (This)->lpVtbl -> GetPinPlugState(This,ulPinName,bPlugState)

#define IPropSet_SetHDAudioSupportedFormat(This,SetFormat)	\
    (This)->lpVtbl -> SetHDAudioSupportedFormat(This,SetFormat)

#define IPropSet_GetSWDrc(This,pSWDRC)	\
    (This)->lpVtbl -> GetSWDrc(This,pSWDRC)

#define IPropSet_SetSWDrc(This,pSWDRC)	\
    (This)->lpVtbl -> SetSWDrc(This,pSWDRC)

#define IPropSet_SetHDAudioStop(This)	\
    (This)->lpVtbl -> SetHDAudioStop(This)

#define IPropSet_SetHDAudioDisable(This,bState)	\
    (This)->lpVtbl -> SetHDAudioDisable(This,bState)

#define IPropSet_StartCBLKHDAudioAuthentication(This,pStartBlockKsKc,pStartBlockRsFc)	\
    (This)->lpVtbl -> StartCBLKHDAudioAuthentication(This,pStartBlockKsKc,pStartBlockRsFc)

#define IPropSet_FinishCBLKHDAudioAuthentication(This)	\
    (This)->lpVtbl -> FinishCBLKHDAudioAuthentication(This)

#define IPropSet_GetCBLKHDAudioSupportedFormat(This,pFormat,Count)	\
    (This)->lpVtbl -> GetCBLKHDAudioSupportedFormat(This,pFormat,Count)

#define IPropSet_GetCBLKHDAudioSupportedFormatNumber(This,Count)	\
    (This)->lpVtbl -> GetCBLKHDAudioSupportedFormatNumber(This,Count)

#define IPropSet_SetCBLKHDAudioSupportedFormat(This,SetFormat)	\
    (This)->lpVtbl -> SetCBLKHDAudioSupportedFormat(This,SetFormat)

#define IPropSet_SetCBLKHDAudioStop(This)	\
    (This)->lpVtbl -> SetCBLKHDAudioStop(This)

#define IPropSet_NotifyDockOrUndock(This,bDock)	\
    (This)->lpVtbl -> NotifyDockOrUndock(This,bDock)

#define IPropSet_GetMicNoiseSuppressionSupported(This,bSupported)	\
    (This)->lpVtbl -> GetMicNoiseSuppressionSupported(This,bSupported)

#define IPropSet_GetMicNoiseSuppression(This,bEnable)	\
    (This)->lpVtbl -> GetMicNoiseSuppression(This,bEnable)

#define IPropSet_SetMicNoiseSuppression(This,bEnable)	\
    (This)->lpVtbl -> SetMicNoiseSuppression(This,bEnable)

#define IPropSet_GetMicBeamFormingSupported(This,bSupported)	\
    (This)->lpVtbl -> GetMicBeamFormingSupported(This,bSupported)

#define IPropSet_GetMicBeamForming(This,bEnable)	\
    (This)->lpVtbl -> GetMicBeamForming(This,bEnable)

#define IPropSet_SetMicBeamForming(This,bEnable)	\
    (This)->lpVtbl -> SetMicBeamForming(This,bEnable)

#define IPropSet_GetMicAECSupported(This,bSupported)	\
    (This)->lpVtbl -> GetMicAECSupported(This,bSupported)

#define IPropSet_GetMicAEC(This,bEnable)	\
    (This)->lpVtbl -> GetMicAEC(This,bEnable)

#define IPropSet_SetMicAEC(This,bEnable)	\
    (This)->lpVtbl -> SetMicAEC(This,bEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetChannelNum_Proxy( 
    IPropSet * This,
    /* [in] */ long Num);


void __RPC_STUB IPropSet_SetChannelNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_Init_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMaxChannelNum_Proxy( 
    IPropSet * This,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IPropSet_GetMaxChannelNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetChannelNum_Proxy( 
    IPropSet * This,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IPropSet_GetChannelNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontHeadPhoneOuputMode_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetFrontHeadPhoneOuputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontMicInOutputMode_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetFrontMicInOutputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetRearLineInOutputMode_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetRearLineInOutputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetRearMicInOutputMode_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetRearMicInOutputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontHeadPhoneUAJOutputMode_Proxy( 
    IPropSet * This,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IPropSet_GetFrontHeadPhoneUAJOutputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontMicInUAJOutputMode_Proxy( 
    IPropSet * This,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IPropSet_GetFrontMicInUAJOutputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontMicInUAJDeviceMode_Proxy( 
    IPropSet * This,
    /* [in] */ long DeviceType);


void __RPC_STUB IPropSet_SetFrontMicInUAJDeviceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontHeadPhoneUAJDeviceMode_Proxy( 
    IPropSet * This,
    /* [in] */ long DeviceType);


void __RPC_STUB IPropSet_SetFrontHeadPhoneUAJDeviceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetRearLineInOutputMode_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL InOutMode);


void __RPC_STUB IPropSet_SetRearLineInOutputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetRearMicInOutputMode_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL InOutMode);


void __RPC_STUB IPropSet_SetRearMicInOutputMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetCenLfeSwapStatus_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetCenLfeSwapStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetCenLfeSwapStatus_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bStatus);


void __RPC_STUB IPropSet_SetCenLfeSwapStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontHPTunOnRearSpeaker_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL Enable);


void __RPC_STUB IPropSet_SetFrontHPTunOnRearSpeaker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontHPTunOnRearSpeaker_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetFrontHPTunOnRearSpeaker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetAC3SupportStatus_Proxy( 
    IPropSet * This,
    /* [out] */ WORD *ReturnVal);


void __RPC_STUB IPropSet_GetAC3SupportStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDisableUpMixing_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetDisableUpMixing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDisableUpMixing_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL Enable);


void __RPC_STUB IPropSet_SetDisableUpMixing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMaxDSBufferChannels_Proxy( 
    IPropSet * This,
    /* [out] */ WORD *ReturnVal);


void __RPC_STUB IPropSet_GetMaxDSBufferChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_Get2DEngineStatus_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_Get2DEngineStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_DisableAudioWizard_Proxy( 
    IPropSet * This);


void __RPC_STUB IPropSet_DisableAudioWizard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_CloseAudioWizard_Proxy( 
    IPropSet * This);


void __RPC_STUB IPropSet_CloseAudioWizard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_Set2DEngineStatus_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL Enable);


void __RPC_STUB IPropSet_Set2DEngineStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_Get3DBufferEnabled_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_Get3DBufferEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_Get3DEAXEnabled_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_Get3DEAXEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSVIDValue_Proxy( 
    IPropSet * This,
    /* [out] */ DWORD *ReturnVal);


void __RPC_STUB IPropSet_GetSVIDValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSSIDValue_Proxy( 
    IPropSet * This,
    /* [out] */ DWORD *ReturnVal);


void __RPC_STUB IPropSet_GetSSIDValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_CreateSaveWaveFile_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG node,
    /* [in] */ LPSTR pszFileName);


void __RPC_STUB IPropSet_CreateSaveWaveFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_CloseSaveWaveFile_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG node);


void __RPC_STUB IPropSet_CloseSaveWaveFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_EnableSaveWaveFile_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG node,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_EnableSaveWaveFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetCreatedSaveWaveFile_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG node,
    /* [in] */ LPSTR pszFileName,
    /* [in] */ DWORD dwBufSize);


void __RPC_STUB IPropSet_GetCreatedSaveWaveFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSaveWaveStatus_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG node,
    /* [out] */ BOOL *pfEnabled);


void __RPC_STUB IPropSet_GetSaveWaveStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSaveWaveOverflow_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG node,
    /* [out] */ BOOL *pfOverflow);


void __RPC_STUB IPropSet_GetSaveWaveOverflow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyPL2Enable_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetDolbyPL2Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyPL2Enable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetDolbyPL2Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyHPEnable_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetDolbyHPEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyHPEnable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetDolbyHPEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyVSEnable_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetDolbyVSEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyVSEnable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetDolbyVSEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyPL2Panorama_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetDolbyPL2Panorama_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyPL2Panorama_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetDolbyPL2Panorama_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyPL2Mode_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pMode);


void __RPC_STUB IPropSet_GetDolbyPL2Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyPL2Mode_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG Mode);


void __RPC_STUB IPropSet_SetDolbyPL2Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyPL2Dimension_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pDim);


void __RPC_STUB IPropSet_GetDolbyPL2Dimension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyPL2Dimension_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG Dim);


void __RPC_STUB IPropSet_SetDolbyPL2Dimension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyPL2CenterWidth_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pCenterWidth);


void __RPC_STUB IPropSet_GetDolbyPL2CenterWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyPL2CenterWidth_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG CenterWidth);


void __RPC_STUB IPropSet_SetDolbyPL2CenterWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyHPRoom_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pRoom);


void __RPC_STUB IPropSet_GetDolbyHPRoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyHPRoom_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG Room);


void __RPC_STUB IPropSet_SetDolbyHPRoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyVSRoom_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pRoom);


void __RPC_STUB IPropSet_GetDolbyVSRoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyVSRoom_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG Room);


void __RPC_STUB IPropSet_SetDolbyVSRoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetBassManagement_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetBassManagement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetBassManagement_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetBassManagement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSubwooferEnable_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetSubwooferEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSubwooferEnable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetSubwooferEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSendBass2Sub_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetSendBass2Sub_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSendBass2Sub_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetSendBass2Sub_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetCenterDelay_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pDelay);


void __RPC_STUB IPropSet_GetCenterDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetCenterDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetCenterDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSubwooferDelay_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pDelay);


void __RPC_STUB IPropSet_GetSubwooferDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSubwooferDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetSubwooferDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetRearLeftDelay_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pDelay);


void __RPC_STUB IPropSet_GetRearLeftDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetRearLeftDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetRearLeftDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetRearRightDelay_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pDelay);


void __RPC_STUB IPropSet_GetRearRightDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetRearRightDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetRearRightDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontLeftTrim_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pTrim);


void __RPC_STUB IPropSet_GetFrontLeftTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontLeftTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetFrontLeftTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontRightTrim_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pTrim);


void __RPC_STUB IPropSet_GetFrontRightTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontRightTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetFrontRightTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetCenterTrim_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pTrim);


void __RPC_STUB IPropSet_GetCenterTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetCenterTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetCenterTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSubwooferTrim_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pTrim);


void __RPC_STUB IPropSet_GetSubwooferTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSubwooferTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetSubwooferTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetRearLeftTrim_Proxy( 
    IPropSet * This,
    LONG *pTrim);


void __RPC_STUB IPropSet_GetRearLeftTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetRearLeftTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetRearLeftTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetRearRightTrim_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pTrim);


void __RPC_STUB IPropSet_GetRearRightTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetRearRightTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetRearRightTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFullRangeFrontSpeaker_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetFullRangeFrontSpeaker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFullRangeFrontSpeaker_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetFullRangeFrontSpeaker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyPL2XMode_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfIsPL2XMode);


void __RPC_STUB IPropSet_GetDolbyPL2XMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSideLeftDelay_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pDelay);


void __RPC_STUB IPropSet_GetSideLeftDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSideLeftDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetSideLeftDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSideRightDelay_Proxy( 
    IPropSet * This,
    LONG *pDelay);


void __RPC_STUB IPropSet_GetSideRightDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSideRightDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetSideRightDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSideLeftTrim_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pTrim);


void __RPC_STUB IPropSet_GetSideLeftTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSideLeftTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetSideLeftTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSideRightTrim_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pTrim);


void __RPC_STUB IPropSet_GetSideRightTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSideRightTrim_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Trim);


void __RPC_STUB IPropSet_SetSideRightTrim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDriverModel_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bDModel);


void __RPC_STUB IPropSet_GetDriverModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontMicDevType_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *ulDeviceType);


void __RPC_STUB IPropSet_GetFrontMicDevType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontMicDevType_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG ulDeviceType);


void __RPC_STUB IPropSet_SetFrontMicDevType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontLineInDevType_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *ulDeviceType);


void __RPC_STUB IPropSet_GetFrontLineInDevType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontLineInDevType_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG ulDeviceType);


void __RPC_STUB IPropSet_SetFrontLineInDevType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetLineIn1MuteState_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bMuteState);


void __RPC_STUB IPropSet_GetLineIn1MuteState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetLineIn1MuteState_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bMuteState);


void __RPC_STUB IPropSet_SetLineIn1MuteState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetLineIn2MuteState_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bMuteState);


void __RPC_STUB IPropSet_GetLineIn2MuteState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetLineIn2MuteState_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bMuteState);


void __RPC_STUB IPropSet_SetLineIn2MuteState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMultiStreamState_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet_GetMultiStreamState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDTSSupportStatus_Proxy( 
    IPropSet * This,
    /* [out] */ WORD *ReturnVal);


void __RPC_STUB IPropSet_GetDTSSupportStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDtsNeoEnable_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetDtsNeoEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDtsNeoEnable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetDtsNeoEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDtsNeoMode_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pMode);


void __RPC_STUB IPropSet_GetDtsNeoMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDtsNeoMode_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG Mode);


void __RPC_STUB IPropSet_SetDtsNeoMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDtsNeoCenterGain_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pCenterGain);


void __RPC_STUB IPropSet_GetDtsNeoCenterGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDtsNeoCenterGain_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG CenterGain);


void __RPC_STUB IPropSet_SetDtsNeoCenterGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontLineInSupportDevType_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *ulSuDevType);


void __RPC_STUB IPropSet_GetFrontLineInSupportDevType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontMicSupportDevType_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *ulSuDevType);


void __RPC_STUB IPropSet_GetFrontMicSupportDevType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetEaxIndex_Proxy( 
    IPropSet * This,
    /* [out] */ long *lRetVal);


void __RPC_STUB IPropSet_GetEaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetEAXIndex_Proxy( 
    IPropSet * This,
    /* [in] */ long Index);


void __RPC_STUB IPropSet_SetEAXIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetBbeEnable_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *pfEnable);


void __RPC_STUB IPropSet_GetBbeEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetBbeEnable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IPropSet_SetBbeEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetBbeSpkMode_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pMode);


void __RPC_STUB IPropSet_GetBbeSpkMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetBbeSpkMode_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG Mode);


void __RPC_STUB IPropSet_SetBbeSpkMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetLibVersionTableSize_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pSize);


void __RPC_STUB IPropSet_GetLibVersionTableSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetLibVersionTable_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *pTable,
    /* [in] */ ULONG Size);


void __RPC_STUB IPropSet_GetLibVersionTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyEvent_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG hEvent);


void __RPC_STUB IPropSet_SetDolbyEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_RemoveDolbyEvent_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG hEvent);


void __RPC_STUB IPropSet_RemoveDolbyEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontLeftDelay_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pDelay);


void __RPC_STUB IPropSet_GetFrontLeftDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontLeftDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetFrontLeftDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetFrontRightDelay_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *pDelay);


void __RPC_STUB IPropSet_GetFrontRightDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetFrontRightDelay_Proxy( 
    IPropSet * This,
    /* [in] */ LONG Delay);


void __RPC_STUB IPropSet_SetFrontRightDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyDownMix_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bIsDownMix);


void __RPC_STUB IPropSet_GetDolbyDownMix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyDownMix_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bIsDownMix);


void __RPC_STUB IPropSet_SetDolbyDownMix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDolbyDLiveAutoOverride_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bIsAutoOverride);


void __RPC_STUB IPropSet_GetDolbyDLiveAutoOverride_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDolbyDLiveAutoOverride_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bIsAutoOverride);


void __RPC_STUB IPropSet_SetDolbyDLiveAutoOverride_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetBassManagementMode_Proxy( 
    IPropSet * This,
    /* [out] */ ULONG *ulMode);


void __RPC_STUB IPropSet_GetBassManagementMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetBassManagementMode_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG ulMode);


void __RPC_STUB IPropSet_SetBassManagementMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDBDelayScale_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *lScale);


void __RPC_STUB IPropSet_GetDBDelayScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDBDelayScale_Proxy( 
    IPropSet * This,
    /* [in] */ LONG lScale);


void __RPC_STUB IPropSet_SetDBDelayScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetDBDelayDistance_Proxy( 
    IPropSet * This,
    /* [in] */ LONG lSpeaker,
    /* [out] */ float *fDistance);


void __RPC_STUB IPropSet_GetDBDelayDistance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetDBDelayDistance_Proxy( 
    IPropSet * This,
    /* [in] */ LONG lSpeaker,
    /* [in] */ float fDistance);


void __RPC_STUB IPropSet_SetDBDelayDistance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetASUSMicState_Proxy( 
    IPropSet * This,
    /* [out] */ WORD *ReturnVal);


void __RPC_STUB IPropSet_GetASUSMicState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetASUSMicState_Proxy( 
    IPropSet * This,
    /* [in] */ WORD wValue);


void __RPC_STUB IPropSet_SetASUSMicState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetEQReset_Proxy( 
    IPropSet * This);


void __RPC_STUB IPropSet_SetEQReset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetEQLevel_Proxy( 
    IPropSet * This,
    /* [in] */ long Index,
    /* [in] */ long SetVal);


void __RPC_STUB IPropSet_SetEQLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetEQLevel_Proxy( 
    IPropSet * This,
    /* [in] */ long Index,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IPropSet_GetEQLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetEQIndex_Proxy( 
    IPropSet * This,
    /* [out] */ long *RtnValue);


void __RPC_STUB IPropSet_GetEQIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetEQIndex_Proxy( 
    IPropSet * This,
    /* [in] */ long Index);


void __RPC_STUB IPropSet_SetEQIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetEQEnable_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetEQEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetEQEnable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL Enable);


void __RPC_STUB IPropSet_SetEQEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetVoiceCancelStatus_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IPropSet_GetVoiceCancelStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetVoiceCancelStatus_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet_SetVoiceCancelStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetKaraokePitch_Proxy( 
    IPropSet * This,
    /* [out] */ LONG *ReturnVal);


void __RPC_STUB IPropSet_GetKaraokePitch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetKaraokePitch_Proxy( 
    IPropSet * This,
    /* [in] */ LONG lValue);


void __RPC_STUB IPropSet_SetKaraokePitch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetEQCenter_Proxy( 
    IPropSet * This,
    /* [in] */ long Index,
    /* [out] */ long *lRetrunVal);


void __RPC_STUB IPropSet_GetEQCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetEQCenter_Proxy( 
    IPropSet * This,
    /* [in] */ long Index,
    /* [in] */ long lSetVal);


void __RPC_STUB IPropSet_SetEQCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetEQBandwidth_Proxy( 
    IPropSet * This,
    /* [in] */ long Index,
    /* [out] */ long *lReturnVal);


void __RPC_STUB IPropSet_GetEQBandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetEQBandwidth_Proxy( 
    IPropSet * This,
    /* [in] */ long Index,
    /* [in] */ long lSetVal);


void __RPC_STUB IPropSet_SetEQBandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSWEQ_Proxy( 
    IPropSet * This,
    /* [in] */ long lIndex,
    /* [out] */ long *lGain,
    /* [out] */ long *lFrequency,
    /* [out] */ long *lBandwidth,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet_GetSWEQ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSWEQ_Proxy( 
    IPropSet * This,
    /* [in] */ long lIndex,
    /* [in] */ long lGain,
    /* [in] */ long lFrequency,
    /* [in] */ long lBandwidth,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet_SetSWEQ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_ResetSWEQ_Proxy( 
    IPropSet * This);


void __RPC_STUB IPropSet_ResetSWEQ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_StartHDAudioAuthentication_Proxy( 
    IPropSet * This,
    /* [size_is][in] */ BYTE *pR1,
    /* [size_is][out] */ BYTE *pClientAuthData);


void __RPC_STUB IPropSet_StartHDAudioAuthentication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_FinishHDAudioAuthentication_Proxy( 
    IPropSet * This,
    /* [size_is][in] */ BYTE *pServerAuthData);


void __RPC_STUB IPropSet_FinishHDAudioAuthentication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetHDAudioSupportedFormatNumber_Proxy( 
    IPropSet * This,
    /* [out] */ DWORD *Count);


void __RPC_STUB IPropSet_GetHDAudioSupportedFormatNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetHDAudioSupportedFormat_Proxy( 
    IPropSet * This,
    /* [size_is][out] */ BYTE *pFormat,
    /* [in] */ DWORD Count);


void __RPC_STUB IPropSet_GetHDAudioSupportedFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetAcerPowerManagement_Proxy( 
    IPropSet * This,
    /* [out] */ DWORD *dwData);


void __RPC_STUB IPropSet_GetAcerPowerManagement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetAcerPowerManagement_Proxy( 
    IPropSet * This,
    /* [in] */ DWORD dwData);


void __RPC_STUB IPropSet_SetAcerPowerManagement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSWEQLoudness_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bEnable,
    /* [out] */ long *ldB);


void __RPC_STUB IPropSet_GetSWEQLoudness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSWEQLoudness_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bEnable,
    /* [in] */ long ldB);


void __RPC_STUB IPropSet_SetSWEQLoudness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetAPHandleAndMessage_Proxy( 
    IPropSet * This,
    /* [in] */ HWND hWnd,
    /* [in] */ DWORD dwMessage);


void __RPC_STUB IPropSet_SetAPHandleAndMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetPinPlugState_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG ulPinName,
    /* [out] */ BOOL *bPlugState);


void __RPC_STUB IPropSet_GetPinPlugState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetHDAudioSupportedFormat_Proxy( 
    IPropSet * This,
    /* [in] */ HDAudioSupportFormat SetFormat);


void __RPC_STUB IPropSet_SetHDAudioSupportedFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetSWDrc_Proxy( 
    IPropSet * This,
    /* [out] */ SWDRCPROPERTIES *pSWDRC);


void __RPC_STUB IPropSet_GetSWDrc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetSWDrc_Proxy( 
    IPropSet * This,
    /* [in] */ SWDRCPROPERTIES pSWDRC);


void __RPC_STUB IPropSet_SetSWDrc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetHDAudioStop_Proxy( 
    IPropSet * This);


void __RPC_STUB IPropSet_SetHDAudioStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetHDAudioDisable_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bState);


void __RPC_STUB IPropSet_SetHDAudioDisable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_StartCBLKHDAudioAuthentication_Proxy( 
    IPropSet * This,
    /* [size_is][in] */ BYTE *pStartBlockKsKc,
    /* [size_is][out] */ BYTE *pStartBlockRsFc);


void __RPC_STUB IPropSet_StartCBLKHDAudioAuthentication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_FinishCBLKHDAudioAuthentication_Proxy( 
    IPropSet * This);


void __RPC_STUB IPropSet_FinishCBLKHDAudioAuthentication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetCBLKHDAudioSupportedFormat_Proxy( 
    IPropSet * This,
    /* [size_is][out] */ BYTE *pFormat,
    /* [in] */ DWORD Count);


void __RPC_STUB IPropSet_GetCBLKHDAudioSupportedFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetCBLKHDAudioSupportedFormatNumber_Proxy( 
    IPropSet * This,
    /* [out] */ DWORD *Count);


void __RPC_STUB IPropSet_GetCBLKHDAudioSupportedFormatNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetCBLKHDAudioSupportedFormat_Proxy( 
    IPropSet * This,
    /* [in] */ HDAudioSupportFormat SetFormat);


void __RPC_STUB IPropSet_SetCBLKHDAudioSupportedFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetCBLKHDAudioStop_Proxy( 
    IPropSet * This);


void __RPC_STUB IPropSet_SetCBLKHDAudioStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_NotifyDockOrUndock_Proxy( 
    IPropSet * This,
    /* [in] */ ULONG bDock);


void __RPC_STUB IPropSet_NotifyDockOrUndock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMicNoiseSuppressionSupported_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bSupported);


void __RPC_STUB IPropSet_GetMicNoiseSuppressionSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMicNoiseSuppression_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet_GetMicNoiseSuppression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetMicNoiseSuppression_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet_SetMicNoiseSuppression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMicBeamFormingSupported_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bSupported);


void __RPC_STUB IPropSet_GetMicBeamFormingSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMicBeamForming_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet_GetMicBeamForming_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetMicBeamForming_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet_SetMicBeamForming_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMicAECSupported_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bSupported);


void __RPC_STUB IPropSet_GetMicAECSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_GetMicAEC_Proxy( 
    IPropSet * This,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet_GetMicAEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet_SetMicAEC_Proxy( 
    IPropSet * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet_SetMicAEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet_INTERFACE_DEFINED__ */


#ifndef __IABIT_INTERFACE_DEFINED__
#define __IABIT_INTERFACE_DEFINED__

/* interface IABIT */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IABIT;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E29C6B1D-263F-4F3D-A9C5-88B15B6019F5")
    IABIT : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEQLevel( 
            /* [in] */ long Index,
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQLevel( 
            /* [in] */ long Index,
            /* [in] */ long SetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEAXIndex( 
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEAXIndex( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetReverbStatus( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetReverbStatus( 
            /* [in] */ BOOL Enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChannelNum( 
            /* [out] */ long *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEQEnable( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEQEnable( 
            /* [in] */ BOOL Enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSpkChannel( 
            /* [in] */ int nChannel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IABITVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IABIT * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IABIT * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IABIT * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IABIT * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IABIT * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IABIT * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IABIT * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IABIT * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEQLevel )( 
            IABIT * This,
            /* [in] */ long Index,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQLevel )( 
            IABIT * This,
            /* [in] */ long Index,
            /* [in] */ long SetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEAXIndex )( 
            IABIT * This,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEAXIndex )( 
            IABIT * This,
            /* [in] */ long Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetReverbStatus )( 
            IABIT * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetReverbStatus )( 
            IABIT * This,
            /* [in] */ BOOL Enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetChannelNum )( 
            IABIT * This,
            /* [out] */ long *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEQEnable )( 
            IABIT * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEQEnable )( 
            IABIT * This,
            /* [in] */ BOOL Enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSpkChannel )( 
            IABIT * This,
            /* [in] */ int nChannel);
        
        END_INTERFACE
    } IABITVtbl;

    interface IABIT
    {
        CONST_VTBL struct IABITVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IABIT_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IABIT_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IABIT_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IABIT_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IABIT_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IABIT_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IABIT_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IABIT_Init(This,ReturnVal)	\
    (This)->lpVtbl -> Init(This,ReturnVal)

#define IABIT_GetEQLevel(This,Index,ReturnVal)	\
    (This)->lpVtbl -> GetEQLevel(This,Index,ReturnVal)

#define IABIT_SetEQLevel(This,Index,SetVal)	\
    (This)->lpVtbl -> SetEQLevel(This,Index,SetVal)

#define IABIT_GetEAXIndex(This,ReturnVal)	\
    (This)->lpVtbl -> GetEAXIndex(This,ReturnVal)

#define IABIT_SetEAXIndex(This,Index)	\
    (This)->lpVtbl -> SetEAXIndex(This,Index)

#define IABIT_GetReverbStatus(This,ReturnVal)	\
    (This)->lpVtbl -> GetReverbStatus(This,ReturnVal)

#define IABIT_SetReverbStatus(This,Enable)	\
    (This)->lpVtbl -> SetReverbStatus(This,Enable)

#define IABIT_GetChannelNum(This,ReturnVal)	\
    (This)->lpVtbl -> GetChannelNum(This,ReturnVal)

#define IABIT_GetEQEnable(This,ReturnVal)	\
    (This)->lpVtbl -> GetEQEnable(This,ReturnVal)

#define IABIT_SetEQEnable(This,Enable)	\
    (This)->lpVtbl -> SetEQEnable(This,Enable)

#define IABIT_SetSpkChannel(This,nChannel)	\
    (This)->lpVtbl -> SetSpkChannel(This,nChannel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_Init_Proxy( 
    IABIT * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IABIT_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_GetEQLevel_Proxy( 
    IABIT * This,
    /* [in] */ long Index,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IABIT_GetEQLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_SetEQLevel_Proxy( 
    IABIT * This,
    /* [in] */ long Index,
    /* [in] */ long SetVal);


void __RPC_STUB IABIT_SetEQLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_GetEAXIndex_Proxy( 
    IABIT * This,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IABIT_GetEAXIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_SetEAXIndex_Proxy( 
    IABIT * This,
    /* [in] */ long Index);


void __RPC_STUB IABIT_SetEAXIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_GetReverbStatus_Proxy( 
    IABIT * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IABIT_GetReverbStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_SetReverbStatus_Proxy( 
    IABIT * This,
    /* [in] */ BOOL Enable);


void __RPC_STUB IABIT_SetReverbStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_GetChannelNum_Proxy( 
    IABIT * This,
    /* [out] */ long *ReturnVal);


void __RPC_STUB IABIT_GetChannelNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_GetEQEnable_Proxy( 
    IABIT * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IABIT_GetEQEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_SetEQEnable_Proxy( 
    IABIT * This,
    /* [in] */ BOOL Enable);


void __RPC_STUB IABIT_SetEQEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IABIT_SetSpkChannel_Proxy( 
    IABIT * This,
    /* [in] */ int nChannel);


void __RPC_STUB IABIT_SetSpkChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IABIT_INTERFACE_DEFINED__ */


#ifndef __ISONY_INTERFACE_DEFINED__
#define __ISONY_INTERFACE_DEFINED__

/* interface ISONY */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISONY;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B27FD3E-75C0-4EC5-98DD-22B56E2BFC5A")
    ISONY : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutoSelectOutputFormat( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAutoSelectOutputFormat( 
            /* [in] */ BOOL bValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCSSMODE( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCSSMODE( 
            /* [in] */ BOOL bValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSPDIFSR( 
            /* [out] */ DWORD *pdwSampleRate) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSPDIFSR( 
            /* [in] */ DWORD dwSampleRate) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSPDIFOutStatus( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSPDIFOutStatus( 
            /* [in] */ BOOL bStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISONYVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISONY * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISONY * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISONY * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISONY * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISONY * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISONY * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISONY * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutoSelectOutputFormat )( 
            ISONY * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAutoSelectOutputFormat )( 
            ISONY * This,
            /* [in] */ BOOL bValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCSSMODE )( 
            ISONY * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCSSMODE )( 
            ISONY * This,
            /* [in] */ BOOL bValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ISONY * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSPDIFSR )( 
            ISONY * This,
            /* [out] */ DWORD *pdwSampleRate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSPDIFSR )( 
            ISONY * This,
            /* [in] */ DWORD dwSampleRate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSPDIFOutStatus )( 
            ISONY * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSPDIFOutStatus )( 
            ISONY * This,
            /* [in] */ BOOL bStatus);
        
        END_INTERFACE
    } ISONYVtbl;

    interface ISONY
    {
        CONST_VTBL struct ISONYVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISONY_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISONY_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISONY_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISONY_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISONY_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISONY_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISONY_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISONY_GetAutoSelectOutputFormat(This,ReturnVal)	\
    (This)->lpVtbl -> GetAutoSelectOutputFormat(This,ReturnVal)

#define ISONY_SetAutoSelectOutputFormat(This,bValue)	\
    (This)->lpVtbl -> SetAutoSelectOutputFormat(This,bValue)

#define ISONY_GetCSSMODE(This,ReturnVal)	\
    (This)->lpVtbl -> GetCSSMODE(This,ReturnVal)

#define ISONY_SetCSSMODE(This,bValue)	\
    (This)->lpVtbl -> SetCSSMODE(This,bValue)

#define ISONY_Init(This,ReturnVal)	\
    (This)->lpVtbl -> Init(This,ReturnVal)

#define ISONY_GetSPDIFSR(This,pdwSampleRate)	\
    (This)->lpVtbl -> GetSPDIFSR(This,pdwSampleRate)

#define ISONY_SetSPDIFSR(This,dwSampleRate)	\
    (This)->lpVtbl -> SetSPDIFSR(This,dwSampleRate)

#define ISONY_GetSPDIFOutStatus(This,ReturnVal)	\
    (This)->lpVtbl -> GetSPDIFOutStatus(This,ReturnVal)

#define ISONY_SetSPDIFOutStatus(This,bStatus)	\
    (This)->lpVtbl -> SetSPDIFOutStatus(This,bStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_GetAutoSelectOutputFormat_Proxy( 
    ISONY * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB ISONY_GetAutoSelectOutputFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_SetAutoSelectOutputFormat_Proxy( 
    ISONY * This,
    /* [in] */ BOOL bValue);


void __RPC_STUB ISONY_SetAutoSelectOutputFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_GetCSSMODE_Proxy( 
    ISONY * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB ISONY_GetCSSMODE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_SetCSSMODE_Proxy( 
    ISONY * This,
    /* [in] */ BOOL bValue);


void __RPC_STUB ISONY_SetCSSMODE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_Init_Proxy( 
    ISONY * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB ISONY_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_GetSPDIFSR_Proxy( 
    ISONY * This,
    /* [out] */ DWORD *pdwSampleRate);


void __RPC_STUB ISONY_GetSPDIFSR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_SetSPDIFSR_Proxy( 
    ISONY * This,
    /* [in] */ DWORD dwSampleRate);


void __RPC_STUB ISONY_SetSPDIFSR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_GetSPDIFOutStatus_Proxy( 
    ISONY * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB ISONY_GetSPDIFOutStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISONY_SetSPDIFOutStatus_Proxy( 
    ISONY * This,
    /* [in] */ BOOL bStatus);


void __RPC_STUB ISONY_SetSPDIFOutStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISONY_INTERFACE_DEFINED__ */


#ifndef __IRTLCSSAPI_INTERFACE_DEFINED__
#define __IRTLCSSAPI_INTERFACE_DEFINED__

/* interface IRTLCSSAPI */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRTLCSSAPI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C31A1F2E-67CC-4352-8AAD-602266840274")
    IRTLCSSAPI : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAutoSelectOutputFormat( 
            /* [in] */ BOOL bValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutoSelectOutputFormat( 
            /* [out] */ BOOL *ReturnValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCSSMODE( 
            /* [out] */ BOOL *ReturnValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCSSMODE( 
            /* [in] */ BOOL bBOOL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [out] */ BOOL *ReturnValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSPDIFSR( 
            /* [out] */ DWORD *ReturnValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSPDIFSR( 
            /* [in] */ DWORD dwSR) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSPDIFOutStatus( 
            /* [out] */ BOOL *ReturnVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSPDIFOutStatus( 
            /* [in] */ BOOL Enable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTLCSSAPIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTLCSSAPI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTLCSSAPI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTLCSSAPI * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTLCSSAPI * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTLCSSAPI * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTLCSSAPI * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTLCSSAPI * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAutoSelectOutputFormat )( 
            IRTLCSSAPI * This,
            /* [in] */ BOOL bValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutoSelectOutputFormat )( 
            IRTLCSSAPI * This,
            /* [out] */ BOOL *ReturnValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCSSMODE )( 
            IRTLCSSAPI * This,
            /* [out] */ BOOL *ReturnValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCSSMODE )( 
            IRTLCSSAPI * This,
            /* [in] */ BOOL bBOOL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IRTLCSSAPI * This,
            /* [out] */ BOOL *ReturnValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSPDIFSR )( 
            IRTLCSSAPI * This,
            /* [out] */ DWORD *ReturnValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSPDIFSR )( 
            IRTLCSSAPI * This,
            /* [in] */ DWORD dwSR);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSPDIFOutStatus )( 
            IRTLCSSAPI * This,
            /* [out] */ BOOL *ReturnVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSPDIFOutStatus )( 
            IRTLCSSAPI * This,
            /* [in] */ BOOL Enable);
        
        END_INTERFACE
    } IRTLCSSAPIVtbl;

    interface IRTLCSSAPI
    {
        CONST_VTBL struct IRTLCSSAPIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTLCSSAPI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTLCSSAPI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTLCSSAPI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTLCSSAPI_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRTLCSSAPI_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRTLCSSAPI_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRTLCSSAPI_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRTLCSSAPI_SetAutoSelectOutputFormat(This,bValue)	\
    (This)->lpVtbl -> SetAutoSelectOutputFormat(This,bValue)

#define IRTLCSSAPI_GetAutoSelectOutputFormat(This,ReturnValue)	\
    (This)->lpVtbl -> GetAutoSelectOutputFormat(This,ReturnValue)

#define IRTLCSSAPI_GetCSSMODE(This,ReturnValue)	\
    (This)->lpVtbl -> GetCSSMODE(This,ReturnValue)

#define IRTLCSSAPI_SetCSSMODE(This,bBOOL)	\
    (This)->lpVtbl -> SetCSSMODE(This,bBOOL)

#define IRTLCSSAPI_Init(This,ReturnValue)	\
    (This)->lpVtbl -> Init(This,ReturnValue)

#define IRTLCSSAPI_GetSPDIFSR(This,ReturnValue)	\
    (This)->lpVtbl -> GetSPDIFSR(This,ReturnValue)

#define IRTLCSSAPI_SetSPDIFSR(This,dwSR)	\
    (This)->lpVtbl -> SetSPDIFSR(This,dwSR)

#define IRTLCSSAPI_GetSPDIFOutStatus(This,ReturnVal)	\
    (This)->lpVtbl -> GetSPDIFOutStatus(This,ReturnVal)

#define IRTLCSSAPI_SetSPDIFOutStatus(This,Enable)	\
    (This)->lpVtbl -> SetSPDIFOutStatus(This,Enable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_SetAutoSelectOutputFormat_Proxy( 
    IRTLCSSAPI * This,
    /* [in] */ BOOL bValue);


void __RPC_STUB IRTLCSSAPI_SetAutoSelectOutputFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_GetAutoSelectOutputFormat_Proxy( 
    IRTLCSSAPI * This,
    /* [out] */ BOOL *ReturnValue);


void __RPC_STUB IRTLCSSAPI_GetAutoSelectOutputFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_GetCSSMODE_Proxy( 
    IRTLCSSAPI * This,
    /* [out] */ BOOL *ReturnValue);


void __RPC_STUB IRTLCSSAPI_GetCSSMODE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_SetCSSMODE_Proxy( 
    IRTLCSSAPI * This,
    /* [in] */ BOOL bBOOL);


void __RPC_STUB IRTLCSSAPI_SetCSSMODE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_Init_Proxy( 
    IRTLCSSAPI * This,
    /* [out] */ BOOL *ReturnValue);


void __RPC_STUB IRTLCSSAPI_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_GetSPDIFSR_Proxy( 
    IRTLCSSAPI * This,
    /* [out] */ DWORD *ReturnValue);


void __RPC_STUB IRTLCSSAPI_GetSPDIFSR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_SetSPDIFSR_Proxy( 
    IRTLCSSAPI * This,
    /* [in] */ DWORD dwSR);


void __RPC_STUB IRTLCSSAPI_SetSPDIFSR_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_GetSPDIFOutStatus_Proxy( 
    IRTLCSSAPI * This,
    /* [out] */ BOOL *ReturnVal);


void __RPC_STUB IRTLCSSAPI_GetSPDIFOutStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRTLCSSAPI_SetSPDIFOutStatus_Proxy( 
    IRTLCSSAPI * This,
    /* [in] */ BOOL Enable);


void __RPC_STUB IRTLCSSAPI_SetSPDIFOutStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTLCSSAPI_INTERFACE_DEFINED__ */


#ifndef __IPropSet10059_INTERFACE_DEFINED__
#define __IPropSet10059_INTERFACE_DEFINED__

/* interface IPropSet10059 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet10059;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5CD87431-AE49-4aa0-9346-792D2F81FF9D")
    IPropSet10059 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get_EAPD_Status( 
            /* [out] */ DWORD *dwEAPDStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set_EAPD_Status( 
            /* [in] */ DWORD dwEAPDStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet10059Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet10059 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet10059 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet10059 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet10059 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet10059 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet10059 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet10059 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get_EAPD_Status )( 
            IPropSet10059 * This,
            /* [out] */ DWORD *dwEAPDStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Set_EAPD_Status )( 
            IPropSet10059 * This,
            /* [in] */ DWORD dwEAPDStatus);
        
        END_INTERFACE
    } IPropSet10059Vtbl;

    interface IPropSet10059
    {
        CONST_VTBL struct IPropSet10059Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet10059_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet10059_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet10059_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet10059_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet10059_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet10059_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet10059_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet10059_Get_EAPD_Status(This,dwEAPDStatus)	\
    (This)->lpVtbl -> Get_EAPD_Status(This,dwEAPDStatus)

#define IPropSet10059_Set_EAPD_Status(This,dwEAPDStatus)	\
    (This)->lpVtbl -> Set_EAPD_Status(This,dwEAPDStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10059_Get_EAPD_Status_Proxy( 
    IPropSet10059 * This,
    /* [out] */ DWORD *dwEAPDStatus);


void __RPC_STUB IPropSet10059_Get_EAPD_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10059_Set_EAPD_Status_Proxy( 
    IPropSet10059 * This,
    /* [in] */ DWORD dwEAPDStatus);


void __RPC_STUB IPropSet10059_Set_EAPD_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet10059_INTERFACE_DEFINED__ */


#ifndef __IPropSet10060_INTERFACE_DEFINED__
#define __IPropSet10060_INTERFACE_DEFINED__

/* interface IPropSet10060 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet10060;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9061B497-F158-4E18-A904-5B5A6ACCF2EA")
    IPropSet10060 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTurnOffSPDIF( 
            /* [out] */ BOOL *bTurnOff) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTurnOffSPDIF( 
            /* [in] */ BOOL bTurnOff) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisableMuteInternalSpkStatus( 
            /* [out] */ DWORD *dwStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDisableMuteInternalSpkStatus( 
            /* [in] */ DWORD dwStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet10060Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet10060 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet10060 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet10060 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet10060 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet10060 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet10060 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet10060 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTurnOffSPDIF )( 
            IPropSet10060 * This,
            /* [out] */ BOOL *bTurnOff);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTurnOffSPDIF )( 
            IPropSet10060 * This,
            /* [in] */ BOOL bTurnOff);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisableMuteInternalSpkStatus )( 
            IPropSet10060 * This,
            /* [out] */ DWORD *dwStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDisableMuteInternalSpkStatus )( 
            IPropSet10060 * This,
            /* [in] */ DWORD dwStatus);
        
        END_INTERFACE
    } IPropSet10060Vtbl;

    interface IPropSet10060
    {
        CONST_VTBL struct IPropSet10060Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet10060_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet10060_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet10060_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet10060_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet10060_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet10060_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet10060_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet10060_GetTurnOffSPDIF(This,bTurnOff)	\
    (This)->lpVtbl -> GetTurnOffSPDIF(This,bTurnOff)

#define IPropSet10060_SetTurnOffSPDIF(This,bTurnOff)	\
    (This)->lpVtbl -> SetTurnOffSPDIF(This,bTurnOff)

#define IPropSet10060_GetDisableMuteInternalSpkStatus(This,dwStatus)	\
    (This)->lpVtbl -> GetDisableMuteInternalSpkStatus(This,dwStatus)

#define IPropSet10060_SetDisableMuteInternalSpkStatus(This,dwStatus)	\
    (This)->lpVtbl -> SetDisableMuteInternalSpkStatus(This,dwStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10060_GetTurnOffSPDIF_Proxy( 
    IPropSet10060 * This,
    /* [out] */ BOOL *bTurnOff);


void __RPC_STUB IPropSet10060_GetTurnOffSPDIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10060_SetTurnOffSPDIF_Proxy( 
    IPropSet10060 * This,
    /* [in] */ BOOL bTurnOff);


void __RPC_STUB IPropSet10060_SetTurnOffSPDIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10060_GetDisableMuteInternalSpkStatus_Proxy( 
    IPropSet10060 * This,
    /* [out] */ DWORD *dwStatus);


void __RPC_STUB IPropSet10060_GetDisableMuteInternalSpkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10060_SetDisableMuteInternalSpkStatus_Proxy( 
    IPropSet10060 * This,
    /* [in] */ DWORD dwStatus);


void __RPC_STUB IPropSet10060_SetDisableMuteInternalSpkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet10060_INTERFACE_DEFINED__ */


#ifndef __IPropSet10061_INTERFACE_DEFINED__
#define __IPropSet10061_INTERFACE_DEFINED__

/* interface IPropSet10061 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet10061;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C502E968-A3B7-4a7e-8060-106E737E6A35")
    IPropSet10061 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutoDectectAntenna( 
            /* [out] */ DWORD *dwAuto) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAutoDectectAntenna( 
            /* [in] */ DWORD dwAuto) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet10061Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet10061 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet10061 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet10061 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet10061 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet10061 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet10061 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet10061 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutoDectectAntenna )( 
            IPropSet10061 * This,
            /* [out] */ DWORD *dwAuto);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAutoDectectAntenna )( 
            IPropSet10061 * This,
            /* [in] */ DWORD dwAuto);
        
        END_INTERFACE
    } IPropSet10061Vtbl;

    interface IPropSet10061
    {
        CONST_VTBL struct IPropSet10061Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet10061_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet10061_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet10061_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet10061_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet10061_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet10061_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet10061_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet10061_GetAutoDectectAntenna(This,dwAuto)	\
    (This)->lpVtbl -> GetAutoDectectAntenna(This,dwAuto)

#define IPropSet10061_SetAutoDectectAntenna(This,dwAuto)	\
    (This)->lpVtbl -> SetAutoDectectAntenna(This,dwAuto)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10061_GetAutoDectectAntenna_Proxy( 
    IPropSet10061 * This,
    /* [out] */ DWORD *dwAuto);


void __RPC_STUB IPropSet10061_GetAutoDectectAntenna_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10061_SetAutoDectectAntenna_Proxy( 
    IPropSet10061 * This,
    /* [in] */ DWORD dwAuto);


void __RPC_STUB IPropSet10061_SetAutoDectectAntenna_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet10061_INTERFACE_DEFINED__ */


#ifndef __IPropSet10063_INTERFACE_DEFINED__
#define __IPropSet10063_INTERFACE_DEFINED__

/* interface IPropSet10063 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet10063;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B5F0A41-9D64-40eb-8637-1A8F42B05623")
    IPropSet10063 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPowerManagementSupported( 
            /* [out] */ BOOL *bPMSupported,
            /* [out] */ BOOL *bPMLevelSupported) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPowerManagementEnabled( 
            /* [out] */ BOOL *bEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPowerManagementEnabled( 
            /* [in] */ BOOL bEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPowerManagementOnlyBattery( 
            /* [out] */ BOOL *bOnlyBattery) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPowerManagementOnlyBattery( 
            /* [in] */ BOOL bOnlyBattery) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPowerManagementDelayTime( 
            /* [out] */ LONG *lDelayTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPowerManagementDelayTime( 
            /* [in] */ LONG lDelayTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet10063Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet10063 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet10063 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet10063 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet10063 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet10063 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet10063 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet10063 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPowerManagementSupported )( 
            IPropSet10063 * This,
            /* [out] */ BOOL *bPMSupported,
            /* [out] */ BOOL *bPMLevelSupported);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPowerManagementEnabled )( 
            IPropSet10063 * This,
            /* [out] */ BOOL *bEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPowerManagementEnabled )( 
            IPropSet10063 * This,
            /* [in] */ BOOL bEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPowerManagementOnlyBattery )( 
            IPropSet10063 * This,
            /* [out] */ BOOL *bOnlyBattery);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPowerManagementOnlyBattery )( 
            IPropSet10063 * This,
            /* [in] */ BOOL bOnlyBattery);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPowerManagementDelayTime )( 
            IPropSet10063 * This,
            /* [out] */ LONG *lDelayTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPowerManagementDelayTime )( 
            IPropSet10063 * This,
            /* [in] */ LONG lDelayTime);
        
        END_INTERFACE
    } IPropSet10063Vtbl;

    interface IPropSet10063
    {
        CONST_VTBL struct IPropSet10063Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet10063_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet10063_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet10063_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet10063_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet10063_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet10063_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet10063_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet10063_GetPowerManagementSupported(This,bPMSupported,bPMLevelSupported)	\
    (This)->lpVtbl -> GetPowerManagementSupported(This,bPMSupported,bPMLevelSupported)

#define IPropSet10063_GetPowerManagementEnabled(This,bEnabled)	\
    (This)->lpVtbl -> GetPowerManagementEnabled(This,bEnabled)

#define IPropSet10063_SetPowerManagementEnabled(This,bEnabled)	\
    (This)->lpVtbl -> SetPowerManagementEnabled(This,bEnabled)

#define IPropSet10063_GetPowerManagementOnlyBattery(This,bOnlyBattery)	\
    (This)->lpVtbl -> GetPowerManagementOnlyBattery(This,bOnlyBattery)

#define IPropSet10063_SetPowerManagementOnlyBattery(This,bOnlyBattery)	\
    (This)->lpVtbl -> SetPowerManagementOnlyBattery(This,bOnlyBattery)

#define IPropSet10063_GetPowerManagementDelayTime(This,lDelayTime)	\
    (This)->lpVtbl -> GetPowerManagementDelayTime(This,lDelayTime)

#define IPropSet10063_SetPowerManagementDelayTime(This,lDelayTime)	\
    (This)->lpVtbl -> SetPowerManagementDelayTime(This,lDelayTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10063_GetPowerManagementSupported_Proxy( 
    IPropSet10063 * This,
    /* [out] */ BOOL *bPMSupported,
    /* [out] */ BOOL *bPMLevelSupported);


void __RPC_STUB IPropSet10063_GetPowerManagementSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10063_GetPowerManagementEnabled_Proxy( 
    IPropSet10063 * This,
    /* [out] */ BOOL *bEnabled);


void __RPC_STUB IPropSet10063_GetPowerManagementEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10063_SetPowerManagementEnabled_Proxy( 
    IPropSet10063 * This,
    /* [in] */ BOOL bEnabled);


void __RPC_STUB IPropSet10063_SetPowerManagementEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10063_GetPowerManagementOnlyBattery_Proxy( 
    IPropSet10063 * This,
    /* [out] */ BOOL *bOnlyBattery);


void __RPC_STUB IPropSet10063_GetPowerManagementOnlyBattery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10063_SetPowerManagementOnlyBattery_Proxy( 
    IPropSet10063 * This,
    /* [in] */ BOOL bOnlyBattery);


void __RPC_STUB IPropSet10063_SetPowerManagementOnlyBattery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10063_GetPowerManagementDelayTime_Proxy( 
    IPropSet10063 * This,
    /* [out] */ LONG *lDelayTime);


void __RPC_STUB IPropSet10063_GetPowerManagementDelayTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet10063_SetPowerManagementDelayTime_Proxy( 
    IPropSet10063 * This,
    /* [in] */ LONG lDelayTime);


void __RPC_STUB IPropSet10063_SetPowerManagementDelayTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet10063_INTERFACE_DEFINED__ */


#ifndef __IPropSet20065_INTERFACE_DEFINED__
#define __IPropSet20065_INTERFACE_DEFINED__

/* interface IPropSet20065 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20065;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F8F4AEB-9090-4f5b-98F2-000A08FC4A04")
    IPropSet20065 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDeviceCount( 
            ULONG *ulCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDeviceName( 
            /* [in] */ ULONG ulIndex,
            /* [out] */ WCHAR *cDeviceName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetEqEnable( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEqEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetEqEnable( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEqEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetEqLevel( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ ULONG ulEqIndex,
            /* [out] */ LONG *lEqLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetEqLevel( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ ULONG ulEqIndex,
            /* [in] */ LONG lEqLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20065Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20065 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20065 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20065 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20065 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20065 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20065 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20065 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDeviceCount )( 
            IPropSet20065 * This,
            ULONG *ulCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDeviceName )( 
            IPropSet20065 * This,
            /* [in] */ ULONG ulIndex,
            /* [out] */ WCHAR *cDeviceName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetEqEnable )( 
            IPropSet20065 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEqEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetEqEnable )( 
            IPropSet20065 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEqEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetEqLevel )( 
            IPropSet20065 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ ULONG ulEqIndex,
            /* [out] */ LONG *lEqLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetEqLevel )( 
            IPropSet20065 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ ULONG ulEqIndex,
            /* [in] */ LONG lEqLevel);
        
        END_INTERFACE
    } IPropSet20065Vtbl;

    interface IPropSet20065
    {
        CONST_VTBL struct IPropSet20065Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20065_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20065_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20065_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20065_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20065_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20065_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20065_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20065_GetDeviceCount(This,ulCount)	\
    (This)->lpVtbl -> GetDeviceCount(This,ulCount)

#define IPropSet20065_GetDeviceName(This,ulIndex,cDeviceName)	\
    (This)->lpVtbl -> GetDeviceName(This,ulIndex,cDeviceName)

#define IPropSet20065_VistaGetEqEnable(This,ulDeviceIndex,bEqEnable)	\
    (This)->lpVtbl -> VistaGetEqEnable(This,ulDeviceIndex,bEqEnable)

#define IPropSet20065_VistaSetEqEnable(This,ulDeviceIndex,bEqEnable)	\
    (This)->lpVtbl -> VistaSetEqEnable(This,ulDeviceIndex,bEqEnable)

#define IPropSet20065_VistaGetEqLevel(This,ulDeviceIndex,ulEqIndex,lEqLevel)	\
    (This)->lpVtbl -> VistaGetEqLevel(This,ulDeviceIndex,ulEqIndex,lEqLevel)

#define IPropSet20065_VistaSetEqLevel(This,ulDeviceIndex,ulEqIndex,lEqLevel)	\
    (This)->lpVtbl -> VistaSetEqLevel(This,ulDeviceIndex,ulEqIndex,lEqLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20065_GetDeviceCount_Proxy( 
    IPropSet20065 * This,
    ULONG *ulCount);


void __RPC_STUB IPropSet20065_GetDeviceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20065_GetDeviceName_Proxy( 
    IPropSet20065 * This,
    /* [in] */ ULONG ulIndex,
    /* [out] */ WCHAR *cDeviceName);


void __RPC_STUB IPropSet20065_GetDeviceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20065_VistaGetEqEnable_Proxy( 
    IPropSet20065 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ BOOL *bEqEnable);


void __RPC_STUB IPropSet20065_VistaGetEqEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20065_VistaSetEqEnable_Proxy( 
    IPropSet20065 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ BOOL bEqEnable);


void __RPC_STUB IPropSet20065_VistaSetEqEnable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20065_VistaGetEqLevel_Proxy( 
    IPropSet20065 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ ULONG ulEqIndex,
    /* [out] */ LONG *lEqLevel);


void __RPC_STUB IPropSet20065_VistaGetEqLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20065_VistaSetEqLevel_Proxy( 
    IPropSet20065 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ ULONG ulEqIndex,
    /* [in] */ LONG lEqLevel);


void __RPC_STUB IPropSet20065_VistaSetEqLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20065_INTERFACE_DEFINED__ */


#ifndef __IPropSet20066_INTERFACE_DEFINED__
#define __IPropSet20066_INTERFACE_DEFINED__

/* interface IPropSet20066 */
/* [unique][helpstring][dual][uuid][object] */ 

typedef /* [public] */ 
enum __MIDL_IPropSet20066_0001
    {	PLAYBACK_STOP_AND_RECORD_STOP	= 0,
	PLAYBACK_PLAYING_ONLY	= PLAYBACK_STOP_AND_RECORD_STOP + 1,
	RECORD_ONLY	= PLAYBACK_PLAYING_ONLY + 1,
	PLAYBACK_AND_RECORD	= RECORD_ONLY + 1
    } 	VISTA_AUDIO_STATE;


EXTERN_C const IID IID_IPropSet20066;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F8F4AEB-9090-4f5b-98F2-000A08FC4A05")
    IPropSet20066 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVistaAudioState( 
            /* [out] */ LONG *AudioState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterAudioStateEvent( 
            /* [in] */ OLE_HANDLE AudioEvent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20066Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20066 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20066 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20066 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20066 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20066 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20066 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20066 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVistaAudioState )( 
            IPropSet20066 * This,
            /* [out] */ LONG *AudioState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RegisterAudioStateEvent )( 
            IPropSet20066 * This,
            /* [in] */ OLE_HANDLE AudioEvent);
        
        END_INTERFACE
    } IPropSet20066Vtbl;

    interface IPropSet20066
    {
        CONST_VTBL struct IPropSet20066Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20066_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20066_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20066_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20066_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20066_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20066_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20066_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20066_GetVistaAudioState(This,AudioState)	\
    (This)->lpVtbl -> GetVistaAudioState(This,AudioState)

#define IPropSet20066_RegisterAudioStateEvent(This,AudioEvent)	\
    (This)->lpVtbl -> RegisterAudioStateEvent(This,AudioEvent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20066_GetVistaAudioState_Proxy( 
    IPropSet20066 * This,
    /* [out] */ LONG *AudioState);


void __RPC_STUB IPropSet20066_GetVistaAudioState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20066_RegisterAudioStateEvent_Proxy( 
    IPropSet20066 * This,
    /* [in] */ OLE_HANDLE AudioEvent);


void __RPC_STUB IPropSet20066_RegisterAudioStateEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20066_INTERFACE_DEFINED__ */


#ifndef __IPropSet20068_INTERFACE_DEFINED__
#define __IPropSet20068_INTERFACE_DEFINED__

/* interface IPropSet20068 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20068;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F8F4AEB-9090-4f5b-98F2-000A08FC4A06")
    IPropSet20068 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVistaD2PowerStateControl( 
            /* [out] */ DWORD *dwPowerControl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVistaD2PowerStateControl( 
            /* [in] */ DWORD dwPowerControl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetEqIndex( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ LONG *Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetEqIndex( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetVoiceCancelEnabled( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetVoiceCancelEnabled( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetKeyValue( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ LONG *Key) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetKeyValue( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG Key) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20068Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20068 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20068 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20068 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20068 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20068 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20068 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20068 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVistaD2PowerStateControl )( 
            IPropSet20068 * This,
            /* [out] */ DWORD *dwPowerControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVistaD2PowerStateControl )( 
            IPropSet20068 * This,
            /* [in] */ DWORD dwPowerControl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetEqIndex )( 
            IPropSet20068 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ LONG *Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetEqIndex )( 
            IPropSet20068 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetVoiceCancelEnabled )( 
            IPropSet20068 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetVoiceCancelEnabled )( 
            IPropSet20068 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetKeyValue )( 
            IPropSet20068 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ LONG *Key);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetKeyValue )( 
            IPropSet20068 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG Key);
        
        END_INTERFACE
    } IPropSet20068Vtbl;

    interface IPropSet20068
    {
        CONST_VTBL struct IPropSet20068Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20068_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20068_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20068_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20068_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20068_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20068_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20068_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20068_GetVistaD2PowerStateControl(This,dwPowerControl)	\
    (This)->lpVtbl -> GetVistaD2PowerStateControl(This,dwPowerControl)

#define IPropSet20068_SetVistaD2PowerStateControl(This,dwPowerControl)	\
    (This)->lpVtbl -> SetVistaD2PowerStateControl(This,dwPowerControl)

#define IPropSet20068_VistaGetEqIndex(This,ulDeviceIndex,Index)	\
    (This)->lpVtbl -> VistaGetEqIndex(This,ulDeviceIndex,Index)

#define IPropSet20068_VistaSetEqIndex(This,ulDeviceIndex,Index)	\
    (This)->lpVtbl -> VistaSetEqIndex(This,ulDeviceIndex,Index)

#define IPropSet20068_VistaGetVoiceCancelEnabled(This,ulDeviceIndex,bEnabled)	\
    (This)->lpVtbl -> VistaGetVoiceCancelEnabled(This,ulDeviceIndex,bEnabled)

#define IPropSet20068_VistaSetVoiceCancelEnabled(This,ulDeviceIndex,bEnabled)	\
    (This)->lpVtbl -> VistaSetVoiceCancelEnabled(This,ulDeviceIndex,bEnabled)

#define IPropSet20068_VistaGetKeyValue(This,ulDeviceIndex,Key)	\
    (This)->lpVtbl -> VistaGetKeyValue(This,ulDeviceIndex,Key)

#define IPropSet20068_VistaSetKeyValue(This,ulDeviceIndex,Key)	\
    (This)->lpVtbl -> VistaSetKeyValue(This,ulDeviceIndex,Key)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_GetVistaD2PowerStateControl_Proxy( 
    IPropSet20068 * This,
    /* [out] */ DWORD *dwPowerControl);


void __RPC_STUB IPropSet20068_GetVistaD2PowerStateControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_SetVistaD2PowerStateControl_Proxy( 
    IPropSet20068 * This,
    /* [in] */ DWORD dwPowerControl);


void __RPC_STUB IPropSet20068_SetVistaD2PowerStateControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_VistaGetEqIndex_Proxy( 
    IPropSet20068 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ LONG *Index);


void __RPC_STUB IPropSet20068_VistaGetEqIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_VistaSetEqIndex_Proxy( 
    IPropSet20068 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG Index);


void __RPC_STUB IPropSet20068_VistaSetEqIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_VistaGetVoiceCancelEnabled_Proxy( 
    IPropSet20068 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ BOOL *bEnabled);


void __RPC_STUB IPropSet20068_VistaGetVoiceCancelEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_VistaSetVoiceCancelEnabled_Proxy( 
    IPropSet20068 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ BOOL bEnabled);


void __RPC_STUB IPropSet20068_VistaSetVoiceCancelEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_VistaGetKeyValue_Proxy( 
    IPropSet20068 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ LONG *Key);


void __RPC_STUB IPropSet20068_VistaGetKeyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20068_VistaSetKeyValue_Proxy( 
    IPropSet20068 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG Key);


void __RPC_STUB IPropSet20068_VistaSetKeyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20068_INTERFACE_DEFINED__ */


#ifndef __IPropSet20069_INTERFACE_DEFINED__
#define __IPropSet20069_INTERFACE_DEFINED__

/* interface IPropSet20069 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20069;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F8F4AEB-9090-4f5b-98F2-000A08FC4A07")
    IPropSet20069 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetMicNoiseSuppression( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetMicNoiseSuppression( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetMicBeamForming( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetMicBeamForming( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetMicAEC( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetMicAEC( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20069Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20069 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20069 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20069 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20069 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20069 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20069 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20069 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetMicNoiseSuppression )( 
            IPropSet20069 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetMicNoiseSuppression )( 
            IPropSet20069 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetMicBeamForming )( 
            IPropSet20069 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetMicBeamForming )( 
            IPropSet20069 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetMicAEC )( 
            IPropSet20069 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetMicAEC )( 
            IPropSet20069 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnable);
        
        END_INTERFACE
    } IPropSet20069Vtbl;

    interface IPropSet20069
    {
        CONST_VTBL struct IPropSet20069Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20069_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20069_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20069_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20069_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20069_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20069_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20069_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20069_VistaGetMicNoiseSuppression(This,ulDeviceIndex,bEnable)	\
    (This)->lpVtbl -> VistaGetMicNoiseSuppression(This,ulDeviceIndex,bEnable)

#define IPropSet20069_VistaSetMicNoiseSuppression(This,ulDeviceIndex,bEnable)	\
    (This)->lpVtbl -> VistaSetMicNoiseSuppression(This,ulDeviceIndex,bEnable)

#define IPropSet20069_VistaGetMicBeamForming(This,ulDeviceIndex,bEnable)	\
    (This)->lpVtbl -> VistaGetMicBeamForming(This,ulDeviceIndex,bEnable)

#define IPropSet20069_VistaSetMicBeamForming(This,ulDeviceIndex,bEnable)	\
    (This)->lpVtbl -> VistaSetMicBeamForming(This,ulDeviceIndex,bEnable)

#define IPropSet20069_VistaGetMicAEC(This,ulDeviceIndex,bEnable)	\
    (This)->lpVtbl -> VistaGetMicAEC(This,ulDeviceIndex,bEnable)

#define IPropSet20069_VistaSetMicAEC(This,ulDeviceIndex,bEnable)	\
    (This)->lpVtbl -> VistaSetMicAEC(This,ulDeviceIndex,bEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20069_VistaGetMicNoiseSuppression_Proxy( 
    IPropSet20069 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet20069_VistaGetMicNoiseSuppression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20069_VistaSetMicNoiseSuppression_Proxy( 
    IPropSet20069 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet20069_VistaSetMicNoiseSuppression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20069_VistaGetMicBeamForming_Proxy( 
    IPropSet20069 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet20069_VistaGetMicBeamForming_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20069_VistaSetMicBeamForming_Proxy( 
    IPropSet20069 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet20069_VistaSetMicBeamForming_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20069_VistaGetMicAEC_Proxy( 
    IPropSet20069 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ BOOL *bEnable);


void __RPC_STUB IPropSet20069_VistaGetMicAEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20069_VistaSetMicAEC_Proxy( 
    IPropSet20069 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPropSet20069_VistaSetMicAEC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20069_INTERFACE_DEFINED__ */


#ifndef __IPropSet20070_INTERFACE_DEFINED__
#define __IPropSet20070_INTERFACE_DEFINED__

/* interface IPropSet20070 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20070;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F8F4AEB-9090-4f5b-98F2-000A08FC4A08")
    IPropSet20070 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetDefaultDevice( 
            /* [in] */ BOOL bIsPlayback,
            /* [out] */ WCHAR *wcDeviceID,
            /* [out] */ BOOL *bIsDefDeviceID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetDefaultDevice( 
            /* [in] */ BOOL bIsPlayback,
            /* [in] */ WCHAR *wcDeviceID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20070Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20070 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20070 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20070 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20070 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20070 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20070 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20070 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetDefaultDevice )( 
            IPropSet20070 * This,
            /* [in] */ BOOL bIsPlayback,
            /* [out] */ WCHAR *wcDeviceID,
            /* [out] */ BOOL *bIsDefDeviceID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetDefaultDevice )( 
            IPropSet20070 * This,
            /* [in] */ BOOL bIsPlayback,
            /* [in] */ WCHAR *wcDeviceID);
        
        END_INTERFACE
    } IPropSet20070Vtbl;

    interface IPropSet20070
    {
        CONST_VTBL struct IPropSet20070Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20070_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20070_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20070_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20070_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20070_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20070_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20070_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20070_VistaGetDefaultDevice(This,bIsPlayback,wcDeviceID,bIsDefDeviceID)	\
    (This)->lpVtbl -> VistaGetDefaultDevice(This,bIsPlayback,wcDeviceID,bIsDefDeviceID)

#define IPropSet20070_VistaSetDefaultDevice(This,bIsPlayback,wcDeviceID)	\
    (This)->lpVtbl -> VistaSetDefaultDevice(This,bIsPlayback,wcDeviceID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20070_VistaGetDefaultDevice_Proxy( 
    IPropSet20070 * This,
    /* [in] */ BOOL bIsPlayback,
    /* [out] */ WCHAR *wcDeviceID,
    /* [out] */ BOOL *bIsDefDeviceID);


void __RPC_STUB IPropSet20070_VistaGetDefaultDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20070_VistaSetDefaultDevice_Proxy( 
    IPropSet20070 * This,
    /* [in] */ BOOL bIsPlayback,
    /* [in] */ WCHAR *wcDeviceID);


void __RPC_STUB IPropSet20070_VistaSetDefaultDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20070_INTERFACE_DEFINED__ */


#ifndef __IPropSet20072_INTERFACE_DEFINED__
#define __IPropSet20072_INTERFACE_DEFINED__

/* interface IPropSet20072 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20072;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4D8A8F85-EB19-4d33-98A3-9B1FDBF394D3")
    IPropSet20072 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetMonoMute( 
            /* [in] */ DWORD dwMute) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20072Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20072 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20072 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20072 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20072 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20072 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20072 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20072 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetMonoMute )( 
            IPropSet20072 * This,
            /* [in] */ DWORD dwMute);
        
        END_INTERFACE
    } IPropSet20072Vtbl;

    interface IPropSet20072
    {
        CONST_VTBL struct IPropSet20072Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20072_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20072_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20072_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20072_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20072_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20072_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20072_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20072_VistaSetMonoMute(This,dwMute)	\
    (This)->lpVtbl -> VistaSetMonoMute(This,dwMute)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20072_VistaSetMonoMute_Proxy( 
    IPropSet20072 * This,
    /* [in] */ DWORD dwMute);


void __RPC_STUB IPropSet20072_VistaSetMonoMute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20072_INTERFACE_DEFINED__ */


#ifndef __IPropSet20080_INTERFACE_DEFINED__
#define __IPropSet20080_INTERFACE_DEFINED__

/* interface IPropSet20080 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20080;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48A11455-E534-4e9d-9630-9C71BB97A58F")
    IPropSet20080 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCodecAddress( 
            /* [out] */ DWORD *dwCodecAddress,
            /* [out] */ DWORD *fgID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendVerb( 
            /* [in] */ ULONG cad,
            /* [in] */ ULONG WidgetId,
            /* [in] */ ULONG VerbId,
            /* [in] */ ULONG Payload,
            /* [retval][out] */ ULONG *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendParameter( 
            /* [in] */ ULONG cad,
            /* [in] */ ULONG WidgetId,
            /* [in] */ ULONG ParameterId,
            /* [retval][out] */ ULONG *retVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20080Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20080 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20080 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20080 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20080 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20080 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20080 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20080 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCodecAddress )( 
            IPropSet20080 * This,
            /* [out] */ DWORD *dwCodecAddress,
            /* [out] */ DWORD *fgID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendVerb )( 
            IPropSet20080 * This,
            /* [in] */ ULONG cad,
            /* [in] */ ULONG WidgetId,
            /* [in] */ ULONG VerbId,
            /* [in] */ ULONG Payload,
            /* [retval][out] */ ULONG *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendParameter )( 
            IPropSet20080 * This,
            /* [in] */ ULONG cad,
            /* [in] */ ULONG WidgetId,
            /* [in] */ ULONG ParameterId,
            /* [retval][out] */ ULONG *retVal);
        
        END_INTERFACE
    } IPropSet20080Vtbl;

    interface IPropSet20080
    {
        CONST_VTBL struct IPropSet20080Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20080_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20080_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20080_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20080_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20080_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20080_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20080_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20080_GetCodecAddress(This,dwCodecAddress,fgID)	\
    (This)->lpVtbl -> GetCodecAddress(This,dwCodecAddress,fgID)

#define IPropSet20080_SendVerb(This,cad,WidgetId,VerbId,Payload,retVal)	\
    (This)->lpVtbl -> SendVerb(This,cad,WidgetId,VerbId,Payload,retVal)

#define IPropSet20080_SendParameter(This,cad,WidgetId,ParameterId,retVal)	\
    (This)->lpVtbl -> SendParameter(This,cad,WidgetId,ParameterId,retVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20080_GetCodecAddress_Proxy( 
    IPropSet20080 * This,
    /* [out] */ DWORD *dwCodecAddress,
    /* [out] */ DWORD *fgID);


void __RPC_STUB IPropSet20080_GetCodecAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20080_SendVerb_Proxy( 
    IPropSet20080 * This,
    /* [in] */ ULONG cad,
    /* [in] */ ULONG WidgetId,
    /* [in] */ ULONG VerbId,
    /* [in] */ ULONG Payload,
    /* [retval][out] */ ULONG *retVal);


void __RPC_STUB IPropSet20080_SendVerb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20080_SendParameter_Proxy( 
    IPropSet20080 * This,
    /* [in] */ ULONG cad,
    /* [in] */ ULONG WidgetId,
    /* [in] */ ULONG ParameterId,
    /* [retval][out] */ ULONG *retVal);


void __RPC_STUB IPropSet20080_SendParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20080_INTERFACE_DEFINED__ */


#ifndef __IPropSet20082_INTERFACE_DEFINED__
#define __IPropSet20082_INTERFACE_DEFINED__

/* interface IPropSet20082 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20082;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC057E92-289C-422e-A61A-48462D97E089")
    IPropSet20082 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetDeviceInfo( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ ULONG *DeviceFormFactor,
            /* [out] */ BOOL *bIsPlayback,
            /* [out] */ BOOL *bIsDefDevice,
            /* [out] */ WCHAR *wcDeviceID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20082Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20082 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20082 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20082 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20082 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20082 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20082 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20082 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetDeviceInfo )( 
            IPropSet20082 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ ULONG *DeviceFormFactor,
            /* [out] */ BOOL *bIsPlayback,
            /* [out] */ BOOL *bIsDefDevice,
            /* [out] */ WCHAR *wcDeviceID);
        
        END_INTERFACE
    } IPropSet20082Vtbl;

    interface IPropSet20082
    {
        CONST_VTBL struct IPropSet20082Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20082_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20082_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20082_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20082_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20082_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20082_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20082_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20082_VistaGetDeviceInfo(This,ulDeviceIndex,DeviceFormFactor,bIsPlayback,bIsDefDevice,wcDeviceID)	\
    (This)->lpVtbl -> VistaGetDeviceInfo(This,ulDeviceIndex,DeviceFormFactor,bIsPlayback,bIsDefDevice,wcDeviceID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20082_VistaGetDeviceInfo_Proxy( 
    IPropSet20082 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ ULONG *DeviceFormFactor,
    /* [out] */ BOOL *bIsPlayback,
    /* [out] */ BOOL *bIsDefDevice,
    /* [out] */ WCHAR *wcDeviceID);


void __RPC_STUB IPropSet20082_VistaGetDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20082_INTERFACE_DEFINED__ */


#ifndef __IPropSet20083_INTERFACE_DEFINED__
#define __IPropSet20083_INTERFACE_DEFINED__

/* interface IPropSet20083 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20083;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B8FF54B-0054-4918-BCBF-4406A4AB7C54")
    IPropSet20083 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetRoomCorrectionEnabled( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetRoomCorrectionEnabled( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetRoomCorrectScaleMode( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ LONG *ScaleMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetRoomCorrectScaleMode( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG ScaleMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetRoomCorrectGain( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [out] */ LONG *Gain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetRoomCorrectGain( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [in] */ LONG Gain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetRoomCorrectDistance( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [out] */ LONG *Distance) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetRoomCorrectDistance( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [in] */ LONG Distance) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetRoomCorrectDistRange( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [out] */ LONG *MinRange,
            /* [out] */ LONG *MaxRange) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetDVDASupportedWithFilter( 
            /* [in] */ WCHAR *FilterName,
            /* [out] */ BOOL *Supported) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20083Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20083 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20083 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20083 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20083 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20083 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20083 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20083 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetRoomCorrectionEnabled )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *bEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetRoomCorrectionEnabled )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL bEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetRoomCorrectScaleMode )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ LONG *ScaleMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetRoomCorrectScaleMode )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG ScaleMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetRoomCorrectGain )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [out] */ LONG *Gain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetRoomCorrectGain )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [in] */ LONG Gain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetRoomCorrectDistance )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [out] */ LONG *Distance);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetRoomCorrectDistance )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [in] */ LONG Distance);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetRoomCorrectDistRange )( 
            IPropSet20083 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ LONG SpeakerIndex,
            /* [out] */ LONG *MinRange,
            /* [out] */ LONG *MaxRange);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetDVDASupportedWithFilter )( 
            IPropSet20083 * This,
            /* [in] */ WCHAR *FilterName,
            /* [out] */ BOOL *Supported);
        
        END_INTERFACE
    } IPropSet20083Vtbl;

    interface IPropSet20083
    {
        CONST_VTBL struct IPropSet20083Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20083_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20083_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20083_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20083_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20083_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20083_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20083_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20083_VistaGetRoomCorrectionEnabled(This,ulDeviceIndex,bEnabled)	\
    (This)->lpVtbl -> VistaGetRoomCorrectionEnabled(This,ulDeviceIndex,bEnabled)

#define IPropSet20083_VistaSetRoomCorrectionEnabled(This,ulDeviceIndex,bEnabled)	\
    (This)->lpVtbl -> VistaSetRoomCorrectionEnabled(This,ulDeviceIndex,bEnabled)

#define IPropSet20083_VistaGetRoomCorrectScaleMode(This,ulDeviceIndex,ScaleMode)	\
    (This)->lpVtbl -> VistaGetRoomCorrectScaleMode(This,ulDeviceIndex,ScaleMode)

#define IPropSet20083_VistaSetRoomCorrectScaleMode(This,ulDeviceIndex,ScaleMode)	\
    (This)->lpVtbl -> VistaSetRoomCorrectScaleMode(This,ulDeviceIndex,ScaleMode)

#define IPropSet20083_VistaGetRoomCorrectGain(This,ulDeviceIndex,SpeakerIndex,Gain)	\
    (This)->lpVtbl -> VistaGetRoomCorrectGain(This,ulDeviceIndex,SpeakerIndex,Gain)

#define IPropSet20083_VistaSetRoomCorrectGain(This,ulDeviceIndex,SpeakerIndex,Gain)	\
    (This)->lpVtbl -> VistaSetRoomCorrectGain(This,ulDeviceIndex,SpeakerIndex,Gain)

#define IPropSet20083_VistaGetRoomCorrectDistance(This,ulDeviceIndex,SpeakerIndex,Distance)	\
    (This)->lpVtbl -> VistaGetRoomCorrectDistance(This,ulDeviceIndex,SpeakerIndex,Distance)

#define IPropSet20083_VistaSetRoomCorrectDistance(This,ulDeviceIndex,SpeakerIndex,Distance)	\
    (This)->lpVtbl -> VistaSetRoomCorrectDistance(This,ulDeviceIndex,SpeakerIndex,Distance)

#define IPropSet20083_VistaGetRoomCorrectDistRange(This,ulDeviceIndex,SpeakerIndex,MinRange,MaxRange)	\
    (This)->lpVtbl -> VistaGetRoomCorrectDistRange(This,ulDeviceIndex,SpeakerIndex,MinRange,MaxRange)

#define IPropSet20083_VistaGetDVDASupportedWithFilter(This,FilterName,Supported)	\
    (This)->lpVtbl -> VistaGetDVDASupportedWithFilter(This,FilterName,Supported)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaGetRoomCorrectionEnabled_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ BOOL *bEnabled);


void __RPC_STUB IPropSet20083_VistaGetRoomCorrectionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaSetRoomCorrectionEnabled_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ BOOL bEnabled);


void __RPC_STUB IPropSet20083_VistaSetRoomCorrectionEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaGetRoomCorrectScaleMode_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ LONG *ScaleMode);


void __RPC_STUB IPropSet20083_VistaGetRoomCorrectScaleMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaSetRoomCorrectScaleMode_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG ScaleMode);


void __RPC_STUB IPropSet20083_VistaSetRoomCorrectScaleMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaGetRoomCorrectGain_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG SpeakerIndex,
    /* [out] */ LONG *Gain);


void __RPC_STUB IPropSet20083_VistaGetRoomCorrectGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaSetRoomCorrectGain_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG SpeakerIndex,
    /* [in] */ LONG Gain);


void __RPC_STUB IPropSet20083_VistaSetRoomCorrectGain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaGetRoomCorrectDistance_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG SpeakerIndex,
    /* [out] */ LONG *Distance);


void __RPC_STUB IPropSet20083_VistaGetRoomCorrectDistance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaSetRoomCorrectDistance_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG SpeakerIndex,
    /* [in] */ LONG Distance);


void __RPC_STUB IPropSet20083_VistaSetRoomCorrectDistance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaGetRoomCorrectDistRange_Proxy( 
    IPropSet20083 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ LONG SpeakerIndex,
    /* [out] */ LONG *MinRange,
    /* [out] */ LONG *MaxRange);


void __RPC_STUB IPropSet20083_VistaGetRoomCorrectDistRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20083_VistaGetDVDASupportedWithFilter_Proxy( 
    IPropSet20083 * This,
    /* [in] */ WCHAR *FilterName,
    /* [out] */ BOOL *Supported);


void __RPC_STUB IPropSet20083_VistaGetDVDASupportedWithFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20083_INTERFACE_DEFINED__ */


#ifndef __IPropSet20086_INTERFACE_DEFINED__
#define __IPropSet20086_INTERFACE_DEFINED__

/* interface IPropSet20086 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPropSet20086;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF97231B-A45C-4b51-8A6C-6E3C8CEBE4B9")
    IPropSet20086 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetEaxIndex( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ ULONG *EaxIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetEaxIndex( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ ULONG EaxIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaGetEaxEnabled( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *Enabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VistaSetEaxEnabled( 
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL Enabled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropSet20086Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropSet20086 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropSet20086 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropSet20086 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPropSet20086 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPropSet20086 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPropSet20086 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPropSet20086 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetEaxIndex )( 
            IPropSet20086 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ ULONG *EaxIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetEaxIndex )( 
            IPropSet20086 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ ULONG EaxIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaGetEaxEnabled )( 
            IPropSet20086 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [out] */ BOOL *Enabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VistaSetEaxEnabled )( 
            IPropSet20086 * This,
            /* [in] */ ULONG ulDeviceIndex,
            /* [in] */ BOOL Enabled);
        
        END_INTERFACE
    } IPropSet20086Vtbl;

    interface IPropSet20086
    {
        CONST_VTBL struct IPropSet20086Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropSet20086_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropSet20086_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropSet20086_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropSet20086_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPropSet20086_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPropSet20086_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPropSet20086_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPropSet20086_VistaGetEaxIndex(This,ulDeviceIndex,EaxIndex)	\
    (This)->lpVtbl -> VistaGetEaxIndex(This,ulDeviceIndex,EaxIndex)

#define IPropSet20086_VistaSetEaxIndex(This,ulDeviceIndex,EaxIndex)	\
    (This)->lpVtbl -> VistaSetEaxIndex(This,ulDeviceIndex,EaxIndex)

#define IPropSet20086_VistaGetEaxEnabled(This,ulDeviceIndex,Enabled)	\
    (This)->lpVtbl -> VistaGetEaxEnabled(This,ulDeviceIndex,Enabled)

#define IPropSet20086_VistaSetEaxEnabled(This,ulDeviceIndex,Enabled)	\
    (This)->lpVtbl -> VistaSetEaxEnabled(This,ulDeviceIndex,Enabled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20086_VistaGetEaxIndex_Proxy( 
    IPropSet20086 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ ULONG *EaxIndex);


void __RPC_STUB IPropSet20086_VistaGetEaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20086_VistaSetEaxIndex_Proxy( 
    IPropSet20086 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ ULONG EaxIndex);


void __RPC_STUB IPropSet20086_VistaSetEaxIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20086_VistaGetEaxEnabled_Proxy( 
    IPropSet20086 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [out] */ BOOL *Enabled);


void __RPC_STUB IPropSet20086_VistaGetEaxEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPropSet20086_VistaSetEaxEnabled_Proxy( 
    IPropSet20086 * This,
    /* [in] */ ULONG ulDeviceIndex,
    /* [in] */ BOOL Enabled);


void __RPC_STUB IPropSet20086_VistaSetEaxEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropSet20086_INTERFACE_DEFINED__ */



#ifndef __RTCOMDLLLib_LIBRARY_DEFINED__
#define __RTCOMDLLLib_LIBRARY_DEFINED__

/* library RTCOMDLLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RTCOMDLLLib;

EXTERN_C const CLSID CLSID_PropSet;

#ifdef __cplusplus

class DECLSPEC_UUID("C6606CA5-2108-4CAF-8E52-1953F2DBF716")
PropSet;
#endif

EXTERN_C const CLSID CLSID_ABIT;

#ifdef __cplusplus

class DECLSPEC_UUID("697A25AB-7233-4E22-A6AB-896387D1980F")
ABIT;
#endif

EXTERN_C const CLSID CLSID_SONY;

#ifdef __cplusplus

class DECLSPEC_UUID("A9C2CEBF-36DC-40A3-92E6-ED59FDD9D20D")
SONY;
#endif

EXTERN_C const CLSID CLSID_RTLCSSAPI;

#ifdef __cplusplus

class DECLSPEC_UUID("CC0CA09A-5B84-43F2-BE5C-9169C192565F")
RTLCSSAPI;
#endif
#endif /* __RTCOMDLLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


