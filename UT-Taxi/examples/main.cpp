#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "handlers.hpp"
#include "my_server.hpp"

using namespace std;

int main(int argc, char *argv[]){
    string line;
    int id = 1;
    string error_massage;
    
    try{
        MyServer server(argc > 1 ? atoi(argv[1]) : 8080);
        Utaxy* utaxi = new Utaxy();
        utaxi->read_locations(argv[1]);
        server.get("/signup", new ShowPage("static/signupcss.html"));
        server.post("/signup", new SignupHandler(utaxi,error_massage));
        server.get("/req_trip", new ShowPage("static/requestcss.html"));
        server.post("/get_trip",new RecTripHandler(utaxi,id,error_massage));
        server.get("/cancel_trip", new ShowPage("static/cancel.html"));
        server.post("/cancel_trip", new CancleTripHandler(utaxi,id,error_massage));
        server.get("/show_trips", new ShowPage("static/showtrip.html"));
        // server.post("/show_trips", new SignupHandler());    //--> don't forget it.
        server.get("/show_error", new ExceptHandler(error_massage));
        server.get("/home.png", new ShowImage("static/home.png"));
        server.get("/", new ShowPage("static/home.html"));
        server.run();
    }
    catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }

    return 0;
}