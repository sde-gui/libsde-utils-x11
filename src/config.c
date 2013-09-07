#include "config.h"

GKeyFile* settings;

void load_config()
{
	settings = g_key_file_new();
	g_key_file_load_from_file (settings, config_file, 0, NULL);
}

void save_config()
{
	FILE* f = fopen( config_file, "w");
	if (f)
	{
		fprintf(f, "[ColorSample]\n");
		fprintf(f, "SaturationMin=%f\n", g_key_file_get_double(settings, "ColorSample", "SaturationMin", NULL));
		fprintf(f, "SaturationMax=%f\n", g_key_file_get_double(settings, "ColorSample", "SaturationMax", NULL));
		fprintf(f, "ValueMin=%f\n", g_key_file_get_double(settings, "ColorSample", "ValueMin", NULL));
		fprintf(f, "ValueMax=%f\n", g_key_file_get_double(settings, "ColorSample", "ValueMax", NULL));
		fprintf(f, "SaturationDelta=%f\n", g_key_file_get_double(settings, "ColorSample", "SaturationDelta", NULL));
		fprintf(f, "ValueDelta=%f\n", g_key_file_get_double(settings, "ColorSample", "ValueDelta", NULL));
		fprintf(f, "\n[Dim]\n");
		fprintf(f, "AlphaMultiplier=%f\n", g_key_file_get_double(settings, "Dim", "AlphaMultiplier", NULL));
		fprintf(f, "RGBOffset=%f\n", g_key_file_get_double(settings, "Dim", "RGBOffset", NULL));
		fprintf(f, "Desaturation=%f\n", g_key_file_get_double(settings, "Dim", "Desaturation", NULL));
		fclose(f);
	}
}

void free_config()
{
	g_key_file_free(settings);
}


