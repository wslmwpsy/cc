
#pragma once

////////////////////////////////////////////////////////////////////////////////
//      .h　文件
/********************************************************************
        Copyright@ 版权所有@ 1998-2005hengai。保留所有权利。
********************************************************************/
 
 
/********************************************************************
  文件说明: 能够读取 JPG 图像文件中的 EXIF 信息
  文件名称: exif.h
  版本号  : 1.0.0
  作    者: hengai
  修改纪录:
  使用方法: 包含此头文件，然后调用函数
              int EXIF_Read(LPCTSTR pszJpgFileName, EXIFINFO* pExifInfo)
              即可获取 EXIF 信息。EXIF信息包含在参数 pExifInfo 中
            在定义了 #define EXIF_OUTPUT_ERRMSG (默认下已经定义)后可以使用
              LPCTSTR EXIF_GetErrorString(); 获取出错信息
*********************************************************************/
 
//////////////////////////////////////////////////////////////////////////
#ifndef STATIC
#define STATIC    static
#endif
#define EXIF_OUTPUT_ERRMSG      //定义是否输出出错信息
//////////////////////////////////////////////////////////////////////////
//              定义常量
#define MAX_COMMENT   1000      //最大的注释字符串长度
 
//////////////////////////////////////////////////////////////////////////
//写入注释时，表明注释的类型，如 ASCII, UNICODE 等
typedef enum ECT{
  CT_ASCII = 0,
  CT_UNICODE,
  CT_JIS,
  CT_UNDEFINE
}COMMENT_TYPE;
//////////////////////////////////////////////////////////////////////////
//              定义需要的结构体
#define ET_NOT_CLOSE_FILE       0x00000001  //最后不关闭打开的文件句柄
#define ET_MALLOC_THUMBNAIL     0x00000002  //拷贝缩略图的数据，调用者需要使用 free()
#define ET_MALLOC_USERCOM       0x00000004  //是否拷贝用户注释，调用者需要使用 free()
#define ET_MALLOC_MAKERCOM      0x00000008  //是否拷贝厂商注释，调用者需要使用 free()
//JPG 文件中的读入后的 EXIFF 信息保存到这个结构体中
typedef struct tag_ExifInfo {
  DWORD dwExifType;             //取值为 ET_NOT_CLOSE_FILE|ET_MALLOC_THUMBNAIL, ....
  DWORD dwExifType2;
  char  Version      [5];       //EXIF 信息版本
  char  CameraMake   [32];      //DC 制造商
  char  CameraModel  [40];      //DC 型号
  char  DateTime     [20];      //JPG 文件日期
  char  DateTimeDigitized[20];  //JPG 文件被其它软件修改日期
  int   Height, Width;          //图像高度、宽度
  int   Orientation;            //拍摄方向，例如相机向左手方向旋转后拍摄的
  int   IsColor;                //
  int   Process;                //被处理
  int   FlashUsed;              //是否使用闪光灯
  float FocalLength;            //焦距
  float ExposureTime;           //曝光时间(快门速度)
  float ApertureFNumber;        //光圈数
  float Distance;               //拍摄物体距离
  float CCDWidth;               //CCD 大小
  float ExposureBias;           //曝光补偿
  int   Whitebalance;           //白平衡
  int   MeteringMode;           //测光模式
  int   ExposureProgram;        //曝光
  int   ISOequivalent;          //ISO
  int   CompressionLevel;       //压缩
  float FocalplaneXRes;         //焦平面X轴分辨率
  float FocalplaneYRes;         //焦平面Y轴分辨率
  float FocalplaneUnits;        //焦平面分辨率单位
  float Xresolution;            //X 轴分辨率
  float Yresolution;            //Y 轴分辨率
  float ResolutionUnit;         //分辨率单位
  float Brightness;             //亮度
  char  Comments[MAX_COMMENT];  //注释
  DWORD UserCOMLength;          //用户注释长度。如果==0表示没有用户注释
  char  *UserCOM;               //用户注释
                                //if(dwExifType&ET_MALLOC_USERCOM == TRUE) 这个数值保存了用户注释数据，调用者需要使用 free()
                                //否则为用户注释的偏移量(相对于文件起始0处)
  DWORD MakerCOMLength;         //厂商注释长度。如果==0表示没有厂商注释
  char  *MakerCOM;              //厂商注释
                                //if(dwExifType&ET_MALLOC_MAKERCOM == TRUE) 这个数值保存了厂商注释数据，调用者需要使用 free()
                                //否则为厂商注释的偏移量(注意：是在当前SECTION中的偏移量，不是相对整个文件的)
 
 
  UCHAR * ThumbnailPointer;     //缩略图数据。
                                //if(dwExifType&ET_MALLOC_THUMBNAIL == TRUE) 这个数值保存了缩略图的数据
                                //否则为一个 DWORD(需要强制转换) 表示缩略图在JPG文件中的偏移值(相对于文件起始0处)
  DWORD ThumbnailSize;          //缩略图的大小(字节流 ThumbnailPointer 的长度)
                                //如果<=0表示该 JPG 文件没有缩略图
  HFILE hJpgFileHandle;         //返回打开的 JPG 文件句柄。必须 dwExifType&ET_NOT_CLOSE_FILE == TRUE 才是有效句柄
                                //用户需要使用 CloseHandle(hJpgFileHandle)来关闭这个句柄
  BOOL  IsExif;                 //是否存在 EXIF 信息
} EXIFINFO;
//////////////////////////////////////////////////////////////////////////
//              接口函数
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