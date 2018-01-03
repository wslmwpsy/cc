
#pragma once

////////////////////////////////////////////////////////////////////////////////
//      .h���ļ�
/********************************************************************
        Copyright@ ��Ȩ����@ 1998-2005hengai����������Ȩ����
********************************************************************/
 
 
/********************************************************************
  �ļ�˵��: �ܹ���ȡ JPG ͼ���ļ��е� EXIF ��Ϣ
  �ļ�����: exif.h
  �汾��  : 1.0.0
  ��    ��: hengai
  �޸ļ�¼:
  ʹ�÷���: ������ͷ�ļ���Ȼ����ú���
              int EXIF_Read(LPCTSTR pszJpgFileName, EXIFINFO* pExifInfo)
              ���ɻ�ȡ EXIF ��Ϣ��EXIF��Ϣ�����ڲ��� pExifInfo ��
            �ڶ����� #define EXIF_OUTPUT_ERRMSG (Ĭ�����Ѿ�����)�����ʹ��
              LPCTSTR EXIF_GetErrorString(); ��ȡ������Ϣ
*********************************************************************/
 
//////////////////////////////////////////////////////////////////////////
#ifndef STATIC
#define STATIC    static
#endif
#define EXIF_OUTPUT_ERRMSG      //�����Ƿ����������Ϣ
//////////////////////////////////////////////////////////////////////////
//              ���峣��
#define MAX_COMMENT   1000      //����ע���ַ�������
 
//////////////////////////////////////////////////////////////////////////
//д��ע��ʱ������ע�͵����ͣ��� ASCII, UNICODE ��
typedef enum ECT{
  CT_ASCII = 0,
  CT_UNICODE,
  CT_JIS,
  CT_UNDEFINE
}COMMENT_TYPE;
//////////////////////////////////////////////////////////////////////////
//              ������Ҫ�Ľṹ��
#define ET_NOT_CLOSE_FILE       0x00000001  //��󲻹رմ򿪵��ļ����
#define ET_MALLOC_THUMBNAIL     0x00000002  //��������ͼ�����ݣ���������Ҫʹ�� free()
#define ET_MALLOC_USERCOM       0x00000004  //�Ƿ񿽱��û�ע�ͣ���������Ҫʹ�� free()
#define ET_MALLOC_MAKERCOM      0x00000008  //�Ƿ񿽱�����ע�ͣ���������Ҫʹ�� free()
//JPG �ļ��еĶ����� EXIFF ��Ϣ���浽����ṹ����
typedef struct tag_ExifInfo {
  DWORD dwExifType;             //ȡֵΪ ET_NOT_CLOSE_FILE|ET_MALLOC_THUMBNAIL, ....
  DWORD dwExifType2;
  char  Version      [5];       //EXIF ��Ϣ�汾
  char  CameraMake   [32];      //DC ������
  char  CameraModel  [40];      //DC �ͺ�
  char  DateTime     [20];      //JPG �ļ�����
  char  DateTimeDigitized[20];  //JPG �ļ�����������޸�����
  int   Height, Width;          //ͼ��߶ȡ����
  int   Orientation;            //���㷽��������������ַ�����ת�������
  int   IsColor;                //
  int   Process;                //������
  int   FlashUsed;              //�Ƿ�ʹ�������
  float FocalLength;            //����
  float ExposureTime;           //�ع�ʱ��(�����ٶ�)
  float ApertureFNumber;        //��Ȧ��
  float Distance;               //�����������
  float CCDWidth;               //CCD ��С
  float ExposureBias;           //�عⲹ��
  int   Whitebalance;           //��ƽ��
  int   MeteringMode;           //���ģʽ
  int   ExposureProgram;        //�ع�
  int   ISOequivalent;          //ISO
  int   CompressionLevel;       //ѹ��
  float FocalplaneXRes;         //��ƽ��X��ֱ���
  float FocalplaneYRes;         //��ƽ��Y��ֱ���
  float FocalplaneUnits;        //��ƽ��ֱ��ʵ�λ
  float Xresolution;            //X ��ֱ���
  float Yresolution;            //Y ��ֱ���
  float ResolutionUnit;         //�ֱ��ʵ�λ
  float Brightness;             //����
  char  Comments[MAX_COMMENT];  //ע��
  DWORD UserCOMLength;          //�û�ע�ͳ��ȡ����==0��ʾû���û�ע��
  char  *UserCOM;               //�û�ע��
                                //if(dwExifType&ET_MALLOC_USERCOM == TRUE) �����ֵ�������û�ע�����ݣ���������Ҫʹ�� free()
                                //����Ϊ�û�ע�͵�ƫ����(������ļ���ʼ0��)
  DWORD MakerCOMLength;         //����ע�ͳ��ȡ����==0��ʾû�г���ע��
  char  *MakerCOM;              //����ע��
                                //if(dwExifType&ET_MALLOC_MAKERCOM == TRUE) �����ֵ�����˳���ע�����ݣ���������Ҫʹ�� free()
                                //����Ϊ����ע�͵�ƫ����(ע�⣺���ڵ�ǰSECTION�е�ƫ������������������ļ���)
 
 
  UCHAR * ThumbnailPointer;     //����ͼ���ݡ�
                                //if(dwExifType&ET_MALLOC_THUMBNAIL == TRUE) �����ֵ����������ͼ������
                                //����Ϊһ�� DWORD(��Ҫǿ��ת��) ��ʾ����ͼ��JPG�ļ��е�ƫ��ֵ(������ļ���ʼ0��)
  DWORD ThumbnailSize;          //����ͼ�Ĵ�С(�ֽ��� ThumbnailPointer �ĳ���)
                                //���<=0��ʾ�� JPG �ļ�û������ͼ
  HFILE hJpgFileHandle;         //���ش򿪵� JPG �ļ���������� dwExifType&ET_NOT_CLOSE_FILE == TRUE ������Ч���
                                //�û���Ҫʹ�� CloseHandle(hJpgFileHandle)���ر�������
  BOOL  IsExif;                 //�Ƿ���� EXIF ��Ϣ
} EXIFINFO;
//////////////////////////////////////////////////////////////////////////
//              �ӿں���
int EXIF_Read(LPCTSTR pszJpgFileName, EXIFINFO* pExifInfo);
LPCTSTR EXIF_GetErrorString();
int EXIF_AddUserComments(LPCTSTR pszJpgFileName, LPCTSTR pszUserComments, DWORD dwCommentLength, COMMENT_TYPE nCommentType);

class CExifTags
{
public:
	CExifTags(void);
	~CExifTags(void);
public:
	int GetExifRead(LPCTSTR pszJpgFileName, EXIFINFO* pExifInfo){
		return EXIF_Read(pszJpgFileName, pExifInfo);
	}
	LPCTSTR GetExifErrorString(){
		return EXIF_GetErrorString();
	}
	int SetExifAddUserComments(LPCTSTR pszJpgFileName, LPCTSTR pszUserComments, DWORD dwCommentLength, COMMENT_TYPE nCommentType){
		return EXIF_AddUserComments(pszJpgFileName, pszUserComments, dwCommentLength, nCommentType);
	}
};