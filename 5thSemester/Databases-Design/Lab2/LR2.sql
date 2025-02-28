use `library db 3sem`;
select * from author;
Delimiter //
BEGIN
    DECLARE tValue INT;
    DECLARE pChar VARCHAR(25);

    DECLARE tCursor CURSOR FOR
        SELECT AuthorID,FirstName FROM author;
    OPEN tCursor;
    FETCH tCursor INTO tValue, pChar; 
    while tValue != 3 do
        FETCH tCursor INTO tValue, pChar;
        IF tValue = 3
			THEN 
            set pChar = 'Борис';
            select pChar;
        END IF;
    END while;
    CLOSE tCursor;
END
Delimiter /;

call L2Ex4Test();