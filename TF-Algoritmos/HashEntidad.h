#pragma once
#ifndef __ENTIDADHASH_HPP__
#define __ENTIDADHASH_HPP__
#include <string>
using std::string;

template <class G>
class HashEntidad {
private:
	string key;
	G value;

public:
	HashEntidad() {}
	HashEntidad(string key, G value) {
		this->key = key;
		this->value = value;
	}
	string getKey() {
		return this->key;
	}
	G getValue() {
		return this->value;
	}
	void setKey(string key) {
		this->key = key;
	}
	void setValue(G value) {
		this->value = value;
	}
};



#endif // !__ENTIDADHASH_HPP__