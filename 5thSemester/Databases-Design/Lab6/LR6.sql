CREATE USER 'TestUser3`@`localhost' IDENTIFIED BY '123456789';

CREATE USER 'TestUser4`@`localhost';
SET PASSWORD FOR 'TestUser4'@'localhost' = '123456789';
GRANT SELECT, INSERT ON `library db 3sem`.author TO 'TestUser4'@'localhost';
REVOKE SELECT ON your_database.your_table FROM 'user'@'localhost';
drop user 'TestUser4`@`localhost';
drop user 'TestUser3`@`localhost';