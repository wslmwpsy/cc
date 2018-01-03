#include "StdAfx.h"
#include "ExifTags.h"

////////////////////////////////////////////////////////////////////////
//   .c 文件

/********************************************************************
        Copyright@ 版权所有@ 1998-2005 HENGAI。保留所有权利。
********************************************************************/
 
 
/********************************************************************
  文件说明:
  文件名称: exif.c
  版本号  : 1.0.0
  作    者: hengai
  修改纪录:
*********************************************************************/
#include "ExifTags.h"
//////////////////////////////////////////////////////////////////////////
//读取 EXIF 过程中需要的结构体
typedef struct tag_Section_t{
    UCHAR     *Data;
    int       Type;
    unsigned  Size;
} Section_t;
//////////////////////////////////////////////////////////////////////////
#ifdef  EXIF_OUTPUT_ERRMSG
STATIC TCHAR m_szLastError[256];  //这里保存了出错的信息
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
#define MAX_SECTIONS   20       //JPG 文件中能够允许的最多 SECTION 个数
 
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
 
//定义 APP 标识(SECTION)
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
//注意: 下面的定义是按照 Intel CPU 来定义的，也就是说所有的都是高位在后，
//这样的定义可能与 EXIF 白皮书上的定义不一致。例如白皮书上把 TAG_MAKE 定义为 0F01
//下面是主要信息
#define TAG_MAKE              0x010F    //相机DC 制造商
#define TAG_MODEL             0x0110    //DC 型号
#define TAG_ORIENTATION       0x0112    //拍摄时方向，例如向左手旋转DC 90度拍摄照片
#define TAG_XRESOLUTION       0x011A    //X 轴分辨率
#define TAG_YRESOLUTION       0x011B    //Y 轴分辨率
#define TAG_RESOLUTIONUNIT    0x0128    //分辨率单位，例如 inch, cm
#define TAG_DATATIME          0x0132    //日期时间
#define TAG_YBCR_POSITION     0x0213    //YCbCr 位置控制，例如 居中
#define TAG_COPYRIGHT         0x8298    //版权
#define TAG_EXIF_OFFSET       0x8769    //EXIF 偏移，这时候相当于处理一个新的 EXIF 信息
 
//
#define TAG_IMAGEWIDTH        0x0001    //图像宽度
#define TAG_IMAGEHEIGHT       0x0101    //图像高度
//BOOKMARK
//辅助信息
#define TAG_EXPOSURETIME      0x829A    //曝光时间，例如 1/30 秒
#define TAG_FNUMBER           0x829D    //光圈，例如 F2.8
#define TAG_EXIF_VERSION      0x9000    //EXIF 信息版本
#define TAG_DATETIME_ORIGINAL 0x9003    //照片拍摄时间，例如 2005-10-13 11:09:35
#define TAG_DATATIME_DIGITIZED  0x9004  //相片被其它图像修改软件修改后的时间，例如  2005-10-13 11:36:35
#define TAG_COMPONCONFIG      0x9101    //ComponentsConfiguration 色彩空间配置
#define TAG_COMPRESS_BIT      0x9202    //每像素压缩位数
#define TAG_SHUTTERSPEED      0x9201    //快门速度，例如 1/30 秒
#define TAG_APERTURE          0x9202    //光圈值，例如 F2.8
#define TAG_BRIGHTNESS        0x9203    //亮度
#define TAG_EXPOSURE_BIAS     0x9204    //曝光补偿，例如 EV0.0
#define TAG_MAXAPERTURE       0x9205    //最大光圈值，例如 F2.8
#define TAG_SUBJECT_DISTANCE  0x9206    //拍摄物距离，例如 3.11 米
#define TAG_METERING_MODE     0x9207    //测光模式，例如矩阵
#define TAG_WHITEBALANCE      0x9208    //LightSource 白平衡
#define TAG_FLASH             0x9209    //是否使用闪光灯
#define TAG_FOCALLENGTH       0x920A    //焦距，例如 7.09mm
#define TAG_USERCOMMENT       0x9286    //用户注释
#define TAG_MAKE_COMMENT      0x927C    //厂商注释。这个版本不提供(2005-10-13)
#define TAG_SUBSECTIME        0x9290    //SubSecTime
#define TAG_SUBTIME_ORIGINAL  0x9291    //SubSecTimeOriginal
#define TAG_SUBTIME_DIGITIZED 0x9292    //SubSecTimeDigitized
#define TAG_FLASHPIXVERSION   0x00A0    //Flash Pix 版本
#define TAG_COLORSPACE        0x01A0    //色彩空间，例如 sRGB
 
#define TAG_PIXEL_XDIMENSION  0x02A0    //
#define TAG_PIXEL_YDIMENSION  0x03A0    //
#define TAG_
//EXIFR98
 
//缩略图
#define TAG_INTEROP_OFFSET    0xa005    //偏移
 
#define TAG_FOCALPLANEXRES    0xA20E    //焦平面X轴分辨率，例如 1024000/278
#define TAG_FOCALPLANEYRES    0xA20F    //焦平面X轴分辨率，例如 768000/209
#define TAG_FOCALPLANEUNITS   0xA210    //焦平面分辨率单位
#define TAG_EXIF_IMAGEWIDTH   0xA002    //EXIF 图像宽度(就是这张 JPG 图像)
#define TAG_EXIF_IMAGELENGTH  0xA003    //EXIF 图像高度
 
#define TAG_EXPOSURE_PROGRAM  0x8822    //
#define TAG_ISO_EQUIVALENT    0x8827    //
#define TAG_COMPRESSION_LEVEL 0x9102    //
 
#define TAG_THUMBNAIL_OFFSET  0x0201    //缩略图偏移
#define TAG_THUMBNAIL_LENGTH  0x0202    //缩略图大小
 
 
#define TAG_GPS_VERSIONID       0x0000  //GPS 版本
#define TAG_GPS_LATITUDEREF     0x0001  //纬度参考，例如南纬
#define TAG_GPS_LATITUDE        0x0002  //纬度值
#define TAG_GPS_LONGITUDEREF    0x0003  //经度参考，例如东经
#define TAG_GPS_LONGITUDE       0x0004  //经度值
#define TAG_GPS_ALTITUDEREF     0x0005  //海拔高度参考
#define TAG_GPS_ALTITUDE        0x0006  //海拔
#define TAG_GPS_TIMESTAMP       0x0007  //时间戳
#define TAG_GPS_SATELLITES      0x0008  //卫星
#define TAG_GPS_STATUS          0x0009  //状态
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
  函数声明:
  参    数:
          IN:
         OUT:
         I/O:
    返回值:
  功能描述: 处理 JPG 文件中的注释信息
  引    用:
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
  函数声明: STATIC BOOL EXIF_ProcessExifDir(...)
  参    数:
          IN: CONST UCHAR* DataStart: 数据流的起始位置。这个数值仅仅在函数 EXIF_Decode 中能够改变
              CONST DWORD dwFilePointerBeforeReadData: 在读取数据流之前的文件指针位置
              UCHAR *DirStart: SECTION 中数据流，去除了前面的 EXIF\0\0(6)+II(2)+2A00(2)+08000000(6)=14
              UCHAR *OffsetBase: 仅仅去除了 EXIFF\0\0(6)=6字节
              UINT ExifLength: 整个 SECTION 数据流的长度去除 EXIF\0\0后的长度==All Length - 6
              EXIFINFO * const m_exifinfo: 
         OUT:
         I/O:
              UCHAR **const LastExifRefdP: 偏移过后的位置
    返回值:
  功能描述:
  引    用:
*********************************************************************/
STATIC BOOL EXIF_ProcessExifDir(CONST UCHAR* DataStart, CONST DWORD dwFilePointerBeforeReadData,
                                UCHAR *DirStart, UCHAR *OffsetBase, CONST UINT ExifLength,
                                EXIFINFO * const m_exifinfo, UCHAR **const LastExifRefdP )
{
  int de = 0;                 //
  int a = 0;                  //
  int NumTagEntries = 0;      //包含的 TAG 的个数
  UINT ThumbnailOffset = 0;   //缩略图偏移量
  UINT ThumbnailSize = 0;     //缩略图的大小
  int  BytesCount = 0;        //
  UCHAR * TagEntry = 0;       //每个 TAG 的入口
  int Tag, Format, Components;
  UCHAR * ValuePtr = 0;       //偏移后的位置。因为 TAG 与内容很多时候都不是连续的，而是中间有个偏移量
  DWORD OffsetVal = 0;        //偏移量
 
  //读取文件中存在 TAG 个数
  NumTagEntries = EXIF_Get16u(DirStart);
 
  //判断 EXIF 信息的长度是否正确
  //下面 DirStart+2 指再去除了 NumTagEntries 所占的 2 个字节
  if ((DirStart+2+NumTagEntries*12) > (OffsetBase+ExifLength))
  {
    EXIF_ERR_OUT(L"Illegally sized directory");
    return 0;
  }
  for (de=0;de<NumTagEntries;de++)
  {
    //在下面的操作中，所有的数据通通使用 UCHAR* 来表示
    TagEntry = DirStart+2+12*de;    //TagEntry 的入口点
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
        //JPG 文件内容遭到破坏
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
      //当前已经处理的进度
      //这样可以再次的检测 JPG 文件的合法性
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
    //日期和时间 
    case TAG_DATETIME_ORIGINAL:
      strncpy(m_exifinfo->DateTime, (char*)ValuePtr, 19);
      break;
    case TAG_DATATIME_DIGITIZED:
      strncpy(m_exifinfo->DateTimeDigitized, (char*)ValuePtr, 19);
      break;
    //用户注释
    case TAG_USERCOMMENT:
      m_exifinfo->UserCOMLength = BytesCount;
      if(m_exifinfo->dwExifType & ET_MALLOC_USERCOM)
      {
        m_exifinfo->UserCOM = (char*)malloc(BytesCount);
        memcpy(m_exifinfo->UserCOM, ValuePtr, BytesCount);
        /*//Olympus 誠cf9 誠cf9 蟎cf9 郳cf9 籠cf9 鶿cf9 籠cf9 醆cf9 診cf9 赲cf9 譢cf9 cf9 蔦cf9 蚛cf9 礬cf9 腬cf9 譢cf9 頫cf9 篭cf9 骪cf9 肻cf9 鎈cf9 蘚cf9 頫cf9 砛cf9 鋅cf9 縗cf9 誠cf9 竆cf9 馶cf8 0x20禱cf9 鳿cf9 瞈cf9 籠cf9 蔦cf9 荺cf7 '\0',
        //下面先将后面的空格替换成 '\0' 然后再拷贝注释Comment
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
        //将用户注释拷贝到 exifinfo.Comments 中
        //首先判断是否是 ASCII 模式(就是注释的前面 5 个字符是 ASCII)
        //如果是，则取消拷贝最前面的  ASCII 五个字符
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
        //记录用户注释相对于整个文件起始处的偏移量
        m_exifinfo->UserCOM = (CHAR*)(OffsetBase+OffsetVal-DataStart+dwFilePointerBeforeReadData);
        //m_exifinfo->UserCOM = (char*)OffsetVal;  //偏移
      }
      break;
    //厂商注释
    case TAG_MAKE_COMMENT:
      m_exifinfo->MakerCOMLength = BytesCount;
      if(m_exifinfo->dwExifType & ET_MALLOC_MAKERCOM)
      {
        m_exifinfo->MakerCOM = (char*)malloc(BytesCount);
        memcpy(m_exifinfo->MakerCOM, ValuePtr, BytesCount);
      }
      else
      {
        m_exifinfo->MakerCOM = (char*)OffsetVal; //偏移
      }
      break;
    //光圈
    case TAG_FNUMBER:
      m_exifinfo->ApertureFNumber = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    case TAG_APERTURE:    //光圈值
    case TAG_MAXAPERTURE: //最大光圈值
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
 
    //焦距信息(例如 7.09mm)     
    case TAG_FOCALLENGTH:
    //Nice digital cameras actually save the focal length
    //as a function of how farthey are zoomed in.
     
      m_exifinfo->FocalLength = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    //目标距离(例如 1.11米)
    case TAG_SUBJECT_DISTANCE:
    //Inidcates the distacne the autofocus camera is focused to.
    //Tends to be less accurate as distance increases.
      m_exifinfo->Distance = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    //曝光时间(例如 1/30 秒)
    case TAG_EXPOSURETIME:
    //Simplest way of expressing exposure time, so I
    //trust it most.  (overwrite previously computd value
    //if there is one)
      m_exifinfo->ExposureTime =
        (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
 
    //SHUTTERSPEED 快门速度不需要   
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
 
  //FLASH 闪光灯信息不需要     
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
    //EXIF 图像高度与宽度(例如 1024*768)
    case TAG_EXIF_IMAGELENGTH:
    case TAG_EXIF_IMAGEWIDTH:
      a = (int)EXIF_ConvertAnyFormat(ValuePtr, Format);
      if (m_ExifImageWidth < a) m_ExifImageWidth = a;
      break;
  //焦平面 X 轴分辨率(例如 1024000/278)，理论上与 Y 一致
    case TAG_FOCALPLANEXRES:
      m_exifinfo->FocalplaneXRes = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
  //焦平面 Y 轴分辨率(例如 768000/209)，理论上与 X 一致
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
    //焦平面分辨率单位(例如米)
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
 
    //曝光补偿信息
    case TAG_EXPOSURE_BIAS:
      m_exifinfo->ExposureBias = (float) EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //白平衡
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
    //X 轴分辨率
    case TAG_XRESOLUTION:
      m_exifinfo->Xresolution = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //Y 轴分辨率
    case TAG_YRESOLUTION:
      m_exifinfo->Yresolution = (float)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //缩略图 偏移量 
    case TAG_THUMBNAIL_OFFSET:
      ThumbnailOffset = (unsigned)EXIF_ConvertAnyFormat(ValuePtr, Format);
      break;
    //缩略图的大小
    case TAG_THUMBNAIL_LENGTH:
        ThumbnailSize = (unsigned)EXIF_ConvertAnyFormat(ValuePtr, Format);
        break;
    } //end switch(Tag)
    //EXIF 信息偏移
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
    //如果文件中存在缩略图，那么将缩略图的数据保存
    //注意：这里仅仅负责 malloc，调用者需要自己 free
    if (ThumbnailSize + ThumbnailOffset <= ExifLength)
    {
      //将缩略图的数据全部拷贝到一块新开辟的内存
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
  函数声明: STATIC BOOL EXIF_process_EXIF(UCHAR * CharBuf, UINT length)
  参    数:
          IN: CONST UCHAR* DataStart: 数据流的起始位置。这个数值仅仅在函数 EXIF_Decode 中能够改变
              CONST DWORD dwFilePointerBeforeReadData: 在读取数据流之前的文件指针位置
              UCHAR * CharBuf: 这个 SECTION 数据内容。注意：前面已经去掉了包含长度的2个字符
              CONST UINT length: 这个 SECTION 数据流的长度
    返回值:
  功能描述: 处理某个 SECTION 中的 EXIF 信息。
            成功返回TRUE表示EXIF信息存在且正确，失败返回FALSE
  引    用:
*********************************************************************/
STATIC BOOL EXIF_process_EXIF(CONST UCHAR *DataStart,  CONST DWORD dwFilePointerBeforeReadData,
                              UCHAR *CharBuf, CONST UINT length)
{
  int FirstOffset = 0;
  UCHAR *LastExifRefd = 0;
  m_pExifInfo->FlashUsed = 0;
  m_pExifInfo->Comments[0] = '\0';
 
  m_ExifImageWidth = 0;
 
  //检查 EXIF 头是否正确
  {
    static const unsigned char ExifHeader[] = "Exif\0\0";
    if (memcmp(CharBuf+0, ExifHeader,6))
    {
      EXIF_ERR_OUT(L"Incorrect Exif header");
      return 0;
    }
  }
  //判断内存中数据的排列是按照 Intel 还是按照 Motorola CPU 排列的
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
 
  //检查下面 2 个字节是否是 0x2A00
  if (EXIF_Get16u(CharBuf+8) != 0x2A)
  {
    EXIF_ERR_OUT(L"Invalid Exif start (1)");
    return 0;
  }
 
  //判断下面的 0th IFD Offset 是否是 0x08000000
  FirstOffset = EXIF_Get32u(CharBuf+10);
  if (FirstOffset < 8 || FirstOffset > 16)
  {
    EXIF_ERR_OUT(L"Suspicious offset of first IFD value");
    return 0;
  }
 
  LastExifRefd = CharBuf;
 
  //开始处理 EXIF 信息
  if (!EXIF_ProcessExifDir(DataStart, dwFilePointerBeforeReadData,
    CharBuf+14, CharBuf+6, length-6, m_pExifInfo, &LastExifRefd))
  {
    return 0;
  }
 
  // This is how far the interesting (non thumbnail) part of the exif went.
  // int ExifSettingsLength = LastExifRefd - CharBuf; 
  // 计算 CCD 宽度(单位:毫米)
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
  int nHaveCom = 0;             //是否存在注释，并且保存注释字符串的长度
  int nSectionsRead = 0;        //已经读取 SECTION 的个数
  DWORD dwFileRead = 0;         //使用 ReadFile 读取文件时，读取的字节数
  DWORD dwFilePointerBeforeReadData = 0;  //在读取数据流之前，文件指针的位置
  Section_t Sections[MAX_SECTIONS];       //JPG 文件中 SECTIONS
 
    int   nSectionLength=0;     //SECTION(APP) 长度
    int   marker = 0;           //
    int   ll=0,lh=0, got=0;     //
    UCHAR *Data = 0;            //
 
  //读入 JPG 第1, 2个字节，判断是否是 0xFF,M_SOI
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
  //判断该文件是否是 EXIF 文件
  //EXIF 文件的起始 2 字节必定是 FF D8
  if (a != 0xFF || b != M_SOI)
  {
    EXIF_ERR_OUT(L"File Format Error");
    return -1;
  }
  //使用一个循环，读取 JPG 文件中的 SECTION
  //第一个 SECTION 肯定是 APP1，而APP1起始的Marker肯定为 FFE1
  for(;;)
  {
    if (nSectionsRead >= MAX_SECTIONS)
    {
      EXIF_ERR_OUT(L"Too many sections in this jpg file");
      return -1;
    }
    //查找 JPG 文件填充字符，接下来的7个字符必须有一个不是 0xFF
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
    if(nSectionsRead==0)  //是 APP 1
    {
      //ASSERT(marker == M_APP1);
    }
#endif
    Sections[nSectionsRead].Type = marker;
    //记录读取流数据之前的文件指针位置
    dwFilePointerBeforeReadData = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
    //读取这个 SECTION 的长度
    ReadFile(hFile, &lh, 1, &dwFileRead, NULL);
    ReadFile(hFile, &ll, 1, &dwFileRead, NULL);
    nSectionLength = (lh << 8) | ll;    //EXIF 文件高字节在前，低字节在后，不能读取一个WORD类型
   
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
    //得到当前文件的指针位置
    nSectionsRead += 1;
    switch(marker)
    {
    case M_SOS:   //到了数据区
      return 1;
    case M_EOI:   //End Of Image
      EXIF_ERR_OUT(L"No image in this jpeg file");
      return -1;
    case M_COM:   //注释区
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
      //标准的 JPG 文件通常都有 TAG，并且处于 M_APP0 中
      //EXIF 图像使用 exif 标记(在 M_APP1 中)来取代这个
      //但是有些软件(例如 ACDSee)在修改 JPG 文件后会同时保留这 2 个TAG
      //我们在这里不需要 M_JFIF 信息，直接跳过去即可
      //如果是重写文件，仅仅需要把 JFIF 信息复制到新的JPG文件头
      free(Sections[--nSectionsRead].Data);
      Sections[nSectionsRead].Data=0;
      break;
    case M_EXIF:
      //EXIF 信息 TAG
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
  函数声明:
  参    数:
          IN: LPCTSTR pszJpgFileName: JPG 文件全路径名
         OUT:
         I/O: EXIFINFO* pExifInfo: 保存了 EXIF 信息的结构体
    返回值: >=0表示成功，<0读取失败
  功能描述: 读取并返回 JPG 文件中的 EXIF 信息
  引    用: 外部调用者
  注    意:
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
    OPEN_EXISTING,                    //DWORD dwCreate.打开文件，如果不存在则失败
    FILE_ATTRIBUTE_NORMAL,            //DWORD dwFlagsAndAttributes
    NULL                              //HANDLE hTemplateFile
    );
  //打开 JPG 文件失败
  if(hFile == INVALID_HANDLE_VALUE)
  {
    EXIF_ERR_OUT(L"JPG File Not Found!");
    return -1;
  }
  //将文件指针移到最前
  SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
  //开始处理 JPG 文件
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
  函数声明: int EXIF_AddUserComments(LPCTSTR pszJpgFileName, LPCTSTR pszUserComments, DWORD dwCommentLength, COMMENT_TYPE nCommentType)
  参    数:
          IN: LPCTSTR pszJpgFileName: JPG 文件全路径名
              LPCTSTR pszUserComments: 需要写入的注释
              DWORD dwCommentLength: 需要写入的注释的长度
              COMMENT_TYPE nCommentType: 注释写入时的类型，例如 ASCII, UNICODE, JIS 等
         OUT:
         I/O:
    返回值: 成功返回一个>0的数值表示写入的注释长度，失败返回<0
  功能描述: 将指定的用户注释写入到 JPG 文件中
  引    用:
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
    OPEN_ALWAYS,                      //DWORD dwCreate.打开文件，如果不存在则创建
    FILE_ATTRIBUTE_NORMAL,            //DWORD dwFlagsAndAttributes
    NULL                              //HANDLE hTemplateFile
    );
  //打开 JPG 文件失败
  if(hFile == INVALID_HANDLE_VALUE)
  {
    EXIF_ERR_OUT(L"JPG File Not Found!");
    return -1;
  }
  //将文件指针移到最前
  SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
  //开始处理 JPG 文件
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
  //如果这个 JPG 文件中没有内存缓冲区
  if(m_pExifInfo->UserCOMLength<=8)
  {
    EXIF_ERR_OUT(L"This JPG file not include user comments buffer area!");
    CloseHandle(hFile);
    return -1;
  }
  SetFilePointer(hFile, 0, 0, FILE_BEGIN);
  SetFilePointer(hFile, (DWORD)m_pExifInfo->UserCOM, 0, FILE_BEGIN);
  //下面写入用户的注释
  //写入编码方式
  WriteFile(hFile, pszCommentType, 8, &dwWriteBytes, NULL);
  m_pExifInfo->UserCOMLength -= 8;  //前面有 8 个字节的编码方式
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
  //再写入 \0
  //WriteFile(hFile, '\0', 1, &dwWriteBytes, NULL);
  return nReturn;
}

CExifTags::CExifTags(void)
{
}


CExifTags::~CExifTags(void)
{
}
