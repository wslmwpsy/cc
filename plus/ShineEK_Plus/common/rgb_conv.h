#pragma once


/*--------颜色表节点结构定义------------------------------*/
typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char reserved;
}RGB_QUAD;

/*--------索引节点结构定义--------------------------------*/
typedef struct  INDEXTABLENODE
{
	unsigned char node;
	struct INDEXTABLENODE* next;
}INDEX_TABLE_NODE;


class rgb_conv
{
public:
	rgb_conv(void);
	~rgb_conv(void);

	/*-----------------------------------------------------------------------
	*函数trans: 功能: 实现32bits位图到8bits(256色)位图转换.
	*           参数:
	*           返回值: = 0 转换成功.
	*                   = 1 转换失败.
	*-----------------------------------------------------------------------*/
	int rgb32torgb8(TCHAR *rgb32_path,TCHAR *rgb8_path);
	/*---------------------------------------------------------------/
	* 函数get_index : 功能 : 由节点rgb值返回调色板索引
	*                 参数 : unsigned char  r, g, b,带查询像素rgb值
	*                 返回 : 成功返回调色版索引,否则返回0
	*---------------------------------------------------------------*/
	unsigned char get_index(unsigned char r, unsigned char g, unsigned char b);
};
