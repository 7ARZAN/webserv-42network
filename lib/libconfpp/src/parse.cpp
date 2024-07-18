#include "../includes/libconfpp.h"
#include <any>

// TODO :
// add quoting support				[done] [needs refactoring]
// escaped chars [\t, \r, \", ...]		[done]
// refactor code 				[done]
// add error handeling				[done]
// add support for replacing			[done]
// add support for namespaces			[done]
// add support for comments
// edit the vector to hold any value

int cline = 1;

char expand_escaped(char escape_seq){
	char escaped[] = {0x8, 0x9, 0xa, 0xc, 0xd, 0x22, 0x5c};
	char symbol[] = {'b', 't', 'n', 'f', 'r', '"', '\\'};
	int i = -1;

	while (++i < 7){
		if (escape_seq == symbol[i])
			return (escaped[i]);
	}
	return (escape_seq);
}

std::string extract_string (std::string base_string, std::string delims, int *start){
	int idx = *start;
	int offset = 0;
	int len = 0;
	char qtype;

	// counting the length of the key 
	while (idx < (int) base_string.length() && strschr(delims, base_string[idx]) == -1){
		if (base_string[idx] == '\\'){
			base_string.erase(idx, 1);
			base_string[idx]  = expand_escaped(base_string[idx]);
			idx++;
			offset++;
		}
		else if (base_string[idx] == '\'' || base_string[idx] == '"'){
			qtype = base_string[idx];
			idx++;
			while (base_string[idx] != qtype && base_string[idx - 1] != '\\'
					&& idx < (int) base_string.length() && base_string[idx] != '\n'){
				idx++;
				offset++;
			}
			if (base_string[idx] == qtype){
				idx++;
				offset++;
			} else
				throw (std::runtime_error("unterminated quote"));
			len  = 1;
		}else {
			offset++;
			idx++;
		}
	}
	*start = idx;
	return (base_string.substr(idx - offset, offset - len));
}

ws_config_container *parse_key_val(std::string conf, int *start){
	ws_config_container	*container = new ws_config_container;
	int			idx = *start;
	bool			eq = false;

	try {
		container->key = extract_string(conf, "= \t\n", &idx);
		if (container->key.size() < 1)
			throw(std::runtime_error("no key is specified"));

		// skipping spaces and eq sign
		while (idx < (int) conf.length() && strschr(" \t=", conf[idx]) != -1){
			if (conf[idx] == '='){
				if (eq == true)
					throw(std::runtime_error("syntax error, multiple '='"
								" between key and value"));
				eq = true;
			}
			idx++;
		}
		if (conf[idx] == '\n' || eq == false){
			if (conf[idx] == '\n')
				throw(std::runtime_error("key without value"));
			throw(std::runtime_error("syntax error, no '=' between key and value"));
		}
		container->val = extract_string(conf, "= \t\n", &idx);
	}catch (std::exception &x){
		*start = idx + 1;
		delete container;
		throw(std::runtime_error(x.what()));
	}
	// skipping until the next line
	while (conf[idx] != '\n' && idx < (int) conf.length())
		idx++;
	if (conf[idx] == '\n')
		idx++;
	*start = idx;
	return container;
}

ws_config_table *ws_config::parse_table(std::string conf, int *idx){
	int i = *idx;
	size_t table_idx = 0;
	std::string table_name;
	ws_config_table *new_table;

	while (conf[i] != '\n' && conf[i] != ']'){
		i++;
	}
	if (conf[i] == '\n')			// no closing bracket?
		throw (std::runtime_error("non closed '[' in table"));
	table_name = conf.substr(*idx, i - *idx);
	i++;
	table_idx = 0;
	while (table_idx < core.size()){
		if ((core)[table_idx]->table_name == table_name){
			return (core[table_idx]);
		}
		table_idx++;
	}
	*idx = i;
	new_table = new ws_config_table;
	new_table->table_name = table_name;
	this->push_table_back(new_table);
	return (new_table);
}

void ws_config::parse_string(std::string conf){
	int			idx = 0;
	int			i;
	int			conflen = conf.length();
	ws_config_container	*conf_container;
	ws_config_table *default_table = core[0];

	while (idx < conflen){
		// skipping spaces at the beginning of the line
		while (idx < conflen && strschr(" \t", conf[idx]) != -1){
			idx++;
		}
		if (conf[idx] != '\n'){
			if (conf[idx] == '#'){
				while (idx < conflen && conf[idx] != '\n'){
					idx++;
				}
				idx++;
			}
			else {
			try {
				if (conf[idx] == '['){
					default_table = parse_table(conf, &(++idx));
				} else {
					i = -1;
					conf_container = parse_key_val(conf, &idx);
					// iterating to replace a value if its already declared
					while (++i < (int) default_table->tables.size()){
						if (default_table->tables[i]->key == conf_container->key){
							default_table->tables[i]->val = conf_container->val;
							break;
						}
					}
					if (i == (int) default_table->tables.size())
						default_table->tables.push_back(conf_container);
					else 
						delete conf_container;
				}
			} catch(std::exception &x) {
				std::cerr << "warning : line [" << cline << "] :" << x.what() << std::endl;
				while (idx < conflen && conf[idx] != '\n')		// the line is ignored
					idx++;
			}
		}
		} else {
			idx++;
		}
		cline++;
	}
}
