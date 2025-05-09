/**
 * @File: JSON.h
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/29
 * @Description: Json数据的解析与生成
 */
#ifndef INVDK_JSON_H
#define INVDK_JSON_H

#include "INVDK_String.h"

namespace INVDK
{
// JSON 类型
#define INVDK_JSON_Invalid (0)	   /* 无效类型 */
#define INVDK_JSON_False (1 << 0)  /* Bool 类型 */ 
#define INVDK_JSON_True (1 << 1)   /* Bool 类型 */ 
#define INVDK_JSON_NULL (1 << 2)   /* 空 */ 
#define INVDK_JSON_Number (1 << 3) /* 数字类型 */ 
#define INVDK_JSON_String (1 << 4) /* 字符串类型 */ 
#define INVDK_JSON_Array (1 << 5)  /* 数组类型 */
#define INVDK_JSON_Object (1 << 6) /* JSON 类型 */ 
#define INVDK_JSON_Raw (1 << 7)	   /* 原始 Json */

#define INVDK_JSON_Reference (1 << 8)	  /* 用来判断位是否被设置，如果被设置了说明指针是引用，并非自己持有 */
#define INVDK_JSON_StringIsConst (1 << 9) /* 用来判断位是否被设置，如果被设置了说明字符串是常量 */


	// JSON 结构
	typedef struct JSON
	{
		JSON* prev;  // 指向上一个节点
		JSON* next;  // 指向下一个节点
		JSON* child; // 指向子节点

		INVDK_INT type; // 节点的类型

		INVDK_PCHAR valueString;  // 如果节点的类型是 INVDK_JSON_String，值就放在这里
		INVDK_INT valueInt;		  // 如果节点的类型是 INVDK_JSON_Number，值就放在这里
		INVDK_DOUBLE valueDouble; // 如果节点的类型是 INVDK_JSON_Number，值就放在这里

		INVDK_PCHAR name; // 节点的名字
	} JSON;


	// 限制嵌套深度
#ifndef INVDK_JSON_NESTING_LIMIT
#	define INVDK_JSON_NESTING_LIMIT 1000
#endif

	/// @brief 解析 JSON 字符串
	/// @param value [IN] 字符串
	/// @return 解析的 JSON 对象
	INVDK_SDK_API JSON* JSON_Parse(INVDK_PCCHAR value);
	/// @brief 解析指定长度的 JSON 字符串
	/// @param value [IN] 字符串
	/// @param bufferLength [IN] 字符串长度
	/// @return 解析的 JSON 对象
	INVDK_SDK_API JSON* JSON_ParseWithLength(INVDK_PCCHAR value, INVDK_SIZE bufferLength);
	/// @brief 解析 JSON 字符串
	/// @param value [IN] 字符串
	/// @param returnParseEnd [OUT] 用于返回解析结束的位置
	/// @param requireNullTerminated [IN] 指示 JSON 字符串是否要以 '\0' 终止
	/// @return 解析的 JSON 对象
	INVDK_SDK_API JSON* JSON_ParseWithOpts(INVDK_PCCHAR value, INVDK_PCCHAR* returnParseEnd, INVDK_BOOL requireNullTerminated);
	/// @brief 解析指定长度的 JSON 字符串
	/// @param value [IN] 字符串
	/// @param bufferLength [IN] 字符串长度
	/// @param returnParseEnd [OUT] 用于返回解析结束的位置
	/// @param requireNullTerminated [IN] 指示 JSON 字符串是否要以 '\0' 终止
	/// @return 解析的 JSON 对象
	INVDK_SDK_API JSON* JSON_ParseWithLengthOpts(INVDK_PCCHAR value, INVDK_SIZE bufferLength, INVDK_PCCHAR* returnParseEnd, INVDK_BOOL requireNullTerminated);

	/// @brief 删除 JSON 节点
	/// @param item [IN] JSON 节点
	/// @return
	INVDK_SDK_API INVDK_VOID JSON_Delete(JSON* item);

	/// @brief 获取 INVDK_JSON_Array 类型的 JSON 对象的数组长度
	/// @param array [IN] INVDK_JSON_Array 类型的 JSON 对象
	/// @return INVDK_JSON_Array 类型的 JSON 对象的数组长度
	INVDK_SDK_API INVDK_INT JSON_GetArraySize(const JSON* array);
	/// @brief 获取数组中第 index 个元素
	/// @param array [IN] INVDK_JSON_Array 类型的 JSON 对象
	/// @param index [IN] 索引
	/// @return INVDK_JSON_Array 类型的 JSON 对象的数组中第 index 个元素
	INVDK_SDK_API JSON* JSON_GetArrayItem(const JSON* array, INVDK_INT index);
	/// @brief 从 object 里面获取键值为 name 的 JSON 对象
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @return 如果找到匹配的项，则返回指向该项的指针；否则返回 NULL
	INVDK_SDK_API JSON* JSON_GetObjectItem(const JSON* const object, INVDK_PCCHAR const name);

	/// @brief 创建 INVDK_JSON_NULL 类型的节点
	/// @return INVDK_JSON_NULL 类型的节点
	INVDK_SDK_API JSON* JSON_CreateNull();
	/// @brief 创建 INVDK_JSON_True 类型的节点
	/// @return INVDK_JSON_True 类型的节点
	INVDK_SDK_API JSON* JSON_CreateTrue();
	/// @brief 创建 INVDK_JSON_False 类型的节点
	/// @return INVDK_JSON_False 类型的节点
	INVDK_SDK_API JSON* JSON_CreateFalse();
	/// @brief 创建 INVDK_JSON_True 或 INVDK_JSON_False 类型的节点
	/// @param boolean [IN] 节点的值
	/// @return INVDK_JSON_True 或 INVDK_JSON_False 类型的节点
	INVDK_SDK_API JSON* JSON_CreateBool(INVDK_BOOL boolean);
	/// @brief 创建 INVDK_JSON_Number 类型的节点
	/// @param num [IN] 节点的值
	/// @return INVDK_JSON_Number 类型的节点
	INVDK_SDK_API JSON* JSON_CreateNumber(INVDK_DOUBLE num);
	/// @brief 创建 INVDK_JSON_String 类型的节点
	/// @param string [IN] 节点的值
	/// @return INVDK_JSON_String 类型的节点
	INVDK_SDK_API JSON* JSON_CreateString(INVDK_PCCHAR string);
	/// @brief 创建 INVDK_JSON_Raw 类型的节点
	/// @param raw [IN] 包含 JSON 数据的字符串
	/// @return INVDK_JSON_Raw 类型的节点
	INVDK_SDK_API JSON* JSON_CreateRaw(INVDK_PCCHAR raw);
	/// @brief 创建 INVDK_JSON_Array 类型的节点
	/// @return 创建 INVDK_JSON_Array 类型的节点
	INVDK_SDK_API JSON* JSON_CreateArray();
	/// @brief 创建 INVDK_JSON_Object 类型的节点
	/// @return INVDK_JSON_Object 类型的节点
	INVDK_SDK_API JSON* JSON_CreateObject();

	/// @brief 创建 INVDK_JSON_String 类型的引用节点
	/// @param string [IN] 节点的值
	/// @return INVDK_JSON_String 类型的引用节点
	INVDK_SDK_API JSON* JSON_CreateStringReference(INVDK_PCCHAR string);
	/// @brief 创建 INVDK_JSON_Object 类型的引用节点
	/// @return INVDK_JSON_Object 类型的引用节点
	INVDK_SDK_API JSON* JSON_CreateObjectReference(const JSON* child);
	/// @brief 创建 INVDK_JSON_Array 类型的引用节点
	/// @return 创建 INVDK_JSON_Array 类型的引用节点
	INVDK_SDK_API JSON* JSON_CreateArrayReference(const JSON* child);

	/// @brief 添加 JSON 节点到 JSON 数组里面
	/// @param array [IN] JSON 数组
	/// @param item [IN] 要添加的节点
	/// @return TRUE:成功	FALSE:失败
	INVDK_SDK_API INVDK_BOOL JSON_AddItemToArray(JSON* array, JSON* item);
	/// @brief 添加 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @param item [IN] 要添加的节点
	/// @return TRUE:成功	FALSE:失败
	INVDK_SDK_API INVDK_BOOL JSON_AddItemToObject(JSON* object, INVDK_PCCHAR name, JSON* item);

	/// @brief 添加空的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddNullToObject(JSON* const object, INVDK_PCCHAR const name);
	/// @brief 添加 INVDK_JSON_True 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddTrueToObject(JSON* const object, INVDK_PCCHAR const name);
	/// @brief 添加 INVDK_JSON_False 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddFalseToObject(JSON* const object, INVDK_PCCHAR const name);
	/// @brief 添加 INVDK_JSON_True 或 INVDK_JSON_False 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @param boolean [IN] INVDK_BOOL 类型的值
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddBoolToObject(JSON* const object, INVDK_PCCHAR const name, const INVDK_BOOL boolean);
	/// @brief 添加 INVDK_JSON_Number 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @param number [IN] 整数的值
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddNumberToObject(JSON* const object, INVDK_PCCHAR const name, const INVDK_DOUBLE number);
	/// @brief 添加 INVDK_JSON_String 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @param string [IN] 要添加的字符串
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddStringToObject(JSON* const object, INVDK_PCCHAR const name, INVDK_PCCHAR const string);
	/// @brief 添加 INVDK_JSON_Raw 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @param raw [IN] 存放 JSON 数据的字符串
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddRawToObject(JSON* const object, INVDK_PCCHAR const name, INVDK_PCCHAR const raw);
	/// @brief 添加 INVDK_JSON_Object 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddObjectToObject(JSON* const object, INVDK_PCCHAR const name);
	/// @brief 添加 INVDK_JSON_Array 类型的 JSON 节点到 JSON 对象里面
	/// @param object [IN] JSON 对象
	/// @param name [IN] 键值
	/// @return 成功返回添加的 JSON 节点，失败返回 NULL
	INVDK_SDK_API JSON* JSON_AddArrayToObject(JSON* const object, INVDK_PCCHAR const name);

	/// @brief JSON 对象转换为格式化的字符串
	/// @param item [IN] JSON 对象
	/// @return 转换后的字符串
	INVDK_SDK_API INVDK_PCHAR JSON_Print(const JSON* item);
	/// @brief JSON 对象转换为不格式化的字符串
	/// @param item [IN] JSON 对象
	/// @return 转换后的字符串
	INVDK_SDK_API INVDK_PCHAR JSON_PrintUnformatted(const JSON* item);

	/// @brief 判断 JSON 节点是否是 INVDK_Invalid 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsInvalid(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_False 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsFalse(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_True 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsTrue(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_True 或 INVDK_JSON_False 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsBool(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_NULL 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsNull(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_Number 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsNumber(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_String 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsString(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_Array 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsArray(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_Object 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsObject(const JSON* const item);
	/// @brief 判断 JSON 节点是否是 INVDK_JSON_Raw 类型的
	/// @param item [IN] 要判断的 JSON 节点
	/// @return TRUE: 是	FALSE: 不是
	INVDK_SDK_API INVDK_BOOL JSON_IsRaw(const JSON* const item);
}

#endif // !INVDK_JSON_H
