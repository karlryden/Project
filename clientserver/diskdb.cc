#include "diskdb.h"
#include <algorithm>
// #include <cctype>

using std::string;
using std::cout;
using std::endl;
namespace fs = std::experimental::filesystem;
using std::fstream;

char delimiter{'^'};

/*
Tänker att vi kör att newsgroupmappar heter name+ng_id? Och sen heter articlefiler bara a_id?
*/


unsigned int ng_hash(string name) {
    return 1;
}

unsigned int art_hash(string title, string author) {
    return 1;
}

string ng_string(fs::directory_entry entry) {
    string name = entry.path().string();
    string ng_id = entry.path().string();

    name.erase(std::remove_if(std::begin(name), std::end(name), 
                                [](char c) {return std::isdigit(c);}), name.end()); 

    ng_id.erase(std::remove_if(std::begin(ng_id), std::end(ng_id), 
                                [](char c) {return !std::isdigit(c);}), ng_id.end());   

    return ng_id + " " + name;
}

string art_string(fs::directory_entry entry) {
    string a_id = entry.path().string();
    a_id.erase(std::remove_if(std::begin(a_id), std::end(a_id), 
                                [](char c) {return !std::isdigit(c);}), a_id.end());   

    return a_id;
}

DiskDatabase::DiskDatabase() {
    if (!fs::exists("data")) {
        cout << "creating data" << endl;
        fs::create_directory("data");
    }
    fstream file;
    int id{0};
    if (!fs::exists("data/ng_count.txt")) {
        cout << "creating count" << endl;
        file.open("data/ng_count.txt", fstream::out);
        file << 0;
        file.close();
    }
     
}

unsigned int DiskDatabase::getNewId(){
    unsigned int new_id;
    unsigned int next;
    fstream file;
    file.open("data/ng_count.txt", fstream::out);
    file >> next;
    new_id = next++;
    file << next;
    file.close();
    return new_id;
}


string DiskDatabase::get_newsgroup(unsigned int ng_id) const {
    fs::directory_entry ng;
    string::size_type dlim;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        dlim = dir.find(delimiter);
        unsigned int id{std::stoul(dir.substr(dlim+1))};
        if (id == ng_id) {
            ng = entry;
            break;
        }
    } if (ng.path() == "") { // Om ingen ng-mapp hittades?
        return ""; 
    }
    string name{ng.path().string().substr(5, dlim - 5)};

    return name; 
}

// titel|författare|text 
string DiskDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {
    fs::directory_entry ng;
    string::size_type ng_dlim;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        ng_dlim = dir.find(delimiter);
        unsigned int nid{std::stoul(dir.substr(ng_dlim+1))};
        if (nid == ng_id) {
            ng = entry;
            break;
        }
    } if (ng.path() == "") { // Om ingen ng-mapp hittades?
        return ""; 
    }
    fs::directory_entry art;
    string::size_type a_dlim;
    for (const auto& entry : fs::directory_iterator(ng.path())) {
        string fn = entry.path();
        a_dlim = fn.substr(ng_dlim + 1).find(delimiter) + ng_dlim + 1;
        string::size_type ppos = fn.find_last_of(".");
        unsigned int aid{std::stoul(fn.substr(a_dlim+1, ppos-a_dlim - 1))};
        if (aid == a_id) {
            art = entry;
            break;
        }
    } if (art.path() == "") {    // Om ingen article-fil hittades?
        return ""; 
    }
    // art.path() = datat/ng^0/artikel1^0.txt
    // öppna filen med filestream, returna innehåll?
    std::ifstream file;
    file.open(art.path(), fstream::out);
    string title{};
    getline(file, title);
    string author{};
    getline(file, author);
    string text{};
    while (file.good()){
        string s;
        getline(file, s);
        text +=  s+"\n";
    }
    file.close();
    string ret{};
    ret += title;
    ret += "DELIM";
    ret += author;
    ret += "DELIM";
    ret += text;
    return title + "DELIM" + author;
}

bool DiskDatabase::set_newsgroup(string name) {
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.find(name) != string::npos) {
            return false; // finns redan ng med samma namn
        }
    }
    unsigned int ng_id = 1;
    fs::create_directory("data/" + name);
    return true;
}

bool DiskDatabase::set_article(unsigned int ng_id, string author, string title, string text) {
    fs::directory_entry ng;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.find(ng_id) != string::npos) {
            ng = entry;
            break;
        }
    } if (ng.path() == "") { // Om ingen ng-mapp hittades?
        return false; 
    } 
    // jobbigt att kolla om någon artikel har samma author och titel
    // om inte, skapa ny artikel-fil
    return true;
}

bool DiskDatabase::remove_newsgroup(unsigned int ng_id) {
    fs::directory_entry ng("data");
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.find(ng_id) != string::npos) {
            ng = entry;
            break;
        }
    cout << entry.path().string() << endl;
    } if (ng.path().string() == "data") { // Om ingen ng-mapp hittades?
        return false; 
    } 
    fs::remove(ng.path());
    return true;
}

bool DiskDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {
    fs::directory_entry ng;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.find(ng_id) != string::npos) {
            ng = entry;
            break;
        }
    } if (ng.path() == "") { // Om ingen ng-mapp hittades?
        return false; 
    } 
    fs::directory_entry art;
    for (const auto& entry : fs::directory_iterator(ng.path())) {
        string dir = entry.path();
        if (dir.find(a_id) != string::npos) {   // kan bli problem om ng_id == a_id
            art = entry;
            break;
        }
    } if (ng.path().string() + "/" == art.path()) {    // Om ingen article-fil hittades?
        return false;
    }
    fs::remove(art.path());
    return true;
}

string DiskDatabase::list_newsgroups() {
    string ret{};
    for (const auto& entry : fs::directory_iterator("data")) {
        ret += ng_string(entry) + "\n";
    }
    return ret;
}

string DiskDatabase::list_articles(unsigned int ng_id) {
    fs::directory_entry ng;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.find(ng_id) != string::npos) {
            ng = entry;
            break;
        }
    } if (ng.path() == "") { // Om ingen ng-mapp hittades?
        return "";   
    }
    string ret{ng_string(ng) + "\n"};
    for (const auto& entry : fs::directory_iterator(ng.path())) {
        ret += art_string(entry) + "\n"; // ??
    }
    return ret;
}



int main() {
    DiskDatabase ddb{};
    // cout << ddb.getNewId() << endl;
    // cout << ddb.getNewId() << endl;
    // cout << ddb.getNewId() << endl;
    // cout << ddb.getNewId() << endl;
    // string s = ddb.get_newsgroup(0);
    // cout << s << endl;

    string a = ddb.get_article(0, 0);
    cout << a << endl;

    // ddb.set_newsgroup("ng");
    // ddb.remove_newsgroup(1);
}