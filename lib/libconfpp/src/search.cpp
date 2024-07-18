#include "../includes/libconfpp.h"

ws_config_table *ws_config::search_table(std::string table_name){
	size_t i = 0;

	if (core.size() < 1)
		return (NULL);
	while (i < core.size()){
		if (core[i]->table_name == table_name)
			return core[i];
		i++;
	}
	return (NULL);
}

std::string ws_config::search_val(std::string table_name, std::string key){
	ws_config_table *table = search_table(table_name);
	int i = -1;

	if (table == NULL)
		return ("");
	if (table->tables.size() < 1)
		return ("");
	while (++i < (int) table->tables.size()){
		if (key == table->tables[i]->key){
			return (table->tables[i]->val);
		}
	}
	return ("");
}
