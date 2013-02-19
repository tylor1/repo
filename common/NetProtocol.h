/**********************************************************************
 * ������:	DrvExam
 * �ļ���:	NetProtocol.h
 * �汾��:	1.0
 * ����:	����ͨѶЭ��
 * ����:
 * ��������:	2012-03-27
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 *********************************************************************/

#ifndef NETPROTOCOL_H
#define NETPROTOCOL_H

#include "common.h"
#include "..\utils\api.h"

// const int KMaxPackSize = 7168;	// < 8192
// const int KPackFileSize = 6144;
const DWORD KPackMarker = 0x5A5AA5A5; /** ����Ч�Լ�� */

const int KMaxPackSize = 2048;
const int KPackFileSize = 512;

const int KPackBufferSize = 512;
const int KwszIPSize = 16;

const int KFileTransferBlockSize = 1024;	/** ���ļ���������С */

/**********************************************************************
 * ˵��: �������ݰ�����
 **********************************************************************/
enum EPackType
{
	ept_unknown = 0x0010,	/** δ֪���Ͱ� */
	ept_head,	/** ��ͷӦ�� */
	ept_hello,	/** �ʺ� */
	ept_chk,	/** ������ݰ��Ƿ��͵��� */
	ept_list,	/** list���� */
	ept_cmd,	/** ָ�� */
	ept_buf,	/** ���� */
	ept_score,	/** ������Ŀ�ɼ� */
	ept_file,	/** �����ļ� */
};

/**********************************************************************
 * ˵��: ����
 **********************************************************************/
enum ECommand
{
	ecmd_photo = 0,	/** �ɼ���Ƭ */
};

/**********************************************************************
 * ˵��: �¼�
 **********************************************************************/
enum ENetEvent
{
	ene_error = 0,	/** ����������� */
	ene_new_connect,	/** �������� */
	ene_break,	/** ���ӶϿ�/�жϿ����� */
	ene_huge,	/** �����̫�� */
	ene_connect_failed,	/** ������������ʧ�� */
	ene_set_failed,	/** ��������ʧ�� */
};


/**********************************************************************
 * ˵��: ���ļ�����¼�
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
	eft_connect_accept = 1,	/** �ļ������������������ */
	eft_connect_refuse,	/** �ļ�����������Ѿ���������, �ܾ����� */
	eft_disconnect,	/** ���ӶϿ� */
	eft_request = 10,	/** �ļ��������� */
	eft_accept,	/** ��ʼ���������ļ������� */
	eft_refuse,	/** �ܾ��ļ����� */
	eft_cancel,	/** ȡ���ļ����� */
};

/**********************************************************************
 * class: TPackHead
 * ˵�� : �������ͷ��Ӧ���
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

		/** �����Լ��Ĵ��л� */
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
	int m_ept;	/** ������ */
	int m_nDataLength;
	int m_nIndexYY;
	DWORD m_dwPackMarker;	/** �жϰ��Ƿ����ڴ����Ǹ� */ 
private:
	BOOL m_bAck;
	BOOL m_bDataPack;
};

/**********************************************************************
 * class: TPackHello
 * ˵�� : �ʺ�
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

		/** �����Լ��Ĵ��л� */
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
 * ˵�� : ���������
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

		/** �����Լ��Ĵ��л� */
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
	DWORD m_dwPackSize;	/** ����С */
};


/**********************************************************************
 * class: TPackCheck
 * ˵�� : ���԰����������繤��״���������һ�����Ƿ��ʹ�
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
 * ˵�� : ������Ա���俼����Ŀ��
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

		/** �����Լ��Ĵ��л� */
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

	int m_nIndex;		/** ��ǰ��������� */
	int m_nTotol;		/** �б������� */
	int m_nExamItem;	/** ������Ŀ */
};

/**********************************************************************
 * class: TPackScore
 * ˵�� : ���Գɼ���
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

		/** �����Լ��Ĵ��л� */
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
	int m_nIdentifier;	/** ׼��֤�� */
	int m_nExamItem;	/** ������Ŀ */
	int m_nAreaNum;	/** ������� */ 
	int m_nScore;	/** ĳ��Ŀ���ԡ��ɼ��� */
	time_t m_time;	/** ʱ�� */
};

/**********************************************************************
 * class: TPackBuf
 * ˵�� : �ַ��������
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

		/** �����Լ��Ĵ��л� */
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
	int m_nBufLen;	/** ����ʹ�ô�С */
	// CString m_strBuf;	/** ���� */
	TCHAR m_wszBuf[MAX_PATH];	/** ���� */
};

/**********************************************************************
 * class: TPackCmd
 * ˵�� : ָ���
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

		/** �����Լ��Ĵ��л� */
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
	int m_nCommand;	/** ���� */
	int m_nContext;	/** �������� */
};


/**********************************************************************
 * class: TPackFile
 * ˵�� : �ļ���
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
	DWORD m_dwFileSize;	/** �ļ���С */
	TCHAR m_wszFileName[MAX_PATH];	/** �ļ��� */
};


/** �ļ���� */
typedef TPackHead* LPPACKHEAD;
typedef CList<LPPACKHEAD, LPPACKHEAD&> LstPack;
typedef CMap<CString,LPCTSTR, LstPack*, LstPack*&> MapListPack;	/** ���ط����������г����ն˵�SOCKET�Ե����ݰ� */
// typedef CMap<int,int, LstPack*, LstPack*&> MapListPack;	/** ���ط����������г����ն˵�SOCKET�Ե����ݰ� */

#endif /** #ifndef NETPROTOCOL_H */
