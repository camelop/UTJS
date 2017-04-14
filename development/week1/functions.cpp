//return ID
int Login(string userName, string passWord)

//return ID
int RegisterUser(User newUser)

void Logout()

class User {
	int id;
	string userName, passWord;
};

bool DeleteUser(int id)

bool CreateUser()

bool ModifyUser()

class Train {

};

Train ViewTrainInfo(int id)

bool DeleteTrain()

bool ModifyUser()

bool AddLog(string)

class Ticket {
	int trainId, num;
	Date date;
	Station s, t;
};

list<Ticket> QueryTicket(Station s, Station t, Date date, int typeOfTrain, int trainId, bool onSale)

bool PurchaseTicket(string id, Ticket)
