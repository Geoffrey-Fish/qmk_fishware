// File: arasaka_display.c
#include "quantum.h"

// State variables for animation
static uint16_t arasaka_timer = 0;
static bool show_text = true;
static bool glitch = false;
static bool dirty = false;
static uint8_t frame_count = 0;

// Function prototypes
void arasaka_text_clean(void);
void arasaka_text_glitch_dirty(void);
void arasaka_text_glitch(bool can_be_dirty);
void arasaka_logo_clean(void);
void arasaka_logo_glitch_dirty(void);
void arasaka_logo_glitch(bool can_be_dirty);
void arasaka_draw(void);

/**
 * Display the clean version of the text.
 */
void arasaka_text_clean(void) {
    oled_write_raw_P(text_clean, frame_size);
}

/**
 * Display a dirty glitch version of the text.
 */
void arasaka_text_glitch_dirty(void) {
    oled_write_raw_P(text_glitch_dirty[rand() % text_glitch_dirty_count], frame_size);
}

/**
 * Display a glitching version of the text.
 * @param can_be_dirty If true, allows dirty glitches; otherwise, only clean glitches.
 */
void arasaka_text_glitch(bool can_be_dirty) {
    uint8_t frame = rand() % (can_be_dirty ? (text_glitch_count + text_glitch_dirty_count) : text_glitch_count);

    if (frame < text_glitch_count) {
        oled_write_raw_P(text_glitch[frame], frame_size);
    } else {
        arasaka_text_glitch_dirty();
    }
}

/**
 * Display the clean version of the logo.
 */
void arasaka_logo_clean(void) {
    oled_write_raw_P(logo_clean, frame_size);
}

/**
 * Display a dirty glitch version of the logo.
 */
void arasaka_logo_glitch_dirty(void) {
    oled_write_raw_P(logo_glitch_dirty[rand() % logo_glitch_dirty_count], frame_size);
}

/**
 * Display a glitching version of the logo.
 * @param can_be_dirty If true, allows dirty glitches; otherwise, only clean glitches.
 */
void arasaka_logo_glitch(bool can_be_dirty) {
    uint8_t frame = rand() % (can_be_dirty ? (logo_glitch_count + logo_glitch_dirty_count) : logo_glitch_count);

    if (frame < logo_glitch_count) {
        oled_write_raw_P(logo_glitch[frame], frame_size);
    } else {
        arasaka_logo_glitch_dirty();
    }
}

/**
 * Main function to draw the Arasaka animation on the OLED.
 */
void arasaka_draw(void) {
    uint16_t elapsed_time = timer_elapsed(arasaka_timer);

    // Animation timing logic
    if (elapsed_time < 150) {
        (show_text ? arasaka_text_glitch_dirty : arasaka_logo_glitch_dirty)();
        return;
    }

    if (elapsed_time < 250 || (elapsed_time > 9750 && elapsed_time < 9850)) {
        (show_text ? arasaka_text_glitch : arasaka_logo_glitch)(true);
        return;
    }

    if (elapsed_time > 9850 && elapsed_time < 10000) {
        (show_text ? arasaka_text_glitch_dirty : arasaka_logo_glitch_dirty)();
        return;
    }

    if (elapsed_time > 10000) {
        show_text = !show_text;
        arasaka_timer = timer_read();
    }

    // Glitch effect logic
    if (glitch && frame_count > 0) {
        frame_count--;
        (show_text ? arasaka_text_glitch : arasaka_logo_glitch)(true);
        return;
    }

    // Reset glitch and render clean text/logo
    glitch = false;
    dirty = false;
    (show_text ? arasaka_text_clean : arasaka_logo_clean)();

    // Random chance to trigger glitch effect
    if (rand() % 60 == 0) {
        glitch = true;
        frame_count = 1 + rand() % 4;
        return;
    }

    if (rand() % 60 == 0) {
        glitch = true;
        frame_count = 1 + rand() % 10;
        dirty = frame_count > 5;
    }
}

/**
 * OLED task to handle Arasaka display updates.
 */
void oled_task_user(void) {
    oled_set_brightness(0);
    arasaka_draw();
}
