/*
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 * IT WILL BE REPLACED DURING GRADING
 */

#include <stdio.h>

#include "ticker.h"
#include "cli.h"
#include "bitstamp.h"

// Table of predefined watcher types.
WATCHER_TYPE watcher_types[] = {
    [CLI_WATCHER_TYPE]
    {.name = "CLI",
     .argv = NULL,
     .start = cli_watcher_start,
     .stop = cli_watcher_stop,
     .send = cli_watcher_send,
     .recv = cli_watcher_recv,
     .trace = cli_watcher_trace},

    [BITSTAMP_WATCHER_TYPE]
    {.name = "bitstamp.net",
     .argv = (char *[]){"uwsc", "wss://ws.bitstamp.net", NULL},
     .start = bitstamp_watcher_start,
     .stop = bitstamp_watcher_stop,
     .send = bitstamp_watcher_send,
     .recv = bitstamp_watcher_recv,
     .trace = bitstamp_watcher_trace},

     [GRADER_WATCHER_TYPE]
     {.name = "grader.local",
      .argv = (char *[]){"/bin/cse320_server", NULL},
      .start = bitstamp_watcher_start,
      .stop = bitstamp_watcher_stop,
      .send = bitstamp_watcher_send,
      .recv = bitstamp_watcher_recv,
      .trace = bitstamp_watcher_trace},

    // The test watcher entry substitutes a different executable for 'uwsc',
    // but otherwise behaves just like the bitstamp watcher.  If it turns out
    // that too many students have inappropriately hard-coded the name of
    // the executable somewhere besides this table, then we can still make it
    // work by just replacing 'uwsc' by the 'tester' executable.
    // Note that "extra arguments" from the start command do not end up as
    // arguments to the executable, but rather only as arguments to the start
    // function for the particular watcher type.  We might be able to encode
    // additional information in the single channel argument, but this ends up
    // getting sent as JSON to the watcher program and it would have to be
    // decoded there.
    [TEST_WATCHER_TYPE]
    {.name = "tester",
     .argv = (char *[]){"util/tester", "LINK_TO_TEST_DATA", NULL},
     .start = bitstamp_watcher_start,
     .stop = bitstamp_watcher_stop,
     .send = bitstamp_watcher_send,
     .recv = bitstamp_watcher_recv,
     .trace = bitstamp_watcher_trace},

    {0}
};
