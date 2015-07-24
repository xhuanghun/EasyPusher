#ifndef __EASY_PUSHER_API_H__
#define __EASY_PUSHER_API_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#define EasyPusher_API  __declspec(dllexport)
#define Easy_APICALL  __stdcall
#else
#define EasyPusher_API
#define Easy_APICALL 
#endif

typedef unsigned char           Easy_U8;
typedef unsigned char           Easy_UCHAR;
typedef unsigned short          Easy_U16;
typedef unsigned int            Easy_U32;



enum
{
    Easy_NoErr						= 0,
    Easy_RequestFailed				= -1,
    Easy_Unimplemented				= -2,
    Easy_RequestArrived				= -3,
    Easy_OutOfState					= -4,
    Easy_NotAModule					= -5,
    Easy_WrongVersion				= -6,
    Easy_IllegalService				= -7,
    Easy_BadIndex					= -8,
    Easy_ValueNotFound				= -9,
    Easy_BadArgument				= -10,
    Easy_ReadOnly					= -11,
    Easy_NotPreemptiveSafe			= -12,
    Easy_NotEnoughSpace				= -13,
    Easy_WouldBlock					= -14,
    Easy_NotConnected				= -15,
    Easy_FileNotFound				= -16,
    Easy_NoMoreData					= -17,
    Easy_AttrDoesntExist			= -18,
    Easy_AttrNameExists				= -19,
    Easy_InstanceAttrsNotAllowed	= -20,
	Easy_InvalidSocket				= -21,
	Easy_MallocError				= -22,
	Easy_ConnectError				= -23,
	Easy_SendError					= -24
};
typedef int Easy_Error;

/* ����Ƶ���� */
#define EASY_SDK_VIDEO_CODEC_H264	0x01000001		/* H264 */
#define EASY_SDK_AUDIO_CODEC_AAC	0x01000011		/* AAC */
#define EASY_SDK_AUDIO_CODEC_G711	0x01000012		/* G711 */
#define EASY_SDK_AUDIO_CODEC_G726	0x01000013		/* G726 */

/* ����Ƶ֡��ʶ */
#define EASY_SDK_VIDEO_FRAME_FLAG	0x02000001	/* ��Ƶ֡��־ */
#define EASY_SDK_AUDIO_FRAME_FLAG	0x02000002	/* ��Ƶ֡��־ */

/* ��Ƶ�ؼ��ֱ�ʶ */
#define EASY_SDK_VIDEO_FRAME_I		0x03000001	/* �ؼ�֡ */
#define EASY_SDK_VIDEO_FRAME_P		0x03000001	/* �ǹؼ�֡ */

typedef struct __EASY_AV_Frame
{
    Easy_U32    u32AVFrameFlag;		/* ֡��־  ��Ƶ or ��Ƶ*/
    Easy_U32    u32AVFrameLen;		/* ֡�ĳ���*/
    Easy_U32    u32VFrameType;		/* ��Ƶ�����ͣ�I֡��P֡*/
    Easy_U8     *pBuffer;			/* ���� */
}EASY_AV_Frame;

typedef struct __EASY_MEDIA_INFO_T
{
	Easy_U32 u32VideoCodec;
	Easy_U32 u32VideoFps;
  
	Easy_U32 u32AudioCodec;
	Easy_U32 u32AudioSamplerate;
	Easy_U32 u32AudioChannel;
}EASY_MEDIA_INFO_T;


typedef enum __EASY_PUSH_STATE_T
{
    EASY_PUSH_STATE_CONNECTING   =   1,     //������
    EASY_PUSH_STATE_CONNECTED,              //���ӳɹ�
    EASY_PUSH_STATE_CONNECT_FAILED,         //����ʧ��
    EASY_PUSH_STATE_CONNECT_ABORT,          //�����쳣�ж�
    EASY_PUSH_STATE_PUSHING,                //������
    EASY_PUSH_STATE_DISCONNECTED,           //�Ͽ�����
    EASY_PUSH_STATE_ERROR
}EASY_PUSH_STATE_T;

typedef int (*EasyPusher_Callback)(int _id, EASY_PUSH_STATE_T _state, EASY_AV_Frame *_frame, void *_userptr);



#ifdef __cplusplus
extern "C"
{
#endif

	/* �������;��  ����Ϊ���ֵ */
	EasyPusher_API Easy_U32 Easy_APICALL EASY_SDK_API_Create();
	/* �ͷ����;�� */
	EasyPusher_API Easy_U32 Easy_APICALL EASY_SDK_API_Release(Easy_U32 handle);

    /* �����������¼��ص�  */
    EasyPusher_API Easy_U32 Easy_APICALL EASY_SDK_API_SetEventCallback(Easy_U32 handle,  EasyPusher_Callback callback, int id, void *userptr);

	/* ��ʼ������ */
	EasyPusher_API Easy_U32 Easy_APICALL EASY_SDK_API_StartStream(Easy_U32 handle, char* serverAddr, Easy_U16 port, char* streamName, char *username, char *password, EASY_MEDIA_INFO_T*  pstruStreamInfo);

	/* ֹͣ������  */
	EasyPusher_API Easy_U32 Easy_APICALL EASY_SDK_API_StopStream(Easy_U32 handle);

	//����
	EasyPusher_API Easy_U32 Easy_APICALL EASY_SDK_API_PushFrame(Easy_U32 handle, EASY_AV_Frame* frame );

#ifdef __cplusplus
}
#endif











#endif