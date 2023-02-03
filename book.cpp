#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : Product(category, name, price, qty){
	isbn_ = isbn;
	author_ = author;
}
std::string Book::displayString() const{
	stringstream ss;
	ss<<fixed<<setprecision(2)<<price_;
	string res;
	res+=name_;
	res+="\n";
	res+="Author: ";
	res+=author_;
	res+=" ISBN: ";
	res+=isbn_;
	res+="\n";
	res+=ss.str();
	res+=" ";
	res+=to_string(qty_);
	res+=" left.";
	return res;
}
std::set<string> Book::keywords() const{
	std::set<std::string> res;
	res.insert(isbn_);
	std::set<string>::iterator it;
	set<string> authorSet = parseStringToWords(author_);
	for(it = authorSet.begin(); it != authorSet.end(); ++it){
		res.insert(convToLower(*it));
	}
	set<string> nameSet = parseStringToWords(name_);
	std::set<string>::iterator it2;
	for(it2 = nameSet.begin(); it2 != nameSet.end(); ++it2){
		res.insert(convToLower(*it2));
	}
	return res;
}
void Book::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}