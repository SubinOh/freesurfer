#include "romp_support.h"
#include <omp.h>
#include <malloc.h>

ROMP_level romp_level = ROMP_shown_reproducible;


typedef struct StaticData {
    ROMP_pf_static_struct* next;
    Nanosecs in_pf, in_pflb;
} StaticData;

ROMP_pf_static_struct* known_ROMP_pf;

static StaticData* init(ROMP_pf_static_struct * pf_static)
{
    StaticData* ptr = (StaticData*)pf_static->ptr;
    if (ptr) return ptr;
#pragma omp critical
    {	// Might have been made by another thread
    	ptr = (StaticData*)pf_static->ptr;
    	if (!ptr) {
    	    ptr = (StaticData*)calloc(1, sizeof(StaticData));
    	    pf_static->ptr = ptr;
    	    ptr->next = known_ROMP_pf;
    	    known_ROMP_pf = pf_static;
    	}
    }
    return ptr;
}

void ROMP_pf_begin(
    ROMP_pf_static_struct * pf_static,
    ROMP_pf_stack_struct  * pf_stack) 
{
    pf_stack->staticInfo = pf_static;
    StaticData* staticData = init(pf_static);
    if (!staticData) return;
    TimerStartNanosecs(&pf_stack->beginTime);
    pf_stack->tid = omp_get_thread_num();
}

void ROMP_pf_end(
    ROMP_pf_stack_struct  * pf_stack) 
{
    ROMP_pf_static_struct * pf_static = pf_stack->staticInfo;
    if (!pf_static) return;
    Nanosecs delta = TimerElapsedNanosecs(&pf_stack->beginTime);
    StaticData* staticData = (StaticData*)(pf_static->ptr);
    #pragma omp atomic
    staticData->in_pf.ns += delta.ns;
}

void ROMP_pflb_begin(
    ROMP_pf_stack_struct   * pf_stack,
    ROMP_pflb_stack_struct * pflb_stack)
{
    pflb_stack->pf_stack = pf_stack;
    ROMP_pf_static_struct * pf_static = pf_stack->staticInfo;
    if (!pf_static) { pflb_stack->pf_stack = NULL; return; }
    TimerStartNanosecs(&pflb_stack->beginTime);
    pflb_stack->tid = omp_get_thread_num();
}

void ROMP_pflb_end(
    ROMP_pflb_stack_struct  * pflb_stack)
{
    if (!pflb_stack->pf_stack) return;
    ROMP_pf_stack_struct  * pf_stack = pflb_stack->pf_stack;
    ROMP_pf_static_struct * pf_static = pf_stack->staticInfo;
    Nanosecs delta = TimerElapsedNanosecs(&pf_stack->beginTime);
    StaticData* staticData = (StaticData*)(pf_static->ptr);
    #pragma omp atomic
    staticData->in_pflb.ns += delta.ns;
}

void ROMP_show_stats(FILE* file)
{
    fprintf(file, "ROMP_show_stats\n");
    ROMP_pf_static_struct* pf;
    for (pf = known_ROMP_pf; pf; ) {
    	StaticData* sd = (StaticData*)(pf->ptr);
    	fprintf(file, "%s:%d %ld %ld\n", pf->file, pf->line, sd->in_pf.ns, sd->in_pflb.ns);
    	pf = sd->next;
    }
}
