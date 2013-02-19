/**********************************************************************
 * 工程名:	DrvExam
 * 文件名:	common.h
 * 版本号:	1.0
 * 功能:	
 * 作者:	
 * 创建日期:	2012-03-26
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef COMMON_H
#define COMMON_H

#if !defined NOIMPORT
	#ifdef DEVELOPER
		#define IMPORT __declspec(dllexport)
	#else
		#define IMPORT __declspec(dllimport)
	#endif
#else
	#define IMPORT
#endif

/**********************************************************************
 * 说明: 常量
 **********************************************************************/
const int KNetRetryTime	= 3;

const TCHAR KDBServer[]	= _T("dbsvr");
const TCHAR KControlServer[]	= _T("controlsvr");


/**********************************************************************
 * 说明: 宏
 **********************************************************************/

#define SAFECALL(pointer, function)\
	if (0 != pointer)\
		pointer->function

#endif

