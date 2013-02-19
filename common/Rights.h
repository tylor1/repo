
#ifndef RIGHTS_H
#define RIGHTS_H

#define RIGHTS_LOGIN							0x00000001		/** R01-登录的权限 */
#define RIGHTS_PRACTICE							0x00000002		/** R02-练习的权限 */
#define RIGHTS_EXAMINATION						0x00000004		/** R03-考试的权限 */
#define RIGHTS_QUERY							0x00000008		/** R04-查询统计的权限 */
#define RIGHTS_PRINT							0x00000010		/** R05-打印成绩的权限 */
#define RIGHTS_SET								0x00000020		/** R06-参数设置的权限 */
#define RIGHTS_PHOTO							0x00000040		/** R07-相片采集的权限 */
#define RIGHTS_FINGERPRINT						0x00000080		/** R08-指纹采集的权限 */
#define RIGHTS_MODIFYPASSWD						0x00000100		/** R09-修改密码的权限 */
#define RIGHTS_DOWNLOAD							0x00000200		/** R10-联网下载预约的权限 */
#define RIGHTS_UPLOAD							0x00000400		/** R11-联网上传成绩的权限 */
#define RIGHTS_DELETE							0x00000800		/** R12-考生信息删除的权限 */
#define RIGHTS_MODIFY_BASE						0x00001000		/** R13-基本信息修改的权限 */
#define RIGHTS_MODIFY_EXAM						0x00002000		/** R14-考试信息修改的权限 */
#define RIGHTS_DETERMINANT_FAIL					0x00004000		/** R15-人工评判不合格的权限 */
#define RIGHTS_EXCEPTION_MANAGE					0x00008000		/** R16-考试异常处理的权限 */
#define RIGHTS_BACKUP							0x00010000		/** R17-数据备份转储的权限 */
#define RIGHTS_SINGINAL_CHECK					0x00020000		/** R18-场地信号检测的权限 */
#define RIGHTS_LOG_CHECK						0x00040000		/** R19-查看系统日志的权限 */
#define RIGHTS_RIGHTS_MANAGE					0x00080000		/** R20-用户权限管理的权限 */
#define RIGHTS_GRADE_CELL_SET					0x00100000		/** R21-扣分代码设置的权限 */
#define RIGHTS_INFORMATION						0x00200000		/** R22-综合信息设置的权限 */
#define RIGHTS_IP_SET							0x00400000		/** R23-访问控制管理权限(IP) */


#define A101				100		/** 不按规定使用安全带或者戴安全头盔	100	0	1 */
#define A102				100		/** 不按交通信号灯、标志、标线或者民警指挥信号行驶	100	0	1 */
#define A105				100		/** 起步时车辆后溜距离大于30厘米	100	0	1 */
#define A203				20		/** 起步时车辆后溜，但后溜距离小于30厘米	20	0	1 */
#define A308				10		/** 因操作不当造成发动机熄火一次	10	1	1 */
#define B101				100		/** 不按规定路线、顺序行驶	100	0	1 */
#define B102				100		/** 碰擦桩杆	100	0	1 */
#define B103				100		/** 车身出线	100	0	1 */
#define B104				100		/** 移库不入	100	0	1 */
#define B201				100		/** 车辆停止后，汽车前保险杠或者摩托车前轴未定于桩杆线上，且前后超出50厘米	100	0	1 */
#define B202				20		/** 车辆停止后，汽车前保险杠或者摩托车前轴未定于桩杆线上，且前后不超出50厘米	20	0	1 */
#define B203				20		/** 车辆停止后，车身距离路边缘线30厘米以上	20	0	1 */
#define B301				100		/** 车辆在入库停止后，车身出线	100	0	1 */
#define B302				100		/** 碰擦桩杆	100	0	1 */
#define B303				10		/** 行驶中轮胎触轧车道边线	10	0	1 */
#define B401				20		/** 其中有一车轮未上桥	20	1	1 */
#define B402				10		/** 已骑上桥面，在行驶中出现一个车轮掉下桥面	10	1	1 */
#define B501				100		/** 车轮驶出边缘线	100	0	1 */
#define B502				20		/** 车轮轧路边缘线	20	1	1 */
#define B601				100		/** 车轮触轧突出点或驶出边缘线	100	0	1 */
#define B602				20		/** 车轮轧道路边缘线	20	1	1 */
#define B603				10		/** 借助倒车完成	10	1	1 */
#define B701				100		/** 时速低于20公里/小时通过	100	0	1 */
#define B702				100		/** 不按规定路线、顺序行驶	100	0	1 */
#define B703				20		/** 每碰擦一次限宽门悬杆	20	1	1 */


#endif
