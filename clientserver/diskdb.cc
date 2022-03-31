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
    std::ifstream ifile;
    ifile.open("data/ng_count.txt", fstream::in);
    ifile >> next;
    new_id = next++;
    ifile.close();
    std::ofstream ofile;
    ofile.open("data/ng_count.txt", fstream::out);
    ofile << next;
    ofile.close();

    return new_id;
}


fs::path DiskDatabase::get_newsgroup_path(unsigned int ng_id) const{
    fs::directory_entry ng;
    string::size_type dlim;
    bool ng_found{false};
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.compare("data/ng_count.txt")) {
            dlim = dir.find(delimiter);;
            unsigned int id{static_cast<unsigned int>(std::stoul(dir.substr(dlim+1)))};
            if (id == ng_id) {
                ng = entry;
                ng_found = true;
                break;
            }
        }  
    }
    if (ng_found) {
        return ng.path();
    } else {
        return "";
    }
}
fs::path DiskDatabase::get_article_path(unsigned int ng_id, unsigned int art_id) const{
    fs::path ng_path{get_newsgroup_path(ng_id)};
    if (ng_path == "") { // Om ingen ng-mapp hittades?
        return ng_path; 
    }
    fs::directory_entry art;
    string::size_type a_dlim;
    string::size_type ng_dlim{ng_path.string().find(delimiter)};
    for (const auto& entry : fs::directory_iterator(ng_path)) {
        string fn = entry.path();
        a_dlim = fn.substr(ng_dlim + 1).find(delimiter) + ng_dlim + 1;
        string::size_type ppos = fn.find_last_of(".");
        unsigned int aid{static_cast<unsigned int>(std::stoul(fn.substr(a_dlim+1, ppos-a_dlim - 1)))};
        if (aid == art_id && (fn.find("art_count.txt") == string::npos)) {
            art = entry;
            break;
        }
    }
    cout << art.path().string() << endl;
    return art.path();

}

string DiskDatabase::get_newsgroup(unsigned int ng_id) const {
    
    fs::path ng_path(get_newsgroup_path(ng_id));
    if (ng_path == "") { // Om ingen ng-mapp hittades?
        return ""; 
    }
    string::size_type dlim{ng_path.string().find(delimiter)};
    string name{ng_path.string().substr(5, dlim - 5)};

    return name; 
}

// titel|författare|text 
string DiskDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {
    
    fs::path art_path{get_article_path(ng_id, a_id)};
    if (art_path == "") {    // Om ingen article-fil hittades?
        return ""; 
    }
    // art.path() = datat/ng^0/artikel1^0.txt
    // öppna filen med filestream, returna innehåll?
    std::ifstream file;
    file.open(art_path, fstream::out);
    string title{};
    getline(file, title);
    if (title.back() == '\r'){
        title = title.substr(0, title.length() - 1);
    }
    
    string author{};
    getline(file, author);
    if (author.back() == '\r'){
        author = author.substr(0, title.length() - 1);
    }
    
    string text{};
    while (file.good()){
        string s;
        getline(file, s);
        if (s.back() == '\r'){
            s = s.substr(0, title.length() - 1);
        }
        text +=  s+"\n";
    }
    text = text.substr(0, text.length() - 1);
    file.close();
    string ret{};
    ret += title;
    ret += "|";
    ret += author;
    ret += "|";
    ret += text;
    return ret;
}

bool DiskDatabase::set_newsgroup(string name) {
    fs::directory_entry ng;
    string::size_type ng_dlim;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        ng_dlim = dir.find(delimiter);
        string nname{dir.substr(5, ng_dlim - 5)};
        if (nname == name) {
            return false;
        }
    }
    unsigned int ng_id = getNewId();
    fs::create_directory("data/" + name + delimiter + std::to_string(ng_id));
    fstream file;
    file.open("data/" + name + delimiter + std::to_string(ng_id) + "/art_count.txt", fstream::out);
    file << 0;
    file.close();
    
    return true;
}

unsigned int DiskDatabase::getNewArtId(fs::path ng_path) {
    unsigned int new_id;
    unsigned int next;
    std::ifstream ifile;
    ifile.open(ng_path.string() + "/art_count.txt", fstream::in);
    ifile >> next;
    new_id = next++;
    ifile.close();
    std::ofstream ofile;
    ofile.open(ng_path.string() + "/art_count.txt", fstream::out);
    ofile << next;
    ofile.close();

    return new_id;
}

bool DiskDatabase::set_article(unsigned int ng_id, string title, string author, string text) {

    fs::path ng_path{get_newsgroup_path(ng_id)};
    if (ng_path == "") { // Om ingen ng-mapp hittades?
        return false; 
    }
    fs::directory_entry art;
    string::size_type a_dlim;
    string::size_type ng_dlim{ng_path.string().find(delimiter)};
    for (const auto& entry : fs::directory_iterator(ng_path)) {
        string fn = entry.path();
        a_dlim = fn.substr(ng_dlim + 1).find(delimiter) + ng_dlim + 1;
        string::size_type spos = fn.find_last_of("/");
        string atitle{fn.substr(spos + 1, a_dlim - spos - 1)};
        if (atitle == title) {
            return false;
        }
    }

    fstream file;
    unsigned int a_id = getNewArtId(ng_path);
    file.open(ng_path.string() + "/" + title + delimiter + std::to_string(a_id) + ".txt", fstream::out);
    file << title << "\n" << author << "\n" << text;
    file.close();

    return true;
}

bool DiskDatabase::remove_newsgroup(unsigned int ng_id) {
    fs::directory_entry ng;
    string::size_type ng_dlim;
    for (const auto& entry : fs::directory_iterator("data")) {
        string dir = entry.path();
        if (dir.compare("data/ng_count.txt")) {
            ng_dlim = dir.find(delimiter);
            unsigned int nid{static_cast<unsigned int>(std::stoul(dir.substr(ng_dlim+1)))};
            if (nid == ng_id) {
                ng = entry;
                fs::remove_all(ng.path());

                return true;
            }
        }       
    }
    return false;
}

bool DiskDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {
    fs::path art_path{get_article_path(ng_id, a_id)}; 
    if (art_path == "") { // Om ingen ng-mapp hittades?
        return false; 
    }

    fs::remove(art_path);
    return true;
}

// std::size_t number_of_files_in_directory(std::filesystem::path path)
string DiskDatabase::list_newsgroups() {
    string ret{};
    int nb_ng{-1};
    for(const auto& entry: fs::directory_iterator("data")){
        nb_ng++;
    }
    if(nb_ng == 0){
        return "0";
    }
    ret = std::to_string(nb_ng);
    for (const auto& entry : fs::directory_iterator("data")) {
        string ng_path{entry.path().string()};
        if (ng_path.find("ng_count.txt") == string::npos) {
            string::size_type dlim{ng_path.find(delimiter)};
            cout << ng_path.substr(dlim + 1) << endl;
            unsigned int ng_id{static_cast<unsigned int>(std::stoul(ng_path.substr(dlim + 1)))};
            string name{ng_path.substr(5, dlim - 5)};
            ret += " " + std::to_string(ng_id) + " " + std::to_string(name.length()) + " " + name;
        }
    }
    return ret;
}

string DiskDatabase::list_articles(unsigned int ng_id) {
    string ret{};
    string::size_type ng_dlim;
    std::vector<std::pair<int, string>> output;
    int nbr_art{-1};
    
    fs::path ng_path{get_newsgroup_path(ng_id)};
    ng_dlim  = {ng_path.string().find(delimiter)};
    if (ng_path == "") { // Om ingen ng-mapp hittades?
        return ""; 
    }
    for (const auto& entry:  fs::directory_iterator(ng_path)){
        nbr_art++;
    }
    if (nbr_art == 0){
        return "0";
    }
    ret += std::to_string(nbr_art);
    for (const auto& entry : fs::directory_iterator(ng_path)) {
        string art_path{entry.path().string()};

        string::size_type a_dlim = art_path.substr(ng_dlim + 1).find(delimiter) + ng_dlim + 1;
        unsigned int aid{static_cast<unsigned int>(std::stoul(art_path.substr(a_dlim+1)))};
        string::size_type spos = art_path.find_last_of("/");
        if (art_path.find("art_count.txt") == string::npos) {
            string atitle{art_path.substr(spos + 1, a_dlim - spos - 1)};
            std::pair<int, string> ap{aid,  " " + std::to_string(aid) + " " + std::to_string(atitle.length()) + " " + atitle};
            output.push_back(ap);
        }
    }
    std::sort(output.begin(), output.end(), [](const std::pair<int, string>& p1, const std::pair<int, string>& p2){return (p1.first < p2.first);});
    std::for_each(output.begin(), output.end(), [&ret](const std::pair<int, string>& p){ret += p.second;});
    cout << ret << endl;
    return ret;
}


