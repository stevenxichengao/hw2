#include "datastore.h"
#include <vector>
#include <map>

class MyDataStore: public DataStore{
	public:
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		void addToCart(std::string username, Product* p);
		void viewCart(std::string username);
		void buyCart(std::string username);
	private:
		std::vector<Product*> products;
		std::vector<User*> users;
		std::map<User*, std::vector<Product*>> carts;
		std::map<std::string, std::set<Product*>> mapKeywordProduct;
		std::map<std::string, User*> mapUsers;
};