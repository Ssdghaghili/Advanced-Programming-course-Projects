#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include<iomanip> 
#include <sstream>
#include <stdexcept>
#include <fstream>

class Location{
public:
    Location(std::string location_name , double latitude, double longitude, double traffic);
    double get_latitude(){return latitude; }
    double get_longitude(){return longitude; }
    double get_traffic(){return traffic; }
private:
    std::string location_name;
    double latitude;
    double longitude;
    double traffic;
};

class Person{
public:
    Person(std::string name);
    std::string get_name(){return name; }
    void change_to_cant_trip();
    void change_to_can_trip();
    void change_to_can_accept();
    void change_to_cant_accept();
    int is_tarveling;
    int can_accept;
protected:
    std::string name;
};

class Driver : public Person{
public:
    Driver(std::string name);
private:
};

class Passenger : public Person{
public:
    Passenger(std::string name);
private:
};

class Trip{
public:
    Trip(std::string name, std::string origin, std::string destination, int id, double price);
    std::string get_name(){return name; }
    std::string get_destination(){return destination; }
    std::string get_situation(){return situation; }
    std::string get_origin(){return origin; }
    double get_price(){return price; }
    void set_price(double new_price);
    void change_situation(std::string new_situation);
    int get_finesh_situ(){return is_finished; }
    int get_accepet_situ(){return is_accepted; }
    int get_id(){return id; }
protected:
    int id;
    int is_finished;
    int is_accepted;
    double price;
    std::string name;
    std::string origin;
    std::string destination;
    std::string situation;
};

class Utaxy{
public:
    std::vector<Driver*> get_drivers(){return drivers; }
    std::vector<Passenger*> get_passengers(){return passengers; }
    std::vector<Trip*> get_trips(){return trips; }
    std::vector<std::string> split_by_space(std::string str);
    std::vector<std::string> split_by_commas(std::string str);
    double calculate_trip_cost(std::string name, std::string origin, std::string destination, int id);
    double calculate_trip_cost_with_hurry(std::string name, std::string origin, std::string destination, int id);
    double trip_distant(std::string orgin, std::string destination);
    void read_locations(std::string file_name);
    void add_driver_member(std::string driver_name);
    void add_passenger_member(std::string passenger_name);
    void add_trip(std::string name, std::string origin, std::string destination, int &id, double price);
    void check_user(std::string user_name);
    void check_location(std::string origin , std::string destination);
    void show_selected_trip(int id);
    void show_all_trips();
    void show_trips_sorted_by_const();
    void check_trip(std::string name);
    void delete_selected_trip(std::string name, int id);
    void accept_trip(std::string name, int id);
    void finish_trip(std::string name, int id);
    void is_passenger(std::string name);
    void is_driver(std::string name);
    int find_user(std::string name);
    int find_id(int id);
    int find_loc(std::string loc_name);
    int print_trip_id();
private:
    std::vector<Driver*> drivers;
    std::vector<Passenger*> passengers;
    std::vector<Person*> users;
    std::vector<Trip*> trips;
    std::vector<Location*> location_list;
};

class ExceptHandler : public RequestHandler
{
public:
  ExceptHandler(std::string &error_massage);
  Response *callback(Request *);

private:
  std::string &error_massage;
};

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
	SignupHandler(Utaxy *_utaxi, std::string &_error_massage);
    Response *callback(Request *);
private:
    Utaxy *utaxi;
    std::string &error_massage;
};


class CancleTripHandler : public RequestHandler {
public:
    CancleTripHandler(Utaxy *_utaxi, int &_id, std::string &_error_massage);
    Response *callback(Request *);
private:
    Utaxy *utaxi;
    int &id;
    std::string &error_massage;
};

class RecTripHandler : public RequestHandler {
public:
    RecTripHandler(Utaxy *_utaxi, int &_id, std::string &_error_massage);
    Response *callback(Request *);
private:
    Utaxy *utaxi;
    int &id;
    std::string &error_massage;
};

#endif