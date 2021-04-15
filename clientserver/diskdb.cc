#include "diskdb.h"

using std::string;

DiskDatabase::DiskDatabase() : filename("data.txt") {}

DiskDatabase::DiskDatabase(const std::string fn) : filename(fn) {}

std::string DiskDatabase::get_newsgroup(unsigned int ng_id) const {

}

std::string DiskDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {

}

bool DiskDatabase::set_newsgroup(std::string name) {
	
}

bool DiskDatabase::set_article(std::string name, std::string author, std::string title, std::string text) {

}

bool DiskDatabase::remove_newsgroup(unsigned int ng_id) {

}

bool DiskDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {

}