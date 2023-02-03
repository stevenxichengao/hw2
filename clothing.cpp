#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product(category,name,price,qty){
	size_ = size;
	brand_ = brand;
}

std::string Clothing::displayString() const{
	stringstream ss;
	ss<<fixed<<setprecision(2)<<price_;
	string res;
	res+=name_;
	res+="\n";
	res+="Size: ";
	res+=size_;
	res+=" Brand: ";
	res+=brand_;
	res+="\n";
	res+=ss.str();
	res+=" ";
	res+=to_string(qty_);
	res+=" left.";
	return res;
}
std::set<string> Clothing::keywords() const{
	set<string> res;
	set<string> brandSet = parseStringToWords(brand_);
	set<string>::iterator it;
	for(it = brandSet.begin(); it != brandSet.end(); ++it){
		res.insert(convToLower(*it));
	}
	set<string> nameSet = parseStringToWords(name_);
	set<string>::iterator it2;
	for(it2 = nameSet.begin(); it2 != nameSet.end(); ++it2){
		res.insert(convToLower(*it2));
	}
	return res;
}
void Clothing::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}