#include "matrix.h"
#include "wait.h"

// Suite16mx R84 scan-timing diagnostic.
//
// The slave matrix travels over RJ45 and shares the four row lines with the
// master. R83 proved that a held switch has exactly one row and one column
// endpoint, so the extra same-column presses are likely transient coupling
// while a column is first driven low.
//
// Normal QMK waits only the platform GPIO input delay before sampling. Give
// the selected column and shared row lines 30 us to settle before reading.
void matrix_output_select_delay(void) {
    wait_us(30);
}
