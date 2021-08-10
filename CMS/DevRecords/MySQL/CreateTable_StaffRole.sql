
DROP TABLE IF EXISTS StaffRole;

CREATE TABLE StaffRole (
	RoleID INT(11) NOT NULL COMMENT '角色编号（外键）',
	StaffID INT(11) NOT NULL COMMENT '权限编号（外键）',
	Param VARCHAR(10) COMMENT '预留字段',
	FOREIGN KEY (RoleID) REFERENCES guidocms.role (RoleID),
	FOREIGN KEY (StaffID) REFERENCES guidocms.staff (StaffID)
	);
