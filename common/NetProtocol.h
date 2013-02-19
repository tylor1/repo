/**********************************************************************
 * 工程名:	DrvExam
 * 文件名:	NetProtocol.h
 * 版本号:	1.0
 * 功能:	网络通讯协议
 * 作者:
 * 创建日期:	2012-03-27
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef NETPROTOCOL_H
#define NETPROTOCOL_H

#include "common.h"
#include "..\utils\api.h"

// const int KMaxPackSize = 7168;	// < 8192
// const int KPackFileSize = 6144;
const DWORD KPackMarker = 0x5A5AA5A5; /** 包有效性检查 */

const int KMaxPackSize = 2048;
const int KPackFileSize = 512;

const int KPackBufferSize = 512;
const int KwszIPSize = 16;

const int KFileTransferBlockSize = 1024;	/** 传文件缓冲区大小 */

/**********************************************************************
 * 说明: 网络数据包类型
 **********************************************************************/
enum EPackType
{
	ept_unknown = 0x0010,	/** 未知类型包 */
	ept_head,	/** 包头应答 */
	ept_hello,	/** 问候 */
	ept_chk,	/** 检查数据包是否发送到达 */
	ept_list,	/** list数据 */
	ept_cmd,	/** 指令 */
	ept_buf,	/** 缓冲 */
	ept_score,	/** 考试项目成绩 */
	ept_file,	/** 传输文件 */
};

/**********************************************************************
 * 说明: 命令
 **********************************************************************/
enum ECommand
{
	ecmd_photo = 0,	/** 采集照片 */
};

/**********************************************************************
 * 说明: 事件
 **********************************************************************/
enum ENetEvent
{
	ene_error = 0,	/** 有网络错误发生 */
	ene_new_connect,	/** 有新连接 */
	ene_break,	/** 连接断开/有断开连接 */
	ene_huge,	/** 网络包太大 */
	ene_connect_failed,	/** 网络连接请求失败 */
	ene_set_failed,	/** 网络设置失败 */
};


/**********************************************************************
 * 说明: 传文件命令、事件
 **********************************************************************/
// #define CONNECT_BE_ACCEPT    0x00
// #define CONNECT_BE_REFUSE    0x01
// #define DISCONNECT           0x02
// #define REQUEST              0x03
// #define ACCEPT               0x04
// #define REFUSE               0x05
// #define CANCEL               0x06
enum EFileTransfer
{
	eft_connect_accept = 1,	/** 文件传输服务器接收连接 */
	eft_connect_refuse,	/** 文件传输服务器已经建立连接, 拒绝连接 */
	eft_disconnect,	/** 连接断开 */
	eft_request = 10,	/** 文件传输请求 */
	eft_accept,	/** 开始监听传输文件的连接 */
	eft_refuse,	/** 拒绝文件传输 */
	eft_cancel,	/** 取消文件传输 */
};

/**********************************************************************
 * class: TPackHead
 * 说明 : 网络包包头或应答包
 **********************************************************************/
class TPackHead : public CObject
{
	friend class TBasePack;
	DECLARE_SERIAL(TPackHead)
public:
	TPackHead(BOOL bAck = FALSE, EPackType ept = ept_head)
		:m_bAck(bAck),
		m_bDataPack(FALSE),
		m_ept(ept),
		m_nDataLength(0),
		m_nIndexYY(0),
		m_dwPackMarker(0)
	{
	}
	virtual ~TPackHead() {};

	TPackHead& operator=( const TPackHead& identifier )
	{
		// this->m_nPackSize = identifier.m_nPackSize;
		m_bAck = identifier.m_bAck;
		m_bDataPack = identifier.m_bDataPack;
		m_ept = identifier.m_ept;
		m_nDataLength = identifier.m_nDataLength;
		m_nIndexYY = identifier.m_nIndexYY;
		m_dwPackMarker = identifier.m_dwPackMarker;
		return *this;
	}


	BOOL IsACK() const{ return m_bAck; };
	BOOL IsDataPack() const { return m_bDataPack; }
	void SetACK(BOOL bAck = TRUE) { m_bAck = bAck; };

	virtual int GetDataLength()
	{
		int nLength = sizeof(BOOL);
		nLength += sizeof(BOOL);
		nLength += sizeof(int);
		nLength += sizeof(int);
		nLength += sizeof(int);
		nLength += sizeof(DWORD);

		m_nDataLength = nLength;
		return nLength;
	};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				ar << m_bAck;
				ar << m_bDataPack;
				ar << m_ept;
				ar << m_nDataLength;
				ar << m_nIndexYY;
				ar << m_dwPackMarker;
			}
			else
			{
				ar >> m_bAck;
				ar >> m_bDataPack;
				ar >> m_ept;
				ar >> m_nDataLength;
				ar >> m_nIndexYY;
				ar >>m_dwPackMarker;
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}
	};
public:
	int m_ept;	/** 包类型 */
	int m_nDataLength;
	int m_nIndexYY;
	DWORD m_dwPackMarker;	/** 判断包是否是期待的那个 */ 
private:
	BOOL m_bAck;
	BOOL m_bDataPack;
};

/**********************************************************************
 * class: TPackHello
 * 说明 : 问候
 **********************************************************************/
class TPackHello : public TPackHead
{
	DECLARE_SERIAL(TPackHello)
public:
	TPackHello(EPackType ept = ept_hello)
		:TPackHead(FALSE, ept),
		m_nIndex(0)
	{
	}
	virtual ~TPackHello() {};

	TPackHello& operator=( const TPackHello& identifier )
	{
		TPackHead::operator = (identifier);
		this->m_nIndex = identifier.m_nIndex;
		return *this;
	}

	virtual int GetDataLength()
	{
		int nLength = TPackHead::GetDataLength();
		nLength += sizeof(int);

		m_nDataLength = nLength;
		return m_nDataLength;
	};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TPackHead::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				ar << m_nIndex;
			}
			else
			{
				ar >> m_nIndex;
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

	};

	int m_nIndex;
};

/**********************************************************************
 * class: TBasePack
 * 说明 : 网络包基类
 **********************************************************************/
class TBasePack : public TPackHead
{
	DECLARE_SERIAL(TBasePack)
public:
	TBasePack(EPackType ept = ept_unknown)
		:TPackHead(FALSE, ept)
	{
		m_dwPackSize = sizeof(TBasePack);
		m_bDataPack = TRUE;
	}

	virtual ~TBasePack() {};

	TBasePack& operator=( const TBasePack& identifier )
	{
		TPackHead::operator = (identifier);
		this->m_dwPackSize = identifier.m_dwPackSize;
		return *this;
	}

	virtual int GetDataLength()
	{
		int nLength = TPackHead::GetDataLength();
		nLength += sizeof(DWORD);

		m_nDataLength = nLength;
		return m_nDataLength;
	};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TPackHead::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				ar << m_dwPackSize;
			}
			else
			{
				ar >> m_dwPackSize;
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}

	};
public:
	DWORD m_dwPackSize;	/** 包大小 */
};


/**********************************************************************
 * class: TPackCheck
 * 说明 : 测试包，测试网络工作状况，检查上一个包是否送达
 **********************************************************************/
class TPackCheck : public TBasePack
{
	DECLARE_SERIAL(TPackCheck)
public:
	TPackCheck(EPackType ept = ept_chk)
		:TBasePack(ept)
	{
		m_dwPackSize = sizeof(TPackCheck);
	}
	virtual ~TPackCheck() {};

	TPackCheck& operator=( const TPackCheck& identifier )
	{
		TBasePack::operator = (identifier);
		// this->m_nIndex = identifier.m_nIndex;
		return *this;
	}
};

/**********************************************************************
 * class: TPackList
 * 说明 : 考试人员及其考试项目包
 **********************************************************************/
class TPackList : public TBasePack
{
	DECLARE_SERIAL(TPackList)
public:
	TPackList(EPackType ept = ept_list)
		:TBasePack(ept),
		m_nIndex(1),
		m_nTotol(1),
		m_nExamItem(0)
	{
		m_dwPackSize = sizeof(TPackList);
	}

	virtual ~TPackList() {};

	TPackList& operator=( const TPackList& identifier )
	{
		TBasePack::operator = (identifier);
		this->m_nIndex = identifier.m_nIndex;
		this->m_nTotol = identifier.m_nTotol;
		this->m_nExamItem = identifier.m_nExamItem;
		return *this;
	}

	virtual int GetDataLength()
	{
		int nLength = TBasePack::GetDataLength();
		nLength += sizeof(int);
		nLength += sizeof(int);
		nLength += sizeof(int);

		m_nDataLength = nLength;
		return m_nDataLength;
	};
	
// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TBasePack::Serialize(ar);

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

	};

	int m_nIndex;		/** 当前条索引序号 */
	int m_nTotol;		/** 列表总条数 */
	int m_nExamItem;	/** 考试项目 */
};

/**********************************************************************
 * class: TPackScore
 * 说明 : 考试成绩包
 **********************************************************************/
class TPackScore : public TBasePack
{
	DECLARE_SERIAL(TPackScore)
public:
	TPackScore(EPackType ept = ept_score)
		:TBasePack(ept),
		m_nIdentifier(0),
		m_nExamItem(0),
		m_nAreaNum(0),
		m_nScore(0),
		m_time(0)
	{
		m_dwPackSize = sizeof(TPackScore);
	}

	virtual ~TPackScore() {};

	TPackScore& operator=( const TPackScore& identifier )
	{
		TBasePack::operator = (identifier);
		this->m_nIdentifier = identifier.m_nIdentifier;
		this->m_nExamItem = identifier.m_nExamItem;
		this->m_nAreaNum = identifier.m_nAreaNum;
		this->m_nScore = identifier.m_nScore;
		this->m_time = identifier.m_time;
		return *this;
	}

	virtual int GetDataLength()
	{
		int nLength = TBasePack::GetDataLength();
		nLength += sizeof(int);
		nLength += sizeof(int);
		nLength += sizeof(int);
		nLength += sizeof(int);
		nLength += sizeof(time_t);

		m_nDataLength = nLength;
		return m_nDataLength;
	};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TBasePack::Serialize(ar);

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
class TPackBuf : public TBasePack
{
	DECLARE_SERIAL(TPackBuf)
public:
	TPackBuf(EPackType ept = ept_buf)
		:TBasePack(ept),
		m_nBufLen(0)
	{
		m_dwPackSize = sizeof(TPackBuf);
		// m_strBuf = _T("");
		// memset(m_wszBuf, 0, KPackBufferSize);/*_tcslen(m_wszBuf)*/
		memset(m_wszBuf,0,MAX_PATH*sizeof(TCHAR));
	}

	virtual ~TPackBuf() {};

	TPackBuf& operator=( const TPackBuf& identifier )
	{
		TBasePack::operator = (identifier);
		// this->m_strBuf = identifier.m_strBuf;
		lstrcpy(this->m_wszBuf, identifier.m_wszBuf);
		this->m_nBufLen = identifier.m_nBufLen;
		return *this;
	}

	virtual int GetDataLength()
	{
		int nLength = TBasePack::GetDataLength();
		nLength += sizeof(int);
		// nLength += m_strBuf.GetLength() + 1;
		nLength += lstrlen(m_wszBuf) + 1;

		m_nDataLength = nLength;
		return m_nDataLength;
	};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TBasePack::Serialize(ar);

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
				int nSize = 0;
				CString str;
				ar >> m_nBufLen;
				ar >> str;
				nSize = str.GetLength();
				if (nSize <= MAX_PATH)
				{
					lstrcpy( m_wszBuf, str.GetBuffer( nSize ) );
				}
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}
	};

public:
	int m_nBufLen;	/** 缓冲使用大小 */
	// CString m_strBuf;	/** 缓冲 */
	TCHAR m_wszBuf[MAX_PATH];	/** 缓冲 */
};

/**********************************************************************
 * class: TPackCmd
 * 说明 : 指令包
 **********************************************************************/
class TPackCmd : public TBasePack
{
	DECLARE_SERIAL(TPackCmd)
public:
	TPackCmd(EPackType ept = ept_cmd)
		:TBasePack(ept)
	{
		m_dwPackSize = sizeof(TPackCmd);
		m_nCommand = 0;
		m_nContext = 0;
	}

	virtual ~TPackCmd() {};

	TPackCmd& operator=( const TPackCmd& identifier )
	{
		TBasePack::operator = (identifier);
		this->m_nCommand = identifier.m_nCommand;
		this->m_nContext = identifier.m_nContext;
		return *this;
	}

	virtual int GetDataLength()
	{
		int nLength = TBasePack::GetDataLength();
		nLength += sizeof(int);
		nLength += sizeof(int);
	
		m_nDataLength = nLength;
		return m_nDataLength;
	};

// Overridables
	virtual void Serialize(CArchive& ar)
	{
		TBasePack::Serialize(ar);

		/** 增加自己的串行化 */
		try
		{
			if (ar.IsStoring())
			{
				ar << m_nCommand;
				ar >> m_nContext;
			}
			else
			{
				ar >> m_nCommand;
				ar >> m_nContext;
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}
	};

public:
	int m_nCommand;	/** 命令 */
	int m_nContext;	/** 命令内容 */
};


/**********************************************************************
 * class: TPackFile
 * 说明 : 文件包
 **********************************************************************/
class TPackFile : public TBasePack
{
	DECLARE_SERIAL(TPackFile)
public:
	TPackFile(EPackType ept = ept_file)
		:TBasePack(ept),
		m_dwFileSize(0)
	{
		memset(m_wszFileName,0,MAX_PATH*sizeof(TCHAR));
	}

	virtual ~TPackFile() {};

	TPackFile& operator=( const TPackFile& identifier )
	{
		TBasePack::operator = (identifier);
		this->m_dwFileSize = identifier.m_dwFileSize;
		_tcscpy(this->m_wszFileName,identifier.m_wszFileName);
		return *this;
	}

	virtual int GetDataLength()
	{
		int nLength = TBasePack::GetDataLength();
		nLength += sizeof(DWORD);
		nLength += lstrlen(m_wszFileName) + 1;

		m_nDataLength = nLength;
		return m_nDataLength;
	};
	
	
	// Overridables

	virtual void Serialize(CArchive& ar)
	{
		TBasePack::Serialize(ar);

		try
		{
			if (ar.IsStoring())
			{
				CString strFileName = m_wszFileName;
				ar << m_dwFileSize;
				ar << strFileName;
			}
			else
			{
				CString strFileName;
				ar >> m_dwFileSize;
				ar >> strFileName;
				if ( strFileName.GetLength() < MAX_PATH )
				{
					_tcscpy(m_wszFileName, strFileName.GetBuffer(strFileName.GetLength()));
				}
			}
		}
		catch (CArchiveException* e)
		{
			TCHAR wszError[MAX_PATH];
			e->GetErrorMessage(wszError,MAX_PATH);
			Log(wszError);
		}
	};

public:
	DWORD m_dwFileSize;	/** 文件大小 */
	TCHAR m_wszFileName[MAX_PATH];	/** 文件名 */
};


/** 文件最后 */
typedef TPackHead* LPPACKHEAD;
typedef CList<LPPACKHEAD, LPPACKHEAD&> LstPack;
typedef CMap<CString,LPCTSTR, LstPack*, LstPack*&> MapListPack;	/** 工控服务器和所有车载终端的SOCKET对的数据包 */
// typedef CMap<int,int, LstPack*, LstPack*&> MapListPack;	/** 工控服务器和所有车载终端的SOCKET对的数据包 */

#endif /** #ifndef NETPROTOCOL_H */
