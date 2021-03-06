CREATE TABLE Owner(
	OwnerID		Integer,
	FirstName	char(50),
	LastName	char(50),
	StreetAddr	char(100),
	City		char(50),
	ZipCode		Integer,
	Primary Key(OwnerID)
);

CREATE TABLE Building(
	BuildingID	Integer,
	Location	char(200),
	Rooms		Integer,
	Auditoriums	Integer,
	OwnID		Integer,
	Primary Key(BuildingID),
	Foreign Key(OwnID) References Owner(OwnerID)
);

CREATE TABLE Department(
	DepartmentID	Integer,
	HeadofDep	char(200),
	NumofFaculty	Integer,
	MinGPA		Decimal(3,2),
	BuildID		Integer,
	Primary Key(DeparmentID),
	Foreign Key(BuildID) References Building(BuildingID)
)

CREATE TABLE TeachingA(
	TAID		Integer,
	Major		char(100),
	FirstName	char(50),
	LastName	char(50),
	Primary Key(TAID)
)

CREATE TABLE Office(
	OfficeID	Integer,
	BuildID		Integer,
	Location	char(200),
	TANum		Integer,
	Foreign Key(BuildID) References Building(BuildingID),
	Foreign Key(TANum) References TeachingA(TAID),
	Primary Key(BuildID, OfficeID)
)

CREATE TABLE Accessories(
	AccID		Integer,
	Usage		char(200),
	Price		float(10),
	Quantity	Integer,
	Primary Key(AccID)
)

CREATE TABLE OfficeAccessories(
	OffAcc		Integer,
	AccessID	Integer,
	OffID		Integer,
	Foreign Key(AccessID) References Accessories(AccID),
	Foreign Key(OffID) References Office(OfficeID),
	Primary Key(OffAcc)
)
