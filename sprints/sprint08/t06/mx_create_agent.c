#include "create_agent.h"

t_agent *mx_create_agent(char *name, int power, int strength) {
	if (name == NULL || power == NULL || strength == NULL) {
	    return NULL;
	}

	t_agent *agent = malloc(sizeof(struct s_agent));
	(*agent).name = mx_strdup(name);
	(*agent).power = power;
	(*agent).strength = strength;

	return agent;
}

