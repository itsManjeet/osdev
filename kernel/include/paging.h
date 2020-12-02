#pragma once
#include "kernel/kernel.h"

typedef struct page_s
{
    u32 present     : 1;
    u32 rw          : 1;
    u32 user        : 1;
    u32 accessed    : 1;
    u32 dirty       : 1;
    u32 unused      : 7;
    u32 frame       : 20;
} page_t;

typedef struct page_table_s
{
    page_t pages[1024];
} page_table_t;

typedef struct page_dir_s
{
    page_table_t *tables[1024];
    u32 table_phy[1024];
    u32 phy_addr;
} page_dir_t;

void initialise_paging();

void switch_page_directory(page_dir_t *);

page_t* get_page(u32 addr, int make, page_dir_t* dir);

void page_fault(registers_t regs);