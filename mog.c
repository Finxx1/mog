#include <xcb/xcb.h>

int main() {
	int screen_num = 0;
	xcb_connection_t* connection = xcb_connect(NULL, &screen_num);
	
	const xcb_setup_t* setup = xcb_get_setup(connection);
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
	for (int i = 0; i < screen_num; i++)
		xcb_screen_next(&iter);
	
	xcb_screen_t* screen = iter.data;
	
	uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t vals[2] = { screen->white_pixel, XCB_EVENT_MASK_EXPOSURE };
	
	xcb_window_t window = xcb_generate_id(connection);
	xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, 640, 480, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, vals);
	
	mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	vals[0] = screen->black_pixel;
	vals[1] = 0;
	
	xcb_gcontext_t gc = xcb_generate_id(connection);
	xcb_create_gc(connection, gc, window, mask, vals);
	
	xcb_map_window(connection, window);
	xcb_flush(connection);
	
	xcb_generic_event_t* event;
	while ((event = xcb_wait_for_event(connection))) {
		switch (event->response_type & ~0x80) {
			case XCB_EXPOSE: {
				
				xcb_flush(connection);
			} break;
		}
	}
	
	xcb_disconnect(connection);
}
