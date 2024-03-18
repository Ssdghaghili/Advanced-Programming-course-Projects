#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int Default_Money = 1000;
const int Max_Money = 10000;
const int Min_Money = 0;
const int Default_Health = 100;
const int Min_Health = 0;
const int HEAVY = 0;
const int KNIFE = 1;
const int PISTOL = 2;
const int ZERO = 0;
const int ONE = 1;
const int Winner_Gift = 2700;
const int Loser_Gift = 2400;
const string Command_Err = "Wrong command!";

class Gun{
public:
    string get_name(){return name; }
    int get_price(){return price; }
    int get_damage(){return damage; }
    int get_scorers(){return scores; }
    Gun(string Name, int Price, int Damage, int Score){
        name=Name;
        price=Price;
        damage=Damage;
        scores=Score;
    }
    private:
    string name;
    int price;
    int damage;
    int scores;
};
class Player{
public:
    Player(string name , string team_type);
    string get_name(){return name; }
    string get_team_type(){return team_type; }
    string get_player_situation(){return player_situation;}
    int get_health(){return health; }
    int get_money(){return money; }
    vector<Gun> get_gun(){return Guns; }
    void change_player_situation(string situation){
        player_situation = situation; }
    void change_player_money(int player_money){
        money = player_money; }
    void change_player_health(int player_health){
        health = player_health; }
    void set_new_gun(Gun gun){
        Guns.push_back(gun); }
    bool check_gun(string name){
        bool result = true;
        for (int i=0; i < Guns.size() ;i++) {
            if (Guns[i].get_name() == name){
                result = false;
                break;
            }
        }
        return result;
    }
private:
    vector<Gun> Guns;
    string name;
    string team_type;
    string player_situation;
    int health;
    int money;
};

Player::Player(string Name , string TeamType){
    name = Name;
    team_type = TeamType;
    player_situation = "active";
    health = Default_Health;
    money = Default_Money;
    Guns.push_back(Gun("knife" , 0 , 20 , 200));
}

void Start( int* check_game_start){
    cout << "fight!" <<endl;
    *check_game_start = ONE;
}

void Add_usr(vector<Player> users){
    string name;
    string type;
    while (true) {
        cin >> name >> type;
        Player input_player(name,type);
        users.push_back(input_player);
        cout<<"ok"<<endl;
        break;
    }
}
//int Find_gun(vector<Player> users , string name){
//    for (int i = 0; i < users.size(); i++) {
//        if (users[i].get_name() == name){
//
//
//        }
//    }
//    cout <<"weapon not available!";
//    abort();
//    return 0;
//}

int Find_player_name(vector<Player> users , string name){
    for (int i = 0; i < users.size(); i++) {
        if (users[i].get_name() == name){
            return i;
        }
    }
    cout <<"user not available" << endl;
    abort();
    return 0;
}
void Get_money(vector<Player> users){
    string name;
    cin >> name;
    int number = Find_player_name(users, name);
    cout << users[number].get_money() << endl;
}
void Get_health(vector<Player> users){
    string name;
    cin >> name;
    int number = Find_player_name(users, name);
    cout << users[number].get_health()<< endl;
}
void Go_afk_for_palyer(vector<Player> users){
    string name;
    cin >> name;
    int number = Find_player_name(users, name);
    users[number].change_player_situation("inactive");
}
void Go_atk_for_palyer(vector<Player> users){
    string name;
    cin >> name;
    int number = Find_player_name(users, name);
    users[number].change_player_situation("active");
}
int check_money(int money){
    if (money > Max_Money) {
        money = Max_Money;
        return money;
    }
    else if (money < Min_Money){
        money = Min_Money;
        return money;
    }
    return money;
}
int check_health(int health){
    if (health < Min_Health ) {
        health = Min_Health;
        return health;
    }
    return health;
}
void do_attack_operation(vector<Player> users, vector<Gun> gun_type ,int number1 , int number2 , string weapen){
    int correct_atacer_player_money = users[number1].get_money();
    int new_money;
    if (weapen == "heavy") {
        correct_atacer_player_money = correct_atacer_player_money + gun_type[HEAVY].get_scorers();
        new_money = check_money(correct_atacer_player_money);
        users[number1].change_player_money(new_money);
    }
    else if (weapen == "pistol") {
        correct_atacer_player_money = correct_atacer_player_money + gun_type[PISTOL].get_scorers();
        new_money = check_money(correct_atacer_player_money);
        users[number1].change_player_money(new_money);
    }
    else if (weapen == "knife") {
        correct_atacer_player_money = correct_atacer_player_money + gun_type[KNIFE].get_scorers();
        new_money = check_money(correct_atacer_player_money);
        users[number1].change_player_money(new_money);
    }
    int correct_ataced_player_health = users[number2].get_health();
    int new_health;
    if (weapen == "heavy") {
        correct_ataced_player_health = correct_ataced_player_health - gun_type[HEAVY].get_damage();
        new_health = check_health(correct_ataced_player_health);
        users[number2].change_player_health(new_health);
    }
    else if (weapen == "pistol") {
        correct_ataced_player_health = correct_ataced_player_health - gun_type[PISTOL].get_damage();
        new_health = check_health(correct_ataced_player_health);
        users[number2].change_player_health(new_health);
    }
    else if (weapen == "knife") {
        correct_ataced_player_health = correct_ataced_player_health - gun_type[KNIFE].get_damage();
        new_health = check_health(correct_ataced_player_health);
        users[number2].change_player_health(new_health);
    }
}

void is_can_attack_to_player(vector<Player> users, vector<Gun> gun_type ,int number1 , int number2 , string weapen , int* check_game_start){
    if (users[number1].get_player_situation() == "inactive" || users[number2].get_player_situation() == "inactive") {
        cout << "user not available" << endl;
    }
    else if (users[number1].get_team_type() == users[number2].get_team_type()){
        cout << "you can't shoot this player" << endl;
    }
    else if (users[number1].get_health() == Min_Health){
        cout << "attacker is dead" << endl;
    }
    else if (users[number2].get_health() == Min_Health){
        cout << "attacked is dead" << endl;
    }
    else if(*check_game_start == ONE){
        cout << "The game hasn't started yet" <<endl;
    }
    else if(*check_game_start == ONE){
        cout << "you can't buy weapons anymore" <<endl;
    }
    else{
        cout << "nice shot" << endl;
        do_attack_operation(users,gun_type,number1,number2,weapen);
    }
}
void Shoot(vector<Player> users , vector<Gun> gun_type , int* check_game_start){
    string attacker;
    string attacked;
    string weapen_type;
    cin >> attacker >> attacked >> weapen_type;
    int attacker_number = Find_player_name(users, attacker);
    int attacked_number = Find_player_name(users, attacked);
    is_can_attack_to_player(users,gun_type,attacker_number,attacked_number,weapen_type , check_game_start);
}

void buying_weapon(vector<Player> users , vector<Gun> gun_type , int player_num , string weapen_name){
    int correct_atacer_player_money = users[player_num].get_money();
    int new_money;
    if (weapen_name == "heavy") {
        users[player_num].set_new_gun(Gun("heavy" , 3000 , 45 , 100));
        correct_atacer_player_money = correct_atacer_player_money - gun_type[HEAVY].get_price();
        new_money = check_money(correct_atacer_player_money);
        users[player_num].change_player_money(new_money);
    }
    else if (weapen_name == "pistol"){
        users[player_num].set_new_gun(Gun("pistol" , 400 , 20 , 200));
        correct_atacer_player_money = correct_atacer_player_money - gun_type[PISTOL].get_price();
        new_money = check_money(correct_atacer_player_money);
        users[player_num].change_player_money(new_money);
    }
}
void is_can_buy_weapen(vector<Player> users , vector<Gun> gun_type ,int player_num , string weapen_name , int* check_game_start){
    if (users[player_num].get_player_situation() == "inactive") {
        cout << "weapon not available" << endl;
    }
    else if (weapen_name == "heavy") {
        if (users[player_num].get_money() >= gun_type[HEAVY].get_price())
            cout << "insufficient money" << endl;
    }
    else if (weapen_name == "pistol") {
        if (users[player_num].get_money() >= gun_type[PISTOL].get_price())
            cout << "insufficient money" << endl;
    }
    else if (weapen_name == "knife") {
        cout << "you already have this weapon" << endl;
    }
    else if (weapen_name!="heavy" || weapen_name!="pistol" || weapen_name!= "knife"){
        cout << "weapon not available" << endl;
    }
    else if (!users[player_num].check_gun(weapen_name)){
        cout << "you already have this weapon" <<endl;
    }
    else if(*check_game_start == ONE){
        cout << "you can't buy weapons anymore" <<endl;
    }
    
    else{
        cout << "weapon bought successfully" << endl;
        buying_weapon(users,gun_type,player_num,weapen_name);
    }
}
void Buy_weapen(vector<Player> users , vector<Gun> gun_type , int* check_game_start){
    string user_name;
    string weaoen_name;
    cin >> user_name >> weaoen_name;
    int player_number = Find_player_name(users, user_name);
    is_can_buy_weapen(users,gun_type,player_number,weaoen_name,check_game_start);
}
void show_score_board(vector<Player> users){
    
}
void get_commands(vector<Player> users , vector<Gun> gun_type , int num_of_command , string command , int *check_game_start){
   
    for (int i = 0; i < num_of_command; i++){
        
        if (command == "start"){
            Start(check_game_start);
            continue;
        }
        else if (command == "get-money"){
             Get_money(users);
            continue;
        }
        else if (command == "get-health"){
            Get_health(users);
            continue;
        }
        else if (command == "go-afk"){
            Go_afk_for_palyer(users);
            continue;
        }
        else if (command == "go-atk"){
            Go_atk_for_palyer(users);
            continue;
        }
        else if (command == "shoot"){
            Shoot(users , gun_type , check_game_start);
            continue;
        }
        else if (command == "buy"){
            Buy_weapen(users,gun_type,check_game_start);
            continue;
        }
        else if (command == "score-board"){
            show_score_board(users);
            continue;
        }
        else{
            cerr << Command_Err<< endl;
            continue;
        }
    }
}
void Rounds(vector<Player> users , vector<Gun> gun_type , int* check_game_start){
    int num_of_command;
    string input;
    string command;
    while (true) {
        cin >>input;
        if (input == "add-user"){
            Add_usr(users);
        }
        else{
            break;
        }
    }
    cin >> command;
    cin >> num_of_command;
    get_commands(users,gun_type,num_of_command,command,check_game_start);
}
void give_winner_gift(vector<Player> users , string winner_team){
    if (winner_team == "counter-terrorist") {
        for (int i=0 ; i < users.size(); i++) {
            if (users[i].get_player_situation() == "counter-terrorist"){
                int correct_atacer_player_money = users[i].get_money();
                int new_money;
                correct_atacer_player_money = correct_atacer_player_money + Winner_Gift;
                new_money = check_money(correct_atacer_player_money);
                users[i].change_player_money(new_money);
            }
            else{
                int correct_atacer_player_money = users[i].get_money();
                int new_money;
                correct_atacer_player_money = correct_atacer_player_money + Winner_Gift;
                new_money = check_money(correct_atacer_player_money);
                users[i].change_player_money(new_money);
            }
        }
    }
    else{
        for (int i=0 ; i < users.size(); i++) {
            if (users[i].get_player_situation() == "counter-terrorist"){
                int correct_atacer_player_money = users[i].get_money();
                int new_money;
                correct_atacer_player_money = correct_atacer_player_money + Loser_Gift;
                new_money = check_money(correct_atacer_player_money);
                users[i].change_player_money(new_money);
            }
            else{
                int correct_atacer_player_money = users[i].get_money();
                int new_money;
                correct_atacer_player_money = correct_atacer_player_money + Winner_Gift;
                new_money = check_money(correct_atacer_player_money);
                users[i].change_player_money(new_money);
            }
        }
    }
}
void check_winner_team(vector<Player> users){
    string winner_team;
    for(int i = 0 ; i < users.size() ; i++){
        if(users[i].get_player_situation() == "counter-terrorist" && users[i].get_health() > Min_Health){
            cout << "counter-terrorist won" << endl;
            winner_team = "counter-terrorist";
            give_winner_gift(users , winner_team);
        }
        else{
            cout << "terrorist won" << endl;
            winner_team = "terrorist";
            give_winner_gift(users , winner_team);
        }
    }
}
int main() {
    int check_game_start = ZERO;
    Gun heavy("heavy" , 3000 , 45 , 100);
    Gun knife("knife" , 0 , 35 , 500);
    Gun pistol("pistol" , 400 , 20 , 200);
    vector<Gun> gun_type;
    gun_type.push_back(heavy); gun_type.push_back(knife); gun_type.push_back(pistol);
    vector<Player> users;
    int num_of_round;
    cin >> num_of_round;
    for (int i = 0; i < num_of_round; i++) {
        Rounds(users , gun_type , &check_game_start);
        check_winner_team(users);
    }
    return 0;
}
