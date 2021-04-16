#include "diskdb.h"

using std::string;
namespace fs = std::experimental::filesystem;   //vet ej om vi borde köra på fs eller linux funktioner
using std::fstream;

/*
Tänker att vi kör att newsgroupmappar heter name+ng_id? Och sen heter articlefiler bara a_id?
Finns en fs::exists funktion som kollar om de finns ett entry i ett dir men kör inte på den för
måste ändå leta upp mappen om den finns sen. 
*/

DiskDatabase::DiskDatabase() {
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
    iter = fs::recursive_directory_iterator("data");
}

std::string DiskDatabase::get_newsgroup(unsigned int ng_id) const {
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

std::string DiskDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {
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

bool DiskDatabase::set_newsgroup(std::string name) {
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

bool DiskDatabase::set_article(unsigned int ng_id, std::string author, std::string title, std::string text) {
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

}

bool DiskDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {

}