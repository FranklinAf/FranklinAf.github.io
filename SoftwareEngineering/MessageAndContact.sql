CREATE DATABASE MessageAndContact

USE MessageAndContact

CREATE TABLE Person (
	person_id int IDENTITY(1,1) NOT NULL,
	first_name varchar(255) NOT NULL,
	last_name varchar(255) NOT NULL,
	gender tinyint, --ISO standard 5218
	PRIMARY KEY (person_id)
);
GO

CREATE TABLE Contact_List (
	connection_id int Identity(1,1) NOT NULL,
	person_id int NOT NULL,
	contact_id int NOT NULL,
	favorite int, --The person_id who is their favorite, optional
	PRIMARY KEY (connection_id),
	FOREIGN KEY (person_id) REFERENCES Person(person_id)
);
GO

CREATE TABLE Message (
	message_id int Identity(1,1) NOT NULL,
	sender_id int NOT NULL,
	message varchar(255),
	message_timestamp datetime NOT NULL,
	PRIMARY KEY (message_id),
	FOREIGN KEY (sender_id) REFERENCES Person(person_id)
);
GO

CREATE TABLE Image (
	    image_id int IDENTITY(1,1) NOT NULL,
	    image_name VARCHAR(50) NOT NULL,
	    image_location VARCHAR(250) NOT NULL,
		image_file varbinary(max) NOT NULL, --actual image file stored as vbinary, not image as deprecated
	    PRIMARY KEY(image_id)
	);
GO
	
	--translation table between messages and images
CREATE TABLE Message_Image (
	    message_id int NOT NULL,
	    image_id int NOT NULL,
	    FOREIGN KEY (message_id) REFERENCES Message(message_id),
		FOREIGN KEY (image_id) REFERENCES Image(image_id)
	);
GO

SELECT * FROM INFORMATION_SCHEMA.COLUMNS
