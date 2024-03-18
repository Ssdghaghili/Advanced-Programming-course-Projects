#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Time {
    int hours;
    int minutes;
};
struct Translator{
    string name;
    Time start_free_time;
    Time finish_free_time;
    vector<string> languages;
};
struct Event{
    string event_name;
    Time start_event_time;
    Time finish_event_time;
    vector<string> languages_needed;
};
struct Conference{
    string event_name;
    string language_needed;
    string translator_name;
};

vector<string> split_by_space(string str){
    vector<string> result;
    int start_pos = 0;
    while (start_pos < str.length()) {
        int space_pos = str.find(" ", start_pos);
        if (space_pos == string::npos) {
            result.push_back(str.substr(start_pos));
            break;
        }
        result.push_back(str.substr(start_pos, space_pos - start_pos));
        start_pos = space_pos + 1;
    }
    return result;
}
Time create_time(string time_str){
    Time result;
    result.hours = stoi(time_str.substr(0,2));
    result.minutes = stoi(time_str.substr(2));
    return result;
}
Translator read_translator(string str){
    vector<string> fields = split_by_space(str);
    vector<string> tr_languages;
    Translator new_translator;
    new_translator.name = fields[0];
    new_translator.start_free_time = create_time(fields[1]);
    new_translator.finish_free_time = create_time(fields[2]);
    for (int i = 3; i < fields.size(); i++) {
        tr_languages.push_back(fields[i]);
    }
    new_translator.languages = tr_languages;
    return new_translator;
}
vector<Translator> read_translator_info(string filename){
    vector<Translator> translator;
    ifstream input_txt(filename);

    int number_of_translators;
    string line;
    cin >> number_of_translators;
    for (int i = 0; i < number_of_translators; i++){
        getline(input_txt, line);
        translator.push_back(read_translator(line));
    }

    input_txt.close();
    return translator;
}
Event read_event(string str){
    vector<string> fields = split_by_space(str);
    vector<string> event_languages;
    Event new_event;
    new_event.event_name = fields[0];
    new_event.start_event_time = create_time(fields[1]);
    new_event.finish_event_time = create_time(fields[2]);
    for (int i = 3; i < fields.size(); i++) {
        event_languages.push_back(fields[i]);
    }
    new_event.languages_needed = event_languages;
    return new_event;
}
vector<Event> read_event_info(string filename){
    vector<Event> event;
    ifstream input_txt(filename);

    int number_of_event;
    string line;
    cin >> number_of_event;
    for (int i = 0; i < number_of_event; i++){
        getline(input_txt, line);
        event.push_back(read_event(line));
    }

    input_txt.close();
    return event;
}
bool is_free_at(Translator trn , Event eve){
    return not_before(Event.start_event_time , trn.start_free_time) && not_after(Event.finish_event_time,
                                                                                 trn.finish_free_time);
}
vector<Translator> find_free_translators(vector<Translator> translator_info,vector<Event> event_info){
    vector<Translator> free_translator;
    Event eve;
    for (Translator trn : translator_info){
        if (is_free_at(translator_info , eve))
            free_translator.push_back(trn);
        return free_translator;
    }
}
vector<Conference> plan_conference(vector<Translator> translator_info , vector<Event> event_info){
    vector<Conference> conference;
    //while (...) {
    vector<Translator> free_translator = find_free_translators(translator_info,event_info);
    if (free_translator.size() > 0){

    }
    //}
}
int main() {
    vector<Translator> translator_info = read_translator_info("input.txt");
    vector<Event> event_info = read_event_info("input.txt");
    vector<Conference> conference = plan_conference(translator_info , event_info);
    //output the plan
}
