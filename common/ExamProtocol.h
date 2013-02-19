/**********************************************************************
 * 工程名:	DrvExam
 * 文件名:	ExamProtocol.h
 * 版本号:	1.0
 * 功能:	网络包协议、串口包协议
 * 作者:	tylor
 * 创建日期:	2012-04-13
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

#ifndef EXAMPROTOCOL_H
#define EXAMPROTOCOL_H

// #include "common.h"
// #include "NetProtocol.h"

/**********************************************************************
 * 说明: 考试项目
 **********************************************************************/
#define EI_B1					0x0001	/** 桩考 */
#define EI_B2					0x0002	/** 坡起 */
#define EI_B3					0x0004	/** 侧方 */
#define EI_B4					0x0008	/** 单边 */
#define EI_B5					0x0010	/** 曲线 */
#define EI_B6					0x0020	/** 直角 */
#define EI_B7					0x0040	/** 限宽 */
#define EI_B8					0x0080	/** 圆饼 */
#define EI_B9					0x0100	/** 百米 */
#define EI_BA					0x0200	/** 起伏 */

#define EI_POLE					0x0001	/** 桩考 */
#define EI_SLOPE				0x0002	/** 坡起 */
#define EI_SIDE					0x0004	/** 侧方 */
#define EI_BRIDGE				0x0008	/** 单边 */
#define EI_CURVE				0x0010	/** 曲线 */
#define EI_ANGLE				0x0020	/** 直角 */
#define EI_DOOR					0x0040	/** 限宽 */
#define EI_OBSTACLE				0x0080	/** 圆饼 */
#define EI_GEAR					0x0100	/** 百米 */
#define EI_WAVY					0x0200	/** 起伏 */

/**********************************************************************
 * 说明: 考试项目枚举
 **********************************************************************/
enum EExamItem
{
	eei_pole = 1,	/** 桩考 */

	eei_slope,		/** 坡起 */
	eei_side,		/** 侧方 */
	eei_bridge,		/** 单边 */
	eei_curve,		/** 曲线 */
	eei_angle,		/** 直角 */
	eei_door,		/** 限宽 */
	eei_obstacle,	/** 圆饼 */
	eei_gear,		/** 百米 */
	eei_wavy		/** 起伏 */
};

/**********************************************************************
 * 说明: 桩考
 **********************************************************************/


/**********************************************************************
 * 说明: 坡起
 **********************************************************************/
#define SLOPE_START					0x0001	/** 起步红外 */
#define SLOPE_END					0x0002	/** 结束红外 */
#define SLOPE_50D					0x0004	/** 离标杆-50cm */
#define SLOPE_50U					0x0008	/** 离标杆+50cm */
#define SLOPE_15D					0x0010	/** 离标杆-15cm */
#define SLOPE_15U					0x0020	/** 离标杆+15cm */
#define SLOPE_SIDE30				0x0040	/** 接近开关测量30cm */

#define SLOPE_OTHER0				0x0080	/** 其他项目 */	/** 车上检测项目 */
#define SLOPE_OTHER1				0x0100	/** 其他项目 */
#define SLOPE_OTHER2				0x0200	/** 其他项目 */
#define SLOPE_OTHER3				0x0400	/** 其他项目 */

/**********************************************************************
 * 说明: 侧方
 **********************************************************************/
#define SIDE_START					0x0001	/** 起步红外 */
#define SIDE_END					0x0002	/** 结束红外 */
#define SIDE_FRONT					0x0004	/** 红外-库前 */
#define SIDE_RIGHT					0x0008	/** 红外-库右 */
#define SIDE_BOTTOM					0x0010	/** 红外-库底 */
#define SIDE_LEFT					0x0020	/** 红外-库左 */
#define SIDE_SHAKELF				0x0040	/** 吊杆振动-左前 */
#define SIDE_SHAKERF				0x0080	/** 吊杆振动-右前 */
#define SIDE_SHAKERB				0x0100	/** 吊杆振动-右后 */
#define SIDE_SHAKELB				0x0200	/** 吊杆振动-左后 */
#define SIDE_SIDE					0x0400	/** 车道边缘压电/红外 */

#define SIDE_OTHER0					0x0800	/** 其他项目 */	/** 车上检测项目 */
#define SIDE_OTHER1					0x1000	/** 其他项目 */
#define SIDE_OTHER2					0x2000	/** 其他项目 */
#define SIDE_OTHER3					0x4000	/** 其他项目 */

/**********************************************************************
 * 说明: 单边
 **********************************************************************/
#define BRIDGE_START				0x0001	/** 起步红外 */
#define BRIDGE_END					0x0002	/** 结束红外 */
#define BRIDGE_AFRONT				0x0004	/** 行程开关-甲桥前 */
#define BRIDGE_AMIDDLE				0x0008	/** 行程开关-甲桥中 */
#define BRIDGE_ABACK				0x0010	/** 行程开关-甲桥后 */
#define BRIDGE_BFRONT				0x0020	/** 行程开关-乙桥前 */
#define BRIDGE_BMIDDLE				0x0040	/** 行程开关-乙桥中 */
#define BRIDGE_BBACK				0x0080	/** 行程开关-乙桥后 */

#define BRIDGE_OTHER0				0x0100	/** 其他项目 */	/** 车上检测项目 */
#define BRIDGE_OTHER1				0x0200	/** 其他项目 */
#define BRIDGE_OTHER2				0x0400	/** 其他项目 */
#define BRIDGE_OTHER3				0x0800	/** 其他项目 */

/**********************************************************************
 * 说明: 曲线
 **********************************************************************/
#define CURVE_START					0x0001	/** 起步红外 */
#define CURVE_END					0x0002	/** 结束红外 */
#define CURVE_LINNER				0x0004	/** 压电电缆-左内侧 */
#define CURVE_RINNER				0x0008	/** 压电电缆-右内侧 */
#define CURVE_LOUTER				0x0010	/** 压电电缆-左外侧 */
#define CURVE_ROUTER				0x0020	/** 压电电缆-右外侧 */

#define CURVE_OTHER0				0x0040	/** 其他项目 */	/** 车上检测项目 */
#define CURVE_OTHER1				0x0080	/** 其他项目 */
#define CURVE_OTHER2				0x0100	/** 其他项目 */
#define CURVE_OTHER3				0x0200	/** 其他项目 */

/**********************************************************************
 * 说明: 直角
 **********************************************************************/
#define ANGLE_START					0x0001	/** 起步红外 */
#define ANGLE_END					0x0002	/** 结束红外 */
#define ANGLE_LINNER				0x0004	/** 压电电缆-左内侧 */
#define ANGLE_RINNER				0x0008	/** 压电电缆-右内侧 */
#define ANGLE_LOUTER				0x0010	/** 压电电缆-左外侧 */
#define ANGLE_ROUTER				0x0020	/** 压电电缆-右外侧 */
#define ANGLE_POINT 				0x0040	/** 突触点行程开关 */

#define ANGLE_OTHER0				0x0080	/** 其他项目 */	/** 车上检测项目 */
#define ANGLE_OTHER1				0x0100	/** 其他项目 */
#define ANGLE_OTHER2				0x0200	/** 其他项目 */
#define ANGLE_OTHER3				0x0400	/** 其他项目 */

/**********************************************************************
 * 说明: 限宽
 **********************************************************************/
#define DOOR_START					0x0001	/** 起步红外 */
#define DOOR_END					0x0002	/** 结束红外 */
#define DOOR_FRONT					0x0004	/** 违例漫反射-前 */
#define DOOR_MIDDLE					0x0008	/** 违例漫反射-中 */
#define DOOR_BOTTOM					0x0010	/** 违例漫反射-后 */
#define DOOR_SHAKELF				0x0020	/** 吊杆振动-前左 */
#define DOOR_SHAKERF				0x0040	/** 吊杆振动-前右 */
#define DOOR_SHAKELM				0x0080	/** 吊杆振动-中左 */
#define DOOR_SHAKERM				0x0100	/** 吊杆振动-中右 */
#define DOOR_SHAKELB				0x0200	/** 吊杆振动-后左 */
#define DOOR_SHAKERB				0x0400	/** 吊杆振动-后右 */

#define DOOR_OTHER0					0x0800	/** 其他项目 */	/** 车上检测项目 */
#define DOOR_OTHER1					0x1000	/** 其他项目 */
#define DOOR_OTHER2					0x2000	/** 其他项目 */
#define DOOR_OTHER3					0x4000	/** 其他项目 */

/**********************************************************************
 * 说明: 圆饼
 **********************************************************************/
#define OBSTACLE_START					0x00000001	/** 起步红外 */
#define OBSTACLE_END					0x00000002	/** 结束红外 */
#define OBSTACLE_LINNER					0x00000004	/** 压电电缆-左内侧 */
#define OBSTACLE_RINNER					0x00000008	/** 压电电缆-右内侧 */
#define OBSTACLE_LOUTER					0x00000010	/** 压电电缆-左外侧 */
#define OBSTACLE_ROUTER					0x00000020	/** 压电电缆-右外侧 */
#define OBSTACLE_SWITCH1				0x00000040	/** 行程开关-第1饼 */
#define OBSTACLE_SWITCH2				0x00000080	/** 行程开关-第2饼 */
#define OBSTACLE_SWITCH3				0x00000100	/** 行程开关-第3饼 */
#define OBSTACLE_SWITCH4				0x00000200	/** 行程开关-第4饼 */
#define OBSTACLE_SWITCH5				0x00000400	/** 行程开关-第5饼 */
#define OBSTACLE_SWITCH6				0x00000800	/** 行程开关-第6饼 */
#define OBSTACLE_SHAKE1					0x00001000	/** 振动传感器-第1饼 */
#define OBSTACLE_SHAKE2					0x00002000	/** 振动传感器-第2饼 */
#define OBSTACLE_SHAKE3					0x00004000	/** 振动传感器-第3饼 */
#define OBSTACLE_SHAKE4					0x00008000	/** 振动传感器-第4饼 */
#define OBSTACLE_SHAKE5					0x00010000	/** 振动传感器-第5饼 */
#define OBSTACLE_SHAKE6					0x00020000	/** 振动传感器-第6饼 */
#define OBSTACLE_ONEL					0x00040000	/** 非必经漫反射-1饼左 */
#define OBSTACLE_ONER					0x00080000	/** 非必经漫反射-1饼右 */
#define OBSTACLE_TWO					0x00100000	/** 必经漫反射-2饼 */
#define OBSTACLE_THREE					0x00200000	/** 必经漫反射-3饼 */
#define OBSTACLE_FOUR					0x00400000	/** 必经漫反射-4饼 */
#define OBSTACLE_FIVE					0x00800000	/** 必经漫反射-5饼 */
#define OBSTACLE_SIXL					0x01000000	/** 非必经漫反射-6饼左 */
#define OBSTACLE_SIXR					0x02000000	/** 非必经漫反射-6饼右 */

#define OBSTACLE_OTHER0					0x04000000	/** 其他项目27 */	/** 车上检测项目 */
#define OBSTACLE_OTHER1					0x08000000	/** 其他项目28 */
#define OBSTACLE_OTHER2					0x10000000	/** 其他项目29 */
#define OBSTACLE_OTHER3					0x20000000	/** 其他项目30 */

/**********************************************************************
 * 说明: 百米
 **********************************************************************/
#define GEAR_START					0x0001	/** 起步红外 */
#define GEAR_END					0x0002	/** 结束红外 */

#define GEAR_OTHER0					0x0004	/** 其他项目 */	/** 车上检测项目 */
#define GEAR_OTHER1					0x0008	/** 其他项目 */
#define GEAR_OTHER2					0x0010	/** 其他项目 */
#define GEAR_OTHER3					0x0020	/** 其他项目 */

/**********************************************************************
 * 说明: 起伏
 **********************************************************************/
#define WAVY_START					0x0001	/** 起步红外 */
#define WAVY_END					0x0002	/** 结束红外 */
#define WAVY_TWENTY					0x0004	/** 距离凸凹前20m处红外 */
#define WAVY_TWO					0x0008	/** 距离凸凹前2m处红外 */

#define WAVY_OTHER0					0x0010	/** 其他项目 */	/** 车上检测项目 */
#define WAVY_OTHER1					0x0020	/** 其他项目 */
#define WAVY_OTHER2					0x0040	/** 其他项目 */
#define WAVY_OTHER3					0x0080	/** 其他项目 */

/**********************************************************************
 * 说明: 权限
 **********************************************************************/
#define R00_NONE					0x00000000		/** 无权限 */
#define R01_LOGIN					0x00000001		/** 登录的权限 */
#define R02_PRACTICE				0x00000002		/** 练习的权限 */
#define R03_EXAMINATION				0x00000004		/** 考试的权限 */
#define R04_QUERY					0x00000008		/** 查询统计的权限 */
#define R05_PRINT					0x00000010		/** 打印成绩的权限 */
#define R06_SET						0x00000020		/** 参数设置的权限 */
#define R07_PHOTO					0x00000040		/** 相片采集的权限 */
#define R08_FINGERPRINT				0x00000080		/** 指纹采集的权限 */
#define R09_MODIFYPASSWD			0x00000100		/** 修改密码的权限 */
#define R10_DOWNLOAD				0x00000200		/** 联网下载预约的权限 */
#define R11_UPLOAD					0x00000400		/** 联网上传成绩的权限 */
#define R12_DELETE					0x00000800		/** 考生信息删除的权限 */
#define R13_MODIFY_BASE				0x00001000		/** 基本信息修改的权限 */
#define R14_MODIFY_EXAM				0x00002000		/** 考试信息修改的权限 */
#define R15_DETERMINANT_FAIL		0x00004000		/** 人工评判不合格的权限 */
#define R16_EXCEPTION_MANAGE		0x00008000		/** 考试异常处理的权限 */
#define R17_BACKUP					0x00010000		/** 数据备份转储的权限 */
#define R18_SINGINAL_CHECK			0x00020000		/** 场地信号检测的权限 */
#define R19_LOG_CHECK				0x00040000		/** 查看系统日志的权限 */
#define R20_RIGHTS_MANAGE			0x00080000		/** 用户权限管理的权限 */
#define R21_GRADE_CELL_SET			0x00100000		/** 扣分代码设置的权限 */
#define R22_INFORMATION				0x00200000		/** 综合信息设置的权限 */
#define R23_IP_SET					0x00400000		/** IP访问控制管理权限 */


// typedef CMap<CString,CString&, LstPack*, LstPack*&> MapListPack;	/** 工控服务器和所有车载终端的SOCKET对的数据包 */

#endif /** #ifndef EXAMPROTOCOL_H */