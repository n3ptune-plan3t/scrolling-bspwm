#include "scroll.h"
#include "tree.h"
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
node_t *insert_node_scroll(desktop_t *d, node_t *n)
{
if (d == NULL || n == NULL) {
	return NULL;
}

/* first window */
if (d->root == NULL) {
	d->root = n;
	d->focus = n;
	return n;
}

node_t *f = d->focus;

/* no focus: append at end */
if (f == NULL) {
	node_t *last = second_extrema(d->root);
	node_t *p = last->parent;

	node_t *c = make_node(XCB_NONE);
	c->split_type = TYPE_VERTICAL;
	c->first_child = last;
	c->second_child = n;

	last->parent = c;
	n->parent = c;

	if (p != NULL) {
		if (is_first_child(last)) {
			p->first_child = c;
		} else {
			p->second_child = c;
		}
		c->parent = p;
	} else {
		d->root = c;
	}

	return n;
}

/* insert to the right of focus */
node_t *p = f->parent;

node_t *c = make_node(XCB_NONE);
c->split_type = TYPE_VERTICAL;

c->first_child = f;
c->second_child = n;

f->parent = c;
n->parent = c;

if (p != NULL) {
	if (is_first_child(f)) {
		p->first_child = c;
	} else {
		p->second_child = c;
	}
	c->parent = p;
} else {
	d->root = c;
}

return n;
}

int scroll_index(desktop_t *d, node_t *target)
{
    int i = 0;
    for (node_t *n = first_extrema(d->root);
         n != NULL;
         n = next_leaf(n, d->root)) {

        if (n == target) {
            return i;
        }
        i++;
    }
    return -1;
}

