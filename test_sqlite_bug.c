#include <stdio.h>
#include "sqlite3.h"

int main() {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open the database in memory in debug mode
    rc = sqlite3_open(":memory:", &db);
    if(rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // Register the generate_series module if necessary
    sqlite3_exec(db, "CREATE VIRTUAL TABLE x USING generate_series(1, 10, 1);", 0, 0, &errMsg);

    // Execute the test query
    rc = sqlite3_exec(db, "SELECT * FROM generate_series(1, 10, 1) WHERE ROWID = 1;", 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Query execution error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return 0;
}
