#pragma once

#include "monitor.h"
#include "desktop.h"
#include "tree.h"

void arrange_scroll(monitor_t *m, desktop_t *d);
node_t *insert_node_scroll(desktop_t *d, node_t *n);

