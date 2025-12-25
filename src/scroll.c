#include "scroll.h"
#include "window.h"

#define OFFSCREEN 100000

void arrange_scroll(monitor_t *m, desktop_t *d)
{
	if (d->root == NULL) {
		return;
	}

	xcb_rectangle_t r = m->rectangle;

	for (node_t *n = first_extrema(d->root); n != NULL; n = next_leaf(n, d->root)) {
		if (n->client == NULL) {
			continue;
		}

		if (n == d->focus) {
			apply_rectangle(n, r);
		} else {
			apply_rectangle(n, (xcb_rectangle_t){
				r.x + OFFSCREEN,
				r.y,
				r.width,
				r.height
			});
		}
	}
}
