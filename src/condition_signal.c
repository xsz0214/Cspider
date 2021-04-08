#include<Cspider.h>
int condition_signal(condition_t* cond)
{
    return pthread_cond_signal(&cond->pcond);
}
