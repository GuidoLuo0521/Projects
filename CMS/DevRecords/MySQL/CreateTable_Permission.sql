DROP TABLE IF EXISTS Permission;

CREATE TABLE Permission (
	PermissionID int(11) NOT NULL COMMENT '权限编号（主键）',
	PermissionName VARCHAR(20) NOT NULL COMMENT '权限名称',
	Param VARCHAR(10) COMMENT '预留字段',
	PRIMARY KEY(PermissionID)
	);
	
		
	 