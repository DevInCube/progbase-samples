#include <stdlib.h>
#include <syslog.h>

// read from syslog:
// 		tail -n 10 /var/log/syslog

void process(){

    syslog(LOG_NOTICE, "Writing to my Syslog");
}     

int main (int argc, char *argv[]) {

    setlogmask (LOG_UPTO (LOG_NOTICE));
    openlog ("testd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    process();

    closelog();
    return(EXIT_SUCCESS);
}
