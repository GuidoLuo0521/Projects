
DROP TABLE IF EXISTS RolePermission;

CREATE TABLE RolePermission (
	RoleID INT(11) NOT NULL COMMENT '角色编号（外键）',
	PermissionID INT(11) NOT NULL COMMENT '权限编号（外键）',
	Description VARCHAR(80) COMMENT '说明',
	Param VARCHAR(10) COMMENT '预留字段',
	FOREIGN KEY(RoleID) REFERENCES guidocms.role (RoleID),
	FOREIGN KEY(PermissionID) REFERENCES guidocms.permission (PermissionID)
	);

