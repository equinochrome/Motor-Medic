#include "main.h"
#include "liblvgl/lvgl.h"

#include "medic/motor_medic_gui.hpp"
#include "medic/motor_medic.hpp"

#include <vector>
#include <cstdio>

namespace motor_medic_gui {

static std::vector<pros::Motor*> g_motors;

static lv_obj_t* g_screen   = nullptr;
static lv_obj_t* g_title    = nullptr;
static lv_obj_t* g_list     = nullptr;
static lv_obj_t* g_rows[16] = {nullptr};

static pros::Task* g_update_task = nullptr;

static constexpr int MAX_MOTORS = 16;

static const char* status_text(MotorStatus s) {
  switch (s) {
    case MotorStatus::OK:      return "OK";
    case MotorStatus::WARNING: return "WARN";
    case MotorStatus::FAIL:    return "FAIL";
    default:                                return "?";
  }
}

static void build_ui() {
  // Create a new screen and load it
  g_screen = lv_obj_create(nullptr);
  lv_screen_load(g_screen);

  // Title
  g_title = lv_label_create(g_screen);
  lv_label_set_text(g_title, "Motor Medic");
  lv_obj_align(g_title, LV_ALIGN_TOP_MID, 0, 8);

  // Container for rows
  g_list = lv_obj_create(g_screen);
  lv_obj_set_size(g_list, 460, 210);
  lv_obj_align(g_list, LV_ALIGN_TOP_MID, 0, 40);

  // Make it a vertical list
  lv_obj_set_flex_flow(g_list, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(g_list, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

  // Create row labels (one per motor)
  const int n = (int)g_motors.size();
  const int shown = (n > MAX_MOTORS) ? MAX_MOTORS : n;

  for (int i = 0; i < shown; i++) {
    g_rows[i] = lv_label_create(g_list);
    lv_label_set_text(g_rows[i], "...");
  }

  // If fewer motors than MAX, leave the rest null
  for (int i = shown; i < MAX_MOTORS; i++) g_rows[i] = nullptr;
}

void refresh() {
  if (!g_list) return;

  const int n = (int)g_motors.size();
  const int shown = (n > MAX_MOTORS) ? MAX_MOTORS : n;

  for (int i = 0; i < shown; i++) {
    if (!g_rows[i]) continue;

    pros::Motor& m = *g_motors[i];
    auto rep = motor_medic::check(m);

    // LVGL label copies the text internally, so stack buffer is fine
    char line[96];
    std::snprintf(
      line, sizeof(line),
      "P%-2d  %s   T:%4.1fC   I:%4dmA   V:%5.1f",
      rep.port,
      status_text(rep.status),
      rep.temperature,
      rep.current,
      rep.velocity
    );

    lv_label_set_text(g_rows[i], line);
  }
}

static void update_task_fn(void*) {
  while (true) {
    refresh();
    pros::delay(250);
  }
}

void init(const std::vector<pros::Motor*>& motors) {
  g_motors = motors;

  build_ui();
  refresh();

  if (!g_update_task) {
    g_update_task = new pros::Task(update_task_fn, nullptr, "motor_medic_gui");
  }
}

} // namespace motor_medic_gui
