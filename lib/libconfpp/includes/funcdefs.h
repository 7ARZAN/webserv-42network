#ifndef FUNCDEFS_H
#define FUNCDEFS_H

int	strschr(std::string s, int c);
ws_config parse_string(std::string conf);
ws_config_container *search_container(int table_index, std::string cont_name ,ws_config *conf);
ws_config_container *search_container(std::string table_name, std::string cont_name ,ws_config *conf);
ws_config_table *search_table(std::string table_name, ws_config *conf);

#endif
