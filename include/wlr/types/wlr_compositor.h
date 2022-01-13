/*
 * This an unstable interface of wlroots. No guarantees are made regarding the
 * future consistency of this API.
 */
#ifndef WLR_USE_UNSTABLE
#error "Add -DWLR_USE_UNSTABLE to enable unstable wlroots features"
#endif

#ifndef WLR_TYPES_WLR_COMPOSITOR_H
#define WLR_TYPES_WLR_COMPOSITOR_H

#include <wayland-server-core.h>
#include <wlr/render/wlr_renderer.h>

struct wlr_surface;

struct wlr_compositor {
	struct wl_global *global;
	struct wlr_renderer *renderer;

	struct wl_listener display_destroy;

	struct {
		struct wl_signal new_surface;
		struct wl_signal destroy;
	} events;
};

struct wlr_compositor *wlr_compositor_create(struct wl_display *display,
	struct wlr_renderer *renderer);

#endif
