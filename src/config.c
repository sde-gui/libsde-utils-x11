#include "config.h"

#include <sde-utils.h>

static GKeyFile * settings = NULL;

static void load_config()
{
    settings = g_key_file_new();

    const char * agent_id = agent_id = su_path_resolve_agent_id_by_pointer(get_settings, "sde-utils-gtk");
    su_path_register_default_agent_prefix(agent_id, PACKAGE_INSTALLATION_PREFIX);

    gchar * path = su_path_resolve_config(agent_id, SU_PATH_CONFIG_USER, "sde/sde-utils-gtk", NULL, "settings.ini");

    if (path)
    {
        g_key_file_load_from_file (settings, path, 0, NULL);
        g_free(path);
    }
}

GKeyFile* get_settings(void) 
{
    if (!settings)
        load_config();
    return settings;
}

