#include <pthread.h>
#include <fstream>

void* func(void* _);
void printAttributes(pthread_attr_t* attributes);

int main()
{
    pthread_t thread;

    pthread_create(&thread, NULL, func, NULL);
    pthread_join(thread, NULL);

    return 0;
}


void* func(void* _)
{
    pthread_attr_t attrs;
    
    pthread_getattr_np(pthread_self(), &attrs);
    
    void* addr_of_stack = nullptr;
    size_t size_of_stack = 0;
    if (!pthread_attr_getstack(&attrs, &addr_of_stack, &size_of_stack))
        printf("Address of the stack = %p, size of the stack = %p\n", addr_of_stack, size_of_stack);
    
    int scope = 0;
    if (!pthread_attr_getscope(&attrs, &scope))
        printf("Scope = %s\n", (scope == PTHREAD_SCOPE_SYSTEM) ? "PTHREAD_SCOPE_SYSTEM" : (scope == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" : "unknown");
    
    int detach_state = 0;
    if (!pthread_attr_getdetachstate(&attrs, &detach_state))
        printf("Detach state = %s\n", (detach_state == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" : (detach_state == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" : "unknown");
    
    size_t size_of_guard = 0;
    if (!pthread_attr_getguardsize(&attrs, &size_of_guard))
        printf("Size of the guard = %p\n", size_of_guard);
    
    int inherit_scheduler = 0;
    if (!pthread_attr_getinheritsched(&attrs, &inherit_scheduler))
        printf("Inherit scheduler = %s\n", (inherit_scheduler == PTHREAD_INHERIT_SCHED) ? "PTHREAD_INHERIT_SCHED" : (inherit_scheduler == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" : "unknown");
    
    int schedul_policy = 0;
    if (!pthread_attr_getschedpolicy(&attrs, &schedul_policy))
        printf("Scheduling policy = %s\n", (schedul_policy == SCHED_OTHER) ? "SCHED_OTHER" : (schedul_policy == SCHED_FIFO) ? "SCHED_FIFO" : (schedul_policy == SCHED_RR) ? "SCHED_RR" : "unknown");
    
    return nullptr;
}
