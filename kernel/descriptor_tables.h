#ifndef KERNEL_GDT_H
#define KERNEL_GDT_H

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry {
   unsigned short limit_low;           // The lower 16 bits of the limit.
   unsigned short base_low;            // The lower 16 bits of the base.
   unsigned char  base_middle;         // The next 8 bits of the base.
   unsigned char  access;              // Access flags, determine what ring this segment can be used in.
   unsigned char  granularity;
   unsigned char  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct gdt_ptr {
   unsigned short limit;               // The upper 16 bits of all selector limits.
   unsigned int base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

void init_descriptor_tables(); 


// A struct describing an interrupt gate.
struct idt_entry
{
   unsigned short base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   unsigned short sel;                 // Kernel segment selector.
   unsigned char  always0;             // This must always be zero.
   unsigned char  flags;               // More flags. See documentation.
   unsigned short base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr
{
   unsigned short limit;
   unsigned int base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10 ();
extern void isr11 ();
extern void isr12 ();
extern void isr13 ();
extern void isr14 ();
extern void isr15 ();
extern void isr16 ();
extern void isr17 ();
extern void isr18 ();
extern void isr19 ();
extern void isr20 ();
extern void isr21 ();
extern void isr22 ();
extern void isr23 ();
extern void isr24 ();
extern void isr25 ();
extern void isr26 ();
extern void isr27 ();
extern void isr28 ();
extern void isr29 ();
extern void isr30 ();
extern void isr31 (); 

#endif