/*
ALTER USER 'root'@'localhost' IDENTIFIED BY 'Pass';

drop database lab2;

truncate table author;

truncate table debtor_info;

truncate table debtor_list;

truncate table genres;

truncate table library;

truncate table loans;
*/
use lab2;

INSERT INTO `lab2`.`author` (`A_id`, `A_FullName`) VALUES (1, 'Armando Lucas Correa');
INSERT INTO `lab2`.`author` (`A_id`, `A_FullName`) VALUES (2, 'Jess Kidd');
INSERT INTO `lab2`.`author` (`A_id`, `A_FullName`) VALUES (3, 'Martha McPhee');
INSERT INTO `lab2`.`author` (`A_id`, `A_FullName`) VALUES (4, 'Megan Miranda');
INSERT INTO `lab2`.`author` (`A_id`, `A_FullName`) VALUES (5, 'Helen Phillips');
INSERT INTO `lab2`.`author` (`A_id`, `A_FullName`) VALUES (6, 'Arturio Barebuh');
INSERT INTO `lab2`.`author` (`A_id`, `A_FullName`) VALUES (7, 'Stephen King');

INSERT INTO `lab2`.`debtor_info` (`D_id`, `D_PassportId`, `D_FIO`, `D_address`, `D_mobilenumber`) VALUES (1, 1234899, 'Where is BOB', 'lovestreet 15', '3804861');
INSERT INTO `lab2`.`debtor_info` (`D_id`, `D_PassportId`, `D_FIO`, `D_address`, `D_mobilenumber`) VALUES (2, 2294861, 'Tod MuckTod', 'White House, 11', '1513135');

INSERT INTO `lab2`.`genres` (`G_id`, `Genre`) VALUES (1, 'Horror');
INSERT INTO `lab2`.`genres` (`G_id`, `Genre`) VALUES (2, 'Action');
INSERT INTO `lab2`.`genres` (`G_id`, `Genre`) VALUES (3, 'Adventure');
INSERT INTO `lab2`.`genres` (`G_id`, `Genre`) VALUES (4, 'Comedy');
INSERT INTO `lab2`.`genres` (`G_id`, `Genre`) VALUES (5, 'Crime and mystery');
INSERT INTO `lab2`.`genres` (`G_id`, `Genre`) VALUES (6, 'Fantasy');
INSERT INTO `lab2`.`genres` (`G_id`, `Genre`) VALUES (8, 'LoveCraft');

INSERT INTO `lab2`.`library` (`B_id`, `B_Name`, `B_Count`, `B_Cost`, `B_Pledge`, `Genre`, `B_Author`) VALUES (1, 'Alice: Madness Returns', 7, 500, 2500, 3, 5);
INSERT INTO `lab2`.`library` (`B_id`, `B_Name`, `B_Count`, `B_Cost`, `B_Pledge`, `Genre`, `B_Author`) VALUES (2, 'Carrie', 10, 200, 1500, 1, 7);
INSERT INTO `lab2`.`library` (`B_id`, `B_Name`, `B_Count`, `B_Cost`, `B_Pledge`, `Genre`, `B_Author`) VALUES (3, 'Rage', 14, 250, 3000, 1, 7);
INSERT INTO `lab2`.`library` (`B_id`, `B_Name`, `B_Count`, `B_Cost`, `B_Pledge`, `Genre`, `B_Author`) VALUES (4, 'It', 2, 700, 1500, 1, 7);
INSERT INTO `lab2`.`library` (`B_id`, `B_Name`, `B_Count`, `B_Cost`, `B_Pledge`, `Genre`, `B_Author`) VALUES (5, 'Fairy Tale', 12, 600, 5000, 1, 7);

INSERT INTO `lab2`.`loans` (`id`, `rentdate_start`, `rentdate_end`, `loan_allowance`, `rentDebt`, `rentBook`, `forfeit`, `Sale`) VALUES (2, '2000-04-17', '2002-08-20', 1000, 1500, 1, 1500, null);

INSERT INTO `lab2`.`debtor_list` (`D_debtorId`, `D_LoanId`) VALUES (1, 1);

