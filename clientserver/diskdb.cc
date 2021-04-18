#include "diskdb.h"
#include <algorithm>
#include <cctype>

using std::string;
using std::cout;
using std::endl;
namespace fs = std::experimental::filesystem;   //vet ej om vi borde köra på fs eller linux funktioner
using std::fstream;

/*
Tänker att vi kör att newsgroupmappar heter name+ng_id? Och sen heter articlefiler bara a_id?
*/

DiskDatabase::DiskDatabase() {
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
    iter = fs::recursive_directory_iterator("data");
}

string DiskDatabase::get_newsgroup(unsigned int ng_id) const {
    fs::directory_entry ng;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.find(ng_id) != string::npos) {
            ng = entry;
            break;
        }
    } if (ng.path() == "") { // Om ingen ng-mapp hittades?
        return NULL; // ej säker på om vi ska throwa/returna någon 404
    } 
    return ?? // vad ska vi returna? namn? artiklar?
}

string DiskDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {
    fs::directory_entry ng;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path(); // Kan vara så att det ej går att assigna path till string, isf får vi använda path.string()
        if (dir.find(ng_id) != string::npos) {  // men får inga kompileringsfel för path = string eller path == string
            ng = entry;
            break;
        }
    } if (ng.path() == "") { // Om ingen ng-mapp hittades?
        return NULL; // ej säker på om vi ska throwa/returna någon 404
    } 
    fs::directory_entry art;
    for (const auto& entry : fs::directory_iterator(ng.path())) {
        string fn = entry.path();
        if (fn.find(a_id) != string::npos) { // kan bli problem om ng_id == a_id
            art = entry;
            break;
        }
    } if (ng.path().string() + "/" == art.path()) {    // Om ingen article-fil hittades?
        return NULL; // ej säker på om vi ska throwa/returna någon 404
    }
    // öppna filen med filestream, returna innehåll?
}

bool DiskDatabase::set_newsgroup(string name) {
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.find(name) != string::npos) {
            return false; // finns redan ng med samma namn
        }
    }
    unsigned int ng_id = ?
    fs::create_directory("data/" + name + ng_id);
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
        return NULL;    // ?? 
    }
    string ret{};
    for (const auto& entry : fs::directory_iterator(ng.path())) {
        ret += entry_string(entry) + "\n"; // ??
    }
    return ret;
}

string entry_string(fs::directory_entry entry) {
    string name = entry.path().string();
    string ng_id = entry.path().string();

    name.erase(std::remove_if(std::begin(name), std::end(name), 
                                [](auto c) {return std::isdigit(c);}), name.end()); 

    ng_id.erase(std::remove_if(std::begin(ng_id), std::end(ng_id), 
                                [](auto c) {return !std::isdigit(c);}), ng_id.end());   

    return ng_id + " " + name;
}

int main() {

}