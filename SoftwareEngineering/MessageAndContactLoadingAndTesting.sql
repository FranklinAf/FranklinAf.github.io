--Testing person

SELECT * FROM Person

INSERT INTO Person 
VALUES ('Austin', 'Franklin', 1);
GO

INSERT INTO Person 
VALUES ('Bob', 'Johnson', 1);
GO

INSERT INTO Person 
VALUES ('Amy', 'Adams', 2);
GO

INSERT INTO Person 
VALUES ('Robot', 'Bender', 9);
GO

INSERT INTO Person 
VALUES ('Who', 'IsThis', 0);
GO

INSERT INTO Person 
VALUES ('Joe', 'Jackson', 1);
GO

INSERT INTO Person 
VALUES ('Jillian', 'Franks', 2);
GO

--Fill Contact_List
INSERT INTO Contact_List
VALUES (1, 4, 1)

INSERT INTO Contact_List
VALUES (1, 2, 0)

INSERT INTO Contact_List
VALUES (3, 2, 1)

INSERT INTO Contact_List
VALUES (3, 4, 0)

INSERT INTO Contact_List
VALUES (4, 2, 1)

--THIS FAILS because FK on person_id. person_id=187 doesn't exist.
INSERT INTO Contact_List
VALUES (187, 2, 0)

-- Get all contacts contacts
SELECT p.person_id, p.first_name, p.last_name, personContact.first_name contact_name, 
personContact.last_name contact_last_name FROM Contact_List cl
RIGHT JOIN Person p
ON p.person_id=cl.person_id 
LEFT JOIN Person personContact
ON cl.contact_id=personContact.person_id


-- Load Messages
INSERT INTO Message
VALUES (1, 'This is a test message.', GETDATE());

INSERT INTO Message
VALUES (1, 'This is a second message.', GETDATE());

INSERT INTO Message
VALUES (1, 'This message has an image!', GETDATE());

INSERT INTO Message
VALUES (3, 'Please see this earth picture.', GETDATE());

--THIS FAILS because FK on person_id. person_id=187 doesn't exist.
INSERT INTO Message
VALUES (187, 'FAIL.', GETDATE(), 3);

SELECT * FROM Message

--Load Images
INSERT INTO Image
SELECT 'test','Minnesota', * FROM OPENROWSET(BULK N'C:\lookatthis.jpg', SINGLE_BLOB) rs

INSERT INTO Image
SELECT 'photo-1453728013993-6d66e9c9123a.jpg','Milky Way', * FROM OPENROWSET(BULK N'C:\photo-1453728013993-6d66e9c9123a.jpg', SINGLE_BLOB) rs

INSERT INTO Image
SELECT 'earth.jpg','Upper Stratosphere', * FROM OPENROWSET(BULK N'C:\earth.jpg', SINGLE_BLOB) rs

INSERT INTO Image
SELECT 'space.jpg','In a Galaxy Far Far Away', * FROM OPENROWSET(BULK N'C:\space.jpg', SINGLE_BLOB) rs

SELECT * FROM Message
SELECT * FROM Image

--Link images to specific messages

INSERT INTO Message_Image
VALUES (3, 1)

INSERT INTO Message_Image
VALUES (4, 3)

--THIS FAILS because FK on image_id=15 on Image doesnt exist
INSERT INTO Message_Image
VALUES (3, 15)

--THIS FAILS because FK on message_id=15 on Message doesnt exist
INSERT INTO Message_Image
VALUES (15, 2)

--get all messages, even the ones without an image.
SELECT senderp.first_name sender_firstname, senderp.last_name sender_lastname, receiver_id, 
recp.first_name reciever_firstname, recp.last_name reciever_lastname, *
FROM Message m
LEFT JOIN Message_Image mi 
ON m.message_id=mi.message_id
LEFT JOIN Image i
ON i.image_id=mi.image_id
INNER JOIN Person senderp
ON senderp.person_id=m.sender_id
INNER JOIN Person recp
ON recp.person_id=m.receiver_id

--Save image to a file location on server as a test
USE MessageAndContact 
DECLARE @sql VARCHAR(1000);
SET @sql
    = 'BCP "SELECT image_file FROM MessageAndContact.dbo.Image where image_id=3" QUERYOUT C:\Temp\testfile.jpg -T -f "C:\Temp\Image.fmt" -S ' + @@SERVERNAME;
 
 SELECT @sql;
 
EXEC master.dbo.xp_cmdshell @sql;

EXEC xp_cmdshell 'BCP "SELECT image_file FROM MessageAndContact.dbo.Image where image_id=3" QUERYOUT "C:\Temp\testfile.jpg" -T -fC "C:\Temp\Image.fmt"'

