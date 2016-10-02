#include <httpd.h>
#include <http_config.h>
#include <http_protocol.h>
#include <ap_config.h>
#include <apr_lib.h>
#include <apr_strings.h>
#include <apr_dbd.h>
extern "C"{
#include <mod_dbd.h>
}
#include <string>
#include <sstream>

extern "C" module AP_MODULE_DECLARE_DATA condb_module;

/* The sample content handler */
static int condb_handler(request_rec *r)
{
    if (strcmp(r->handler, "condb")) {
        return DECLINED;
    }
    r->content_type = "text/html";      

    ap_dbd_t *dbd = ap_dbd_acquire(r);
    const char *sql = "SELECT * FROM test;";
    apr_dbd_results_t *res = NULL;
    apr_status_t rv = apr_dbd_select(dbd->driver, r->pool, dbd->handle, &res, sql, 0);
    if (rv) {
        std::stringstream ss;
        ss << rv;
        ap_rputs(ss.str().c_str(), r);
    }

    int ncols = apr_dbd_num_cols(dbd->driver, res);
    apr_dbd_row_t *row = NULL;
    while (!apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
        for (int i = 0; i < ncols; i++) {
            ap_rputs(apr_dbd_get_entry(dbd->driver, row, i), r);
            ap_rputs(",", r);
        }
        ap_rputs("\n", r);
    }

    if (!r->header_only) {
        ap_rputs("The sample page from mod_condb.c\n", r);
    }
    return OK;
}

static void condb_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(condb_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA condb_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                    /* create per-dir    config structures */
    NULL,                    /* merge  per-dir    config structures */
    NULL,                    /* create per-server config structures */
    NULL,                    /* merge  per-server config structures */
    NULL,                    /* table of config file commands       */
    condb_register_hooks  /* register hooks                      */
};

