
-- WildCards are %(0 or above 0 occurrence) and _(sigle occurrence)   not *, ?;
-- Sigle quote to bolder character string, double sigle quotes to repesent one sigle quote in character string.

CREATE DATABASE Books;
SELECT * FROM tablename;
-- SELECT id,

CREATE TABLE Books
(
Title CHAR(60),
ISBN CHAR(13),
Publisher_Id CHAR(6),
Price DECIMAL(10,2)
);


INSERT INTO Books VALUES ("A Guide to the SQL Standard", "0-201-96426-0", "0201", 47.95);
INSERT INTO Books VALUES ("A Pattern Language: Towns, Buildings, Construction", "0-19-501919-9", "019", 65.00);


