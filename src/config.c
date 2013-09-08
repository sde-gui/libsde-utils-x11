#include "config.h"

GKeyFile* settings;

void load_config()
{
	settings = g_key_file_new();
	g_key_file_load_from_file (settings, config_file, 0, NULL);
}

GKeyFile* get_settings(void) 
{
	if (!settings)
		load_config();
	return settings;
}

