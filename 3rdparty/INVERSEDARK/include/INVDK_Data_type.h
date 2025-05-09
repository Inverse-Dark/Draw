/**
 * @File: INVDK_Data_type.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: 数据类型的枚举
 */
#ifndef INVDK_DATA_TYPE_H
#define INVDK_DATA_TYPE_H

typedef enum INVDK_DataType
{
	INVDK_unDef = -1,
	// 基础数据类型(Base Data Type)
	INVDK_BDT_Void,
	INVDK_BDT_Bool,
	INVDK_BDT_Short,
	INVDK_BDT_UShort,
	INVDK_BDT_SInt,
	INVDK_BDT_INT,
	INVDK_BDT_UInt,
	INVDK_BDT_LUInt,
	INVDK_BDT_Char,
	INVDK_BDT_UChar,
	INVDK_BDT_Long,
	INVDK_BDT_ULong,
	INVDK_BDT_LInt,
	INVDK_BDT_ULInt,
	INVDK_BDT_LLong,
	INVDK_BDT_Float,
	INVDK_BDT_Double,
	INVDK_BDT_LDouble,
	INVDK_BDT_Byte,
	INVDK_BDT_Word,
	INVDK_BDT_DWord,
	INVDK_BDT_Size,
	INVDK_BDT_WChar,

	// 常量数据类型(Constant Data Type)
	INVDK_CDT_Char,
	INVDK_CDT_UChar,
	INVDK_CDT_WChar,
	INVDK_CDT_Void,

	// 指针数据类型(Pointer Data Type)
	INVDK_PDT_Char,
	INVDK_PDT_UChar,
	INVDK_PDT_WChar,
	INVDK_PDT_Void,

	// 常量指针数据类型(Constant Pointer Data Type)
	INVDK_CPDT_Char,
	INVDK_CPDT_UChar,
	INVDK_CPDT_WChar,
	INVDK_CPDT_Void,

	// 几何数据类型(Geometry Data Type)
	INVDK_GDT_Point,
	INVDK_GDT_Point3D,
	INVDK_GDT_Size,
	INVDK_GDT_Rect

} INVDK_DType;

#endif	// !INVDK_DATA_TYPE_H

