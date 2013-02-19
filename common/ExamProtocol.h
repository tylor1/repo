/**********************************************************************
 * ������:	DrvExam
 * �ļ���:	ExamProtocol.h
 * �汾��:	1.0
 * ����:	�����Э�顢���ڰ�Э��
 * ����:	tylor
 * ��������:	2012-04-13
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 *********************************************************************/

#ifndef EXAMPROTOCOL_H
#define EXAMPROTOCOL_H

// #include "common.h"
// #include "NetProtocol.h"

/**********************************************************************
 * ˵��: ������Ŀ
 **********************************************************************/
#define EI_B1					0x0001	/** ׮�� */
#define EI_B2					0x0002	/** ���� */
#define EI_B3					0x0004	/** �෽ */
#define EI_B4					0x0008	/** ���� */
#define EI_B5					0x0010	/** ���� */
#define EI_B6					0x0020	/** ֱ�� */
#define EI_B7					0x0040	/** �޿� */
#define EI_B8					0x0080	/** Բ�� */
#define EI_B9					0x0100	/** ���� */
#define EI_BA					0x0200	/** ��� */

#define EI_POLE					0x0001	/** ׮�� */
#define EI_SLOPE				0x0002	/** ���� */
#define EI_SIDE					0x0004	/** �෽ */
#define EI_BRIDGE				0x0008	/** ���� */
#define EI_CURVE				0x0010	/** ���� */
#define EI_ANGLE				0x0020	/** ֱ�� */
#define EI_DOOR					0x0040	/** �޿� */
#define EI_OBSTACLE				0x0080	/** Բ�� */
#define EI_GEAR					0x0100	/** ���� */
#define EI_WAVY					0x0200	/** ��� */

/**********************************************************************
 * ˵��: ������Ŀö��
 **********************************************************************/
enum EExamItem
{
	eei_pole = 1,	/** ׮�� */

	eei_slope,		/** ���� */
	eei_side,		/** �෽ */
	eei_bridge,		/** ���� */
	eei_curve,		/** ���� */
	eei_angle,		/** ֱ�� */
	eei_door,		/** �޿� */
	eei_obstacle,	/** Բ�� */
	eei_gear,		/** ���� */
	eei_wavy		/** ��� */
};

/**********************************************************************
 * ˵��: ׮��
 **********************************************************************/


/**********************************************************************
 * ˵��: ����
 **********************************************************************/
#define SLOPE_START					0x0001	/** �𲽺��� */
#define SLOPE_END					0x0002	/** �������� */
#define SLOPE_50D					0x0004	/** ����-50cm */
#define SLOPE_50U					0x0008	/** ����+50cm */
#define SLOPE_15D					0x0010	/** ����-15cm */
#define SLOPE_15U					0x0020	/** ����+15cm */
#define SLOPE_SIDE30				0x0040	/** �ӽ����ز���30cm */

#define SLOPE_OTHER0				0x0080	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define SLOPE_OTHER1				0x0100	/** ������Ŀ */
#define SLOPE_OTHER2				0x0200	/** ������Ŀ */
#define SLOPE_OTHER3				0x0400	/** ������Ŀ */

/**********************************************************************
 * ˵��: �෽
 **********************************************************************/
#define SIDE_START					0x0001	/** �𲽺��� */
#define SIDE_END					0x0002	/** �������� */
#define SIDE_FRONT					0x0004	/** ����-��ǰ */
#define SIDE_RIGHT					0x0008	/** ����-���� */
#define SIDE_BOTTOM					0x0010	/** ����-��� */
#define SIDE_LEFT					0x0020	/** ����-���� */
#define SIDE_SHAKELF				0x0040	/** ������-��ǰ */
#define SIDE_SHAKERF				0x0080	/** ������-��ǰ */
#define SIDE_SHAKERB				0x0100	/** ������-�Һ� */
#define SIDE_SHAKELB				0x0200	/** ������-��� */
#define SIDE_SIDE					0x0400	/** ������Եѹ��/���� */

#define SIDE_OTHER0					0x0800	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define SIDE_OTHER1					0x1000	/** ������Ŀ */
#define SIDE_OTHER2					0x2000	/** ������Ŀ */
#define SIDE_OTHER3					0x4000	/** ������Ŀ */

/**********************************************************************
 * ˵��: ����
 **********************************************************************/
#define BRIDGE_START				0x0001	/** �𲽺��� */
#define BRIDGE_END					0x0002	/** �������� */
#define BRIDGE_AFRONT				0x0004	/** �г̿���-����ǰ */
#define BRIDGE_AMIDDLE				0x0008	/** �г̿���-������ */
#define BRIDGE_ABACK				0x0010	/** �г̿���-���ź� */
#define BRIDGE_BFRONT				0x0020	/** �г̿���-����ǰ */
#define BRIDGE_BMIDDLE				0x0040	/** �г̿���-������ */
#define BRIDGE_BBACK				0x0080	/** �г̿���-���ź� */

#define BRIDGE_OTHER0				0x0100	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define BRIDGE_OTHER1				0x0200	/** ������Ŀ */
#define BRIDGE_OTHER2				0x0400	/** ������Ŀ */
#define BRIDGE_OTHER3				0x0800	/** ������Ŀ */

/**********************************************************************
 * ˵��: ����
 **********************************************************************/
#define CURVE_START					0x0001	/** �𲽺��� */
#define CURVE_END					0x0002	/** �������� */
#define CURVE_LINNER				0x0004	/** ѹ�����-���ڲ� */
#define CURVE_RINNER				0x0008	/** ѹ�����-���ڲ� */
#define CURVE_LOUTER				0x0010	/** ѹ�����-����� */
#define CURVE_ROUTER				0x0020	/** ѹ�����-����� */

#define CURVE_OTHER0				0x0040	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define CURVE_OTHER1				0x0080	/** ������Ŀ */
#define CURVE_OTHER2				0x0100	/** ������Ŀ */
#define CURVE_OTHER3				0x0200	/** ������Ŀ */

/**********************************************************************
 * ˵��: ֱ��
 **********************************************************************/
#define ANGLE_START					0x0001	/** �𲽺��� */
#define ANGLE_END					0x0002	/** �������� */
#define ANGLE_LINNER				0x0004	/** ѹ�����-���ڲ� */
#define ANGLE_RINNER				0x0008	/** ѹ�����-���ڲ� */
#define ANGLE_LOUTER				0x0010	/** ѹ�����-����� */
#define ANGLE_ROUTER				0x0020	/** ѹ�����-����� */
#define ANGLE_POINT 				0x0040	/** ͻ�����г̿��� */

#define ANGLE_OTHER0				0x0080	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define ANGLE_OTHER1				0x0100	/** ������Ŀ */
#define ANGLE_OTHER2				0x0200	/** ������Ŀ */
#define ANGLE_OTHER3				0x0400	/** ������Ŀ */

/**********************************************************************
 * ˵��: �޿�
 **********************************************************************/
#define DOOR_START					0x0001	/** �𲽺��� */
#define DOOR_END					0x0002	/** �������� */
#define DOOR_FRONT					0x0004	/** Υ��������-ǰ */
#define DOOR_MIDDLE					0x0008	/** Υ��������-�� */
#define DOOR_BOTTOM					0x0010	/** Υ��������-�� */
#define DOOR_SHAKELF				0x0020	/** ������-ǰ�� */
#define DOOR_SHAKERF				0x0040	/** ������-ǰ�� */
#define DOOR_SHAKELM				0x0080	/** ������-���� */
#define DOOR_SHAKERM				0x0100	/** ������-���� */
#define DOOR_SHAKELB				0x0200	/** ������-���� */
#define DOOR_SHAKERB				0x0400	/** ������-���� */

#define DOOR_OTHER0					0x0800	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define DOOR_OTHER1					0x1000	/** ������Ŀ */
#define DOOR_OTHER2					0x2000	/** ������Ŀ */
#define DOOR_OTHER3					0x4000	/** ������Ŀ */

/**********************************************************************
 * ˵��: Բ��
 **********************************************************************/
#define OBSTACLE_START					0x00000001	/** �𲽺��� */
#define OBSTACLE_END					0x00000002	/** �������� */
#define OBSTACLE_LINNER					0x00000004	/** ѹ�����-���ڲ� */
#define OBSTACLE_RINNER					0x00000008	/** ѹ�����-���ڲ� */
#define OBSTACLE_LOUTER					0x00000010	/** ѹ�����-����� */
#define OBSTACLE_ROUTER					0x00000020	/** ѹ�����-����� */
#define OBSTACLE_SWITCH1				0x00000040	/** �г̿���-��1�� */
#define OBSTACLE_SWITCH2				0x00000080	/** �г̿���-��2�� */
#define OBSTACLE_SWITCH3				0x00000100	/** �г̿���-��3�� */
#define OBSTACLE_SWITCH4				0x00000200	/** �г̿���-��4�� */
#define OBSTACLE_SWITCH5				0x00000400	/** �г̿���-��5�� */
#define OBSTACLE_SWITCH6				0x00000800	/** �г̿���-��6�� */
#define OBSTACLE_SHAKE1					0x00001000	/** �񶯴�����-��1�� */
#define OBSTACLE_SHAKE2					0x00002000	/** �񶯴�����-��2�� */
#define OBSTACLE_SHAKE3					0x00004000	/** �񶯴�����-��3�� */
#define OBSTACLE_SHAKE4					0x00008000	/** �񶯴�����-��4�� */
#define OBSTACLE_SHAKE5					0x00010000	/** �񶯴�����-��5�� */
#define OBSTACLE_SHAKE6					0x00020000	/** �񶯴�����-��6�� */
#define OBSTACLE_ONEL					0x00040000	/** �Ǳؾ�������-1���� */
#define OBSTACLE_ONER					0x00080000	/** �Ǳؾ�������-1���� */
#define OBSTACLE_TWO					0x00100000	/** �ؾ�������-2�� */
#define OBSTACLE_THREE					0x00200000	/** �ؾ�������-3�� */
#define OBSTACLE_FOUR					0x00400000	/** �ؾ�������-4�� */
#define OBSTACLE_FIVE					0x00800000	/** �ؾ�������-5�� */
#define OBSTACLE_SIXL					0x01000000	/** �Ǳؾ�������-6���� */
#define OBSTACLE_SIXR					0x02000000	/** �Ǳؾ�������-6���� */

#define OBSTACLE_OTHER0					0x04000000	/** ������Ŀ27 */	/** ���ϼ����Ŀ */
#define OBSTACLE_OTHER1					0x08000000	/** ������Ŀ28 */
#define OBSTACLE_OTHER2					0x10000000	/** ������Ŀ29 */
#define OBSTACLE_OTHER3					0x20000000	/** ������Ŀ30 */

/**********************************************************************
 * ˵��: ����
 **********************************************************************/
#define GEAR_START					0x0001	/** �𲽺��� */
#define GEAR_END					0x0002	/** �������� */

#define GEAR_OTHER0					0x0004	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define GEAR_OTHER1					0x0008	/** ������Ŀ */
#define GEAR_OTHER2					0x0010	/** ������Ŀ */
#define GEAR_OTHER3					0x0020	/** ������Ŀ */

/**********************************************************************
 * ˵��: ���
 **********************************************************************/
#define WAVY_START					0x0001	/** �𲽺��� */
#define WAVY_END					0x0002	/** �������� */
#define WAVY_TWENTY					0x0004	/** ����͹��ǰ20m������ */
#define WAVY_TWO					0x0008	/** ����͹��ǰ2m������ */

#define WAVY_OTHER0					0x0010	/** ������Ŀ */	/** ���ϼ����Ŀ */
#define WAVY_OTHER1					0x0020	/** ������Ŀ */
#define WAVY_OTHER2					0x0040	/** ������Ŀ */
#define WAVY_OTHER3					0x0080	/** ������Ŀ */

/**********************************************************************
 * ˵��: Ȩ��
 **********************************************************************/
#define R00_NONE					0x00000000		/** ��Ȩ�� */
#define R01_LOGIN					0x00000001		/** ��¼��Ȩ�� */
#define R02_PRACTICE				0x00000002		/** ��ϰ��Ȩ�� */
#define R03_EXAMINATION				0x00000004		/** ���Ե�Ȩ�� */
#define R04_QUERY					0x00000008		/** ��ѯͳ�Ƶ�Ȩ�� */
#define R05_PRINT					0x00000010		/** ��ӡ�ɼ���Ȩ�� */
#define R06_SET						0x00000020		/** �������õ�Ȩ�� */
#define R07_PHOTO					0x00000040		/** ��Ƭ�ɼ���Ȩ�� */
#define R08_FINGERPRINT				0x00000080		/** ָ�Ʋɼ���Ȩ�� */
#define R09_MODIFYPASSWD			0x00000100		/** �޸������Ȩ�� */
#define R10_DOWNLOAD				0x00000200		/** ��������ԤԼ��Ȩ�� */
#define R11_UPLOAD					0x00000400		/** �����ϴ��ɼ���Ȩ�� */
#define R12_DELETE					0x00000800		/** ������Ϣɾ����Ȩ�� */
#define R13_MODIFY_BASE				0x00001000		/** ������Ϣ�޸ĵ�Ȩ�� */
#define R14_MODIFY_EXAM				0x00002000		/** ������Ϣ�޸ĵ�Ȩ�� */
#define R15_DETERMINANT_FAIL		0x00004000		/** �˹����в��ϸ��Ȩ�� */
#define R16_EXCEPTION_MANAGE		0x00008000		/** �����쳣�����Ȩ�� */
#define R17_BACKUP					0x00010000		/** ���ݱ���ת����Ȩ�� */
#define R18_SINGINAL_CHECK			0x00020000		/** �����źż���Ȩ�� */
#define R19_LOG_CHECK				0x00040000		/** �鿴ϵͳ��־��Ȩ�� */
#define R20_RIGHTS_MANAGE			0x00080000		/** �û�Ȩ�޹����Ȩ�� */
#define R21_GRADE_CELL_SET			0x00100000		/** �۷ִ������õ�Ȩ�� */
#define R22_INFORMATION				0x00200000		/** �ۺ���Ϣ���õ�Ȩ�� */
#define R23_IP_SET					0x00400000		/** IP���ʿ��ƹ���Ȩ�� */


// typedef CMap<CString,CString&, LstPack*, LstPack*&> MapListPack;	/** ���ط����������г����ն˵�SOCKET�Ե����ݰ� */

#endif /** #ifndef EXAMPROTOCOL_H */