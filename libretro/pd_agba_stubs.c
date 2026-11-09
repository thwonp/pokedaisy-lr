/* The game-code layer, stubbed, for the armGBA build (phase 1). EXPAND (pk_wide), the game's own functions called between
 * frames (pk_call: FLY, PC, REPEL, BIKE, the wild-encounter switch) and the field read are written against mGBA's CPU and
 * renderer structures; armGBA's are its own. Until they are ported (plorpos-oe0.45.2 and .3) every one of them says "not
 * supported", so the companion (party, bag, dex, map, guide, settings, the HUD's readouts) runs and the rest is hidden.
 * GPL-3.0, see ../NOTICE. */
#include "field_items.h"
#include "fly.h"
#include "gb_field.h"
#include "pk_call.h"
#include "pk_wide.h"

#include <stdbool.h>
#include <stdint.h>

/* field_items.c / fly.c's pure helpers (the rest of those files drives the CPU) */
const int repel_kinds[REPEL_KINDS][2] = {{86, 100}, {83, 200}, {84, 250}};
int bag_count(const struct pd_snapshot *snap, int item) { (void)snap; (void)item; return 0; }
int bag_bike(const struct pd_snapshot *snap) { (void)snap; return 0; }
const char *item_reason(enum item_result r) { (void)r; return "Not on this core yet"; }
int fly_flyer(const struct pd_snapshot *snap) { (void)snap; return -1; }
const char *fly_reason(enum fly_result r) { (void)r; return "Not on this core yet"; }

bool field_items_supported(const struct pd_config *cfg, const uint8_t *rom, size_t len) {
  (void)cfg; (void)rom; (void)len;
  return false;
}
bool bike_supported(const struct pd_config *cfg) { (void)cfg; return false; }
bool pc_supported(const struct pd_config *cfg, const uint8_t *rom, size_t len) {
  (void)cfg; (void)rom; (void)len;
  return false;
}
bool fly_supported(const struct pd_config *cfg, const uint8_t *rom, size_t len) {
  (void)cfg; (void)rom; (void)len;
  return false;
}
enum item_result bike_register(struct mCore *core, const struct pd_config *cfg, const uint8_t *rom, size_t len, int item,
                               bool busy, bool battle, uint16_t *old) {
  (void)core; (void)cfg; (void)rom; (void)len; (void)item; (void)busy; (void)battle; (void)old;
  return ITEM_FAILED;
}
void bike_restore(struct mCore *core, const struct pd_config *cfg, int item, uint16_t old) {
  (void)core; (void)cfg; (void)item; (void)old;
}
enum item_result pc_open(struct mCore *core, const struct pd_config *cfg, const uint8_t *rom, size_t len, bool busy,
                         bool battle) {
  (void)core; (void)cfg; (void)rom; (void)len; (void)busy; (void)battle;
  return ITEM_FAILED;
}
int repel_steps(struct mCore *core, const struct pd_config *cfg) { (void)core; (void)cfg; return 0; }
enum item_result repel_use(struct mCore *core, const struct pd_config *cfg, const uint8_t *rom, size_t len, int item,
                           bool busy, bool battle, int *steps) {
  (void)core; (void)cfg; (void)rom; (void)len; (void)item; (void)busy; (void)battle; (void)steps;
  return ITEM_FAILED;
}
void fly_targets(struct mCore *core, const struct pd_config *cfg, const uint8_t *rom, size_t len,
                 const struct pd_snapshot *snap, bool busy, bool battle, struct fly_targets *out) {
  (void)core; (void)cfg; (void)rom; (void)len; (void)snap; (void)busy; (void)battle;
  *out = (struct fly_targets){.result = FLY_FAILED};
}
enum fly_result fly_start(struct mCore *core, const struct pd_config *cfg, const uint8_t *rom, size_t len,
                          const struct pd_snapshot *snap, int mapsec, const struct fly_targets *t, bool busy, bool battle) {
  (void)core; (void)cfg; (void)rom; (void)len; (void)snap; (void)mapsec; (void)t; (void)busy; (void)battle;
  return FLY_FAILED;
}
bool fly_finish(struct mCore *core, const struct pd_config *cfg, const uint8_t *rom, size_t len, int mapsec,
                const struct fly_targets *t, bool leftField) {
  (void)core; (void)cfg; (void)rom; (void)len; (void)mapsec; (void)t; (void)leftField;
  return false;
}
uint32_t fly_main_callback(struct mCore *core, const struct pd_config *cfg) { (void)core; (void)cfg; return 0; }

/* gb_field.c: Game Boy games are not on this core */
enum fly_result gb_field_fly(struct mCore *core, const struct gb_field *f, const uint8_t *rom, size_t len, int mapsec,
                             bool busy) {
  (void)core; (void)f; (void)rom; (void)len; (void)mapsec; (void)busy;
  return FLY_FAILED;
}
void gb_field_fly_targets(struct mCore *core, const struct gb_field *f, const uint8_t *rom, size_t len, bool busy,
                          struct fly_targets *out) {
  (void)core; (void)f; (void)rom; (void)len; (void)busy;
  *out = (struct fly_targets){.result = FLY_FAILED};
}
void gb_field_hold_wild(struct mCore *core, const struct gb_field *f) { (void)core; (void)f; }
enum item_result gb_field_pc(struct mCore *core, const struct gb_field *f, bool busy) {
  (void)core; (void)f; (void)busy;
  return ITEM_FAILED;
}
bool gb_field_release_wild(struct mCore *core, const struct gb_field *f, const uint8_t *rom, size_t len) {
  (void)core; (void)f; (void)rom; (void)len;
  return false;
}
bool gb_field_taken(struct mCore *core, const struct gb_field *f) { (void)core; (void)f; return false; }

/* pk_call.c / pk_wide.c: no calls into the game, no field read, no EXPAND */
int pk_call_safe(struct mCore *core) { (void)core; return 0; }
void pk_rest_note(struct mCore *core) { (void)core; }
void pk_rest_reset(void) {}

/* pk_wide_gb.c, which pk_wide.c hands every call to while a Game Boy game is configured: none are on this core, so
 * pk_wide_gb_knows / _configure say no and the rest are never reached. */
int pk_wide_gb_knows(uint32_t crc) { (void)crc; return 0; }
int pk_wide_gb_configure(uint32_t crc) { (void)crc; return 0; }
void pk_wide_gb_reset(void) {}
int pk_wide_gb_scene(void) { return 0; }
int pk_wide_gb_wants_close(void) { return 0; }
int pk_wide_gb_last_mode(void) { return 0; }
int pk_wide_gb_last_score(void) { return 0; }
int pk_wide_gb_last_torn(void) { return 0; }
int pk_wide_gb_glow(struct mCore *core, const uint32_t *frame, uint32_t *out, struct PkWideView v) {
  (void)core; (void)frame; (void)out; (void)v;
  return 0;
}
int pk_wide_gb_view(struct mCore *core, const uint32_t *frame, uint32_t *out, struct PkWideView v, uint32_t *centre) {
  (void)core; (void)frame; (void)out; (void)v; (void)centre;
  return 0;
}
