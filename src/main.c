#include <pebble.h>
#include <time.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer_hour;
static TextLayer *s_time_layer_colon;
static TextLayer *s_time_layer_min;
static TextLayer *s_time_layer_month;
static TextLayer *s_time_layer_date;
static TextLayer *s_time_layer_weekday;

static GFont s_time_font;
static GFont s_time_font_m;
static GFont s_time_font_s;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static void swich_color() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
}


static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer_hour[] = "00";
  static char buffer_min[] = "00";
  static char buffer_month[] = "000";
  static char buffer_date[] = "00";
  static char buffer_weekday[] = "000";

  //Use 2h hour format
  strftime(buffer_hour, sizeof("00"), "%H", tick_time);
  strftime(buffer_min, sizeof("00"), "%M", tick_time);
  strftime(buffer_month, sizeof("000"), "%b", tick_time);
  strftime(buffer_date, sizeof("00"), "%d", tick_time);
  strftime(buffer_weekday, sizeof("000"), "%a", tick_time);
  
  if(tick_time->tm_hour < 12)
  {
    bitmap_layer_set_compositing_mode(s_background_layer, GCompOpAssignInverted );  
    text_layer_set_text_color(s_time_layer_hour, GColorWhite);
    text_layer_set_text_color(s_time_layer_colon, GColorBlack);  
    text_layer_set_text_color(s_time_layer_min, GColorWhite);
    text_layer_set_text_color(s_time_layer_month, GColorBlack);
    text_layer_set_text_color(s_time_layer_date, GColorBlack);
    text_layer_set_text_color(s_time_layer_weekday, GColorWhite);
  }
  else
  {
    bitmap_layer_set_compositing_mode(s_background_layer, GCompOpAssign );
    text_layer_set_text_color(s_time_layer_hour, GColorBlack);
    text_layer_set_text_color(s_time_layer_colon, GColorWhite);  
    text_layer_set_text_color(s_time_layer_min, GColorBlack);
    text_layer_set_text_color(s_time_layer_month, GColorWhite);
    text_layer_set_text_color(s_time_layer_date, GColorWhite);
    text_layer_set_text_color(s_time_layer_weekday, GColorBlack);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer_hour, buffer_hour);
  text_layer_set_text(s_time_layer_min, buffer_min);
  text_layer_set_text(s_time_layer_month, buffer_month);
  text_layer_set_text(s_time_layer_date, buffer_date);
  text_layer_set_text(s_time_layer_weekday, buffer_weekday);
}

static void main_window_load(Window *window) {
  //Create GBitmap, then set to created BitmapLayer
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CAT);
  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
  
  // Create time TextLayer
  s_time_layer_hour = text_layer_create(GRect(0, 27, 51, 60));
  text_layer_set_background_color(s_time_layer_hour, GColorClear);
  text_layer_set_text(s_time_layer_hour, "00");
  
  s_time_layer_colon = text_layer_create(GRect(58, 27, 30, 60));
  text_layer_set_background_color(s_time_layer_colon, GColorClear);
  text_layer_set_text(s_time_layer_colon, ":");
  
  s_time_layer_min = text_layer_create(GRect(94, 27, 51, 60));
  text_layer_set_background_color(s_time_layer_min, GColorClear);
  text_layer_set_text(s_time_layer_min, "");
  
  s_time_layer_month = text_layer_create(GRect(50, 90, 50, 42));
  text_layer_set_background_color(s_time_layer_month, GColorClear);
  text_layer_set_text(s_time_layer_month, "");
  
  s_time_layer_date = text_layer_create(GRect(55, 113, 50, 42));
  text_layer_set_background_color(s_time_layer_date, GColorClear);
  text_layer_set_text(s_time_layer_date, "");
  
  s_time_layer_weekday = text_layer_create(GRect(90, 125, 60, 42));
  text_layer_set_background_color(s_time_layer_weekday, GColorClear);
  text_layer_set_text(s_time_layer_weekday, "00");
  
  //Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_38));
  s_time_font_m = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_26));
  s_time_font_s = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_22));

  //Apply to TextLayer
  text_layer_set_font(s_time_layer_hour, s_time_font);
  text_layer_set_text_alignment(s_time_layer_hour, GTextAlignmentRight);
  text_layer_set_font(s_time_layer_colon, s_time_font);
  text_layer_set_text_alignment(s_time_layer_colon, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer_min, s_time_font);
  text_layer_set_text_alignment(s_time_layer_min, GTextAlignmentLeft);
  text_layer_set_font(s_time_layer_month, s_time_font_s);
  text_layer_set_text_alignment(s_time_layer_month, GTextAlignmentLeft);
  text_layer_set_font(s_time_layer_date, s_time_font_s);
  text_layer_set_text_alignment(s_time_layer_date, GTextAlignmentLeft);
  text_layer_set_font(s_time_layer_weekday, s_time_font_m);
  text_layer_set_text_alignment(s_time_layer_weekday, GTextAlignmentLeft);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_hour));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_colon));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_min));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_month));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_date));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer_weekday));
  
  // Make sure the time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  //Unload GFont
  fonts_unload_custom_font(s_time_font);
  
  //Destroy GBitmap
  gbitmap_destroy(s_background_bitmap);

  //Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);
  
  // Destroy TextLayer
  text_layer_destroy(s_time_layer_hour);
  text_layer_destroy(s_time_layer_colon);
  text_layer_destroy(s_time_layer_min);
  text_layer_destroy(s_time_layer_month);
  text_layer_destroy(s_time_layer_date);
  text_layer_destroy(s_time_layer_weekday);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
