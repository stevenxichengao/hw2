#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) : Product(category,name,price,qty){
	genre_ = genre;
	rating_ = rating;
}
std::set<string> Movie::keywords() const{
	set<string> res;
	res.insert(convToLower(genre_));
	set<string> nameSet = parseStringToWords(name_);
	set<string>::iterator it;
	for(it = nameSet.begin(); it != nameSet.end(); ++it){
		res.insert(convToLower(*it));
	}
	return res;
}
std::string Movie::displayString() const{
	stringstream ss;
	ss<<fixed<<setprecision(2)<<price_;
	string res;
	res+=name_;
	res+="\n";
	res+="Genre: ";
	res+=genre_;
	res+=" Rating: ";
	res+=rating_;
	res+="\n";
	res+=ss.str();
	res+=" ";
	res+=to_string(qty_);
	res+=" left.";
	return res;
}
void Movie::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}