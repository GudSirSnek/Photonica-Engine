#include "config.h"
#include "global.h"
#include "util.h"
#include "io.h"
#include "SDL2/SDL.h"


static const char *CONFIG_DEFAULT =
	"[controls]\n"
	"left = A\n"
	"right = D\n"
	"up = W\n"
	"down = S\n"
	"escape = Escape\n"
	"\n";

static char tmp_buffer[20] = {0};

static char *config_get_value(const char *config_buffer, const char *value) {
	char *line = strstr(config_buffer, value);
	if (!line)
		pe_printFatalError("Could not find config value: %s. Try deleting config.ini and restarting.\n", value);

	size_t len = strlen(line);
	char *end = line + len;

	char *curr = line;
	char *tmp_ptr = &tmp_buffer[0];
	// Move pointer to '='.
	while (*curr != '=' && curr != end)
		++curr;
	// Consume '='.
	++curr;
	// Consume any spaces.
	while (*curr == ' ')
		++curr;
	// Get characters until end of line.
	while (*curr != '\n' && *curr != 0 && curr != end)
		*tmp_ptr++ = *curr++;

	*(tmp_ptr+1) = 0;

    return tmp_buffer;

}
	

static void load_controls(const char *config_buffer) {
	config_key_bind(INPUT_KEY_LEFT, config_get_value(config_buffer, "left"));
	config_key_bind(INPUT_KEY_RIGHT, config_get_value(config_buffer, "right"));
	config_key_bind(INPUT_KEY_UP, config_get_value(config_buffer, "up"));
	config_key_bind(INPUT_KEY_SHOOT, config_get_value(config_buffer, "shoot"));
	config_key_bind(INPUT_KEY_ESCAPE, config_get_value(config_buffer, "escape"));
}

static int config_load(void){
    char* file_config = io_read_file("./config.ini");

    if(!file_config){
        pe_printError("Could not read file", NULL);
        return 1;
    }

    load_controls(file_config);
    
    free(file_config);

    return 0;
}

void config_init(void){
    if (config_load() == 0)
        return;
    
    io_write_file((void*)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config-ini");


    if (config_load() == 0)
        pe_printError("Could not create or load config file.\n", NULL);
}

void config_key_bind(Input_Key key, const char *key_name) {
	SDL_Scancode scan_code = SDL_GetScancodeFromName(key_name);
	if (scan_code == SDL_SCANCODE_UNKNOWN)
		pe_printError("Invalid scan code when binding key: %s\n", key_name);

	global.config.keybinds[key] = scan_code;
}