#define config_file "/usr/share/sde-config/sde-utils-gtk/settings.ini"

#include <gtk/gtk.h>


extern GKeyFile* settings;

extern void load_config(void);
extern void save_config(void);
extern void free_config(void);

