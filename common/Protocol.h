/**********************************************************************
 * 工程名:	DrvExam
 * 文件名:	Protocol.h
 * 版本号:	1.0
 * 功能:	网络包协议、串口包协议
 * 作者:
 * 创建日期:	2012-03-27
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common.h"
#include "..\utils\api.h"

// #ifdef NET_USE_LOCALE
// const int KMaxPackSize = 7168;	// < 8192
// const int KPackFileSize = 6144;
// #else
// const int KMaxPackSize = 2048;
// const int KPackFileSize = 1024;
// #endif

const int KMaxPackSize = 2048;	// < 8192
const int KPackFileSize = 512;

const int KPackBufferSize = 1024;
const int KwszIPSize = 16;
/**********************************************************************
 * 说明: 考试项目
 **********************************************************************/
#define EI_B1          0x0001	/** 桩考 */
#define EI_B2          0x0002	/** 坡起 */
#define EI_B3          0x0004	/** 侧方 */
#define EI_B4          0x0008	/** 单边 */
#define EI_B5          0x0010	/** 曲线 */
#define EI_B6          0x0020	/** 直角 */
#define EI_B7          0x0040	/** 限宽 */
#define EI_B8          0x0080	/** 圆饼 */
#define EI_B9          0x0100	/** 百米 */
#define EI_BA          0x0200	/** 起伏 */

/**********************************************************************
 * 说明: 网络数据包类型
 **********************************************************************/
enum EPackType
{
	ept_ack = 1,	/** 收到数据包应答 */
	ept_chk,	/** 检查数据包是否发送到达 */
	ept_list,	/** list数据包 */
	ept_cmd,	/** 指令包 */
	ept_buf,	/** 缓冲包 */
	ept_score,	/** 考试项目，使用下面各项 */
	ept_file	/** 文件块 */
};

enum EExamItem
{
	eei_b1 = 21,	/** 桩考 */

	eei_b2,	/** 坡起 */
	eei_b3,	/** 侧方 */
	eei_b4,	/** 单边 */
	eei_b5,	/** 曲线 */
	eei_b6,	/** 直角 */
	eei_b7,	/** 限宽 */
	eei_b8,	/** 圆饼 */
	eei_b9,	/** 百米 */
	eei_ba	/** 起伏 */
};

/**********************************************************************
 * 说明: 命令
 **********************************************************************/
enum EPackCommand
{
	epc_photo = 0	/** 采集照片 */
};

/**********************************************************************
 * 说明: 事件
 **********************************************************************/
enum ENetEvent
{
	ene_error = 0,	/** 有网络错误发生 */
	ene_newc,	/** 有新连接 */
	ene_break,	/** 连接断开/有断开连接 */
	ene_huge,	/** 网络包太大 */
};

#pragma pack(1)
/**********************************************************************
 * class: TNetPack
 * 说明 : 网络包基类，可作为收到包的应答
 **********************************************************************/
class TNetPack : public CObject
{
	DECLARE_SERIAL(TNetPack)
public:
	TNetPack(EPackType ept = ept_ack)
		:m_ept(ept),
		m_nPort(0)
	{
		m_nPackSize = sizeof(TNetPack);
		memset(m_wszIP, 0, KwszIPSize);
	}
	virtual ~TNetPack() {};

	BOOL IsACK() { return (ept_ack == m_ept); };

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				CString str = m_wszIP;
				ar << m_ept;
				ar << m_nPackSize;
				ar << str;
				ar << m_nPort;
			}
			else
			{
				CString str;
				ar >> m_ept;
				ar >> m_nPackSize;
				ar >> str;
				ar >> m_nPort;
				_tcscpy(m_wszIP,str.GetBuffer(str.GetLength()));
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

		/** 结束 */
		ar.Flush();
	};
public:
	int m_ept;	/** 包类型 */
	int m_nPackSize;	/** 包大小 */
	int m_nPort;	/** port */
	TCHAR m_wszIP[KwszIPSize];	/** IP */
};

/**********************************************************************
 * class: TPackCheck
 * 说明 : 测试包，测试网络工作状况，检查上一个包是否送达
 **********************************************************************/
class TPackCheck : public TNetPack
{
	DECLARE_SERIAL(TPackCheck)
public:
	TPackCheck(EPackType ept = ept_chk)
		:TNetPack(ept)
	{
		m_nPackSize = sizeof(TPackCheck);
	}
	virtual ~TPackCheck() {};
};

/**********************************************************************
 * class: TPackList
 * 说明 : 考试人员及其考试项目包
 **********************************************************************/
class TPackList : public TNetPack
{
	DECLARE_SERIAL(TPackList)
public:
	TPackList(EPackType ept = ept_list)
		:TNetPack(ept),
		m_nIndex(1),
		m_nTotol(1),
		m_nExamItem(0)
	{
		m_nPackSize = sizeof(TPackList);
	}

	virtual ~TPackList() {};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TNetPack::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				ar << m_nIndex;
				ar << m_nTotol;
				ar << m_nExamItem;
			}
			else
			{
				ar >> m_nIndex;
				ar >> m_nTotol;
				ar >> m_nExamItem;
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

		/** 结束 */
		ar.Flush();
	};


	int m_nIndex;		/** 当前条索引序号 */
	int m_nTotol;		/** 列表总条数 */
	int m_nExamItem;	/** 考试项目 */
};

/**********************************************************************
 * class: TPackScore
 * 说明 : 考试成绩包
 **********************************************************************/
class TPackScore : public TNetPack
{
	DECLARE_SERIAL(TPackScore)
public:
	TPackScore(EPackType ept = ept_score)
		:TNetPack(ept),
		m_nAreaNum(0),
		m_nScore(0),
		m_time(0)
	{
		m_nPackSize = sizeof(TPackScore);
	}

	virtual ~TPackScore() {};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TNetPack::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				ar << m_nIdentifier;
				ar << m_nExamItem;
				ar << m_nAreaNum;
				ar << m_nScore;
				ar << m_time;
			}
			else
			{

				ar >> m_nIdentifier;
				ar >> m_nExamItem;
				ar >> m_nAreaNum;
				ar >> m_nScore;
				ar >> m_time;
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

		/** 结束 */
		ar.Flush();
	};

public:
	int m_nIdentifier;	/** 准考证号 */
	int m_nExamItem;	/** 考试项目 */
	int m_nAreaNum;	/** 考场编号 */ 
	int m_nScore;	/** 某项目考试“成绩” */
	time_t m_time;	/** 时间 */
};

/**********************************************************************
 * class: TPackBuf
 * 说明 : 字符串缓冲包
 **********************************************************************/
class TPackBuf : public TNetPack
{
	DECLARE_SERIAL(TPackBuf)
public:
	TPackBuf(EPackType ept = ept_buf)
		:TNetPack(ept),
		m_nBufLen(0)
	{
		m_nPackSize = sizeof(TPackBuf);
		memset(m_wszBuf, 0, KPackBufferSize);/*_tcslen(m_wszBuf)*/
	}

	virtual ~TPackBuf() {};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TNetPack::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				CString str = m_wszBuf;
				ar << m_nBufLen;
				ar << str;
			}
			else
			{
				CString str;
				ar >> m_nBufLen;
				ar >> str;
				_tcscpy(m_wszBuf, str.GetBuffer(str.GetLength()));// _tcscpy  lstrcpy
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

		/** 结束 */
		ar.Flush();
	};

public:
	int m_nBufLen;	/** 缓冲使用大小 */
	TCHAR m_wszBuf[KPackBufferSize];	/** 缓冲 */
};

/**********************************************************************
 * class: TPackCmd
 * 说明 : 指令包
 **********************************************************************/
class TPackCmd : public TNetPack
{
	DECLARE_SERIAL(TPackCmd)
public:
	TPackCmd(EPackType ept = ept_cmd)
		:TNetPack(ept)
	{
		m_nPackSize = sizeof(TPackBuf);
	}

	virtual ~TPackCmd() {};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TNetPack::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				ar << m_nCommand;
			}
			else
			{
				ar >> m_nCommand;
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

		/** 结束 */
		ar.Flush();
	};

public:
	int m_nCommand;
};


/**********************************************************************
 * class: TPackFile
 * 说明 : 文件缓冲包
 **********************************************************************/
class TPackFile : public TNetPack
{
	DECLARE_SERIAL(TPackFile)
public:
	TPackFile(EPackType ept = ept_file)
		:TNetPack(ept),
		m_nFileBufSizeUsed(0),
		m_dwFileSize(0),
		m_nIndex(0)
	{
		m_nPackSize = sizeof(TPackFile);
		memset(m_wszFileBuf, 0, KPackFileSize*sizeof(BYTE));
		memset(m_wszFileName,0,MAX_PATH*sizeof(TCHAR));
	}

	virtual ~TPackFile() {};

	TPackFile& operator=( const TPackFile& identifier )
	{
		this->m_nIndex = identifier.m_nIndex;
		this->m_dwFileSize = identifier.m_dwFileSize;
		this->m_nFileBufSizeUsed = identifier.m_nFileBufSizeUsed;
		memcpy(this->m_wszFileBuf,identifier.m_wszFileBuf,identifier.m_nFileBufSizeUsed);
		_tcscpy(this->m_wszFileName,identifier.m_wszFileName);
		return *this;
	}
// Overridables

	virtual void Serialize(CArchive& ar)
	{
		// ASSERT(0);
		TNetPack::Serialize(ar);

		try
		{
			if (ar.IsStoring())
			{
				ar << m_nIndex;
				ar << m_dwFileSize;
				ar << m_nFileBufSizeUsed;
				ar.Write(m_wszFileBuf, m_nFileBufSizeUsed);
				int nFileNameLen = _tcslen(m_wszFileName);
				ar << nFileNameLen;
				ar.Write(m_wszFileName, nFileNameLen*sizeof(TCHAR));
			}
			else
			{
				ar >> m_nIndex;
				ar >> m_dwFileSize;
				ar >> m_nFileBufSizeUsed;
				ar.Read(m_wszFileBuf,m_nFileBufSizeUsed);
				int nFileNameLen = 0;
				ar >> nFileNameLen;
				ar.Read(m_wszFileName, nFileNameLen*sizeof(TCHAR));
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

		/** 结束 */
		ar.Flush();
	};

public:
	int m_nIndex;	/** 包索引 */
	int m_nFileBufSizeUsed;	/** 缓冲使用大小 */
	DWORD m_dwFileSize;	/** 文件大小 */
	TCHAR m_wszFileName[MAX_PATH];	/** 文件名 */
	BYTE m_wszFileBuf[KPackFileSize];	/** 缓冲 */
};

#pragma pack()

/** 文件最后 */
typedef TNetPack* LPNETPACK;
typedef CList<LPNETPACK, LPNETPACK&> LstNetPack;

#endif /** #ifndef PROTOCOL_H */
