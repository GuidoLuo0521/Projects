DROP TABLE IF EXISTS Permission;

CREATE TABLE Permission (
	PermissionID int(11) NOT NULL,
	PermissionName VARCHAR(20) NOT NULL,
	Params VARCHAR(10),
	PRIMARY KEY(PermissionID)
	);
	
		
	 