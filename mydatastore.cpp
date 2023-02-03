#include "mydatastore.h"
#include "util.h"
//#include "amazon.cpp"
#include <map>
using namespace std;

void MyDataStore::addProduct(Product* p){
	products.push_back(p);
	set<string>::iterator it;
	set<string> temp = p->keywords();
	//cout << p->keywords().size() << endl;
	for(it = temp.begin(); it != temp.end(); ++it){
		bool existed = false;
		map<string, set<Product*>>::iterator it2;
		for(it2 = mapKeywordProduct.begin(); it2!=mapKeywordProduct.end(); ++it2){
			//cout << *it << endl;
			//cout << it2->first << endl;
			if(it2->first.compare(*it)==0) {
				mapKeywordProduct[convToLower(it2->first)].insert(p);
				existed = true;
			}
		}
		if(!existed){
			//cout << 111111 << endl;
			set<Product*> ps;
			ps.insert(p);
			mapKeywordProduct.insert(make_pair(*it,ps));
		}
	}

}

void MyDataStore::addUser(User* u){
	users.push_back(u);
	mapUsers.insert(make_pair(u->getName(), u));
	carts.insert(make_pair(mapUsers.find(u->getName())->second,NULL));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	set<Product*> res;
	if(terms.size()>0)  res = mapKeywordProduct[convToLower(terms[0])];

	map<string, set<Product*>>::iterator it;
	bool found = false;
	//cout << res.size() << " " << mapKeywordProduct[terms[1]].size();
	if(type==1)
	{
		vector<string>::iterator it;
		for(it = terms.begin(); it!= terms.end(); ++it){
			if(mapKeywordProduct.find(convToLower(*it))!=mapKeywordProduct.end()) res = setUnion(res, mapKeywordProduct[convToLower(*it)]);
		}
	}
	else{
		vector<string>::iterator it;
		for(it = terms.begin(); it!= terms.end(); ++it){
			if(mapKeywordProduct.find(convToLower(*it))!=mapKeywordProduct.end()) {
				res = setIntersection(res, mapKeywordProduct[convToLower(*it)]);
				found = true;
			}
		}		
		if(!found) res.clear();
	}
	vector<Product*> res1(res.begin(), res.end());

	return res1;
}

void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;
	vector<Product*>::iterator it;
	for(it=products.begin(); it != products.end();++it){
		(*it)->dump(ofile);
		delete(*it);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	vector<User*>::iterator it2;
	for(it2= users.begin(); it2 != users.end(); ++it2){
		(*it2)->dump(ofile);
		delete(*it2);
	}
	ofile << "</users>" << endl;
	
}

void MyDataStore::addToCart(string username, Product* p){
	if(mapUsers.find(username)==mapUsers.end()){
		cout << "Invalid Request";
		return;
	}
	carts[mapUsers[username]].push_back(p);
}

void MyDataStore::viewCart(string username){
	if(mapUsers.find(username)==mapUsers.end()) {
		cout << "Invalid username";
		return;
	}
	vector<Product*> theCart = carts.find(mapUsers.find(username)->second)->second;
	for(unsigned int i = 0; i < theCart.size(); i++){
		cout << "Item " << i+1 << endl;
		cout << theCart[i]->displayString() << endl;
	}
}

void MyDataStore::buyCart(string username){
	if(mapUsers.find(username)==mapUsers.end()) {
		cout<<"Invalid username";
		return;
	}
	if(carts.find(mapUsers[username])==carts.end()) return;
	vector<Product*> theCart = carts[mapUsers[username]];
	vector<Product*> temp;
	for(unsigned int i = 0; i < theCart.size(); i++){
		if(theCart[i]->getQty() > 0 && mapUsers[username]->getBalance()>=theCart[i]->getPrice()){
			theCart[i]->subtractQty(1);
			mapUsers[username]->deductAmount(theCart[i]->getPrice());
		}
		else temp.push_back(theCart[i]);
	}
	carts[mapUsers[username]] = temp;
	if(temp.size()==0) carts.erase(mapUsers[username]);
}
