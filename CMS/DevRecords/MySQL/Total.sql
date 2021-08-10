########### Staff 	
DROP TABLE  IF EXISTS Staff;
CREATE TABLE Staff(
	StaffID int(11) NOT NULL COMMENT '职工编号（主键）' AUTO_INCREMENT,
	StaffName VARCHAR(20) NOT NULL COMMENT '职工姓名',
	StaffPassword VARCHAR(30) NOT NULL COMMENT '密码',
	Sex int(1) NOT NULL COMMENT '性别（0 未知，1 男，2 女）',
	Brithday TIMESTAMP NOT NULL COMMENT '出生日期 YYYYMMDD',
	Department VARCHAR(30) NOT NULL DEFAULT '未分配' COMMENT '部门',
	JobName VARCHAR(30) NOT NULL DEFAULT '未分配' COMMENT '职务',
	Wage FLOAT(11,2) NOT NULL COMMENT '工资',
	WorkingAge SMALLINT(3) NOT NULL DEFAULT 0 COMMENT '工龄',
	Place VARCHAR(50) NOT NULL DEFAULT '未知' COMMENT '籍贯',
	Education VARCHAR(20) NOT NULL DEFAULT '未知' COMMENT '学历',
	Specialty VARCHAR(3) NOT NULL DEFAULT '未知' COMMENT '专业',
	Address VARCHAR(100) NOT NULL DEFAULT '未知' COMMENT '住址',
	Email VARCHAR(20) NOT NULL DEFAULT '未知' COMMENT '邮件',
	Phone VARCHAR(20) NOT NULL DEFAULT '未知' COMMENT '电话',
	EnterCampany TIMESTAMP NOT NULL DEFAULT NOW() COMMENT '入职时间 YYYYMMDD',
	LeaveCampany TIMESTAMP NOT NULL DEFAULT NOW() COMMENT '离职时间 YYYYMMDD',
	Introduction VARCHAR(100) DEFAULT '暂无' COMMENT '描述',
	Resignation int(1) NOT NULL COMMENT '是否离职 0:就职，1：办理入职，2，办理离职，3：离职',
	Params VARCHAR(10) COMMENT '预留字段',
	PRIMARY KEY(StaffID)
	);
	
	
########### Permission 	
DROP TABLE IF EXISTS Permission;
CREATE TABLE Permission (
	PermissionID int(11) NOT NULL COMMENT '权限编号（主键）',
	PermissionName VARCHAR(20) NOT NULL COMMENT '权限名称',
	Param VARCHAR(10) COMMENT '预留字段',
	PRIMARY KEY(PermissionID)
	);
	

########### Department 	
DROP TABLE IF EXISTS Department;
CREATE TABLE Department (
	DepartmntID INT(11) NOT NULL COMMENT '部门编号（主键）',
	DepartmentName VARCHAR(30) NOT NULL COMMENT '部门名称',
	Description VARCHAR(80) COMMENT '说明',
	Param VARCHAR(10) COMMENT '预留字段',
	PRIMARY KEY(DepartmntID)
	);
	
	
########### Job 	
DROP TABLE IF EXISTS Job;
CREATE TABLE Job (
	JobID INT(11) NOT NULL COMMENT '职务编号（主键）',
	JobName VARCHAR(30) NOT NULL COMMENT '职务名称',
	BasicWage FLOAT  COMMENT '基本工资',
	Description VARCHAR(80) COMMENT '说明',
	Param VARCHAR(10) COMMENT '预留字段',
	PRIMARY KEY(JobID)	
	);
	
		
########### Role 	
DROP TABLE IF EXISTS Role;
CREATE TABLE Role (
	RoleID INT(11) NOT NULL COMMENT '角色编号（主键）',
	RoleName VARCHAR(20) NOT NULL COMMENT '角色名称',
	Description VARCHAR(80) NOT NULL COMMENT '说明',
	Param VARCHAR(10) COMMENT '预留字段',
	PRIMARY KEY(RoleID)
	);


########### StaffRole 	
DROP TABLE IF EXISTS StaffRole;
CREATE TABLE StaffRole (
	RoleID INT(11) NOT NULL COMMENT '角色编号（外键）',
	StaffID INT(11) NOT NULL COMMENT '权限编号（外键）',
	Param VARCHAR(10) COMMENT '预留字段',
	FOREIGN KEY (RoleID) REFERENCES guidocms.role (RoleID),
	FOREIGN KEY (StaffID) REFERENCES guidocms.staff (StaffID)
	);

	
########### RolePermission 
DROP TABLE IF EXISTS RolePermission;
CREATE TABLE RolePermission (
	RoleID INT(11) NOT NULL COMMENT '角色编号（外键）',
	PermissionID INT(11) NOT NULL COMMENT '权限编号（外键）',
	Description VARCHAR(80) COMMENT '说明',
	Param VARCHAR(10) COMMENT '预留字段',
	FOREIGN KEY(RoleID) REFERENCES guidocms.role (RoleID),
	FOREIGN KEY(PermissionID) REFERENCES guidocms.permission (PermissionID)
	);

		
	 