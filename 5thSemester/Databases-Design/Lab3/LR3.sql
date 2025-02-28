DELIMITER //
CREATE TRIGGER DiscountTrigger
AFTER INSERT ON debts
FOR EACH ROW
BEGIN
    DECLARE Sumcount INT;
    DECLARE IDMAX INT;

    SELECT COUNT(*) INTO Sumcount FROM debts WHERE VisitorID = NEW.VisitorID;
    SET Sumcount = FLOOR(Sumcount / 10);

    SELECT MAX(DiscountTypeID) INTO IDMAX FROM discounttype;

    IF Sumcount >= IDMAX THEN
        update visitor set DiscountTypeID = IDMAX where visitor.VisitorID = new.VisitorID;
    ELSE
        update visitor set DiscountTypeID = Sumcount where visitor.VisitorID = new.VisitorID;
    END IF;
END;
//
DELIMITER ;

DELIMITER //

CREATE TRIGGER PaymentTrigger
AFTER INSERT ON debts
FOR EACH ROW
BEGIN
    DECLARE PaymentValue DOUBLE;
    DECLARE localBookID INT;

    SELECT BookID INTO localBookID FROM bookobjectplacement WHERE BookPlacementID = NEW.BookID;
    SELECT (Cost + Pladge) INTO PaymentValue FROM valueclass WHERE ValueClassID = (SELECT `Value classID` FROM book WHERE BookID = localBookID);
    INSERT INTO paymentrequest (PaymentMethod, Payment) VALUES (0, PaymentValue);
END;
//

DELIMITER ;

drop trigger PaymentTrigger;