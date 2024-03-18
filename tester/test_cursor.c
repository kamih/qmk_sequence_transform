#include "st_defaults.h"
#include "qmk_wrapper.h"
#include "sequence_transform.h"
#include "tester.h"

//////////////////////////////////////////////////////////////////////
void test_cursor(const st_test_rule_t *rule, st_test_result_t *res)
{
    sim_st_perform(rule->seq_keycodes);
    st_cursor_t *cursor = st_get_cursor();
    st_cursor_init(cursor, 0, false);
    for (int i = 0; i < 200; ++i) {
        st_cursor_next(cursor);
    }
    if (cursor->cursor_pos.index != cursor->buffer->size) {
        RES_FAIL("input cursor didn't stop at end: cursor index %d; buffer size: %d",
                 cursor->cursor_pos.index, cursor->buffer->size);
        return;
    }
    if (st_cursor_init(cursor, 0, true)) {
        for (int i = 0; i < 200; ++i) {
            st_cursor_next(cursor);
        }
    }
    if (cursor->cursor_pos.index != cursor->buffer->size) {
        RES_FAIL("output cursor didn't stop at end: cursor index %d; buffer size: %d",
                 cursor->cursor_pos.index, cursor->buffer->size);
    }
}
