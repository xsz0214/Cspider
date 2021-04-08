#include<Cspider.h>
int condition_lock(condition_t *cond)
{
    return pthread_mutex_lock(&cond->pmutex);
}
