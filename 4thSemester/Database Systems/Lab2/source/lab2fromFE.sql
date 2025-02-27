-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema lab2
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema lab2
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `lab2` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci ;
USE `lab2` ;

-- -----------------------------------------------------
-- Table `lab2`.`author`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab2`.`author` (
  `A_id` INT NOT NULL AUTO_INCREMENT,
  ` FullName` VARCHAR(255) NULL DEFAULT NULL,
  PRIMARY KEY (`A_id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `lab2`.`debtor_info`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab2`.`debtor_info` (
  `D_id` INT NOT NULL AUTO_INCREMENT,
  `D_PassportId` INT NOT NULL,
  `D_FIO` VARCHAR(35) NULL DEFAULT NULL,
  `D_address` VARCHAR(255) NULL DEFAULT NULL,
  `D_mobilenumber` MEDIUMTEXT NULL DEFAULT NULL,
  PRIMARY KEY (`D_id`),
  UNIQUE INDEX `D_PassportId` (`D_PassportId` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `lab2`.`genres`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab2`.`genres` (
  `G_id` INT NOT NULL AUTO_INCREMENT,
  `Genre` VARCHAR(35) NULL DEFAULT NULL,
  PRIMARY KEY (`G_id`),
  UNIQUE INDEX `Genre` (`Genre` ASC) VISIBLE,
  UNIQUE INDEX `G_id_UNIQUE` (`G_id` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `lab2`.`library`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab2`.`library` (
  `B_id` INT NOT NULL AUTO_INCREMENT,
  `B_Name` VARCHAR(35) NULL DEFAULT NULL,
  `B_Count` INT NULL DEFAULT NULL,
  `B_Cost` INT NOT NULL,
  `B_Pledge` INT NOT NULL,
  `Genre` INT NULL DEFAULT NULL,
  `B_Author` INT NULL DEFAULT NULL,
  PRIMARY KEY (`B_id`),
  INDEX `Genre` (`Genre` ASC) VISIBLE,
  INDEX `B_Author` (`B_Author` ASC) VISIBLE,
  CONSTRAINT `library_ibfk_1`
    FOREIGN KEY (`Genre`)
    REFERENCES `lab2`.`genres` (`G_id`),
  CONSTRAINT `library_ibfk_2`
    FOREIGN KEY (`B_Author`)
    REFERENCES `lab2`.`author` (`A_id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `lab2`.`loans`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab2`.`loans` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `rentdate_start` DATE NOT NULL,
  `rentdate_end` DATE NOT NULL,
  `loan allowance` INT ZEROFILL NULL,
  `rentDebt` INT NULL DEFAULT NULL,
  `rentBook` INT NOT NULL,
  `forfeit` INT NOT NULL,
  `Sale` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `rentBook` (`rentBook` ASC) VISIBLE,
  CONSTRAINT `loans_ibfk_1`
    FOREIGN KEY (`rentBook`)
    REFERENCES `lab2`.`library` (`B_id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `lab2`.`debtor_list`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab2`.`debtor_list` (
  `D_id` INT NOT NULL AUTO_INCREMENT,
  `D_DebtorId` INT NULL DEFAULT NULL,
  `D_LoanId` INT NULL DEFAULT NULL,
  PRIMARY KEY (`D_id`),
  UNIQUE INDEX `D_LoanId` (`D_LoanId` ASC) VISIBLE,
  INDEX `debtor_list_ibfk_1_idx` (`D_DebtorId` ASC) VISIBLE,
  CONSTRAINT `debtor_list_ibfk_1`
    FOREIGN KEY (`D_DebtorId`)
    REFERENCES `lab2`.`debtor_info` (`D_id`),
  CONSTRAINT `debtor_list_ibfk_2`
    FOREIGN KEY (`D_LoanId`)
    REFERENCES `lab2`.`loans` (`id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `lab2`.``
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `lab2`.`` (
)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
