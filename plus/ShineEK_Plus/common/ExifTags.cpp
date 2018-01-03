#include "StdAfx.h"
#include "ExifTags.h"

////////////////////////////////////////////////////////////////////////
//   .c �ļ�

/********************************************************************
        Copyright@ ��Ȩ����@ 1998-2005 HENGAI����������Ȩ����
********************************************************************/
 
 
/********************************************************************
  �ļ�˵��:
  �ļ�����: exif.c
  �汾��  : 1.0.0
  ��    ��: hengai
  �޸ļ�¼:
*********************************************************************/
#include "ExifTags.h"
//////////////////////////////////////////////////////////////////////////
//��ȡ EXIF ��������Ҫ�Ľṹ��
typedef struct tag_Section_t{
    UCHAR     *Data;
    int       Type;
    unsigned  Size;
} Section_t;
//////////////////////////////////////////////////////////////////////////
#ifdef  EXIF_OUTPUT_ERRMSG
STATIC TCHAR m_szLastError[256];  //���ﱣ���˳������Ϣ
#define EXIF_ERR_OUT(str_err) _tcscpy(m_szLastError,str_err);
 
LPCTSTR EXIF_GetErrorString()
{
  return (LPCTSTR)m_szLastError;
}
#else
#define EXIF_ERR_OUT
LPCTSTR EXIF_GetErrrorString()
{
  return "Plese #define EXIT_ERR_OUT in exif.h";
}
#endif
 
STATIC EXIFINFO* m_pExifInfo = 0;   //
STATIC     int m_MotorolaOrder   = 0;  //
STATIC  int m_ExifImageWidth  = 0;  //
 
//////////////////////////////////////////////////////////////////////////
 
/* Describes format descriptor */
static const int m_BytesPerFormat[] = {0,1,1,2,4,8,1,1,2,4,8,4,8};
#define NUM_FORMATS     12
 
#define FMT_BYTE        1           //Format Byte
#define FMT_STRING      2
#define FMT_USHORT      3
#define FMT_ULONG       4
#define FMT_URATIONAL   5
#define FMT_SBYTE       6
#define FMT_UNDEFINED   7
#define FMT_SSHORT      8
#define FMT_SLONG       9
#define FMT_SRATIONAL  10
#define FMT_SINGLE     11
#define FMT_DOUBLE     12
//////////////////////////////////////////////////////////////////////////
#define MAX_SECTIONS   20       //JPG �ļ����ܹ��������� SECTION ����
 
#ifndef M_SOI
#define M_SOF0  0xC0            // Start Of Frame N
#define M_SOF1  0xC1            // N indicates which compression process
#define M_SOF2  0xC2            // Only SOF0-SOF2 are now in common use
#define M_SOF3  0xC3
#define M_SOF5  0xC5            // NB: codes C4 and CC are NOT SOF markers
#define M_SOF6  0xC6
#define M_SOF7  0xC7
#define M_SOF9  0xC9
#define M_SOF10 0xCA
#define M_SOF11 0xCB
#define M_SOF13 0xCD
#define M_SOF14 0xCE
#define M_SOF15 0xCF
#define M_SOI   0xD8            // Start Of Image (beginning of datastream)
#define M_EOI   0xD9            // End Of Image (end of datastream)
#define M_SOS   0xDA            // Start Of Scan (begins compressed data)
#define M_JFIF  0xE0            // Jfif marker
#define M_EXIF  0xE1            // Exif marker
#define M_COM   0xFE            // COMment
 
//���� APP ��ʶ(SECTION)
#define M_APP0  0xE0
#define M_APP1  0xE1
#define M_APP2  0xE2
#define M_APP3  0xE3
#define M_APP4  0xE4
#define M_APP5  0xE5
#define M_APP6  0xE6
//...
#endif
 
// Describes tag values
//ע��: ����Ķ����ǰ��� Intel CPU ������ģ�Ҳ����˵���еĶ��Ǹ�λ�ں�
//�����Ķ�������� EXIF ��Ƥ���ϵĶ��岻һ�¡������Ƥ���ϰ� TAG_MAKE ����Ϊ 0F01
//��������Ҫ��Ϣ
#define TAG_MAKE              0x010F    //���DC ������
#define TAG_MODEL             0x0110    //DC �ͺ�
#define TAG_ORIENTATION       0x0112    //����ʱ����������������תDC 90��������Ƭ
#define TAG_XRESOLUTION       0x011A    //X ��ֱ���
#define TAG_YRESOLUTION       0x011B    //Y ��ֱ���
#define TAG_RESOLUTIONUNIT    0x0128    //�ֱ��ʵ�λ������ inch, cm
#define TAG_DATATIME          0x0132    //����ʱ��
#define TAG_YBCR_POSITION     0x0213    //YCbCr λ�ÿ��ƣ����� ����
#define TAG_COPYRIGHT         0x8298    //��Ȩ
#define TAG_EXIF_OFFSET       0x8769    //EXIF ƫ�ƣ���ʱ���൱�ڴ���һ���µ� EXIF ��Ϣ
 
//
#define TAG_IMAGEWIDTH        0x0001    //ͼ����
#define TAG_IMAGEHEIGHT       0x0101    //ͼ��߶�
//BOOKMARK
//������Ϣ
#define TAG_EXPOSURETIME      0x829A    //�ع�ʱ�䣬���� 1/30 ��
#define TAG_FNUMBER           0x829D    //��Ȧ������ F2.8
#define TAG_EXIF_VERSION      0x9000    //EXIF ��Ϣ�汾
#define TAG_DATETIME_ORIGINAL 0x9003    //��Ƭ����ʱ�䣬���� 2005-10-13 11:09:35
#define TAG_DATATIME_DIGITIZED  0x9004  //��Ƭ������ͼ���޸�����޸ĺ��ʱ�䣬����  2005-10-13 11:36:35
#define TAG_COMPONCONFIG      0x9101    //ComponentsConfiguration ɫ�ʿռ�����
#define TAG_COMPRESS_BIT      0x9202    //ÿ����ѹ��λ��
#define TAG_SHUTTERSPEED      0x9201    //�����ٶȣ����� 1/30 ��
#define TAG_APERTURE          0x9202    //��Ȧֵ������ F2.8
#define TAG_BRIGHTNESS        0x9203    //����
#define TAG_EXPOSURE_BIAS     0x9204    //�عⲹ�������� EV0.0
#define TAG_MAXAPERTURE       0x9205    //����Ȧֵ������ F2.8
#define TAG_SUBJECT_DISTANCE  0x9206    //��������룬���� 3.11 ��
#define TAG_METERING_MODE     0x9207    //���ģʽ���������
#define TAG_WHITEBALANCE      0x9208    //LightSource ��ƽ��
#define TAG_FLASH             0x9209    //�Ƿ�ʹ�������
#define TAG_FOCALLENGTH       0x920A    //���࣬���� 7.09mm
#define TAG_USERCOMMENT       0x9286    //�û�ע��
#define TAG_MAKE_COMMENT      0x927C    //����ע�͡�����汾���ṩ(2005-10-13)
#define TAG_SUBSECTIME        0x9290    //SubSecTime
#define TAG_SUBTIME_ORIGINAL  0x9291    //SubSecTimeOriginal
#define TAG_SUBTIME_DIGITIZED 0x9292    //SubSecTimeDigitized
#define TAG_FLASHPIXVERSION   0x00A0    //Flash Pix �汾
#define TAG_COLORSPACE        0x01A0    //ɫ�ʿռ䣬���� sRGB
 
#define TAG_PIXEL_XDIMENSION  0x02A0    //
#define TAG_PIXEL_YDIMENSION  0x03A0    //
#define TAG_
//EXIFR98
 
//����ͼ
#define TAG_INTEROP_OFFSET    0xa005    //ƫ��
 
#define TAG_FOCALPLANEXRES    0xA20E    //��ƽ��X��ֱ��ʣ����� 1024000/278
#define TAG_FOCALPLANEYRES    0xA20F    //��ƽ��X��ֱ��ʣ����� 768000/209
#define TAG_FOCALPLANEUNITS   0xA210    //��ƽ��ֱ��ʵ�λ
#define TAG_EXIF_IMAGEWIDTH   0xA002    //EXIF ͼ����(�������� JPG ͼ��)
#define TAG_EXIF_IMAGELENGTH  0xA003    //EXIF ͼ��߶�
 
#define TAG_EXPOSURE_PROGRAM  0x8822    //
#define TAG_ISO_EQUIVALENT    0x8827    //
#define TAG_COMPRESSION_LEVEL 0x9102    //
 
#define TAG_THUMBNAIL_OFFSET  0x0201    //����ͼƫ��
#define TAG_THUMBNAIL_LENGTH  0x0202    //����ͼ��С
 
 
#define TAG_GPS_VERSIONID       0x0000  //GPS �汾
#define TAG_GPS_LATITUDEREF     0x0001  //γ�Ȳο���������γ
#define TAG_GPS_LATITUDE        0x0002  //γ��ֵ
#define TAG_GPS_LONGITUDEREF    0x0003  //���Ȳο������綫��
#define TAG_GPS_LONGITUDE       0x0004  //����ֵ
#define TAG_GPS_ALTITUDEREF     0x0005  //���θ߶Ȳο�
#define TAG_GPS_ALTITUDE        0x0006  //����
#define TAG_GPS_TIMESTAMP       0x0007  //ʱ���
#define TAG_GPS_SATELLITES      0x0008  //����
#define TAG_GPS_STATUS          0x0009  //״̬
#define TAG_GPS_MEASUREMODE     0x000A  //
#define TAG_GPS_DOP             0x000B  //
#define TAG_GPS_SPEEDREF        0x000C  //
#define TAG_GPS_SPEED           0x000D  //
#define TAG_GPS_TRACKREF        0x000E  //
#define TAG_GPS_TRACK           0x000F  //
#define TAG_GPS_IMGDIRECTIONREF 0x0010  //
#define TAG_GPS_IMGDIRECTION    0x0011  //
#define TAG_GPS_MAPDATUM        0x0012  //
#define TAG_GPS_DESTLATITUDEREF 0x0013  //
#define TAG_GPS_DESTLATITUDE    0x0014  //
#define TAG_GPS_DESTLONGITUDEREF  0x0015//
#define TAG_GPS_DESTLONGITUDE   0x0016  //
#define TAG_GPS_DESTBEARINGREF  0x0017  //
#define TAG_GPS_DESTBEARING     0x0018  //
#define TAG_GPS_DESTDISTANCEREF 0x0019  //
#define TAG_GPS_DESTDISTANCE    0x001A  //
//////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
Get 16 bits motorola order (always) for jpeg header stuff.
--------------------------------------------------------------------------*/
STATIC int EXIF_Get16m(void * Short)
{
  return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
}
 
/*--------------------------------------------------------------------------
Convert a 16 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
STATIC int EXIF_Get16u(void * Short)
{
  if (m_MotorolaOrder)
  {
    return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
  }
  else
  {
    return (((unsigned char *)Short)[1] << 8) | ((unsigned char *)Short)[0];
  }
}
 
/*--------------------------------------------------------------------------
Convert a 32 bit signed value from file's native unsigned char order
--------------------------------------------------------------------------*/
STATIC long EXIF_Get32s(void * Long)
{
  if (m_MotorolaOrder)
  {
    return  ((( char *)Long)[0] << 24) | (((unsigned char *)Long)[1] << 16)
      | (((unsigned char *)Long)[2] << 8 ) | (((unsigned char *)Long)[3] << 0 );
  }
  else
  {
    return  ((( char *)Long)[3] << 24) | (((unsigned char *)Long)[2] << 16)
      | (((unsigned char *)Long)[1] << 8 ) | (((unsigned char *)Long)[0] << 0 );
  }
}
 
/*--------------------------------------------------------------------------
Convert a 32 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
STATIC ULONG EXIF_Get32u(void * Long)
{
  return (unsigned long)EXIF_Get32s(Long) & 0XFFFFFFFF;
}
 
/*--------------------------------------------------------------------------
Evaluate number, be it int, rational, or float from directory.
--------------------------------------------------------------------------*/
STATIC double EXIF_ConvertAnyFormat(void * ValuePtr, int Format)
{
  double Value;
  Value = 0;
 
  switch(Format)
  {
  case FMT_SBYTE:     Value = *(signed char *)ValuePtr;   break;
  case FMT_BYTE:      Value = *(unsigned char *)ValuePtr; break;
   
  case FMT_USHORT:    Value = EXIF_Get16u(ValuePtr);      break;
  case FMT_ULONG:     Value = EXIF_Get32u(ValuePtr);      break;
   
  case FMT_URATIONAL:
  case FMT_SRATIONAL:
    {
      int Num,Den;
      Num = EXIF_Get32s(ValuePtr);
      Den = EXIF_Get32s(4+(char *)ValuePtr);
      if (Den == 0)
      {
        Value = 0;
      }
      else
      {
        Value = (double)Num/Den;
      }
      break;
    }
   
  case FMT_SSHORT:    Value = (signed short)EXIF_Get16u(ValuePtr); break;
  case FMT_SLONG:     Value = EXIF_Get32s(ValuePtr);               break;
   
  /* Not sure if this is correct (never seen float used in Exif format)
    */
  case FMT_SINGLE:    Value = (double)*(float *)ValuePtr;     break;
  case FMT_DOUBLE:    Value = *(double *)ValuePtr;            break;
  }
  return Value;
}
////////////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
 
/*********************************************************************
  ��������:
  ��    ��:
          IN:
         OUT:
         I/O:
    ����ֵ:
  ��������: ���� JPG �ļ��е�ע����Ϣ
  ��    ��:
*********************************************************************/
STATIC void EXIF_Process_COM (CONST UCHAR * Data, int length)
{
  int ch;
  char Comment[MAX_COMMENT+1];
  int nch;
  int a;
 
  nch = 0;
 
  if (length > MAX_COMMENT) length = MAX_COMMENT; // Truncate if it won't fit in our structure.
 
  for (a=2;a<length;a++)
  {
    ch = Data[a];
   
    if (ch == '\r' && Data[a+1] == '\n') continue; // Remove cr followed by lf.
   
    if ((ch>=0x20) || ch == '\n' || ch == '\t')
    {
      Comment[nch++] = (char)ch;
    }
    else
    {
      Comment[nch++] = '?';
    }
  }
 
  Comment[nch] = '\0'; // Null terminate
 
  //if (ShowTags) printf("COM marker comment: %s\n",Comment);
 
  strcpy(m_pExifInfo->Comments,Comment);
}
 
/*********************************************************************
  ��������: STATIC BOOL EXIF_ProcessExifDir(...)
  ��    ��:
          IN: CONST UCHAR* DataStart: ����������ʼλ�á������ֵ�����ں��� EXIF_Decode ���ܹ��ı�
              CONST DWORD dwFilePointerBeforeReadData: �ڶ�ȡ������֮ǰ���ļ�ָ��λ��
              UCHAR *DirStart: SECTION ����������ȥ����ǰ��� EXIF\0\0(6)+II(2)+2A00(2)+08000000(6)=14
              UCHAR *OffsetBase: ����ȥ���� EXIFF\0\0(6)=6�ֽ�
              UINT ExifLength: ���� SECTION �������ĳ���ȥ�� EXIF\0\0��ĳ���==All Length - 6
              EXIFINFO * const m_exifinfo: 
         OUT:
         I/O:
              UCHAR **const LastExifRefdP: ƫ�ƹ����λ��
    ����ֵ:
  ��������:
  ��    ��:
*********************************************************************/
STATIC BOOL EXIF_ProcessExifDir(CONST UCHAR* DataStart, CONST DWORD dwFilePointerBeforeReadData,
                                UCHAR *DirStart, UCHAR *OffsetBase, CONST UINT ExifLength,
                                EXIFINFO * const m_exifinfo, UCHAR **const LastExifRefdP )
{
  int de = 0;                 //
  int a = 0;                  //
  int NumTagEntries = 0;      //������ TAG �ĸ���
  UINT ThumbnailOffset = 0;   //����ͼƫ����
  UINT ThumbnailSize = 0;     //����ͼ�Ĵ�С
  int  BytesCount = 0;        //
  UCHAR * TagEntry = 0;       //ÿ�� TAG �����
  int Tag, Format, Components;
  UCHAR * ValuePtr = 0;       //ƫ�ƺ��λ�á���Ϊ TAG �����ݺܶ�ʱ�򶼲��������ģ������м��и�ƫ����
  DWORD OffsetVal = 0;        //ƫ����
 
  //��ȡ�ļ��д��� TAG ����
  NumTagEntries = EXIF_Get16u(DirStart);
 
  //�ж� EXIF ��Ϣ�ĳ����Ƿ���ȷ
  //���� DirStart+2 ָ��ȥ���� NumTagEntries ��ռ�� 2 ���ֽ�
  if ((DirStart+2+NumTagEntries*12) > (OffsetBase+ExifLength))
  {
    EXIF_ERR_OUT(L"Illegally sized directory");
    return 0;
  }
  for (de=0;de<NumTagEntries;de++)
  {
    //������Ĳ����У����е�����ͨͨʹ�� UCHAR* ����ʾ
    TagEntry = DirStart+2+12*de;    //TagEntry ����ڵ�
    Tag = EXIF_Get16u(TagEntry);
    Format = EXIF_Get16u(TagEntry+2);
    Components = EXIF_Get32u(TagEntry+4);
   
    if ((Format-1) >= NUM_FORMATS)
    {
      //(-1) catches illegal zero case as unsigned underflows to positive large
      EXIF_ERR_OUT(L"Illegal format code in EXIF dir");
      return 0;
    }   
    BytesCount = Components * m_BytesPerFormat[Format];
    if (BytesCount > 4)
    {
      OffsetVal = EXIF_Get32u(TagEntry+8);
      //If its bigger than 4 unsigned chars, the dir entry contains an offset.
      if (OffsetVal+BytesCount > ExifLength)
      {
        //JPG �ļ������⵽�ƻ�
        EXIF_ERR_OUT(L"Illegal pointer offset value in EXIF.");
        return 0;
      }
      ValuePtr = OffsetBase+OffsetVal;
    }
    else
    {
      //4 unsigned chars or less and value is in the dir entry itself
      ValuePtr = TagEntry+8;
    }
    if (*LastExifRefdP < ValuePtr+BytesCount)
    {
      //��ǰ�Ѿ�����Ľ���
      //���������ٴεļ�� JPG �ļ��ĺϷ���
      *LastExifRefdP = ValuePtr+BytesCount;
    }
 
    // Extract useful components of tag
    switch(Tag)
    {
    case TAG_MAKE:
      strncpy(m_exifinfo->CameraMake, (char*)ValuePtr, 31);
      break;
    case TAG_MODEL:
      strncpy(m_exifinfo->CameraModel, (char*)ValuePtr, 39);
      break;
     
    case TAG_EXIF_VERSION:
      strncpy(m_exifinfo->Version,(char*)ValuePtr, 4);
      break;
    //���ں�ʱ�� 
    case TAG_DATETIME_ORIGINAL:
      strncpy(m_exifinfo->DateTime, (char*)ValuePtr, 19);
      break;
    case TAG_DATATIME_DIGITIZED:
      strncpy(m_exifinfo->DateTimeDigitized, (char*)ValuePtr, 19);
      break;
    //�û�ע��
    case TAG_USERCOMMENT:
      m_exifinfo->UserCOMLength = BytesCount;
      if(m_exifinfo->dwExifType & ET_MALLOC_USERCOM)
      {
        m_exifinfo->UserCOM = (char*)malloc(BytesCount);
        memcpy(m_exifinfo->UserCOM, ValuePtr, BytesCount);
        /*//Olympus �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf8 0x20�\cf9 �\cf9 �\cf9 �\cf9 �\cf9 �\cf7 '\0',
        //�����Ƚ�����Ŀո��滻�� '\0' Ȼ���ٿ���ע��Comment
        for (a=BytesCount;a>0;)
        {
          a--;
          if (((char*)ValuePtr)[a] == ' ')
          {
            ((char*)ValuePtr)[a] = '\0';
          }
          else
          {
            break;
          }
        }
        //���û�ע�Ϳ����� exifinfo.Comments ��
        //�����ж��Ƿ��� ASCII ģʽ(����ע�͵�ǰ�� 5 ���ַ��� ASCII)
        //����ǣ���ȡ��������ǰ���  ASCII ����ַ�
        if (memcmp(ValuePtr, "ASCII",5) == 0)
        {
          for (a=5;a<10;a++)
          {
            char c;
            c = ((char*)ValuePtr)[a];
            if (c != '\0' && c != ' ')
            {
              strncpy(m_exifinfo->Comments, (char*)ValuePtr+a, MAX_COMMENT-1);
              break;
            }
          }       
        }
        else
        {
          strncpy(m_exifinfo->Comments, (char*)ValuePtr, MAX_COMMENT-1);
        }*/
      }
      else
      {
        //��¼�û�ע������������ļ���ʼ����ƫ����
        m_exifinfo->UserCOM = (CHAR*)(OffsetBase+OffsetVal-DataStart+dwFilePointerBeforeReadData);
        //m_exifinfo->UserCOM = (char*)OffsetVal;  //ƫ��
      }
      break;
    //����ע��
    case TAG_MAKE_COMMENT:
      m_exifinfo->MakerCOMLength = BytesCount;
      if(m_exifinfo->dwExifType & ET_MALLOC_MAKERCOM)
      {
        m_exifinfo->MakerCOM = (char*)malloc(BytesCount);
        memcpy(m_exifinfo->MakerCOM, ValuePtr, BytesCount);
      }
      else
      {
        m_exifinfo->MakerCOM = (char*)OffsetVal; //ƫ��
      }
      break;
    //��Ȧ
    case TAG_FNUMBER:
      m_exifinfo->ApertureFNumber = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    case TAG_APERTURE:    //��Ȧֵ
    case TAG_MAXAPERTURE: //����Ȧֵ
    //More relevant info always comes earlier, so only
    //use this field if we don't have appropriate aperture
    //information yet.
    /*-  if (m_exifinfo->ApertureFNumber == 0)
      {
        m_exifinfo->ApertureFNumber = (float)exp(EXIF_ConvertAnyFormat(ValuePtr, Format)*log(2)*0.5);//ATTENTION
        m_exifinfo->ApertureFNumber = (float)(EXIF_ConvertAnyFormat(ValuePtr, Format)*log(2)*0.5);
      }-*/
      break;
 
    //Brightness
    case TAG_BRIGHTNESS:
      m_exifinfo->Brightness = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    //������Ϣ(���� 7.09mm)     
    case TAG_FOCALLENGTH:
    //Nice digital cameras actually save the focal length
    //as a function of how farthey are zoomed in.
     
      m_exifinfo->FocalLength = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    //Ŀ�����(���� 1.11��)
    case TAG_SUBJECT_DISTANCE:
    //Inidcates the distacne the autofocus camera is focused to.
    //Tends to be less accurate as distance increases.
      m_exifinfo->Distance = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    //�ع�ʱ��(���� 1/30 ��)
    case TAG_EXPOSURETIME:
    //Simplest way of expressing exposure time, so I
    //trust it most.  (overwrite previously computd value
    //if there is one)
      m_exifinfo->ExposureTime =
        (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    //SHUTTERSPEED �����ٶȲ���Ҫ   
    case TAG_SHUTTERSPEED:
    //More complicated way of expressing exposure time,
    //so only use this value if we don't already have it
    //from somewhere else. 
    /*-  if (m_exifinfo->ExposureTime == 0)
      {
        m_exifinfo->ExposureTime = (float)
          (1/exp(EXIF_ConvertAnyFormat(ValuePtr, Format)*log(2)));
      }-*/
      break;
 
  //FLASH �������Ϣ����Ҫ     
    case TAG_FLASH:
      if ((int)EXIF_ConvertAnyFormat(ValuePtr, Format) & 7)
      {
        m_exifinfo->FlashUsed = 1;
      }
      else
      {
        m_exifinfo->FlashUsed = 0;
      }
      break;
     
    case TAG_ORIENTATION:
      m_exifinfo->Orientation = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      if (m_exifinfo->Orientation < 1 || m_exifinfo->Orientation > 8)
      {
        EXIF_ERR_OUT(L"Undefined rotation value");
        m_exifinfo->Orientation = 0;
      }
      break;
    //EXIF ͼ��߶�����(���� 1024*768)
    case TAG_EXIF_IMAGELENGTH:
    case TAG_EXIF_IMAGEWIDTH:
      a = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      if (m_ExifImageWidth < a) m_ExifImageWidth = a;
      break;
  //��ƽ�� X ��ֱ���(���� 1024000/278)���������� Y һ��
    case TAG_FOCALPLANEXRES:
      m_exifinfo->FocalplaneXRes = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
  //��ƽ�� Y ��ֱ���(���� 768000/209)���������� X һ��
    case TAG_FOCALPLANEYRES:
      m_exifinfo->FocalplaneYRes = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    case TAG_RESOLUTIONUNIT:
      switch((int)EXIF_ConvertAnyFormat(ValuePtr, Format))
      {
      case 1: m_exifinfo->ResolutionUnit = 1.0f;             break;   // 1 inch
      case 2: m_exifinfo->ResolutionUnit = 1.0f;             break;   //
      case 3: m_exifinfo->ResolutionUnit = 0.3937007874f;    break;   // 1 centimeter
      case 4: m_exifinfo->ResolutionUnit = 0.03937007874f;   break;   // 1 millimeter
      case 5: m_exifinfo->ResolutionUnit = 0.00003937007874f;         // 1 micrometer
      }
      break;
    //��ƽ��ֱ��ʵ�λ(������)
    case TAG_FOCALPLANEUNITS:
      switch((int)EXIF_ConvertAnyFormat(ValuePtr, Format))
      {
      case 1: m_exifinfo->FocalplaneUnits = 1.0f;             break;  // 1 inch
      case 2: m_exifinfo->FocalplaneUnits = 1.0f;             break;  //
      case 3: m_exifinfo->FocalplaneUnits = 0.3937007874f;    break;  // 1 centimeter
      case 4: m_exifinfo->FocalplaneUnits = 0.03937007874f;   break;  // 1 millimeter
      case 5: m_exifinfo->FocalplaneUnits = 0.00003937007874f;break;  // 1 micrometer//
      }
      break;
 
    //�عⲹ����Ϣ
    case TAG_EXPOSURE_BIAS:
      m_exifinfo->ExposureBias = (float) EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //��ƽ��
    case TAG_WHITEBALANCE:
      m_exifinfo->Whitebalance = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    case TAG_METERING_MODE:
      m_exifinfo->MeteringMode = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    case TAG_EXPOSURE_PROGRAM:
      m_exifinfo->ExposureProgram = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    case TAG_ISO_EQUIVALENT:
      m_exifinfo->ISOequivalent = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      if ( m_exifinfo->ISOequivalent < 50 ) m_exifinfo->ISOequivalent *= 200;
      break;
    case TAG_COMPRESSION_LEVEL:
      m_exifinfo->CompressionLevel = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //X ��ֱ���
    case TAG_XRESOLUTION:
      m_exifinfo->Xresolution = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //Y ��ֱ���
    case TAG_YRESOLUTION:
      m_exifinfo->Yresolution = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //����ͼ ƫ���� 
    case TAG_THUMBNAIL_OFFSET:
      ThumbnailOffset = (unsigned)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //����ͼ�Ĵ�С
    case TAG_THUMBNAIL_LENGTH:
        ThumbnailSize = (unsigned)EXIF_ConvertAnyFormat(ValuePtr, Format);
        break;
    } //end switch(Tag)
    //EXIF ��Ϣƫ��
    //
    if (Tag == TAG_EXIF_OFFSET || Tag == TAG_INTEROP_OFFSET)
    {
      UCHAR * SubdirStart;
      SubdirStart = OffsetBase + EXIF_Get32u(ValuePtr);
      if (SubdirStart < OffsetBase ||
        SubdirStart > OffsetBase+ExifLength)
      {
        EXIF_ERR_OUT(L"Illegal subdirectory link");
        return 0;
      }
      EXIF_ProcessExifDir(DataStart, dwFilePointerBeforeReadData, SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
      continue;
    } 
  } //end for {for (de=0;de<NumTagEntries;de++)}
  {
    //In addition to linking to subdirectories via exif tags,
    //there's also a potential link to another directory at the end
    //of each directory.  This has got to be the result of a
    //committee! 
   
    UCHAR * SubdirStart;
    unsigned Offset;
    Offset = EXIF_Get16u(DirStart+2+12*NumTagEntries);
    if (Offset)
    {
      SubdirStart = OffsetBase + Offset;
      if (SubdirStart < OffsetBase
        || SubdirStart > OffsetBase+ExifLength)
      {
        EXIF_ERR_OUT(L"Illegal subdirectory link");
        return 0;
      }
      EXIF_ProcessExifDir(DataStart, dwFilePointerBeforeReadData, SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
    }
  }
 
  if (ThumbnailSize && ThumbnailOffset)
  {
    //����ļ��д�������ͼ����ô������ͼ�����ݱ���
    //ע�⣺����������� malloc����������Ҫ�Լ� free
    if (ThumbnailSize + ThumbnailOffset <= ExifLength)
    {
      //������ͼ������ȫ��������һ���¿��ٵ��ڴ�
      if(m_exifinfo->dwExifType&ET_MALLOC_THUMBNAIL)
      {
        UCHAR *pThumbnailData = OffsetBase + ThumbnailOffset;
        DWORD dw = pThumbnailData-DataStart+dwFilePointerBeforeReadData;
        m_exifinfo->ThumbnailPointer = (UCHAR*)malloc(ThumbnailSize);
        memcpy(m_exifinfo->ThumbnailPointer, pThumbnailData, ThumbnailSize);
      }
      else
      {
        m_exifinfo->ThumbnailPointer = (UCHAR*)(OffsetBase+ThumbnailOffset-DataStart+dwFilePointerBeforeReadData);
      }
      m_exifinfo->ThumbnailSize = ThumbnailSize;
    }
  }
 
  return TRUE;
}
 
/*********************************************************************
  ��������: STATIC BOOL EXIF_process_EXIF(UCHAR * CharBuf, UINT length)
  ��    ��:
          IN: CONST UCHAR* DataStart: ����������ʼλ�á������ֵ�����ں��� EXIF_Decode ���ܹ��ı�
              CONST DWORD dwFilePointerBeforeReadData: �ڶ�ȡ������֮ǰ���ļ�ָ��λ��
              UCHAR * CharBuf: ��� SECTION �������ݡ�ע�⣺ǰ���Ѿ�ȥ���˰������ȵ�2���ַ�
              CONST UINT length: ��� SECTION �������ĳ���
    ����ֵ:
  ��������: ����ĳ�� SECTION �е� EXIF ��Ϣ��
            �ɹ�����TRUE��ʾEXIF��Ϣ��������ȷ��ʧ�ܷ���FALSE
  ��    ��:
*********************************************************************/
STATIC BOOL EXIF_process_EXIF(CONST UCHAR *DataStart,  CONST DWORD dwFilePointerBeforeReadData,
                              UCHAR *CharBuf, CONST UINT length)
{
  int FirstOffset = 0;
  UCHAR *LastExifRefd = 0;
  m_pExifInfo->FlashUsed = 0;
  m_pExifInfo->Comments[0] = '\0';
 
  m_ExifImageWidth = 0;
 
  //��� EXIF ͷ�Ƿ���ȷ
  {
    static const unsigned char ExifHeader[] = "Exif\0\0";
    if (memcmp(CharBuf+0, ExifHeader,6))
    {
      EXIF_ERR_OUT(L"Incorrect Exif header");
      return 0;
    }
  }
  //�ж��ڴ������ݵ������ǰ��� Intel ���ǰ��� Motorola CPU ���е�
  if (memcmp(CharBuf+6,"II",2) == 0)
  {
    m_MotorolaOrder = 0;    //
  }
  else if (memcmp(CharBuf+6,"MM",2) == 0)
  {
    m_MotorolaOrder = 1;  //
  }
  else
  {
    EXIF_ERR_OUT(L"Invalid Exif alignment marker.");
    return 0;
  }
 
  //������� 2 ���ֽ��Ƿ��� 0x2A00
  if (EXIF_Get16u(CharBuf+8) != 0x2A)
  {
    EXIF_ERR_OUT(L"Invalid Exif start (1)");
    return 0;
  }
 
  //�ж������ 0th IFD Offset �Ƿ��� 0x08000000
  FirstOffset = EXIF_Get32u(CharBuf+10);
  if (FirstOffset < 8 || FirstOffset > 16)
  {
    EXIF_ERR_OUT(L"Suspicious offset of first IFD value");
    return 0;
  }
 
  LastExifRefd = CharBuf;
 
  //��ʼ���� EXIF ��Ϣ
  if (!EXIF_ProcessExifDir(DataStart, dwFilePointerBeforeReadData,
    CharBuf+14, CharBuf+6, length-6, m_pExifInfo, &LastExifRefd))
  {
    return 0;
  }
 
  // This is how far the interesting (non thumbnail) part of the exif went.
  // int ExifSettingsLength = LastExifRefd - CharBuf; 
  // ���� CCD ���(��λ:����)
  if (m_pExifInfo->FocalplaneXRes != 0)
  {
    m_pExifInfo->CCDWidth = (float)(m_ExifImageWidth * m_pExifInfo->FocalplaneUnits / m_pExifInfo->FocalplaneXRes);
  }
 
  return 1;
}
 
STATIC VOID EXIF_process_SOFn (CONST UCHAR * Data, int marker)
{
  int data_precision, num_components;
 
  data_precision = Data[2];
  m_pExifInfo->Height = EXIF_Get16m((void*)(Data+3));
  m_pExifInfo->Width = EXIF_Get16m((void*)(Data+5));
  num_components = Data[7];
 
  if (num_components == 3)
  {
    m_pExifInfo->IsColor = 1;
  }
  else
  {
    m_pExifInfo->IsColor = 0;
  }
 
  m_pExifInfo->Process = marker;
 
  //if (ShowTags) printf("JPEG image is %uw * %uh, %d color components, %d bits per sample\n",
  //               ImageInfo.Width, ImageInfo.Height, num_components, data_precision);
}
 
STATIC int EXIF_Decode(HANDLE hFile)
{
  int a=0, b=0;
  int nHaveCom = 0;             //�Ƿ����ע�ͣ����ұ���ע���ַ����ĳ���
  int nSectionsRead = 0;        //�Ѿ���ȡ SECTION �ĸ���
  DWORD dwFileRead = 0;         //ʹ�� ReadFile ��ȡ�ļ�ʱ����ȡ���ֽ���
  DWORD dwFilePointerBeforeReadData = 0;  //�ڶ�ȡ������֮ǰ���ļ�ָ���λ��
  Section_t Sections[MAX_SECTIONS];       //JPG �ļ��� SECTIONS
 
    int   nSectionLength=0;     //SECTION(APP) ����
    int   marker = 0;           //
    int   ll=0,lh=0, got=0;     //
    UCHAR *Data = 0;            //
 
  //���� JPG ��1, 2���ֽڣ��ж��Ƿ��� 0xFF,M_SOI
  ReadFile(hFile, &a, 1, &dwFileRead, NULL);
  if(dwFileRead != 1)
  {
    EXIF_ERR_OUT(L"Unexpect File End");
    return -1;
  }
  ReadFile(hFile, &b, 1, &dwFileRead, NULL);
  if(dwFileRead != 1)
  {
    EXIF_ERR_OUT(L"Unexpect File End");
    return -1;
  }
  //�жϸ��ļ��Ƿ��� EXIF �ļ�
  //EXIF �ļ�����ʼ 2 �ֽڱض��� FF D8
  if (a != 0xFF || b != M_SOI)
  {
    EXIF_ERR_OUT(L"File Format Error");
    return -1;
  }
  //ʹ��һ��ѭ������ȡ JPG �ļ��е� SECTION
  //��һ�� SECTION �϶��� APP1����APP1��ʼ��Marker�϶�Ϊ FFE1
  for(;;)
  {
    if (nSectionsRead >= MAX_SECTIONS)
    {
      EXIF_ERR_OUT(L"Too many sections in this jpg file");
      return -1;
    }
    //���� JPG �ļ�����ַ�����������7���ַ�������һ������ 0xFF
    for (a=0;a<7;a++)
    {
      ReadFile(hFile, &marker, 1, &dwFileRead, NULL);
      if(dwFileRead != 1)
      {
        EXIF_ERR_OUT(L"Unexpect File End");
        return -1;
      }
      if (marker != 0xFF) break;
     
      if (a >= 6)
      {
        EXIF_ERR_OUT(L"Too many padding unsigned chars");
        return -1;
      }
    }
#ifdef _DEBUG
    if(nSectionsRead==0)  //�� APP 1
    {
      //ASSERT(marker == M_APP1);
    }
#endif
    Sections[nSectionsRead].Type = marker;
    //��¼��ȡ������֮ǰ���ļ�ָ��λ��
    dwFilePointerBeforeReadData = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
    //��ȡ��� SECTION �ĳ���
    ReadFile(hFile, &lh, 1, &dwFileRead, NULL);
    ReadFile(hFile, &ll, 1, &dwFileRead, NULL);
    nSectionLength = (lh << 8) | ll;    //EXIF �ļ����ֽ���ǰ�����ֽ��ں󣬲��ܶ�ȡһ��WORD����
   
    if (nSectionLength < 2)
    {
      EXIF_ERR_OUT(L"Invalid Marker");
      return -1;
    }
    Data = (UCHAR *)malloc(nSectionLength);
    if (Data == NULL)
    {
      EXIF_ERR_OUT(L"Could not allocate memory!");
      return -1;
    }
    Sections[nSectionsRead].Data = Data;
   
    // Store first two pre-read unsigned chars.
    Data[0] = (UCHAR)lh;
    Data[1] = (UCHAR)ll;
    ReadFile(hFile, Data+2, nSectionLength-2, &dwFileRead, NULL);
    if(dwFileRead !=(DWORD)(nSectionLength-2))
    {
      EXIF_ERR_OUT(L"Premature end of file?");
      return -1;
    }
    dwFileRead = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
    //�õ���ǰ�ļ���ָ��λ��
    nSectionsRead += 1;
    switch(marker)
    {
    case M_SOS:   //����������
      return 1;
    case M_EOI:   //End Of Image
      EXIF_ERR_OUT(L"No image in this jpeg file");
      return -1;
    case M_COM:   //ע����
      if (nHaveCom)
      {
        // Discard this section.
        free(Sections[--nSectionsRead].Data);
        Sections[nSectionsRead].Data=0;
      }
      else
      {
        EXIF_Process_COM(Data, nSectionLength);
        nHaveCom = 1;
      }
    case M_JFIF:
      //��׼�� JPG �ļ�ͨ������ TAG�����Ҵ��� M_APP0 ��
      //EXIF ͼ��ʹ�� exif ���(�� M_APP1 ��)��ȡ�����
      //������Щ���(���� ACDSee)���޸� JPG �ļ����ͬʱ������ 2 ��TAG
      //���������ﲻ��Ҫ M_JFIF ��Ϣ��ֱ������ȥ����
      //�������д�ļ���������Ҫ�� JFIF ��Ϣ���Ƶ��µ�JPG�ļ�ͷ
      free(Sections[--nSectionsRead].Data);
      Sections[nSectionsRead].Data=0;
      break;
    case M_EXIF:
      //EXIF ��Ϣ TAG
      if (memcmp(Data+2, "Exif", 4) == 0)
      {
        m_pExifInfo->IsExif = EXIF_process_EXIF(Data, dwFilePointerBeforeReadData, (unsigned char *)Data+2, nSectionLength);
      }
      else
      {
        // Discard this section.
        free(Sections[--nSectionsRead].Data);
        Sections[nSectionsRead].Data=0;
      }
      break;
    case M_SOF0:
    case M_SOF1:
    case M_SOF2:
    case M_SOF3:
    case M_SOF5:
    case M_SOF6:
    case M_SOF7:
    case M_SOF9:
    case M_SOF10:
    case M_SOF11:
    case M_SOF13:
    case M_SOF14:
    case M_SOF15:
      EXIF_process_SOFn(Data, marker);
      break;
    default:
      // Skip any other sections.
      //if (ShowTags) printf("Jpeg section marker 0x%02x size %d\n",marker, nSectionLength);
      break;
    }
  }
  return 1;
}
/*********************************************************************
  ��������:
  ��    ��:
          IN: LPCTSTR pszJpgFileName: JPG �ļ�ȫ·����
         OUT:
         I/O: EXIFINFO* pExifInfo: ������ EXIF ��Ϣ�Ľṹ��
    ����ֵ: >=0��ʾ�ɹ���<0��ȡʧ��
  ��������: ��ȡ������ JPG �ļ��е� EXIF ��Ϣ
  ��    ��: �ⲿ������
  ע    ��:
*********************************************************************/
int EXIF_Read(LPCTSTR pszJpgFileName, EXIFINFO* pExifInfo)
{
  int nReturn = -1;
  HANDLE hFile = INVALID_HANDLE_VALUE;
  if(pExifInfo == 0)
  {
    EXIF_ERR_OUT(L"Parameter incorreted! pExifInfo must not be NULL!");
    return -1;
  }
  hFile = CreateFile(pszJpgFileName,  //LPCTSTR lpcszFileName
    GENERIC_READ,                     //DWORD dwAccess
    FILE_SHARE_READ,                  //DWORD dwShareMode
    NULL,                             //LPSECURITY_ATTRIBUTES lpSecurityAttributes
    OPEN_EXISTING,                    //DWORD dwCreate.���ļ��������������ʧ��
    FILE_ATTRIBUTE_NORMAL,            //DWORD dwFlagsAndAttributes
    NULL                              //HANDLE hTemplateFile
    );
  //�� JPG �ļ�ʧ��
  if(hFile == INVALID_HANDLE_VALUE)
  {
    EXIF_ERR_OUT(L"JPG File Not Found!");
    return -1;
  }
  //���ļ�ָ���Ƶ���ǰ
  SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
  //��ʼ���� JPG �ļ�
  pExifInfo->ThumbnailPointer = NULL;
  pExifInfo->ThumbnailSize = 0;
  pExifInfo->IsExif = FALSE;
 
  m_pExifInfo = pExifInfo;
  nReturn = EXIF_Decode(hFile);
  if(nReturn>=0 && (m_pExifInfo->dwExifType&ET_NOT_CLOSE_FILE) )
  {
    m_pExifInfo->hJpgFileHandle = (HFILE)hFile;
  }
  else
  {
    CloseHandle(hFile);
  }
  return nReturn;
}
 
/*********************************************************************
  ��������: int EXIF_AddUserComments(LPCTSTR pszJpgFileName, LPCTSTR pszUserComments, DWORD dwCommentLength, COMMENT_TYPE nCommentType)
  ��    ��:
          IN: LPCTSTR pszJpgFileName: JPG �ļ�ȫ·����
              LPCTSTR pszUserComments: ��Ҫд���ע��
              DWORD dwCommentLength: ��Ҫд���ע�͵ĳ���
              COMMENT_TYPE nCommentType: ע��д��ʱ�����ͣ����� ASCII, UNICODE, JIS ��
         OUT:
         I/O:
    ����ֵ: �ɹ�����һ��>0����ֵ��ʾд���ע�ͳ��ȣ�ʧ�ܷ���<0
  ��������: ��ָ�����û�ע��д�뵽 JPG �ļ���
  ��    ��:
*********************************************************************/
int EXIF_AddUserComments(LPCTSTR pszJpgFileName, LPCTSTR pszUserComments, DWORD dwCommentLength, COMMENT_TYPE ctCommentType)
{
  int nReturn = -1;
  EXIFINFO exifinfo = {0};
  HANDLE hFile = INVALID_HANDLE_VALUE;
  DWORD dwWriteBytes = 0;
  TCHAR pszCommentType[8] = {0};
  switch(ctCommentType)
  {
  case CT_ASCII:
    _tcscpy(pszCommentType, L"ASCII");
    break;
  case CT_UNDEFINE:
    _tcscpy(pszCommentType, L"UNICODE");
    break;
  case CT_JIS:
    _tcscpy(pszCommentType, L"JIS");
    break;
  }
 
  if(pszUserComments == 0)
  {
    EXIF_ERR_OUT(L"Parameter incorreted! pszUserComments must not be NULL!");
    return -1;
  }
  if(dwWriteBytes > _tcslen(pszUserComments))
  {
    EXIF_ERR_OUT(L"dwWriteBytes must be bigger or equal than the length of user comments!");
    return -1;
  }
  hFile = CreateFile(pszJpgFileName,  //LPCTSTR lpcszFileName
    GENERIC_WRITE|GENERIC_READ,       //DWORD dwAccess
    FILE_SHARE_WRITE|FILE_SHARE_READ, //DWORD dwShareMode
    NULL,                             //LPSECURITY_ATTRIBUTES lpSecurityAttributes
    OPEN_ALWAYS,                      //DWORD dwCreate.���ļ�������������򴴽�
    FILE_ATTRIBUTE_NORMAL,            //DWORD dwFlagsAndAttributes
    NULL                              //HANDLE hTemplateFile
    );
  //�� JPG �ļ�ʧ��
  if(hFile == INVALID_HANDLE_VALUE)
  {
    EXIF_ERR_OUT(L"JPG File Not Found!");
    return -1;
  }
  //���ļ�ָ���Ƶ���ǰ
  SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
  //��ʼ���� JPG �ļ�
  exifinfo.dwExifType |= ET_NOT_CLOSE_FILE;
  exifinfo.ThumbnailPointer = NULL;
  exifinfo.ThumbnailSize = 0;
  exifinfo.UserCOM = 0;
  exifinfo.UserCOMLength = 0;
  m_pExifInfo = &exifinfo;
  nReturn = EXIF_Decode(hFile);
  if(nReturn>=0 && (m_pExifInfo->dwExifType&ET_NOT_CLOSE_FILE) )
  {
    m_pExifInfo->hJpgFileHandle = (HFILE)hFile;
  }
  else
  {
    CloseHandle(hFile);
  }
  if(nReturn<0)
  {
    return nReturn;
  }
  //������ JPG �ļ���û���ڴ滺����
  if(m_pExifInfo->UserCOMLength<=8)
  {
    EXIF_ERR_OUT(L"This JPG file not include user comments buffer area!");
    CloseHandle(hFile);
    return -1;
  }
  SetFilePointer(hFile, 0, 0, FILE_BEGIN);
  SetFilePointer(hFile, (DWORD)m_pExifInfo->UserCOM, 0, FILE_BEGIN);
  //����д���û���ע��
  //д����뷽ʽ
  WriteFile(hFile, pszCommentType, 8, &dwWriteBytes, NULL);
  m_pExifInfo->UserCOMLength -= 8;  //ǰ���� 8 ���ֽڵı��뷽ʽ
  if(m_pExifInfo->UserCOMLength>dwWriteBytes)
  {
    WriteFile(hFile, pszUserComments, dwCommentLength+1, &dwWriteBytes, NULL);
    nReturn = (int)dwWriteBytes;
  }
  else
  {
    WriteFile(hFile, pszUserComments, m_pExifInfo->UserCOMLength+1, &dwWriteBytes, NULL);
    nReturn = (int)dwWriteBytes;
  }
  //��д�� \0
  //WriteFile(hFile, '\0', 1, &dwWriteBytes, NULL);
  return nReturn;
}

CExifTags::CExifTags(void)
{
}


CExifTags::~CExifTags(void)
{
}
