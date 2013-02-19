/**********************************************************************
 * ������:	DrvExam
 * �ļ���:	Protocol.h
 * �汾��:	1.0
 * ����:	�����Э�顢���ڰ�Э��
 * ����:
 * ��������:	2012-03-27
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
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
 * ˵��: ������Ŀ
 **********************************************************************/
#define EI_B1          0x0001	/** ׮�� */
#define EI_B2          0x0002	/** ���� */
#define EI_B3          0x0004	/** �෽ */
#define EI_B4          0x0008	/** ���� */
#define EI_B5          0x0010	/** ���� */
#define EI_B6          0x0020	/** ֱ�� */
#define EI_B7          0x0040	/** �޿� */
#define EI_B8          0x0080	/** Բ�� */
#define EI_B9          0x0100	/** ���� */
#define EI_BA          0x0200	/** ��� */

/**********************************************************************
 * ˵��: �������ݰ�����
 **********************************************************************/
enum EPackType
{
	ept_ack = 1,	/** �յ����ݰ�Ӧ�� */
	ept_chk,	/** ������ݰ��Ƿ��͵��� */
	ept_list,	/** list���ݰ� */
	ept_cmd,	/** ָ��� */
	ept_buf,	/** ����� */
	ept_score,	/** ������Ŀ��ʹ��������� */
	ept_file	/** �ļ��� */
};

enum EExamItem
{
	eei_b1 = 21,	/** ׮�� */

	eei_b2,	/** ���� */
	eei_b3,	/** �෽ */
	eei_b4,	/** ���� */
	eei_b5,	/** ���� */
	eei_b6,	/** ֱ�� */
	eei_b7,	/** �޿� */
	eei_b8,	/** Բ�� */
	eei_b9,	/** ���� */
	eei_ba	/** ��� */
};

/**********************************************************************
 * ˵��: ����
 **********************************************************************/
enum EPackCommand
{
	epc_photo = 0	/** �ɼ���Ƭ */
};

/**********************************************************************
 * ˵��: �¼�
 **********************************************************************/
enum ENetEvent
{
	ene_error = 0,	/** ����������� */
	ene_newc,	/** �������� */
	ene_break,	/** ���ӶϿ�/�жϿ����� */
	ene_huge,	/** �����̫�� */
};

#pragma pack(1)
/**********************************************************************
 * class: TNetPack
 * ˵�� : ��������࣬����Ϊ�յ�����Ӧ��
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

		/** �����Լ��Ĵ��л� */
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

		/** ���� */
		ar.Flush();
	};
public:
	int m_ept;	/** ������ */
	int m_nPackSize;	/** ����С */
	int m_nPort;	/** port */
	TCHAR m_wszIP[KwszIPSize];	/** IP */
};

/**********************************************************************
 * class: TPackCheck
 * ˵�� : ���԰����������繤��״���������һ�����Ƿ��ʹ�
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
 * ˵�� : ������Ա���俼����Ŀ��
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

		/** ���� */
		ar.Flush();
	};


	int m_nIndex;		/** ��ǰ��������� */
	int m_nTotol;		/** �б������� */
	int m_nExamItem;	/** ������Ŀ */
};

/**********************************************************************
 * class: TPackScore
 * ˵�� : ���Գɼ���
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

		/** ���� */
		ar.Flush();
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

		/** ���� */
		ar.Flush();
	};

public:
	int m_nBufLen;	/** ����ʹ�ô�С */
	TCHAR m_wszBuf[KPackBufferSize];	/** ���� */
};

/**********************************************************************
 * class: TPackCmd
 * ˵�� : ָ���
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

		/** �����Լ��Ĵ��л� */
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

		/** ���� */
		ar.Flush();
	};

public:
	int m_nCommand;
};


/**********************************************************************
 * class: TPackFile
 * ˵�� : �ļ������
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

		/** ���� */
		ar.Flush();
	};

public:
	int m_nIndex;	/** ������ */
	int m_nFileBufSizeUsed;	/** ����ʹ�ô�С */
	DWORD m_dwFileSize;	/** �ļ���С */
	TCHAR m_wszFileName[MAX_PATH];	/** �ļ��� */
	BYTE m_wszFileBuf[KPackFileSize];	/** ���� */
};

#pragma pack()

/** �ļ���� */
typedef TNetPack* LPNETPACK;
typedef CList<LPNETPACK, LPNETPACK&> LstNetPack;

#endif /** #ifndef PROTOCOL_H */
