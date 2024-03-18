#include"handlers.hpp"


using namespace std;

const int CAN_TRIP = 0;
const int CANT_TRIP = 1;
const int CAN_ACCEPT = 0;
const int CANT_ACCEPT = 1;
const double DEFAULT_PRICE = 10000;
const double ADDED_HARRY_COEFFICIENT = 1.2;
const string TRIP_DELETED = "deleted";
const string TRIP_WAITING = "waiting";
const string TRIP_FINISHED = "finished";
const string TRIP_TRAWELING = "traveling";

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

vector<string> Utaxy::split_by_commas(string str) {
	vector<string> result;
	int start_pos = 0;
	while (start_pos < str.length()) {
		int comma_pos = str.find(",", start_pos);
		if (comma_pos == string::npos) {
			result.push_back(str.substr(start_pos));
			break;
		}
		result.push_back(str.substr(start_pos, comma_pos - start_pos));
		start_pos = comma_pos + 1;
	}
	return result;
}

vector<string> Utaxy::split_by_space(string str) {
	vector<string> result;
	int start_pos = 0;
	while (start_pos < str.length()) {
		int comma_pos = str.find(" ", start_pos);
		if (comma_pos == string::npos) {
			result.push_back(str.substr(start_pos));
			break;
		}
		result.push_back(str.substr(start_pos, comma_pos - start_pos));
		start_pos = comma_pos + 1;
	}
	return result;
}

void Utaxy::read_locations(string file_name){
    ifstream my_file(file_name);
    string line;
    getline(my_file, line);
    while (getline(my_file, line)){
        vector<string> loc_info = split_by_commas(line);
        Location *new_loc = new Location(loc_info[0], stod(loc_info[1]), stod(loc_info[2]), stod(loc_info[3]));
        location_list.push_back(new_loc);
    }
}

int Utaxy::find_user(string name){
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->get_name() == name)
            return i;
    }
    throw runtime_error("Bad Request");
}

void Utaxy::is_passenger(string name){
    for (int i = 0; i < passengers.size(); i++) {
        if (passengers[i]->get_name() != name){
            throw runtime_error("Permission Denied.\n");
        }
    }
}

void Utaxy::is_driver(string name){
    for (int i = 0; i < drivers.size(); i++) {
        if (drivers[i]->get_name() != name){
            throw runtime_error("Permission Denied.\n");
        }
    }
    
}

void Utaxy::check_user(string user_name){
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->get_name() == user_name){
            throw runtime_error("Bad Request.\n");
        }
    }
}

void Utaxy::check_location(string origin, string destination){
    for (int i = 0; i < location_list.size(); i++) {
        if (users[i]->get_name() != origin || users[i]->get_name() != destination){
            throw runtime_error("Not Found.\n");
        }
        else
            continue;
    }
}

void Utaxy::add_driver_member(string driver_name){
        Driver *new_dri = new Driver(driver_name);
        check_user(new_dri->get_name());
        drivers.push_back(new_dri);
        users.push_back(new_dri);
}

void Utaxy::add_passenger_member(string passenger_name){
    Passenger *new_pass = new Passenger(passenger_name);
    check_user(new_pass->get_name());
    passengers.push_back(new_pass);
    users.push_back(new_pass);
    //cout << "OK" << endl;
}

void Utaxy::check_trip(string name){
    int user_name = find_user(name);
    is_passenger(name);
    if(users[user_name]->is_tarveling == CAN_TRIP){
        users[user_name]->change_to_cant_trip();
    }
    else
        throw runtime_error("Bad Request.\n");
}

void Utaxy::add_trip(string name, string origin, string destination ,int &id, double price){
        Trip *new_trip = new Trip(name, origin, destination, id, price);
        check_trip(name);
        trips.push_back(new_trip);
        cout << id << endl;
        id++ ;
}

void Utaxy::show_selected_trip(int id){
    for (int i = 0; i < trips.size(); i++){
        if (trips[i]->get_situation() != TRIP_DELETED){
            if (trips[i]->get_id() == id){
                cout<<trips[i]->get_id()<<' '<<trips[i]->get_name()<<' '<<trips[i]->get_origin()
                    <<' '<<trips[i]->get_destination()<<' '<<std::fixed<<std::setprecision(2)<<trips[i]->get_price()
                    <<' '<<trips[i]->get_situation()<<endl;
            }
            else{
                throw runtime_error("Not Found.\n");
            }
        }
        else{
                throw runtime_error("Not Found.\n");

        }
    }
}

void Utaxy::show_all_trips(){
    if (trips.size() > 0){
        for (int i = 0; i < trips.size(); i++){
            cout<<trips[i]->get_id()<<' '<<trips[i]->get_name()<<' '<<trips[i]->get_origin()
                <<' '<<trips[i]->get_destination()<<' '<<std::fixed<<std::setprecision(2)<<trips[i]->get_price()
                <<' '<<trips[i]->get_situation()<<endl;
        }
    }
    else{
        cout<<"EMPTY"<<endl;
    }
}

int Utaxy::find_id(int id){
    for (int i = 0; i < trips.size(); i++) {
            if (trips[i]->get_id() == id)
                return i;
        }
        throw runtime_error("id does not exist.\n");
}

void Utaxy::delete_selected_trip(string name, int id){
    int _id = find_id(id);
    int user_name = find_user(name);
    if(trips[_id]->get_name()==name){
        if (trips[_id]->get_situation() == TRIP_WAITING){
            trips[_id]->change_situation(TRIP_DELETED);
            users[user_name]->change_to_can_trip();
        }
        else{
            throw runtime_error("Bad Request.\n");

        }
    }
    else{
        throw runtime_error("Permission Denied.\n");
    }
}

void Utaxy::accept_trip(string name, int id){
    int _id = find_id(id);
    int user_name = find_user(name);
    if(users[user_name]->can_accept == CAN_ACCEPT){
        trips[_id]->change_situation(TRIP_TRAWELING);
        users[user_name]->change_to_cant_accept();
    }
    else{
        throw runtime_error("Bad Request\n");
    }
}

void Utaxy::finish_trip(string name, int id){
    int _id = find_id(id);
    int user_name = find_user(name);
    trips[_id]->change_situation(TRIP_FINISHED);
    users[user_name]->change_to_can_accept();
}

int Utaxy::find_loc(string loc_name){
    for (int i = 0; i < location_list.size(); i++) {
        if (users[i]->get_name() == loc_name)
            return i;
    }
    throw runtime_error("Not Found\n");
}

double Utaxy::trip_distant(string origin, string destinatoin){
    int origin_name = find_loc(origin);
    int dest_name = find_loc(destinatoin);
    double distance = 110*(sqrt(pow((location_list[dest_name]->get_longitude()-location_list[origin_name]->get_longitude()),2)+
    pow((location_list[dest_name]->get_latitude()-location_list[origin_name]->get_latitude()),2)));
    return distance;
}

double Utaxy::calculate_trip_cost(string name, string origin, string destination, int id){
    int origin_name = find_loc(origin);
    int dest_name = find_loc(destination);
    double dist = trip_distant(origin, destination);
    double price = (dist * DEFAULT_PRICE * (location_list[dest_name]->get_traffic()+location_list[origin_name]->get_traffic()));
    return price;
}

double Utaxy::calculate_trip_cost_with_hurry(string name, string origin, string destination, int id){
    int origin_name = find_loc(origin);
    int dest_name = find_loc(destination);
    double dist = trip_distant(origin, destination);
    double price = (dist * DEFAULT_PRICE * ADDED_HARRY_COEFFICIENT * (location_list[dest_name]->get_traffic()
    +location_list[origin_name]->get_traffic()));
    return price;
}

void Utaxy::show_trips_sorted_by_const(){
    if (trips.size() > 0){
        vector<double>pp;
        vector<Trip*>final;
        for (int i= 0; i<trips.size();i++){
            double o = trips[i]->get_price();
            pp.push_back(o);
        }
        sort(pp.begin(), pp.end(), greater<double>());    
        for (int i= 0; i<pp.size();i++){
            for (int j = 0; j < trips.size(); i++){
                if(pp[i]==trips[j]->get_price()){
                    final.push_back(trips[i]);
                } 
            }
        }
        for (int i = 0; i < final.size(); i++){
            cout<<final[i]->get_id()<<' '<<final[i]->get_name()<<' '<<final[i]->get_origin()
                <<' '<<final[i]->get_destination()<<' '<<std::fixed<<std::setprecision(2)<<final[i]->get_price()
                <<' '<<final[i]->get_situation()<<endl;
        }
    }
    else{
        cout<<"EMPTY"<<endl;
    }
}

RecTripHandler::RecTripHandler(Utaxy *utaxi,int &id,string &error_massage):utaxi(utaxi),id(id),error_massage(error_massage){};

CancleTripHandler::CancleTripHandler(Utaxy *utaxi,int &id,string &error_massage):utaxi(utaxi),id(id),error_massage(error_massage){};

SignupHandler::SignupHandler(Utaxy *utaxi,string &error_message):utaxi(utaxi),error_massage(error_massage){};

ExceptHandler::ExceptHandler(std::string &error_massage) : error_massage(error_massage) {}
Response *ExceptHandler::callback(Request *req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body +="<style>h1{background-color: rgb(37, 40, 15);color:  White ;} body {background-color: rgb(0, 0, 0);}</style>;";
  body += "<h1>";
  body += error_massage;
  body += "</h1>";
  body += "<a href=\"/\">Back</style></a>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *SignupHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string kind= req->getBodyParam("kind");
    try{
    if(kind == "driver"){
        utaxi->add_driver_member(username);
        Response *res = Response::redirect("/");
        return res;
    }
    else if(kind == "passenger"){
        utaxi->add_passenger_member(username);
        Response *res = Response::redirect("/");
        return res;
    }
    else
        throw Server::Exception("Bad Request");
    }
    catch (runtime_error & e) {
    error_massage=e.what();
    Response *res = Response::redirect("/");
    }
}

Response *RecTripHandler::callback(Request *req){
    string username = req->getBodyParam("username");
    string origin= req->getBodyParam("origin");
    string destination = req->getBodyParam("destination");
    string hurry= req->getBodyParam("hurry");
    try{
        utaxi->check_user(username);
        utaxi->check_location(origin,destination);
        double price = utaxi->calculate_trip_cost_with_hurry(username, origin, destination, id);
        utaxi->add_trip(username, origin, destination, id, price);
    }
    catch (runtime_error & e) {
    error_massage=e.what();
    Response *res = Response::redirect("/");
    }
}

Response *CancleTripHandler::callback(Request *req){
    string username = req->getBodyParam("username");
    string trip_id= req->getBodyParam("trip_id");
    try{
        utaxi->delete_selected_trip(username, id);
    }
    catch (runtime_error & e) {
    error_massage=e.what();
    Response *res = Response::redirect("/");
    }
}