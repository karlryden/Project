#include "diskdb.h"

using std::string;
namespace fs = std::experimental::filesystem;   //vet ej om vi borde köra på fs eller linux funktioner
using std::fstream;

DiskDatabase::DiskDatabase() {
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }
    iter = fs::recursive_directory_iterator("data");
}

std::string DiskDatabase::get_newsgroup(unsigned int ng_id) const {
    if (!fs::exists("data/" + ng_id)) {
        return NULL; // ej säker på om vi ska throwa/returna någon 404
    }
    // öppna filen med filestream, läs första raden för namn och returna med articles?
}

std::string DiskDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {
    fs::directory_entry ng;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path().u8string();
        if (dir.find(ng_id) != string::npos) {
            ng = entry;
            break;
        }
    } if (ng.path().u8string() == "") { // Om ingen ng-mapp hittades?
        return NULL; // ej säker på om vi ska throwa/returna någon 404
    } 
    fs::directory_entry art;
    for (const auto& entry : fs::directory_iterator(ng.path().u8string())) {
        string fn = entry.path().u8string();
        if (fn.find(a_id) != string::npos) {
            art = entry;
            break;
        }
    } if (ng.path().u8string() + '/' == art.path().u8string()) {    // Om ingen article-fil hittades?
        return NULL; // ej säker på om vi ska throwa/returna någon 404
    }
    // öppna filen med filestream, returna innehåll?
}

bool DiskDatabase::set_newsgroup(std::string name) {
    for (auto ng_it = fs::directory_iterator("data"); ng_it != fs::directory_iterator(); ng_it++) {
        // öppna varje newsgroup och kolla efter name?
        // if name == *ng_it.name break
    }
    unsigned int ng_id = ?
    fs::create_directory("data/" + ng_id);
}

bool DiskDatabase::set_article(unsigned int ng_id, std::string author, std::string title, std::string text) {

}

bool DiskDatabase::remove_newsgroup(unsigned int ng_id) {

}

bool DiskDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {

}