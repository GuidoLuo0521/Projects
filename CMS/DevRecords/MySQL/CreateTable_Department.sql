
DROP TABLE IF EXISTS Department;

CREATE TABLE Department (
	DepartmntID INT(11) NOT NULL COMMENT '部门编号（主键）',
	DepartmentName VARCHAR(30) NOT NULL COMMENT '部门名称',
	Description VARCHAR(80) COMMENT '说明',
	Param VARCHAR(10) COMMENT '预留字段',
	PRIMARY KEY(DepartmntID)
	);
