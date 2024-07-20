#ifndef ws_config_H
#define ws_config_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/socket.h>

typedef struct ws_config_container{
	std::string	key;
	std::string	val;
} ws_config_container;

typedef struct ws_config_table{
	std::string	table_name;
	std::vector<ws_config_container *> tables;
} ws_config_table;

// main ws_config class
class ws_config {
	private : 
		std::vector<ws_config_table *> core;	// a vector that holds all the ws_config_tables
		ws_config_table *parse_table(std::string conf, int *idx);
	public :
		// canonical form
		ws_config();
		ws_config &operator=(ws_config x);
		ws_config_table *operator[](int index);
		ws_config (ws_config &x);
		~ws_config();

		// members
		void push_table_back(ws_config_table *table);
		void push_cont_back(ws_config_container *cont, int idx);
		int size();

		// seaching
		// search for a container using a table_name and a container_name
		std::string search_val(std::string table_name, std::string key);

		// search for a table by name
		ws_config_table *search_table(std::string table_name);
		ws_config_table *search_table_port(int port);
		void parse_string(std::string conf);
};


std::string search_val_table(ws_config_table *table, std::string key);

#endif
