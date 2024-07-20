#include "../includes/libconfpp.h"

ws_config::ws_config(){
	ws_config_table *def = new ws_config_table;
	def->table_name = "default";
	core.push_back(def);
}

ws_config::~ws_config(){
	int i = -1;
	while (++i < (int) this->core.size()){
		if (core[i] != NULL)
			delete core[i];
	}
}

ws_config &ws_config::operator=(ws_config x){
	int i = -1;
	int j = -1;
	ws_config_table *cont;
	ws_config_container *table;

	if (this == &x)
		return (*this);
	while (++i < (int) x.core.size()){
		if (core[i] != NULL){
			cont = new ws_config_table;
			cont->table_name = x.core[i]->table_name;
			j = -1;
			while (++j < (int) x.core[i]->tables.size()){
				table = new ws_config_container;
				table->key = x.core[i]->tables[j]->key;
				table->val = x.core[i]->tables[j]->val;
				cont->tables.push_back(table);
			}
			this->core.push_back(cont);
		}
	}
	return (*this);
}

ws_config::ws_config(ws_config &x){
	int i = -1;
	int j = -1;
	ws_config_table *cont;
	ws_config_container *table;

	while (++i < (int) x.core.size()){
		if (x.core[i] != NULL){
			cont = new ws_config_table;
			cont->table_name = x.core[i]->table_name;
			j = -1;
			while (++j < (int) x.core[i]->tables.size()){
				table = new ws_config_container;
				table->key = x.core[i]->tables[j]->key;
				table->val = x.core[i]->tables[j]->val;
				cont->tables.push_back(table);
			}
			this->core.push_back(cont);
		}
	}
}

void ws_config::push_table_back(ws_config_table *table){
	if (table != NULL){
		core.push_back(table);
	}
}

void ws_config::push_cont_back(ws_config_container *cont, int idx){
	if (cont == NULL)
		return ;
	if (idx < 1 || idx >= (int) this->core.size())
		return ;
	this->core[idx]->tables.push_back(cont);
}

ws_config_table *ws_config::operator[](int index){
	if (index + 1 > (int) core.size() || index < 0){
		return (NULL);
	}
	return core[index];

}

int ws_config::size(){
	return (core.size());
}
