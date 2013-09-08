#include "config.h"

#define config_file "/usr/share/sde-config/sde-utils-gtk/settings.ini"

static GKeyFile * settings = NULL;

static void load_config()
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

